#ifndef SMV_LIB_H
#define SMV_LIB_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/syscall.h>
#include <string.h>
#include <pthread.h>
#include "mdom.h"
#include "kernel_api.h"

#define LOGGING 0
#define __SOURCEFILE__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)
#define rlog(format, ...) { \
    if( LOGGING ) { \
        fprintf(stdout, "[tpt] " format, ##__VA_ARGS__); \
        fflush(NULL);   \
    }\
}


// can allocate specific tpt for privae stack
//#define THREAD_PRIVATE_STACK
#define NEW_SMV -1

// Note: DONT intercept pthread for Firefox
//#define INTERCEPT_PTHREAD_CREATE
//#ifdef INTERCEPT_PTHREAD_CREATE
//#define pthread_create(tid, attr, fn, args) sthread_create(NEW_SMV, tid, fn, args)
//#endif

extern int ALLOW_GLOBAL; // 1: all threads can access global memdom, 0 otherwise

#ifdef __cplusplus
extern "C" {
#endif

// Telling the kernel that this process will be using thread pagetables 
int tpt_init(int);

// create a new tpt and return its id
int tpt_create(void);

//cleanup a tpt and all its mdoms
int tpt_remove(int tpt_id);

// Check whether a tpt exists
int tpt_exists(int tpt_id);

// attacj a tpt to a memory domain 
int attach_tpt_to_mdom(int mdom_id, int tpt_id);

// detach a tpt from memory domain 
int detach_tpt_from_mdom(int mdom_id, int tpt_id);

// Check if tpt is attached toa mdom
int is_tpt_attached(int mdom_id, int tpt_id);

// Create an sthread with dedicated tpt 
//int sthread_create(int tpt_id, pthread_t *tid, void *(fn)(void*), void *args);



#ifdef __cplusplus
}
#endif

#endif
