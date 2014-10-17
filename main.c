
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
#include <sys/ipc.h>
#include <sys/shm.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(){
	key_t magicword = ftok("./main.c", 83);
	printf( "page size=%d\n",getpagesize());
	
	int ret = shmget(magicword , getpagesize()*200 , 0666|IPC_CREAT);
	
	
	return printf("ret = %x\n",ret);
}

