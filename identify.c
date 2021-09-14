#include "cleaningFunctions.h"
#include "standardHeaders.h"
#include <stdio.h>

//cd pwd and echo will be implemented here itself
void identify(char *name, int numOfArguments, char *arguments[], char* newHome) {

  if (strcmp(name, "cd") == 0) 
  {
    if (numOfArguments > 1) {
      printf("bash: cd: too many arguments\n");
      return;
    }
    else if(numOfArguments == 0)
    {
        if(chdir(newHome) < 0)  perror("error:");
        return;
    }
    else if (numOfArguments==1)
    {
      if(strcmp(arguments[0],"-")==0)
      {
        char cwd[100000]="";
        getcwd(cwd,sizeof(cwd));
        printf("%s\n",cwd);
        return;
      }
      if(chdir(arguments[0]) < 0)
        {
          perror(arguments[0]);
        }
    }
    


  } 

  else if (strcmp(name, "echo") == 0) 
  {

  } 

  else if (strcmp(name, "pwd") == 0) 
  {

  }
};
