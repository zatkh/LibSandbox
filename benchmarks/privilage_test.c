#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <tpt.h>
#include <mdom.h>
#include <pthread.h>
#define NUM_THREADS 10
#define PER_THREAD_TPTS 10
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

int main()
{
    int tpt_id[PER_THREAD_TPTS];
    pthread_t tid[NUM_THREADS];
    int mdom_id;
    int privs = 0;
    int i = 0;
    int *mdom_alloc[1024];

    tpt_init(1);

    tpt_id[0] = tpt_create();
    tpt_id[1] = tpt_create();
    mdom_id=memdom_create();
    printf("tpt created: %d, tpt created: %d, mdom_id: %d\n",tpt_id[0],tpt_id[1],mdom_id);


    attach_tpt_to_mdom(mdom_id, 0);
    memdom_priv_add(mdom_id, 0, MEMDOM_READ | MEMDOM_WRITE);



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


    detach_tpt_from_mdom(mdom_id, 0);
    memdom_kill(mdom_id);

    tpt_remove(tpt_id[0]);
    tpt_remove(tpt_id[1]);

    printf("test\n");

    return 0;
}
