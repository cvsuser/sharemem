
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <errno.h>
#include <unistd.h>

#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
int main(){

    if(argc != 3)
        return 0;

    pid_t pp = fork();
    if(pp == 0){//child
        printf( "start %s \n",argv[1] );
        if(execl(argv[1],(char *)0) < 0){
            perror("execl error!");
        }
    }else{//father
        printf( "start %s \n",argv[2] );
        if(execl(argv[2],(char *)0) < 0){
            perror("execl error!");
        }
    }
    return 0;
}
int maintest(){
    key_t magicword = ftok("./main.c", 83);
    printf( "page size=%d\n",getpagesize());

    int shmid = shmget(magicword , getpagesize()*200 , 0666|IPC_CREAT);

    if( shmid > 0 )
        printf( "Create a shared memory segment %d \n",shmid );

    struct shmid_ds shmds;
    int ret = shmctl( shmid,IPC_STAT,&shmds );
    if( ret == 0 ) {
        printf( "Size of memory segment is %ld\n",shmds.shm_segsz );
        printf( "Numbre of attaches %d\n",( int )shmds.shm_nattch );
    }
    else {
        printf( "shmctl(  ) call failed\n" );
    }

    ret = shmctl( shmid,IPC_RMID,0 );
    if( ret == 0 )
        printf( "Shared memory removed \n" );
    else
        printf( "Shared memory remove failed \n" );
    return 0;

    return printf("ret = %x\n",ret);
}

/*
http://www.cnblogs.com/hicjiajia/archive/2012/05/17/2506638.html
http://www.cnblogs.com/hicjiajia/archive/2012/05/17/2506632.html


http://wenku.baidu.com/link?url=ljZVFpuHnsyL2zBczbAWw02WbRvfKBNGhA64dB8cYAuTiUlRgdDjc8wDlT5ICDTlswfOEGnGhCy7RCvoDiG7uHRM-DVemSBHkKPnnjV_1Fu
http://blog.163.com/qimo601@126/blog/static/15822093201332621139372/
http://blog.csdn.net/charlv/article/details/6639504
http://blog.163.com/xujian900308@126/blog/static/126907615201191394959146/
http://blog.sina.com.cn/s/blog_664c545f0100t2ke.html
http://blog.csdn.net/brucexu1978/article/details/7728717
http://blog.csdn.net/liuhongxiangm/article/details/8308291
http://blog.csdn.net/ljianhui/article/details/10253345
*/

