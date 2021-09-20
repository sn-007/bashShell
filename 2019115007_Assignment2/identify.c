#include "standardHeaders.h"
#include "cleaningFunctions.h"
#include "pinfo.h"
#include "ls.h"
#include "systemCommands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char OLDPWD[1000]=""; 

int max(int a, int b)
{
    if (a >= b)
        return a;
    else
        return b;
}

int min(int a, int b)
{
    if (a >= b)
        return b;
    else
        return a;
}

// inspired from https://tiswww.case.edu/php/chet/readline/history.html
void printHistory(char **arguments,int numOfArguments)
{
  int l1 = history_length,l2;
  
  register int i;

  if(numOfArguments > 1)
  {
    printf("INVALID ARGUMENTS");
    return;
  }

  else if (numOfArguments == 0) l2 = 10; // as the default limit is 10

  else  l2 = atoi(arguments[0]);
  
   
  register HIST_ENTRY **list = history_list();
  if(list)
  {
    for(i = max(l1 - l2, 0); i < (max(l1 - l2, 0) + min(l1, l2)); i++)
    {
      if(list[i]->line[strlen(list[i]->line)-1]=='\n')
        printf("%s", list[i]->line);
      else
       printf("%s\n", list[i]->line);
    }
      
  }
  else printf("Enter atleast one command bro\n");

  return;

}

void assign(char * a, char* b)
{
  int len = strlen(a);
  for(int i =0;i <1000;i++ )
  {
    b[i]='\0';
  }
  for(int i =0;i <len;i++ )
  {
    b[i]=a[i];
  }
  return;
}

//cd pwd echo repeat will be implemented here itself
void identify(char *name, int numOfArguments, char **arguments, char* newHome) {
  

  char cwdBUF[1024];
  char * cwd = getcwd(cwdBUF,1024);

  if (strcmp(name, "cd") == 0) 
  {
    if (numOfArguments > 1) 
    {
      printf("bash: cd: too many arguments\n");
      return;
    }

    else if(numOfArguments == 0)
    {
        if(chdir(newHome) < 0)  perror("error:");

        else assign(cwd,OLDPWD);
        return;
    }

    else if (numOfArguments==1)
    {
      if(strcmp(arguments[0],"-")==0 )
      {
        if(OLDPWD[0])
        {
          printf("%s\n",OLDPWD);
          if(chdir(OLDPWD) < 0)  perror("error:");

          else assign(cwd,OLDPWD);
        }

        else 
        {
          printf("cd : OLDPWD not set yet\n");
        }

        return;
      }

      else if (strcmp(arguments[0],"~")==0 )
      {
        if(chdir(newHome) < 0)  perror("error:");
        else assign(cwd,OLDPWD);
        return;
      }

      else if  (chdir(arguments[0]) < 0)
      {
        perror(arguments[0]);
      }

      else assign(cwd,OLDPWD);

    }
    return;
  } 

  else if (strcmp(name, "echo") == 0) 
  {
    for(int i=0;i<numOfArguments;i++) printf("%s",arguments[i]);
    printf("\n");
    return;
  
  
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
    //printf("%d\n",numOfTimes);
    if(numOfTimes <= 0) {printf("enter a valid number for repetetion\n");return;}

    char * newArguments[100];
    for (int i=2;i<numOfArguments;i++)
      newArguments[i-2] = arguments[i];
    
    for (int i =0;i<numOfTimes;i++)
    {
      identify(arguments[1], numOfArguments-2, newArguments, newHome);
    }
    return;
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
    return;

  }

  else if (strcmp(name, "ls") == 0)
  {
    int lflag=0, aflag=0, laflag=0, folderCount=0;
    char *folders[100];
    for(int i =0; i < numOfArguments;i++)
    {
      if(strcmp(arguments[i], "~")==0 && strlen(arguments[i])==1)
      {
        
        folders[folderCount++] = newHome;
        continue;
      }

      else if(strcmp(arguments[i], "-l")==0 && strlen(arguments[i])==2)
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
  else if (strcmp(name, "history") == 0)
  {
    printHistory(arguments,numOfArguments);

  }
  
  else
  {
    executeSystemCommand(name,numOfArguments,arguments,newHome);
  }


};
