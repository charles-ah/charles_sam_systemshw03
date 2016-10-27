#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <errno.h>
#include <string.h>

int randomInt()
{
  int fd;
  fd = open("/dev/random",O_RDONLY);
  int rand;
  //printf("%d",fd);
  read(fd,&rand,4);
  //printf("%s\n",rand);
  //printf("%d \n",rand);
  close(fd);
  return rand;  
}

int main()
{
  int randArr[10];
  int i;
  
  printf("original array\n");
  for(i=0;i<10;i++)
    {
      *(randArr+i)=randomInt();
      printf("random %d: %d \n",i,*(randArr+i));
    }
  
  umask(0000);//setting mask
  
  int fd;
  fd=open("results",O_CREAT,0666);
  //checks for error
  if ( fd == -1 ) {
    printf( "error: %d - %s\n", errno, strerror(errno) );
  }
  
  printf("\n \n writing numbers into file\n");
  write(fd,randArr,10*sizeof(int));
  close(fd);
  fd = open("results",O_RDONLY);
  //checks for error
  if ( fd == -1 ) {
    printf( "error: %d - %s\n", errno, strerror(errno) );
  }
  
  printf("\n \n reading numbers from file\n");
  read(fd,randArr,10*sizeof(10));
  printf("\nnew array\n");
  for(i=0;i<10;i++)
    {
      //*(randArr+i)=randomInt();
      printf("random %d: %d \n",i,*(randArr+i));
    }
  close(fd);
  return 0;
}
