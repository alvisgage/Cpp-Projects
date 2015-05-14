#include <stdio.h>
/* for exit */
#include <stdlib.h>
/* for string library */
#include <string.h>

void fa(char * s){
char local[] = "hello";
s=local;
}
void fb(char s[]){
char local[] = "hello";
s=local;
}
void fc(char * s){
strcpy(s, "hello");
}
void fd(char * s){
char * p;
p = malloc(6);
strcpy(p, "hey");
*s=*p;
}
void fe(char * s){
char * p;
p = malloc(6);
strcpy(p, "hello");
strcpy(s, p);
}
void ff(char * cmd[], char * line){
cmd[0] = line;
cmd[1] = line;
}
void fg(char * cmd[], char * line){
*cmd = line;
*(cmd+1) = line;
}
void fh(char * cmd[], char * line){
strcpy(cmd[0], line);
strcpy(cmd[1], line);
}
void fi(char * cmd[], char * line){
char tmp[strlen(line)+1];
strcpy(tmp,line);
cmd[0] = strtok(tmp, "|");
}
void fj(char * cmd[], char * line){
char * tmp = malloc(strlen(line)+1);
strcpy(tmp,line);
cmd[0] = strtok(tmp, "|");
}

int main(int argc, char *argv[]){
// code in the main program
char buf3[6];
char buf7[5];
char* cmd1[3];
char* cmd2[3];
cmd2[0] = buf3;
cmd2[1] = buf7;

strcpy(buf3, "hi");
strcpy(buf7, "ok");
char val[] = "ls|wc";
fa(buf3);
printf("fa(buf3) = %s\n", buf3);

fb(buf3);
printf("fb(buf3) = %s\n", buf3);

fc(buf3);
printf("fc(buf3) = %s\n", buf3);

fd(buf3);
printf("fd(buf3) = %s\n", buf3);

fe(buf3);
printf("fb(buf3) = %s\n", buf3);

fa(buf7);
printf("fa(buf7) = %s\n", buf7);

fb(buf7);
printf("fb(buf7) = %s\n", buf7);

fc(buf7);
printf("fc(buf7) = %s\n", buf7);

fd(buf7);
printf("fd(buf7) = %s\n", buf7);

fe(buf7);
printf("fb(buf7) = %s\n", buf7);

ff(cmd1, val);
printf("ff(cmd1[0], val) = %s\n", cmd1[0]);
printf("ff(cmd1, val) = %s\n", cmd1[1]);
fg(cmd1, val);
printf("fg(cmd1[0], val) = %s\n", cmd1[0]);
printf("fg(cmd1, val) = %s\n", cmd1[1]);
fh(cmd1, val);
printf("fh(cmd1[0], val) = %s\n", cmd1[0]);
printf("fh(cmd1, val) = %s\n", cmd1[1]);
fi(cmd1, val);
printf("fi(cmd1[0], val) = %s\n", cmd1[0]);
fj(cmd1, val);
printf("fj(cmd1[0], val) = %s\n", cmd1[0]);

ff(cmd2, val);
printf("ff(cmd2[0], val) = %s\n", cmd2[0]);
printf("ff(cmd2, val) = %s\n", cmd2[1]);
fg(cmd2, val);
printf("fg(cmd2[0], val) = %s\n", cmd2[0]);
printf("fg(cmd2, val) = %s\n", cmd2[1]);
fh(cmd2, val);
printf("fh(cmd2[0], val) = %s\n", cmd2[0]);
printf("fh(cmd2, val) = %s\n", cmd2[1]);
fi(cmd2, val);
printf("fi(cmd2[0], val) = %s\n", cmd2[0]);
fj(cmd2, val);
printf("fj(cmd2[0], val) = %s\n", cmd2[0]);

return 0;
}
