#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
#include<stdlib.h>
#define FIFO_PATH  "/home/ljaep/studio_base/linux_stu/work/fifo"

int fifo_rtest(){
	int fid = mkfifo(FIFO_PATH ,0644);
	if((fid)==-1 && errno!=EEXIST){
		perror("mkfifo");
		return -1;
	}
	int fd = open(FIFO_PATH,O_RDONLY);
	if(fd==-1){
		perror("open");
		return -1;
	}
	while(1){
		char buff[100] = {0};
		read(fd,buff,sizeof(buff));
		printf("buf:%s\n",buff);
	}

	return 0;

}
int fifo_wtest(char *wm){
	int fid = mkfifo(FIFO_PATH ,0644);
	if((fid)==-1 && errno!=EEXIST){
		perror("mkfifo");
		return -1;
	}
	int fd = open(FIFO_PATH,O_WRONLY);
	if(fd==-1){
		perror("open");
		return -1;
	}
	while(1){

		write(fd,wm,strlen(wm));
		sleep(1);

	}

	return 0;


}
int test_pro(){
	int fid = mkfifo(FIFO_PATH ,0644);
	if((fid)==-1 && errno!=EEXIST){
		perror("mkfifo");
		return -1;
	}
	int pid = fork();
	if(pid ==0){
		int fd = open(FIFO_PATH,O_RDONLY);
		if(fd==-1){
			perror("open");
			return -1;
		}
		while(1){
			char buff[100] = {0};
			read(fd,buff,sizeof(buff));
			printf("buf:%s\n",buff);
		}
	}
	else if(pid > 0){
		int fd = open(FIFO_PATH,O_WRONLY);
		if(fd==-1){
			perror("open");
			return -1;
		}
		while(1){
			char *wm = "sun";
			write(fd,wm,strlen(wm));
			sleep(1);

		}

	}
	else{
		perror("fork");
	}


}
int main(int argc ,char * argv[]){
#if 1
test_pro();
#else
	
	int mode = atoi(argv[1]);
	char * wm = argv[2];
	if(mode==0){

		fifo_rtest();
	}
	else{
		fifo_wtest(wm);
	}

	return 0 ;
#endif
	return 0;
}
