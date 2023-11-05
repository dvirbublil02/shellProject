#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#define s_size 30  //using define string size that we can modify it always as we want

//in this method we writing a new line into the file 
//getting handle to the file and flag to show if its succsess or not(-1 fail)
int SpaceOnFile(int f_to,int w_bytes){
		if((w_bytes=write(f_to,"\n",1))== -1){
				printf("write error");
					return -1;
					}
	}
//in this method we writing a string into the file 
//getting handle to the file and flag to show if its succsess or no(-1 fail), and also the strring
int WriteStringOnFile(int f_to,int w_bytes,char* str){
if(w_bytes=write(f_to,str,strlen(str))== -1){
				printf("write error");
					return -1;
					}
	}


int main(int argc,char *argv[]){
//initalize and declaring our variables
char ResturentName[s_size],CustomerName[s_size],str[s_size],buffer[s_size],Total[s_size],tempBuffer[s_size],c;
char dishName[s_size],buffer2[s_size],dishNameFinal[s_size]=" ",priceAtString[s_size],amountAtString[s_size],s[11];
char Path[100]="/home/braude/";
int price,index=0,j=0,i=0,x=0,dishAmount=0;
int f_to,f_toNew,amount=0,w_bytes,flag=1,r_bytes=1,f_from,k=0,found=0,z=0,dishAmount2=0;
DIR *dir;
time_t t = time(NULL); //this 2 declartion for print the date on the end of the file by using the s string we declear above
    		struct tm *tm = localtime(&t);
		//we checking if we got thr right number of paramters
		if(argc!=3){
		perror("Not right number of arguments");
		exit(1);
		}
		//we copping the resturant name and the coustomer name 
	strcpy(ResturentName,argv[1]);
	strcpy(CustomerName,argv[2]);
	strcat(Path,ResturentName);
		//opening the resturant menu to get the dish's from it
		if ((f_from = open(Path, O_RDONLY , 0777)) == -1) 
    	    {
				perror("Resturent dosent exist");
				exit(EXIT_FAILURE);
			}
	strcpy(Path,"/home/braude/");
			//open the ResturantName_Order dir to make the order inside this dir.		
		strcpy(str,ResturentName);
		strcat(str,"_Order");
		strcat(Path,str);
		
		 if ((dir = opendir(Path)) == NULL) {
        perror ("Cannot open the dir");
        exit (1);
  			  }
 		//we moving into the dir path.
		if ((chdir(Path)) == -1)
        {
				perror("get into the directory path");
				exit(EXIT_FAILURE);
		}
		strcpy(Path,"/home/braude/");
		strcat(Path,"/");
		strcat(Path,str);
		strcat(Path,"/");
		strcat(Path,CustomerName);
		// create and open new file in the dir with the name of the coustomer
		if ((f_toNew = open(Path, O_WRONLY | O_CREAT, 0777)) == -1) 
        {
				perror("open file error");
				exit(EXIT_FAILURE);
			}
		//we writing into the new file the name of the resturnat and 2 new linesby calling our method
			WriteStringOnFile(f_toNew,w_bytes,ResturentName);
			SpaceOnFile(f_toNew,w_bytes);
			SpaceOnFile(f_toNew,w_bytes);
			//in this loop we running until we didnt get Finish order from the user
			//we getting the order from the terminal then if its not Finish (flag==1) we starting to take care of the order
printf("Insert Your Order:\n");
			while(flag==1){
			
			rewind(stdin);
			scanf(" %[^\n]s",buffer);
			rewind(stdin);
			if(strcmp(buffer,"Finish")==0) flag=0;
			if(flag==1)
				{
					
						//in this loop we getting the amount of this spesifc dish that we got from the user
						//reading only the digits then we copying it into string and finally use atoi to variable dishAmount
						//resetting to make sure that there is no garbage
						memset(dishNameFinal,0,s_size);
						memset(dishName,0,s_size);
						strcpy(dishNameFinal," ");
						for(i=0;i<strlen(buffer);i++){
							if(isdigit(buffer[i]))
							amountAtString[x++]=buffer[i];
						}
							dishAmount=atoi(amountAtString);
							x=0;
						//getting the dishName from the buffer
						for(i=0;i<strlen(buffer);i++){
							if(!isdigit(buffer[i])) dishName[i]=buffer[i];
							
						}
							
							dishName[i-2]='\0'; //avoiding the empty spaces on the end of the string
							
							strcat(dishNameFinal,dishName);
							
						//getting to the head of the file before we reading from it on a loop 
							if(lseek(f_from,0,SEEK_SET)<0)
							{
							printf("Error iseek");
							return 1;
							}
						found=0; //will indicate if we found the dish on the file
						//reading the file line by line and searcing for the dish
						while(r_bytes>0 && found==0){
						//we reading char by char until \n  (we want read line by line then check if we found the dish or not
						if ((r_bytes = read(f_from,&c,1)) == -1)
     					 {
						perror("read   error");
							exit(EXIT_FAILURE);
							}
							if(c!='\n') tempBuffer[k++]=c;
							else { //if we finish read a line we want to copy the line and serch for the dish on this line
									tempBuffer[k]='\0';
									j=0;
									i=0;
									k=0;
										//here we coppying the words from the line that we read and its will be the dish 										name to compare with  (buffer2 will contain the name of the dish that read from the file)
									while(tempBuffer[j]!= '.' &&tempBuffer[j]!='\0')
									{
										if(tempBuffer[j] == ' ' && tempBuffer[j+1] != ' ') buffer2[i++]=' ';
										if(isalpha(tempBuffer[j])) buffer2[i++]=tempBuffer[j];
										j++;
									}
										j=0;
										if(dishAmount<10) //we setting the end of the string according the number of digits
										buffer2[i-1]='\0';
										else
										buffer2[i]='\0';
										//here we checking if the dish from the user are equal to dish on the resturent then we want to get the price .
										if(strcmp(buffer2,dishNameFinal)==0) { 
												memset(amountAtString,0,s_size);//resseting the string to make sure there is no garbege
											//writing to the file the order dish with amount
												WriteStringOnFile(f_toNew,w_bytes,buffer);
												SpaceOnFile(f_toNew,w_bytes);
											//in this loop we getting the price after the loop we convert it into int and adding it to the bill
											for(j=0;j<strlen(tempBuffer);j++){
												if(isdigit(tempBuffer[j]))
											amountAtString[index++]=tempBuffer[j];
											}
											price+=atoi(amountAtString)*dishAmount;
										//resseting the varabiles and strings before another loop, we set found=1 because we found the dish in the file and we dont want to read the rast of the file
											found=1;
											index=0;
											memset(amountAtString,0,s_size);
											memset(dishNameFinal,0,s_size);
														memset(dishName,0,s_size);
										}
										
											//ressting for next input from the file
										memset(buffer2,0,s_size);
										memset(tempBuffer,0,s_size);
						
							}				//here we handling with the situatuin that we read the whole file and didnt found the dish, we setting the pointer to the beggineng of the file , intialize the varabiles and strigs for the next dish and break the loop.
													if(r_bytes<=0){
												printf("Dish not Found! Enter a new one\n");
												if(lseek(f_from,0,SEEK_SET)<0)
															{
													printf("Error iseek");
													return 1;
													}
														memset(buffer2,0,s_size);
														memset(tempBuffer,0,s_size);
														memset(amountAtString,0,s_size);
														memset(dishNameFinal,0,s_size);
														memset(dishName,0,s_size);
														found=0;
														r_bytes=1;
														break;
								}
						}
						
				}
			}
			//here we reading from the user if he confirm or not 
			printf("Total Price is %d NIS (Confirm to approve/else cancle)\n",price);
			rewind(stdin);
			scanf(" %[^\n]s",buffer);
				//if yes we wrting the bill into the file and wrting spaces , date to the file
			if(strcmp(buffer,"Confirm")==0){
			strcpy(Total,"Total Price: ");
			sprintf(amountAtString,"%d",price);
			printf("Order created!\n");
			WriteStringOnFile(f_toNew,w_bytes,Total);
			WriteStringOnFile(f_toNew,w_bytes,amountAtString);
			sprintf(amountAtString,"%s","NIS");
			WriteStringOnFile(f_toNew,w_bytes,amountAtString);
			SpaceOnFile(f_toNew,w_bytes);
			SpaceOnFile(f_toNew,w_bytes);
			rewind(stdin);
			//writing the date into s then  to the file
			assert(strftime(s, sizeof(s), "%d/%m/%Y", tm));
			WriteStringOnFile(f_toNew,w_bytes,s);
			//here we switching the premmision of the file into read only
			execl("/bin/chmod","chmod","-w","-x",Path,NULL);
			}
			else //if not we deleting the file
				{
					close(f_toNew);
					remove(CustomerName);
				}
		
return 0;
}

