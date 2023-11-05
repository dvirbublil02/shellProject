#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <dirent.h>
#define s_size 40

int main(int argc,char *argv[]){

DIR* resturntDir;
struct dirent* dir;
char Path[100]="/home/braude/";
int count=0;
//if we got wrong number of paramters
if(argc !=2){
printf("Not enough Paramters\n");
exit(1);
}
//setting the path to the directory of the resturnt
strcpy(Path,argv[1]);
strcat(Path,"_Order");
//open an exist resutrnt dir if he exist
if((resturntDir=opendir(Path))==NULL)
	{
		printf("Error No such Resturant!");
		return 1;
	}
	//if exist
	if(resturntDir)
		{
				//we running and read each and adding to counter
			while((dir=readdir(resturntDir)) !=NULL)
			{
				count++;
			}
			printf("%d Orders\n",count-2); //prinitng the spesfic number of files in dir without 2 systemfiels
			closedir(resturntDir);
		}
	return 0;
}

