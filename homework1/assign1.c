/*=============================================================================
 |    File Name:  csce3613/homework1/assign1.c
 |
 |       Author:  GAge Alvis
 |     Language:  ANSI C (tested using gcc on turing [might list version infor])
 |   To Compile:  gcc -Wall example.c
 |
 |        Class:  CSCE3613
 |      Project:  homework assignment 1
 |   Assumption:  n/a
 | Date Created:  1-28-2015
 |     Modified:  2-04-2015
 |
 +-----------------------------------------------------------------------------
 |
 |  Description: A c program implementing basic operation of a linux shell
 |					that handles command line user input, splits
 |					each command into tokens, determines token type, and prints
 |					statement identifying token type
 |
 |	  Input:  Command line user input from keyboard at runtime
 |
 |	 Output:  Statement identifying each token of command provided
 |
 |    Algorithm:  Loop through tokenized command
 |
 |  Required Features Not Included:  The program adheres to all
 |		requirements stated in the program assignment, and all
 |		required features are included.
 |
 |   Known Bugs:  if redirect does not follow command, program assumes
 |					redirect is a command
 |
 +===========================================================================*/
#include <stdio.h>
/* for exit */
#include <stdlib.h>
/* for string library */
#include <string.h>
/* used for string comparisons */
const char *QUIT = "quit";
const char *PIPE = "|";
const char *REDIRECT = ">";
const char *REDIRECT_APP = ">>";
const char *REDIRECT_INP = "<";
/* Input/Output */
char *REDIRECT_TYPE;
/* Print quit statement and exit program */
void EXIT_PROGRAM();
/* Print functions based on token type */
void print_select(char *token);
void print_command(char *tok);
void print_pipe();
void print_redirect(char *tok);
void print_redirect_file(char *tok);
void print_argument(char *tok);
/* functions for checking if token signals redirect, quit, or pipe */
int isRedirect(char *tok);
int isQuit(char *tok);
int isPipe(char *tok);
/* global flags */
int global_cmd_flag, global_pipe_flag, global_redir_flag;
/*
	#########################################################################
	## For every argument passed
	##		if argument is quit, exit
	##		Parse argument into tokens
	##		For every token
	##			if token contains pipe, split token, 
	##				print commands/pipe, set new token ptr
	##			If cmd_flag is set or pipe_flag is set then token is command
	##			elif token is pipe, set pipe_flag
	##			elif token is redirect, set redir_flag
	##			elif redirect_flag is set then token is file
	##			else token is argument
	## TODO:
	##		compile print functions into 1 with extra parameter
	##		define program types -> #define COMMAND 1 etc
	##		store commands in allocated array
	#########################################################################
*/
int main(int argc, char *argv[]){
	//tokenize argument by space
	const char delim[2] = " ";
	//token ptr
	char *token;
	//pipe ptr if pipe is within token
	char *pipe_ptr;
	//index
	int i;
	//for every argument in argv ignoring first
	for (i = 1; i < argc; i++){
		//init global flags
		//command is true as first token is assumed to be valid program
		global_cmd_flag = 1;
		global_pipe_flag = 0;
		global_redir_flag = 0;
		//tokenize argument
		token = strtok(argv[i], delim);
		while (token != NULL){
			//exit any time if quit is found
			if(isQuit(token)){
				EXIT_PROGRAM();
			}
			/*
				## temporary fix
				## if token contains |, print words and pipe then go to next token
			*/
			pipe_ptr = strchr(token, '|');
			if (pipe_ptr != NULL){
				while(pipe_ptr != NULL){
					//replace pipe_ptr with \0
					token[pipe_ptr-token] = '\0';
					//print token
					print_select(token);
					//print pipe
					print_pipe();
					//set pipe flag
					global_pipe_flag = 1;
					//point token to pipe_ptr + 1
					token = pipe_ptr+1;
					//find next pipe
					pipe_ptr = strchr(pipe_ptr+1, '|');
				}
				//reset commdand to true; assumes pipe was the last token found
				global_cmd_flag = 1;
			}
			//print statement based on token type
			print_select(token);
			//get next token
			token = strtok(NULL, delim);		
		}	
	}
	return 0;
}
/*-----------------------print_select --------------------------------------
|  Function print_select
|  Purpose:  determine token type and print corresponding statement
|  Parameters:
|	token (char *) - string containing a token of the argv command
|  Returns:  Nothing.  (This is a void function.)
*-------------------------------------------------------------------*/
void print_select(char *token){
	//do not print if token is null
	if (*token == '\0')
		return;
	//token is command if cmd flag or pipe flag is set
	if(global_cmd_flag || global_pipe_flag){
		global_cmd_flag = 0;
		global_pipe_flag = 0;
		print_command(token);
	} 
	//if token is a pipe
	else if(isPipe(token)){
		global_pipe_flag = 1;
		print_pipe();
	}
	//if token is a redirect
	else if(isRedirect(token)){
		global_redir_flag = 1;
		print_redirect(token);
	}
	//if last token was redirect
	else if(global_redir_flag){
		global_redir_flag = 0;
		print_redirect_file(token);
	}
	//else assume token is argument
	else{
		print_argument(token);
	}
}
//if token == 'quit' - lowercase only - return true
int isQuit(char *tok){
	return (strcmp(tok, QUIT) == 0);
}
//if token == '|' return true
int isPipe(char *tok){
	return (strcmp(tok, PIPE) == 0);
}
//if token is >> or > then set redirect type return true
//if token is < then set redirect type return true
//else return false
int isRedirect(char *tok){
	if ((strcmp(tok, REDIRECT) == 0) || (strcmp(tok, REDIRECT_APP) == 0)){
		REDIRECT_TYPE = "Output";
		return 1;
	}
	else if(strcmp(tok, REDIRECT_INP) == 0){
		REDIRECT_TYPE = "Input";
		return 1;
	}
	return 0;
}
/*-----------------------printers--------------------------------------
|  Function: various print functions
|  Purpose:  print statement for corresponding user input
|  Parameters:
|	token (char *) - string containing a token of the argv command
|  Returns:  Nothing. void functions
*-------------------------------------------------------------------*/
void print_command(char *tok){
	printf("The user command or program is: %s\n", tok);
}
void print_pipe(){
	printf("Pipe:\tYes\n");
}
void print_redirect(char *tok){
	printf("%s redirection:\t%s\n", REDIRECT_TYPE, tok);
}
void print_redirect_file(char *tok){
	printf("%s file:\t%s\n", REDIRECT_TYPE, tok);
}
void print_argument(char *tok){
	printf("The command line argument to the user command and program is:\t%s\n", tok);
}
void EXIT_PROGRAM(){
	printf("Program terminates successfully by the user\n");
	exit(0);
}
