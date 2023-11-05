#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
//in this method we getting input from the user and retruning it as string
char* getInput(char* command) { 
	int i = 0;
	command[i] = getchar();
	while (command[i] != '\n') {
		i++;
		command[i] = getchar();
	}
	command[i] = '\0';
	return command;
}
//in this method we inserting the paramters and the command into the string array (paramtesrs) and counting the number of paramters
int getTheParamters(char* buff, char** paramters) { 
	int i, j = 0, count = 1, k; //we setting count =1 becuase we adding th file name as a paramter
	char temp[256];
	//in this loop we setting the paramters array to null's
	for (i = 0; i < 5; i++) {
		paramters[i] = NULL;
	}
	//in this loop we counting the number of paramters
	for (i = 0; i < strlen(buff); i++) { 
		if (buff[i] == ' ')
			count++;
	}

	//	in this loop we inserting the commands into the paramters array
		for (i = 0; i < count; i++) { 
		strcpy(temp, ""); // empty string
		k = 0;
			//running untiil next word or end of the command
			while (buff[j] != ' ' && j < strlen(buff)) {
					temp[k++] = buff[j++];
			}
		j++; // adding space 
		temp[k] = '\0'; //closing the command with \n
		paramters[i] = (char*)malloc(k * sizeof(char)); // allocate memory to cells in the array for each paramter, and chekcking if its succsuess
		if (!paramters[i]) {
			printf("Memory allocation was failed\n");
		}
		strcpy(paramters[i], temp);//copping the command
	}
	return count; 
}



void main(int argc, char* argv[]) {
	char command[100], Path[256];
	char binStr[100] = "/bin/", BrudeStr[100]= "/home/braude/", * paramters[5];
	int countParamters, i;
	pid_t pid;

	//infinity loop that finish only with exit command from he user . 
	while (1) {
		printf("AdvShell>");
		// get command from the user by calling our method if its not exit
		strcpy(command, getInput(command)); 
		if (strcmp(command, "exit") == 0) {
			printf("GoodBye...\n");
			return;
		}
		countParamters = getTheParamters(command, paramters); 
		//creating chlidren process to seach for the command and run in on bin or in our directory
		pid = fork();
		if (pid == -1) {
			printf("Fork was failed\n");
			return;
		}else 
			//if its the child process
			if (pid == 0) { 
			//we want to search for the command on the Bin directory if he found he will run it then finish
			strcpy(Path, binStr);
			strcat(Path, paramters[0]);
			execvp(Path, paramters); //send the children to search a method in bin
			//if he found he will not get into this next lines  else yes,
			//we want to search for the command in Our directory if he found he will run it then finish
			strcpy(Path, BrudeStr);
			strcat(Path, paramters[0]);
			execvp(Path, paramters); 
			printf("Not Supported\n"); // if the method doesn't exist
			return;
		}
		else
			wait();
	}
}


