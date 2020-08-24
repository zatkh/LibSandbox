#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <tpt.h>
#include <mdom.h>
#include <pthread.h>
#define NUM_THREADS 1
#define PER_THREAD_TPTS 10
#define NUM_MEMDOMS_PER_THREAD 10

pthread_mutex_t mlock;


void *fn(void *args){
    int i = 0;
    int tpt_id[PER_THREAD_TPTS];
    for (i = 0; i < PER_THREAD_TPTS; i++) {
        tpt_id[i] = tpt_create();
    }
    for (i = 0; i < PER_THREAD_TPTS; i++) {
        if (tpt_id[i] != -1) {
            tpt_remove(tpt_id[i]);
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
    int tpt_id[PER_THREAD_TPTS];
    pthread_t tid[NUM_THREADS];
    int mdom_id;
    int privs = 0;
    int i = 0;
    int *mdom_alloc[1024];

//    tpt_init(0);

    mdom_id=memdom_create();

    for (i = 0; i < PER_THREAD_TPTS; i++) {
        tpt_id[i] =tpt_create();
    }


    printf("tpt created: %d, tpt created: %d, mdom_id: %d\n",tpt_id[0],tpt_id[1],mdom_id);

  attach_tpt_to_mdom(mdom_id, tpt_id[0]);
    if (is_tpt_attached(mdom_id, tpt_id[0])) {
        printf("smv %d joined memdom %d\n", tpt_id[0], mdom_id);        
    }

    memdom_priv_add(mdom_id, tpt_id[0], MEMDOM_READ);
    privs = memdom_priv_get(mdom_id, tpt_id[0]);
    printf("smv %d privs %x memdom %d\n", tpt_id[0], privs, mdom_id);

    memdom_priv_add(mdom_id, tpt_id[0], MEMDOM_WRITE);
    privs = memdom_priv_get(mdom_id, tpt_id[0]);
    printf("smv %d privs %x memdom %d\n", tpt_id[0], privs, mdom_id);

    memdom_priv_add(mdom_id, tpt_id[0], MEMDOM_EXECUTE);
    privs = memdom_priv_get(mdom_id, tpt_id[0]);
    printf("smv %d privs %x memdom %d\n", tpt_id[0], privs, mdom_id);

    memdom_priv_add(mdom_id, tpt_id[0], MEMDOM_ALLOCATE);
    privs = memdom_priv_get(mdom_id, tpt_id[0]);
    printf("smv %d privs %x memdom %d\n", tpt_id[0], privs, mdom_id);


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


    detach_tpt_from_mdom(mdom_id, tpt_id[0]);


  for (i = 0; i < PER_THREAD_TPTS; i++) {
        if (tpt_id[i] != -1) {
            tpt_remove(tpt_id[i]);
        }
    }


    printf("test\n");

    return 0;
}


int pthread_test(){
    int i = 0;
    int memdom_id[NUM_MEMDOMS_PER_THREAD];
    pthread_t tid[NUM_THREADS];

    tpt_init(1);

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

int main(){
    int i = 0;
    int memdom_id;
    int tpt_id;
    pthread_t tid;
    int privs;
    int rv=0;
    tpt_init(0);

   // pthread_create(&tid, NULL, fn2, NULL);
    

   memdom_id = memdom_create();

    tpt_id = tpt_create();
    attach_tpt_to_mdom(0, tpt_id);
    memdom_priv_add(0, tpt_id, MEMDOM_READ | MEMDOM_WRITE);


    rv = sthread_create(tpt_id, &tid,fn2, NULL);
    if (rv == -1) {
            printf("sthread_create error\n");
        }

 /* Add privilege and delete them in serve order */
     attach_tpt_to_mdom(memdom_id, tpt_id);

    memdom_priv_add(memdom_id, tpt_id, MEMDOM_READ);
    privs = memdom_priv_get(memdom_id, tpt_id);
    printf("tpt %d privs %x memdom %d\n", tpt_id, privs, memdom_id);


    if (is_tpt_attached(memdom_id, tpt_id)) {
        printf("tpt %d joined memdom %d\n", tpt_id, memdom_id);        
    }


   // pthread_join(tid, NULL);


getchar();
//tpt_remove(tpt_id);

    

    // Try delete a non-existing memdom
    //memdom_kill(12345);
    return 0;
}

