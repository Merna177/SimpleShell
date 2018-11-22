#include <unistd.h> ///that include fork function 
#include <sys/wait.h> ///that include wait function
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int anding=0;
char **get_input(char *input) {
    char **command = (char **)malloc(20 * sizeof(char *));
/// just in case os run out of memory
        if (command == NULL) {
        perror("malloc failed");
        exit(1);
    }

    ///to separate between words with space
    char *separator = " ";
    char *parsed;
    int index = 0;
    //pointer to the first word splitting 
    parsed = strtok(input," ");
    while (parsed != NULL) {
        //put the words in command to send it execvp
        command[index] = parsed;
        index++;
        //point to the next word.
        parsed = strtok(NULL," ");
    }
if(strcmp(command[index-1],"&")==0)anding=1;

    command[index] = NULL;
    return command;
}
int cd(char *path) {
    return chdir(path);
}
int main(){
pid_t ID;
///this is the id of the running process
int stat_loc;
char **command;
while(1){
anding=0;
char *input=(char *)malloc(20 *sizeof(char ));
gets (input, 20, stdin);
command = get_input(input);
///if i enter command : exit will terminate the program
if(strcmp(input,"exit")==0)
exit(0);
  if (strcmp(command[0], "cd") == 0) {
 int flag=cd(command[1]);
if(flag==-1)
printf("Error");
}else{
ID=fork();
/// if os run out of memory and reach the max number of allowed processes
 if (ID < 0) {
  perror("Fork failed");
  exit(1);
        }
if(ID==0){
///check for & to make non blocking 
///child process is the running process
///firsr paramter in execvp is the name of the file to search for it in my OS
/// if condition is the command has something wrong or it doesnt exsit 
int rightCommand=execvp(command[0], command);
           if (rightCommand < 0) {
                perror(command[0]);
                exit(1);
            }
}else {
/// parent process is the running process
/// the parent will wait the child process to terminate 
/// stat_loc is the location that waitpid store a status value.
///WUNTRACED reports on stopped child processes as well as terminated ones.
   if(anding == 0)
            {
                  stat_loc = waitpid(ID,&stat_loc,WUNTRACED);

            }
            else{
printf("A");

                  stat_loc = waitpid(ID,&stat_loc,WNOHANG);
            }
}
}
free(input);
free(command);
}
return 0;
}
