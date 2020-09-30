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
        fprintf(stdout, "[mem_view] " format, ##__VA_ARGS__); \
        fflush(NULL);   \
    }\
}


// can allocate specific mem_view for privae stack
//#define THREAD_PRIVATE_STACK


// Note: DONT intercept pthread for Firefox
//#define INTERCEPT_PTHREAD_CREATE
//#ifdef INTERCEPT_PTHREAD_CREATE
//#define pthread_create(tid, attr, fn, args) coproc_create(-1, tid, fn, args)
//#endif

extern int ALLOW_GLOBAL; // 1: all threads can access global memdom, 0 otherwise

#ifdef __cplusplus
extern "C" {
#endif

// Telling the kernel that this process will be using thread pagetables 
int mem_view_init(int);

// create a new mem_view and return its id
int mem_view_create(void);

//cleanup a mem_view and all its mdoms
int mem_view_remove(int mem_view_id);

// Check whether a mem_view exists
int mem_view_exists(int mem_view_id);

// attacj a mem_view to a memory domain 
int attach_mem_view_to_mdom(int mdom_id, int mem_view_id);

// detach a mem_view from memory domain 
int detach_mem_view_from_mdom(int mdom_id, int mem_view_id);

// Check if mem_view is attached toa mdom
int is_mem_view_attached(int mdom_id, int mem_view_id);

// Create an pthread-based coproc with dedicated mem_view 
// or use clone with CLONE_MEM_VIEW flag directly

int coproc_create(int mem_view_id, pthread_t *tid, void *(fn)(void*), void *args);



#ifdef __cplusplus
}
#endif

#endif
