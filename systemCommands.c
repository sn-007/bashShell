#include "standardHeaders.h"
#include "systemCommands.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wait.h>

char * bgProcessnames[100005];
long long int bgProcessIDS[100005];
long long int bgProcessCount;


void executeSystemCommand(char * name, int numOfArguments, char*arguments[], char * newHome )
{
    char* argv[100];
    argv[0] = name;

    for(int i =0;i < numOfArguments;i++)
        argv[1+i] = arguments[i];
     

    char lastchar = argv[numOfArguments][strlen(argv[numOfArguments])-1];

    int backgroundFlag =0;    

    if( (strcmp(argv[numOfArguments],"&")==0) )
    {
        argv[numOfArguments] = "\0";
        numOfArguments--;
        backgroundFlag=1;
    }
    else if (lastchar=='&')
    {
        backgroundFlag=1;
        argv[numOfArguments][strlen(argv[numOfArguments])-1] = '\0';
    }
    argv[numOfArguments+1]=NULL;
  
    pid_t pid = fork();

    if(pid==-1) {perror("error");return;};

    if(backgroundFlag==1)
    {
        bgProcessnames[bgProcessCount]=name;
        bgProcessIDS[bgProcessCount]=pid;
        bgProcessCount++;
        if(pid!=0) printf("%d\n",pid);
    }
    if(pid==0)
    {
        //char * temp[4] ={"ls","-l","-a",NULL};
        int ans = execvp(name, argv);
        if(ans < 0) perror(name);
    }
    if(backgroundFlag==0)
    {
        wait(NULL);
    }
    
}