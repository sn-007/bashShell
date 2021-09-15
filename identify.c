#include "cleaningFunctions.h"
#include "standardHeaders.h"
#include <stdio.h>

//cd pwd echo repeat will be implemented here itself
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
      if(strcmp(arguments[0],"-")==0 )
      {
        char cwd[100000]="";
        getcwd(cwd,sizeof(cwd));
        printf("%s\n",cwd);
        return;
      }
      else if (strcmp(arguments[0],"~")==0 )
      {
        if(chdir(newHome) < 0)  perror("error:");
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
    for(int i=0;i<numOfArguments;i++) printf("%s",arguments[i]);
    printf("\n");
  } 

  else if (strcmp(name, "pwd") == 0) 
  {
    char cwd[100000]="";
    getcwd(cwd,sizeof(cwd));
    printf("%s\n",cwd);
    return;
  }
  else if (strcmp(name, "repeat") == 0)
  {
    if(numOfArguments < 2 ) {printf("repeat expects atleast 2 arguments\n");return;}
    
    int numOfTimes = atoi(arguments[0]);
    printf("%d\n",numOfTimes);
    if(numOfTimes <= 0) {printf("enter a valid number for repetetion\n");return;}

    char * newArguments[100];
    for (int i=2;i<numOfArguments;i++)
      newArguments[i-2] = arguments[i];
    
    for (int i =0;i<numOfTimes;i++)
    {
      identify(arguments[1], numOfArguments-2, newArguments, newHome);
    }
  }


};
