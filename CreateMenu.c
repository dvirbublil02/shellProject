#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
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
//we checking if we got thr right number of paramters
	if(argc!=3){
		perror("Not right number of paramters!");
		exit(EXIT_FAILURE);
		}
	//initalize and declaring our variables 
	char str[s_size],buffer[s_size],buffer2[s_size], c='a',space[s_size]="   ",BonAp[s_size],dots[s_size];
	char nameOfResturant[s_size],*str2=" Menu",Path[100]="/home/braude/";
	int MenuSize=atoi(argv[2]),w_bytes,f_to,i=0,j=1,flag=1,k=0,index=0;;
	
	//making our Bon appetit msg string
	strcpy(BonAp,"   Bon Appetit");
	//her we building the dir name by using strcpy,and strcat we making the dir name like that :  ResturantName_Order
	strcpy(str,"_Order");
	strcpy(nameOfResturant,argv[1]);
	strcat(nameOfResturant,str);
	
	strcat(Path,nameOfResturant);
		
				//creating the directory with the name that we builded, and checking if its succssed
   
	 if ((mkdir(Path, 0777) == -1))
    {
	  			perror("MakeNewDir");
				exit(EXIT_FAILURE);
    }
	memset(Path,0,100);
	strcpy(Path,"/home/braude/");
	//now we restrating the string and copying again the name of the resturant for opening the ResturnamtName.txt file that will be the menu 
	strcpy(nameOfResturant,"");
  	strcpy(nameOfResturant,argv[1]);
	strcat(Path,nameOfResturant);
	// create and open new file 
	if ((f_to = open(Path, O_WRONLY | O_CREAT, 0777)) == -1) 
        {
				perror("open");
				exit(EXIT_FAILURE);
			}
		//we adding to the name of the resturnat space and the work Menu , than we adding to \n\n (break line) then writing it to the file.txt by calling our method
	strcat(nameOfResturant,str2);
	strcat(nameOfResturant,"\n\n");
	WriteStringOnFile(f_to,w_bytes,nameOfResturant);
	//in this loop we running untill we finihing getting all the dish's from the terminal. in the for loop we only getting the dish type and writing it to the file with the spesific wanted format.
	//then we runing on inside loop for each dish type and getting dish's until we getting STOP from the user. 
	for(i=0;i<MenuSize;i++){
		rewind(stdin);
		printf("Insert Type Dish %c:\n",c);
		scanf(" %[^\n]s",buffer);
		strcat(buffer,"\n");
		//here we adding a. b. c. to the dish type as the request 
			buffer2[0]=c;  
			sprintf(buffer2+1,"%s",". ");
			//writing to the file a. b. c. ... and then the dish type
		WriteStringOnFile(f_to,w_bytes,buffer2);
		WriteStringOnFile(f_to,w_bytes,buffer);
			//in each dish we getting sub-dish's until we getting STOP , and writing it to the file in the spesifc format, our flag will indicate if we got STOP or not
			while(flag==1){
			
			printf("Insert Dish Name %d:\n",j);
			rewind(stdin); //buffer cleaning in each run
			scanf(" %[^\n]s",buffer);
			
			if(strcmp(buffer,"Stop")==0) flag=0;
			if(flag==1)
				{
					//here we building our dish string format to the file , first string with dots then adding NIS .(its -5 beucase we want less dots on the ourput we cant modify it as we want)
					memset(dots,0,s_size);
					strcpy(dots,"");
					memset(dots,'.',s_size-5);
					strcat(dots,"NIS");
					//copy the dish name only not the price to our dots string (our string format)
					for(k=0;k<strlen(buffer);k++)
					{
						if(isdigit(buffer[k])) break;
						dots[k]=buffer[k];
					}
					k--;
					//here we inserting the price of the dish to the end of dots string. (-3 cause of the NIS we put) , k will show the place we stop(digits)
					while(k<strlen(buffer)){
						dots[((strlen(dots)-3)-(strlen(buffer)-k))]=buffer[k++];
					}
				//adding space to the head of our ready string to be like the example that was given to us. then we adding \n to break line and writing it to the file(the spesifc format dish......priceNIS)
				strcat(space,dots);
				strcat(space,"\n");
				WriteStringOnFile(f_to,w_bytes,space);
		
				}//then we getting ready to the next dish , we resting the buffer, and adding to space the same spaces for the next input.
			strcpy(buffer,"");
			strcpy(space,"   ");
				j++; // incresing the dish number
			
	
			}
			SpaceOnFile(f_to,w_bytes); //writing space
			//again getting ready to the next dish type , flag(until STOP), j(dish number),c(the letter that will be before the dish type : a. b. ...),restting the buffer)
			flag=1;
			j=1;
			c++;
			strcpy(buffer,"");//restrting the buffer
	}	
			//after finsihing writing to the file new line and the Bon Apatit msg , and printing to the terminal that the order succsess
		SpaceOnFile(f_to,w_bytes);
		strcat(BonAp,"\0");
		WriteStringOnFile(f_to,w_bytes,BonAp);
	printf("Successfully created\n");
	close(f_to); //closing the file handle

return 0;
}
		
		
		

	
	


