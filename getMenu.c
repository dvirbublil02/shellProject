#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>


int main(int argc,char * argv[]){
  char ResturantName[100];

char buffer[10];
int f_from,r_bytes;
strcpy(ResturantName,argv[1]);

if(argc!=2){
fprintf(stderr,"we didnt get the right paramters");
exit(1);
}

if ((f_from = open(ResturantName, O_RDONLY)) == -1)
        {
perror("open");
exit(EXIT_FAILURE);
}
//reading to the buff from the old file
    if ((r_bytes = read(f_from, buffer, 10)) == -1)
       {
perror("read");
exit(EXIT_FAILURE);
}
//in this loop we running and coppying all the old file to the new one
    while (r_bytes > 0)
        {
       printf("%s", buffer);

        if ((r_bytes = read(f_from, buffer, 10)) == -1)
            {
perror("read");
exit(EXIT_FAILURE);
}
}
   
    printf("\nfinished printing the menu\n");
    close(f_from);
return 0;
   
}
