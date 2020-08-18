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
  int rv = -1;
  ALLOW_GLOBAL = 0;

  // Set kernel's mm->using_smv to true 
  rv = message_to_kernel("smv,maininit");
  if (rv != 0) {
    fprintf(stderr, "smv_main_init() failed\n");
    return -1;
  }
  rlog("kernel responded %d\n", rv);

  /* Initialize mutex for protecting smv_thread_create */
  pthread_mutex_init(&create_thread_mutex, NULL);


  /* Decide whether we allow all threads to access global memdom */
  ALLOW_GLOBAL = global;

  rlog("tpt_init(%d)\n", ALLOW_GLOBAL);
  return rv;
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
  int rv = 0;
  char buf[100];
  sprintf(buf, "smv,kill,%d", tpt_id);
  rv = message_to_kernel(buf);
  if (rv == -1) {
    fprintf(stderr, "smv_kill(%d) failed\n", tpt_id);
    return -1;
  }
  rlog("killed tpt ID= %d", tpt_id);
  return rv;
}

int tpt_exists(int tpt_id) {
  int rv = 0;
  char buf[50];
  sprintf(buf, "smv,exists,%d", tpt_id);
  rv = message_to_kernel(buf);
  if (rv == -1) {
    fprintf(stderr, "tpt_exists(smv %d) failed\n", tpt_id);
    return -1;
  }
  rlog("tpt ID %d exists? %d", tpt_id, rv);
  return rv;
}

int attach_tpt_to_mdom(int memdom_id, int tpt_id) {
  int rv = 0;
  char buf[50];
  sprintf(buf, "smv,domain,%d,join,%d", tpt_id, memdom_id);
  rv = message_to_kernel(buf);
  if (rv == -1) {
    fprintf(stderr, "smv_join_domain(smv %d, memdom %d) failed\n", tpt_id, memdom_id);
    return -1;
  }
  rlog("tpt ID %d joined memdom ID %d", tpt_id, memdom_id);
  return 0;
}

int detach_tpt_from_mdom(int memdom_id, int tpt_id) {
  int rv = 0;
  char buf[100];
  sprintf(buf, "smv,domain,%d,leave,%d", tpt_id, memdom_id);
  rv = message_to_kernel(buf);
  if (rv == -1) {
    fprintf(stderr, "smv_leave_domain(smv %d, memdom %d) failed\n", tpt_id, memdom_id);
    return -1;
  }
  rlog("smv ID %d left memdom ID %d", tpt_id, memdom_id);
  return rv;
}

int is_tpt_attached(int memdom_id, int tpt_id) {
  int rv = 0;
  char buf[50];
  sprintf(buf, "smv,domain,%d,isin,%d", tpt_id, memdom_id);
  rv = message_to_kernel(buf);
  if (rv == -1) {
    fprintf(stderr, "is_tpt_attached(smv %d, memdom %d) failed\n", tpt_id, memdom_id);
    return -1;
  }
  rlog("tpt ID %d in memdom ID %d?: %d", tpt_id, memdom_id, rv);
  return rv;
}


    