#define SHM_SEED 1001
#define MAX_SHM_SIZE 4096*100+4096
#define SEM_SEED 1000

union semun
{
  int val;
  struct semid_ds *buf;
  unsigned short *array;
};

int set_semvalue(int sem_id, int value);
void del_semvalue(int sem_id);
int semaphore_p(int sem_id);
int semaphore_v(int sem_id);
typedef struct shared_use_st
{
  int end_flag;              //用来标记进程间的内存共享是否结束: 0, 未结束； 1， 结束
  int pos;
  char *shm_sp; //共享内存的空间
}shared_use_st;
