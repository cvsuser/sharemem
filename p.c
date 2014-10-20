#include <string.h>
#include <stdio.h>
#include <stdlib.h>


#include <errno.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include "my_sem.h"

int main(char argc, char* argv[])
{

    int frame_cnt = 0;

    int sem_id; // semaphore id
    int shm_id; // shared-memory id

    void* shared_memory = (void*)0;
    shared_use_st* shared_stuff;

    /* Create and init semaphore */
    sem_id = semget((key_t)SEM_SEED, 1, 0666 | IPC_CREAT);
    if (sem_id == -1)
    {
        fprintf(stderr, "semget failed.\n");
        exit(EXIT_FAILURE);
    }

    /* Init shared-memory */
    shm_id = shmget((key_t)SHM_SEED, getpagesize()*(1 + 200), 0666 | IPC_CREAT);
    if (shm_id == -1)
    {
        fprintf(stderr, "shmget failed.\n");
        exit(EXIT_FAILURE);
    }
    struct shmid_ds shmds;
    int ret = shmctl( shm_id,IPC_STAT,&shmds );
    if( ret == 0 ) {
        printf( "Size of memory segment is %ld\n",shmds.shm_segsz );
        printf( "Numbre of attaches %d\n",( int )shmds.shm_nattch );
    }
    else {
        printf( "shmctl(  ) call failed\n" );
    }
    shared_memory = shmat(shm_id, (void*)0, 0);
    if (shared_memory == (void*)-1)
    {
        fprintf(stderr, "shmat failed.\n");
        exit(EXIT_FAILURE);
    }
    ret = shmctl( shm_id,IPC_STAT,&shmds );
    if( ret == 0 ) {
        printf( "2 Size of memory segment is %ld\n",shmds.shm_segsz );
        printf( "2 Numbre of attaches %d\n",( int )shmds.shm_nattch );
    }
    else {
        printf( "2 shmctl(  ) call failed\n" );
    }

    shared_stuff = (struct shared_use_st*)shared_memory;
    shared_stuff->end_flag = 0;
    shared_stuff->shm_sp = (unsigned char *)shared_memory + 4096;

    printf("Write->shared_memory: %p,shared_stuff:%p,shared_stuff->shm_sp:%p\n", shared_memory,shared_stuff,shared_stuff->shm_sp);
    set_semvalue(sem_id, 1);
    char *tmp[1024] = {0};
    int pos = 0;
    while (pos <= 4096*10)
    {
        semaphore_p(sem_id);

        /* Write it into shared memory */
        memcpy(shared_stuff->shm_sp+pos,tmp,1024);
        //write_frame_into_shm(shared_stuff->shm_sp, &frame);

        pos+=1024;
        shared_stuff->pos = pos;
        semaphore_v(sem_id);
        printf("Write-> pos: %d,%p\n", pos,shared_stuff->shm_sp+pos);
    }
    semaphore_p(sem_id);
    shared_stuff->end_flag = 1;
    semaphore_v(sem_id);

    /* over */
    printf("\nWrite-> Producer over!\n");

    del_semvalue(sem_id);
    if (shmdt(shared_memory) == -1)
    {
        fprintf(stderr, "shmdt failed.\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}
