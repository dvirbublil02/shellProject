#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>


#define s_size 30 //we define a size that can be modify on the future
//thi method wrtiting string into file
void WriteStringOnFile(int f_to,int w_bytes,char* str){
if(w_bytes=write(f_to,str,strlen(str))== -1){
				printf("write error");
					return;
					}
}
//this method wrting space into the file
void SpaceOnFile(int f_to,int w_bytes){
		if((w_bytes=write(f_to,"\n",1))== -1){
				printf("write error");
					return;
					}
}

int main(int argc,char *argv[]){
//declartion our varbiels
char ResturentName[s_size],dishName[s_size],buffer2[s_size],tempBuffer[s_size],priceAtString[s_size],finalDish[s_size]=" ";
int r_bytes=1,f_from,i,found=0,price=0,k=0,j=0,index=0,x=0;
char c,Path[100]="/home/braude/";
		if(argc<3){
			printf("Not enofgh paramters!");
			exit(1);
		}
		//getting the restuurant name form the paramters	
		strcpy(ResturentName,argv[1]);
		//in this loop we getting the string from the argument , with space or without we making it 1 string
		for(i=2;i<argc;i++){
			strcpy(tempBuffer,argv[i]);
			while(j<strlen(argv[i])){
			dishName[k++]=tempBuffer[j];
			j++;
			}
			
			dishName[k++]=' ';
			j=0;
			
		}
			
			
			dishName[k]='\0';
			strcat(finalDish,dishName);
		k=0;
		j=0;
		i=0;
	//open the resturant file if he exist by the path /home/braude/RESturant name
	strcpy(Path,ResturentName); 
		if ((f_from = open(Path, O_RDONLY , 0777)) == -1) 
    	    {
				perror("Resturent dosent exist");
				exit(EXIT_FAILURE);
			}
			//in this loop we running on all the file and reading line by line(by 1 char each time until \n)
			//we checking in each line if we found the dish name if yes we getting the price.
			while(r_bytes>0 && found==0){
		if ((r_bytes = read(f_from,&c,1)) == -1)
     	  {
			perror("read   error");
			exit(EXIT_FAILURE);
		}
			if(c!='\n') tempBuffer[k++]=c;  //after reading line we get into the else
				else {
					tempBuffer[k]='\0';
					//in this loop we getting the dish name from the file into the buufer2
					while(tempBuffer[j]!= '.' &&tempBuffer[j]!='\0')
					{
						if(tempBuffer[j] == ' ' && tempBuffer[j+1] != ' ') buffer2[i++]=' ';
						if(isalpha(tempBuffer[j])) buffer2[i++]=tempBuffer[j];
						j++;
					}
					
						buffer2[i]='\0';
						//we checking if the given name is equal to the readed name if yes we will get the price
				if(strcmp(buffer2,finalDish)==0){
							//in this loop we getting the price and afte that we convert it into int , and marking that we found the dish
							for(j=0;j<strlen(tempBuffer);j++){
												if(isdigit(tempBuffer[j]))
													priceAtString[index++]=tempBuffer[j];
												}
										price=atoi(priceAtString);
										found=1;	
						}
				//if not we restarting the whole varbiels and strings to the next iteration
					k=0;
					strcpy(tempBuffer,"");
					strcpy(buffer2,"");	
					j=0;
					i=0;
				}	
		}
		if(!found) printf("We didnt have this dish\n"); //if we didnt found
		if(found) printf("%dNIS\n",price);	
		close(f_from);
return 0;
}

