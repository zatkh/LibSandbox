#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <linux/sched.h>
#include <sys/syscall.h>
#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <limits.h>
#include "tpt.h"

//wrappers around the kernel's abstarction for mdoms and tpts
pthread_mutex_t create_thread_mutex;
int ALLOW_GLOBAL; // 1: all threads can access global memdom, 0 otherwise

//called by main thread to mark the process as tpt-aware
int tpt_init(int global) {
  int ret = -1;
  ALLOW_GLOBAL = 0;

  // Set kernel's mm->using_smv to true 
  ret = message_to_kernel("smv,maininit");
  if (ret != 0) {
    fprintf(stderr, "smv_main_init() failed\n");
    return -1;
  }
  rlog("kernel responded %d\n", ret);

  /* Initialize mutex for protecting smv_thread_create */
  pthread_mutex_init(&create_thread_mutex, NULL);


  /* Decide whether we allow all threads to access global memdom */
  ALLOW_GLOBAL = global;

  rlog("tpt_init(%d)\n", ALLOW_GLOBAL);
  return ret;
}

int tpt_create(void) {
  int tpt_id = -1;
  tpt_id = message_to_kernel("smv,create");
  if (tpt_id < 0) {
    fprintf(stderr, "tpt_create() failed\n");
    return -1;
  }
  rlog("kernel responded smv id %d\n", tpt_id);
  return tpt_id;
}

int tpt_remove(int tpt_id) {
  int ret = 0;
  char buf[100];
  sprintf(buf, "smv,kill,%d", tpt_id);
  ret = message_to_kernel(buf);
  if (ret == -1) {
    fprintf(stderr, "smv_kill(%d) failed\n", tpt_id);
    return -1;
  }
  rlog("killed tpt ID= %d", tpt_id);
  return ret;
}

int tpt_exists(int tpt_id) {
  int ret = 0;
  char buf[50];
  sprintf(buf, "smv,exists,%d", tpt_id);
  ret = message_to_kernel(buf);
  if (ret == -1) {
    fprintf(stderr, "tpt_exists(smv %d) failed\n", tpt_id);
    return -1;
  }
  rlog("tpt ID %d exists? %d", tpt_id, ret);
  return ret;
}

int attach_tpt_to_mdom(int mdom_id, int tpt_id) {
  int ret = 0;
  char buf[50];
  sprintf(buf, "smv,domain,%d,join,%d", tpt_id, mdom_id);
  ret = message_to_kernel(buf);
  if (ret == -1) {
    fprintf(stderr, "smv_join_domain(smv %d, memdom %d) failed\n", tpt_id, mdom_id);
    return -1;
  }
  rlog("tpt ID %d joined memdom ID %d", tpt_id, mdom_id);
  return 0;
}

int detach_tpt_from_mdom(int mdom_id, int tpt_id) {
  int ret = 0;
  char buf[100];
  sprintf(buf, "smv,domain,%d,leave,%d", tpt_id, mdom_id);
  ret = message_to_kernel(buf);
  if (ret == -1) {
    fprintf(stderr, "smv_leave_domain(smv %d, memdom %d) failed\n", tpt_id, mdom_id);
    return -1;
  }
  rlog("smv ID %d left memdom ID %d", tpt_id, mdom_id);
  return ret;
}

int is_tpt_attached(int mdom_id, int tpt_id) {
  int ret = 0;
  char buf[50];
  sprintf(buf, "smv,domain,%d,isin,%d", tpt_id, mdom_id);
  ret = message_to_kernel(buf);
  if (ret == -1) {
    fprintf(stderr, "is_tpt_attached(smv %d, memdom %d) failed\n", tpt_id, mdom_id);
    return -1;
  }
  rlog("tpt ID %d in memdom ID %d?: %d", tpt_id, mdom_id, ret);
  return ret;
}

/* 
 * Create an sthread running in a dedicated tpt.
 * if (tpt_id = -1), sthread_create creates a new tpt 
 * else if (tpt_id != -1) it launch a thread that will have tpt_id view of the memory
 * When no error, return the tpt_id that the new thread is running in. 
 * If we replaces it as pthread_create, return 0.
 */
int sthread_create(int tpt_id, pthread_t* tid, void*(fn)(void*), void* args){
  int ret = 0;
  char buf[100];
  int mdom_id;
  pthread_attr_t attr;
  void* stack_base;
  unsigned long stack_size;

  if(tpt_id == -1){
    tpt_id = tpt_create();
    fprintf(stderr, "creating a new tpt %d for the new thread to run in\n", tpt_id);
  }

  // a thread can only work with valid tpts
  if(!tpt_exists(tpt_id)){
    fprintf(stderr, "thread cannot run in a non-existing tpt %d\n", tpt_id);
    return -1;
  }

// global shared memory (mdom=0) is allowed with all privilages
  if(ALLOW_GLOBAL){
    attach_tpt_to_mdom(0, tpt_id);
    memdom_priv_add(0, tpt_id, MEMDOM_READ | MEMDOM_WRITE | MEMDOM_ALLOCATE | MEMDOM_EXECUTE);
  }

  
  pthread_mutex_lock(& create_thread_mutex);
  pthread_attr_init(& attr);

//thread's stack can also be a thread-local mdom
#ifdef THREAD_PRIVATE_STACK // Use private stack for thread
  
  mdom_id = memdom_create();
  if(mdom_id == -1){
    fprintf(stderr, "failed to create thread local memdom for smv %d\n", tpt_id);
    pthread_mutex_unlock(& create_thread_mutex);
    return -1;
  }
  attach_tpt_to_mdom(mdom_id, tpt_id);
  memdom_priv_add(mdom_id, tpt_id, MEMDOM_READ | MEMDOM_WRITE | MEMDOM_ALLOCATE | MEMDOM_EXECUTE);

// for parent to initalze the stack
  attach_tpt_to_mdom(mdom_id, 0);
  memdom_priv_add(mdom_id, 0, MEMDOM_READ | MEMDOM_WRITE | MEMDOM_ALLOCATE | MEMDOM_EXECUTE);
// setup the stack
  stack_size = PTHREAD_STACK_MIN + 0x8000;
  stack_base = (void*)memdom_mmap(mdom_id, 0, stack_size, PROT_READ | PROT_WRITE,
                                  MAP_PRIVATE | MAP_ANONYMOUS | MAP_MEMDOM, 0, 0);
  if(stack_base == MAP_FAILED){
    perror("mmap for thread stack: ");
    pthread_mutex_unlock(& create_thread_mutex);
    return -1;
  }
  pthread_attr_setstack(& attr, stack_base, stack_size);
  printf("[%s] creating thread with stack base: %p, end: 0x%lx\n", __func__, stack_base, (unsigned long)stack_base + stack_size);

// record the stack info
  memdom[mdom_id]->start = stack_base;
  memdom[mdom_id]->total_size = stack_size;

#endif // THREAD_PRIVATE_STACK

// register the thread as an sthread with its own tpts
  sprintf(buf, "smv,registerthread,%d", tpt_id);
  ret = message_to_kernel(buf);
  if(ret != 0){
        fprintf(stderr, "register_smv_thread for smv %d failed\n", tpt_id);
    pthread_mutex_unlock(& create_thread_mutex);
    return -1;
  }

#ifdef INTERCEPT_PTHREAD_CREATE
#undef pthread_create
#endif

// already registerd it as sthread
  ret = pthread_create(tid, &attr, fn, args);
  if(ret){
    fprintf(stderr, "pthread_create for smv %d failed\n", tpt_id);
    pthread_mutex_unlock(& create_thread_mutex);
    return -1;
  }
  fprintf(stderr, "smv %d is ready to run\n", tpt_id);

#ifdef INTERCEPT_PTHREAD_CREATE
  /* Set return value to 0 to avoid pthread_create error */
  tpt_id = 0;
  /* ReDefine pthread_create to be sthread_create again */
#define pthread_create(tid, attr, fn, args) sthread_create(-1, tid, fn, args)
#endif

#ifdef THREAD_PRIVATE_STACK
// detach the parent from the mdom

  detach_tpt_from_mdom(mdom_id, 0);
#endif
  pthread_mutex_unlock(& create_thread_mutex);
  return tpt_id;
}
    


    