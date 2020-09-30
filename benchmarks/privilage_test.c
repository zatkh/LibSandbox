 #define _GNU_SOURCE             /* See feature_test_macros(7) */
   #include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sched.h>
#include <tpt.h>
#include <mdom.h>
#include <pthread.h>
#include <sys/wait.h>
#include <sys/utsname.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>

#define NUM_THREADS 1
#define PER_THREAD_TPTS 10
#define NUM_MEMDOMS_PER_THREAD 10

//pthread_mutex_t mlock;


void *fn(void *args){
    int i = 0;
    int mem_view_id[PER_THREAD_TPTS];
    for (i = 0; i < PER_THREAD_TPTS; i++) {
        mem_view_id[i] = mem_view_create();
    }
    for (i = 0; i < PER_THREAD_TPTS; i++) {
        if (mem_view_id[i] != -1) {
            mem_view_remove(mem_view_id[i]);
        }
    }
    return NULL;
}

void *fn2(void *args){
    int i = 0;
    int memdom_id[NUM_MEMDOMS_PER_THREAD];
    printf("hey from child\n");
   /* for (i = 0; i < NUM_MEMDOMS_PER_THREAD; i++) {
        memdom_id[i] = memdom_create();
    }
    for (i = 0; i < NUM_MEMDOMS_PER_THREAD; i++) {
        if (memdom_id[i] != -1) {
            memdom_kill(memdom_id[i]);
        }
    }
    */

    return NULL;
}

int priv_test()
{
    int mem_view_id[PER_THREAD_TPTS];
    pthread_t tid[NUM_THREADS];
    int mdom_id;
    int privs = 0;
    int i = 0;
    int *mdom_alloc[1024];

//    mem_view_init(0);

    mdom_id=memdom_create();

    for (i = 0; i < PER_THREAD_TPTS; i++) {
        mem_view_id[i] =mem_view_create();
    }


    printf("tpt created: %d, tpt created: %d, mdom_id: %d\n",mem_view_id[0],mem_view_id[1],mdom_id);

  attach_mem_view_to_mdom(mdom_id, mem_view_id[0]);
    if (is_mem_view_attached(mdom_id, mem_view_id[0])) {
        printf("smv %d joined memdom %d\n", mem_view_id[0], mdom_id);        
    }

    memdom_priv_add(mdom_id, mem_view_id[0], MEMDOM_READ);
    privs = memdom_priv_get(mdom_id, mem_view_id[0]);
    printf("smv %d privs %x memdom %d\n", mem_view_id[0], privs, mdom_id);

    memdom_priv_add(mdom_id, mem_view_id[0], MEMDOM_WRITE);
    privs = memdom_priv_get(mdom_id, mem_view_id[0]);
    printf("smv %d privs %x memdom %d\n", mem_view_id[0], privs, mdom_id);

    memdom_priv_add(mdom_id, mem_view_id[0], MEMDOM_EXECUTE);
    privs = memdom_priv_get(mdom_id, mem_view_id[0]);
    printf("smv %d privs %x memdom %d\n", mem_view_id[0], privs, mdom_id);

    memdom_priv_add(mdom_id, mem_view_id[0], MEMDOM_ALLOCATE);
    privs = memdom_priv_get(mdom_id, mem_view_id[0]);
    printf("smv %d privs %x memdom %d\n", mem_view_id[0], privs, mdom_id);


    mdom_alloc[i] = (int*) memdom_alloc(mdom_id, 0x50);
    *mdom_alloc[i] = i+1;
    printf("mdom_alloc[%d]: %d\n", i, *mdom_alloc[i]);
    memdom_free(mdom_alloc[i]);
    printf("\n");
 
    mdom_alloc[i] = (int*) memdom_alloc(mdom_id, 0x20);
    *mdom_alloc[i] = i+1;
    printf("mdom_alloc[%d]: %d\n", i, *mdom_alloc[i]);
    memdom_free(mdom_alloc[i]);
    printf("\n");
 

    mdom_alloc[i] = (int*) memdom_alloc(mdom_id, 0x50);
    *mdom_alloc[i] = i+1;
    printf("mdom_alloc[%d]: %d\n", i, *mdom_alloc[i]);
    memdom_free(mdom_alloc[i]);
    printf("\n");


    detach_mem_view_from_mdom(mdom_id, mem_view_id[0]);


  for (i = 0; i < PER_THREAD_TPTS; i++) {
        if (mem_view_id[i] != -1) {
            mem_view_remove(mem_view_id[i]);
        }
    }


    printf("test\n");

    return 0;
}


int pthread_test(){
    int i = 0;
    int memdom_id[NUM_MEMDOMS_PER_THREAD];
    pthread_t tid[NUM_THREADS];

    mem_view_init(1);

    for (i = 0; i < NUM_THREADS; i++) {
        pthread_create(&tid[i], NULL, fn2, NULL);
    }

    // main thread create memdoms
    for (i = 0; i < NUM_MEMDOMS_PER_THREAD; i++) {
        memdom_id[i] = memdom_create();
    }
    for (i = 0; i < NUM_MEMDOMS_PER_THREAD; i++) {
        if (memdom_id[i] != -1) {
//          memdom_kill(memdom_id[i]);
        }
    }

    // wait for child threads
    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
    }

    // Try delete a non-existing memdom
    memdom_kill(12345);
    return 0;
}

void *fn3(void *args){
    int i = 0;
    int j[1024];
    for (i = 0; i < 1024; i++) {
        j[i] = i;
        if (i % 1000 == 0) {
            printf("j[%d] = %d\n", i, j[i]);
        }
    }
    return NULL;
}


int __main(){
    int i = 0;
    int memdom_id;
    int mem_view_id;
    pthread_t tid;
    int privs;
    int rv=0;
    mem_view_init(0);

   // pthread_create(&tid, NULL, fn2, NULL);
    

   memdom_id = memdom_create();

    mem_view_id = mem_view_create();
    attach_mem_view_to_mdom(0, mem_view_id);
    memdom_priv_add(0, mem_view_id, MEMDOM_READ | MEMDOM_WRITE);


    rv = coproc_create(mem_view_id, &tid,fn3, NULL);
    if (rv == -1) {
            printf("coproc_create error\n");
        }



     attach_mem_view_to_mdom(memdom_id, mem_view_id);

    memdom_priv_add(memdom_id, mem_view_id, MEMDOM_READ);
    privs = memdom_priv_get(memdom_id, mem_view_id);
    printf("tpt %d privs %x memdom %d\n", mem_view_id, privs, memdom_id);


    if (is_mem_view_attached(memdom_id, mem_view_id)) {
        printf("tpt %d joined memdom %d\n", mem_view_id, memdom_id);        
    }


    pthread_join(tid, NULL);


//mem_view_remove(mem_view_id);

    

    // Try delete a non-existing memdom
    memdom_kill(12345);
    return 0;
}

static int child_func(void* arg) {
  char* buf = (char*)arg;
  printf("Child sees buf = \"%s\"\n", buf);
  strcpy(buf, "hello from child");
  return 0;
}

int main(int argc, char** argv) {
  // Allocate stack for child task.
  const int STACK_SIZE = 65536;
  char* stack = malloc(STACK_SIZE);
  if (!stack) {
    perror("malloc");
    exit(1);
  }

  // When called with the command-line argument "vm", set the CLONE_VM flag on.
  unsigned long flags = 0;
  if (argc > 1 && !strcmp(argv[1], "vm")) {
    flags |= CLONE_VM;
  }

  char buf[100];
  strcpy(buf, "hello from parent");
  if (clone(child_func, stack + STACK_SIZE, flags | SIGCHLD, buf) == -1) {
    perror("clone");
    exit(1);
  }

  int status;
  if (wait(&status) == -1) {
    perror("wait");
    exit(1);
  }

  printf("Child exited with status %d. buf = \"%s\"\n", status, buf);
  return 0;
}

