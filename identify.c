#include "cleaningFunctions.h"
#include "pinfo.h"
#include "standardHeaders.h"
#include "ls.h"
#include <stdio.h>


//cd pwd echo repeat will be implemented here itself
void identify(char *name, int numOfArguments, char **arguments, char* newHome) {

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
          printf("argument for cd is %s\n", arguments[0]);
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

  else if (strcmp(name, "pinfo") == 0)
  {
    
    
    if(numOfArguments==0)
    {
      int tempid = getpid();
      int tempLength = snprintf( NULL, 0, "%d", tempid );
      char* pid = malloc( tempLength + 1 );
      snprintf( pid, tempLength + 1, "%d", tempid );
      //printf("%s\n",pid);      
      processPinfo(pid,newHome);
    }
    else if (numOfArguments == 1)
    {
      char * pid = arguments[0];
      processPinfo(pid,newHome);
      return;
    }
    else
    {
      printf("Invalid Argument size\n");
      return;
    }

  }

  else if (strcmp(name, "ls") == 0)
  {
    int lflag=0, aflag=0, laflag=0, folderCount=0;
    char *folders[100];
    for(int i =0; i < numOfArguments;i++)
    {
      if(strcmp(arguments[i], "-l")==0 && strlen(arguments[i])==2)
      {
        lflag=1;
      }
      else if(strcmp(arguments[i], "-a")==0 && strlen(arguments[i])==2)
      {
        aflag=1;
      }
      else if( ( (strcmp(arguments[i], "-la")==0) || (strcmp(arguments[i], "-al")==0) )  && strlen(arguments[i])==3)
      {
        laflag=1;
      }

      else folders[folderCount++] = arguments[i];
    }
     if(laflag==1){lflag=1;aflag=1;}
    
    processLs(folders,folderCount,lflag,aflag,newHome);
    return;    
  }
  


};
