#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>

#define NAMEDPIPE_NAME "Mahrov"
#define BUFSIZE 30

int main(int argc,char ** argv){
    int fd,len;
	char buf[BUFSIZE];
	unlink(NAMEDPIPE_NAME);
	if(mkfifo(NAMEDPIPE_NAME, 0660) == -1 ){
        fprintf(stderr,"Error in creating! \n");
        return 1;
   }
    printf("%s is created\n",NAMEDPIPE_NAME);

	if((fd = open(NAMEDPIPE_NAME, O_RDONLY)) == -1){
        fprintf(stderr,"Error in opening! \n");
        return 1;
   }
    printf("%s is opened\n",NAMEDPIPE_NAME);
    do{
        memset(buf,'\0',BUFSIZE);
        if((len=read(fd,buf,BUFSIZE-1))<=0){
            printf("END!");
            close(fd);
            remove(NAMEDPIPE_NAME);
            return 0;
       }
        printf("Incomming message(%d):%s\n",len,buf);
    } while(1);
}
