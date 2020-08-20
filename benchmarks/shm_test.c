#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <tpt.h>
#include <mdom.h>
#include <pthread.h>
#define NUM_THREADS 5

int glob;
int *dint;

int block_write;
pthread_mutex_t mlock;


void *fn(void *args){
    int *t = (int*)args;
    fprintf(stderr, "tpt %d read glob: %d\n", *t, glob);
    pthread_mutex_lock(&mlock);
    glob++;   
    printf("tpt %d wrote glob: %d\n", *t, glob);

    printf("tpt %d read *dint: %d\n", *t, *dint);
    *dint = glob + 1;   
    printf("tpt %d wrote *dint: %d\n", *t, *dint);
    pthread_mutex_unlock(&mlock);
    return NULL;
}

int main(){
    int i = 0;
    int rv = 0;
    int tpt_id[NUM_THREADS];
    pthread_t tid[NUM_THREADS];
    int *t[NUM_THREADS];
    glob = 0;
    block_write = 3; // don't allow this tpt to write to global

    tpt_init(1);
    
    pthread_mutex_init(&mlock, NULL);

    int mdom_id = memdom_create();
    dint = (int*)malloc(sizeof(int));
    *dint = 123;

    // main thread create smvs
    for (i = 0; i < NUM_THREADS; i++) {
        tpt_id[i] = tpt_create();

        attach_tpt_to_mdom(mdom_id, tpt_id[i]);    
        memdom_priv_add(mdom_id, tpt_id[i], MEMDOM_READ | MEMDOM_WRITE);

    //attach global mdom to all tpts
        attach_tpt_to_mdom(0, tpt_id[i]);
    // Set privileges to global memdom
        if (block_write == i) {        
            memdom_priv_add(0, tpt_id[i], MEMDOM_READ);
        } else{
            memdom_priv_add(0, tpt_id[i], MEMDOM_READ  | MEMDOM_WRITE);
        }
    }

    for (i = 0; i < NUM_THREADS; i++) {
        t[i] = malloc(sizeof(int));
        *t[i] = i;
        rv = sthread_create(tpt_id[i], &tid[i], fn, t[i]);
        if (rv == -1) {
            printf("smvthread_create error\n");
        }
    }


    for (i = 0; i < NUM_THREADS; i++) {
        pthread_join(tid[i], NULL);
        printf("waited thread %d\n", i);
    }


    for (i = 0; i < NUM_THREADS; i++) {
        if (tpt_id[i] != -1) {
            tpt_remove(tpt_id[i]);
        }
    }

    glob++;
    *dint = glob + 1 ;
    printf("Final glob: %d\n", glob);
    printf("Final dint: %d\n", *dint);
    printf("smv 123 exists? %d\n", tpt_exists(123));

   


    return 0;
}
