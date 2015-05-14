/*=============================================================================
 |    File Name:  csce3613/assign2/assign2.c
 |
 |       Author:  Gage Alvis
 |     Language:  ANSI C (tested using gcc on turing [might list version infor])
 |   To Compile:  gcc -Wall assign2.c
 |
 |        Class:  CSCE3613
 |      Project:  homework assignment 2
 |   Assumption:  1 pipe, 1 redirect
 | Date Created:  2-15-2015
 |     Modified:  2-20-2015
 |
 +-----------------------------------------------------------------------------
 |
 |  Description: A c program implementing basic operation of a linux shell
 |					that handles command line user input and interactive user
 |					input; this program is an extension of assign1; simple 
 |					commands are executed;
 |
 |	  Input:  Command line user input from keyboard at runtime or user input
 |				after prompt
 |
 |	 Output:  Print statements identifying command, result, and execution of command
 |
 |    Algorithm:  Loop through command and dynamically alloc space for each argument
 |
 |  Required Features Not Included:  The program adheres to all
 |		requirements stated in the program assignment, and all
 |		required features are included.
 |
 |   Known Bugs:  With multiple pipes, arguments are continuously added to cmd2;
 |					program does not handle multiple redirects;
 |
 +===========================================================================*/
 #include <stdio.h>
// needed for string library
#include <string.h>
// needed for memory allocation
#include <stdlib.h>
// used for wait, execvp, fork
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
// predefined array, buf sizes
#define CSTRSIZE 100
#define CMDSIZE 30
#define BUFSIZE 1024

/* global vars */
// shell prompt, quit string for strcmp					
const char* PROMPT = "myshell-%";
const char* QUIT = "quit";
// global flags for detecting command complexity
int GLOBAL_PIPE_FLAG;
int GLOBAL_REDR_OUT_FLAG;
int GLOBAL_REDR_OUTAPP_FLAG;
int GLOBAL_REDR_INP_FLAG;

/* function definitions */
int parse_command(char* line,
					char** cmd1,
					char** cmd2,
					char* infile,
					char* outfile);
int isCmd1();
int isCmd2();
int isRedr();
int parseFlagResult();
void resetGlobals();

int main(int argc, char *argv[]){
	// init local vars
	int arg_index;
	int parse_result;
	int pid;
	char infile[CSTRSIZE];
	char outfile[CSTRSIZE];
	char* cmd1[CMDSIZE];
	char* cmd2[CMDSIZE];
	char user_input[BUFSIZE];
	// init globals
	resetGlobals();
	// declare temp values
	parse_result = 9;
	arg_index = 1;
	outfile[0] = 0;
	infile[0] = 0;
	user_input[0] = 0;
	// on 0 user quits
	while(parse_result > 0){
		printf("%s ",PROMPT);
		//check for command-lines
		if (arg_index < argc){
			strcpy(user_input, argv[arg_index]);
			printf("%s\n", user_input);
			arg_index++;
		} else {
			while (fgets(user_input, BUFSIZE, stdin) == NULL)
				printf("%s", PROMPT);
			// fgets adds \n to end of string - replace with NULL
			user_input[strnlen(user_input, BUFSIZE)-1] = '\0';
		}
		//skip if user presses enter or ctrl+d
		if (*user_input != '\0'){
			printf("\tuser command:\t%s\n", user_input);
			parse_result = parse_command(user_input, cmd1, cmd2, infile, outfile);
			printf("\tparse_command:\t%i\n", parse_result);
			//display outfile/infile if possible
			if(strlen(outfile) > 0)
				printf("\toutfile:\t%s\n", outfile);
			if(strlen(infile) > 0)
				printf("\tinfile:\t%s\n", infile);
			// execute simple commands only
			if (parse_result == 1){
				if((pid=fork()) == 0){
					printf("\texecuting simple command...\n");
					execvp(cmd1[0], cmd1);
				}
				else if(pid < 0)
					perror("\nError: could not start process\n");
				else
					wait(NULL);
			}
			//reset values to eval next command
			resetGlobals();
			outfile[0] = 0;
			infile[0] = 0;
		}
	}
	printf("user successfully quits program\n");	
	return 0;
}

int parse_command(char* line, char** cmd1, char** cmd2, char* infile, char* outfile){
	// init counters and temp pointers
	int counter = 0;
	int cmd1_counter = 0;
	int cmd2_counter = 0;
	char* token;
	char* first;
	char* last;
	int index;
	int len = strlen(line);
	if(strcmp(line, QUIT)==0)
		return 0;	
	first = line;
	last = line;
	// iterate over each char
	for(index = 0; index <= len; index++, last++){
		counter++;
		//if currect char is in( |\n<>) assume token is found
		if ((*last==' ')||(*last=='|')||(*last=='\0') || (*last=='<') || (*last=='>')){
			//alloc for token
			token = malloc(sizeof(char*) * (counter+1));
			int i = 0;
			//copy chars into token
			while((first[i] != *last) && (token[i] = first[i]))
				i++;
			token[i+1] = '\0';
			// make sure token is not empty or space
			if (!(*token=='\0' || *token==' ')){
				// check global flags to determine where token goes
				if(isCmd1()){
					//printf("cmd1\tcounter:\t%i\tcmd1_counter:\t%i\n", counter, cmd1_counter);
					// dynamic alloc space for new token
					cmd1[cmd1_counter] = malloc(sizeof(char*) * (counter+1));
					strcpy(cmd1[cmd1_counter], token);
					cmd1_counter++;
				} else if (isCmd2()){
					//printf("cmd2\tcounter:\t%i\tcmd2_counter:\t%i\n", counter, cmd2_counter);
					// dynamic alloc space for new token
					cmd2[cmd2_counter] = malloc(sizeof(char*) * (counter+1));
					strcpy(cmd2[cmd2_counter], token);
					cmd2_counter++;
				} else if (isRedr()){
					//add to outfile or infilfe base on type
					// if multiple redirects occur, outfile/infile is overwritten
					if(GLOBAL_REDR_OUTAPP_FLAG || GLOBAL_REDR_OUT_FLAG){
						strcpy(outfile, token);
					}else {				
						strcpy(infile, token);
					}
				}
			}	
			// free space, reset local vars
			free(token);
			counter = 0;
			first = last+1;	
			// set pipe and redr flags if necessary
			if(*last=='|'){
				GLOBAL_PIPE_FLAG = 1;
			}
			else if(*last=='>'){
				if(*first=='>'){
					GLOBAL_REDR_OUTAPP_FLAG = 1;
					index++;
					last++;
					first++;
				}
				else
					GLOBAL_REDR_OUT_FLAG = 1;
			}
			else if(*last=='<'){
				GLOBAL_REDR_INP_FLAG = 1;
			}
		}
	}
	//end with NULL
	cmd1[cmd1_counter] = '\0';
	cmd2[cmd2_counter] = '\0';
	//separate function to determine command complexity
	return parseFlagResult();
}
// cmd1 until first pipe
int isCmd1(){
	return ( !GLOBAL_PIPE_FLAG && 
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				!GLOBAL_REDR_INP_FLAG);
}
// cmd2 after first pipe and before redirects
int isCmd2(){
	return ( GLOBAL_PIPE_FLAG && 
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				!GLOBAL_REDR_INP_FLAG);
}
// after any redirects
int isRedr(){
	return ( GLOBAL_REDR_OUT_FLAG ||
				GLOBAL_REDR_OUTAPP_FLAG ||
				GLOBAL_REDR_INP_FLAG);
}
// return 9 default
int parseFlagResult(){
	int result = 9;	
	if (isCmd1())
		result = 1;
	else if(!GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				GLOBAL_REDR_INP_FLAG)
		result = 2;
	else if(!GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				GLOBAL_REDR_OUTAPP_FLAG)
		result = 3;
	else if(!GLOBAL_PIPE_FLAG &&				
				GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG)
		result = 4;
	else if(GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				!GLOBAL_REDR_INP_FLAG)
		result = 5;
	else if(GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG &&
				GLOBAL_REDR_INP_FLAG)
		result = 6;
	else if(GLOBAL_PIPE_FLAG &&				
				!GLOBAL_REDR_OUT_FLAG &&
				GLOBAL_REDR_OUTAPP_FLAG)
		result = 7;
	else if(GLOBAL_PIPE_FLAG &&				
				GLOBAL_REDR_OUT_FLAG &&
				!GLOBAL_REDR_OUTAPP_FLAG)
		result = 8;
				
	return result;
}
//reset global flags
void resetGlobals(){
	GLOBAL_PIPE_FLAG = 0;
	GLOBAL_REDR_OUT_FLAG = 0;
	GLOBAL_REDR_OUTAPP_FLAG = 0;
	GLOBAL_REDR_INP_FLAG = 0;
}