#include <stdio.h> 
#include <fcntl.h> 
#include <stdlib.h> 
#include <unistd.h> 
#define BUF_SIZE 1024  
int main(){ 
	int fd,n;         
	char buf[BUF_SIZE];    
	fd=open("log.txt",O_CREAT|O_RDWR|O_TRUNC, 0666);     
	if(fd<0){                 
		printf("file open error\n");                 
		exit(1);         
	}    
	n=write(1,"msg:",4);      
	n=read(0,buf,BUF_SIZE);         
	n=write(fd,buf,n);         
	if(n<0){                 
		printf("file write error\n");                 
		exit(1);         
	}         
	
	lseek(fd,0,SEEK_SET);          
	n=read(fd,buf,BUF_SIZE);         
	if(n==0){                 
		printf("this file is  empty\n");                 
		exit(1);         
	}         
	n=write(1,"readed:",7); 
	n=write(1,buf,n);         
	if(n<0){                 
		printf("file write error\n");                 
		exit(1);         
	}         
	close(fd);  
}