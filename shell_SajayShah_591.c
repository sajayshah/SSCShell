#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 80 /* The maximum length command */

int main (void)
{
char *args[MAXLINE/2 + 1]; /* command line with max 40 arguments */
int should_run = 1; /* flag to determine when to exit program */
//char exitStr[] = "exit";
printf("CS149 Shell from Sajay Shah\n"); /* replace w/ name */
while (should_run) {
  printf("Sajay-591>"); /* prompt- replace FirstName and L3SID */
  fflush(stdout);
  /* After reading user input, the steps are:
  * (1) fork a child process using fork()
  * (2) the child process will invoke execvp()
  * (3) if command included &, parent will NOT invoke wait() */
  char str[MAXLINE];
  // read user input
  fgets(str, MAXLINE, stdin);

  // ampersand detection
  const char *invalid_characters = "&";
  int ampersandFlag = 0;
  char *c = str;
  while (*c)
  {
    if (strchr(invalid_characters, *c))
    {
      ampersandFlag = 1;
    }
    c++;
  }

  // the following removes the trailing newline char from fgets
  str[strcspn(str, "\n")] = 0;

  // begin tokenizing input, fill args array
  char *token;

  /* get the first token */
  token = strtok(str, " ");
  args[0] = token;
  int i = 1;
  while(token)
  {
    //printf("%s\n", token );
    token = strtok(NULL, " ");
    args[i] = token;
    i++;

  }

  // check if user enterted "exit"
    if (strMatch(args[0], "exit")) {
      should_run = 0;
      break;
    }


    // remove the ampersand from args array
    if(ampersandFlag)
    {
      args[i-2] = NULL;
    }

      int pid, status;

      if((pid = fork()) < 0 )
      {
        printf("Fork error\n");
        exit(1);
      }
      if(pid == 0)
      {
        execvp(args[0], args);
        printf("Not a valid command \n");
        //printf("Sajay-591>");
        exit(1);
      }
      // if there's no '&' then we wait. If there is '&' then we don't wait
      if (!ampersandFlag)
      {
        wait(&status);
      }


}


return 0;
}

// helper function to check if user entered "exit". Could've used strlen in retrospect.
int strMatch(char inputStr[], char matchStr[])
{
  int i = 0;
  int flag = 0;

  while(inputStr[i]!='\0' && matchStr[i]!='\0'){
         if(inputStr[i]!=matchStr[i]){
             flag=1;
             break;
         }
         i++;
    }

    if (flag==0 && inputStr[i]=='\0' && matchStr[i]=='\0')
         return 1;
    else
         return 0;

}
