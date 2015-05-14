#include <string.h>
#include <stdio.h>
#include <stdlib.h>
int global_program;
int global_output;
const char *valid_programs[] = {"ls", "grep"};
const int num_val_progs = 2;
void printType(char *word, int type){

}
void determineType(char *word){
	//ifs to determine type
	//if word in list of programs
		//global_program = 1
		//print word, program type
	//elif word is output redir
		//global_output = 1, global_program = 0
		//print word, output redir
	//elif global_program = 1
		//print word, argument
	//elif global_output = 1
		//global_output = 0
		//print word, output file
	//elif pipe
		//global_output = 0, global_program = 0
		//print pipe
	//el
		//print invalid cmd
	
}
void splitCommand(char* cmd, int len){
	//splits the command and determines type
	char word[len];
	int counter = 0;
	int j, k;
	for(j = 0; j < len; ++j){
		char c = cmd[j];
		printf("c:\t%c\n", c);
		if (c == ' '){
			//determine word type
			determineType(word);
			//clear word
			for (k = 0; k < counter; k++)
				word[k] = 0;
			counter = 0;
		} else {
			//add char to word
			word[counter] = c;
			counter = counter + 1;
		}
		//determine word type: cmd, arg, pipe etc
		printf("word:\t%s\n", word);
	}
}
int main(int argc, char *argv[]){
	global_program = 0;
	global_output = 0;
	int i,len;
	char** cmd;
	cmd = malloc(sizeof(char*)*(argc - 1));
	printf("argc:\t%i\n", argc);
	for (i = 1; i < argc; i++){
		printf("argv[%i]:\t%s\n", i, argv[i]);
		len = strlen(argv[i]);
		cmd[i-1] = malloc(sizeof(char)*len);
		cmd[i-1] = argv[i];
		if (strcmp(cmd[i-1], "quit") == 0){
			printf("Program terminates successfully by the user\n");
			break;
		}
		splitCommand(cmd[i-1], len);
	}
	free(cmd);
	return 0;
}
