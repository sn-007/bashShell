#include "standardHeaders.h"
#include "identify.h"
#include "cleaningFunctions.h"


void breakAndProcess(char *commandText, char *newHome) {
  char *commands[100];

  char *token = strtok(commandText, ";");
  commands[0] = token;

  int i = 1;

  while (token != NULL) {
    token = strtok(NULL, ";");
    if (token != NULL)
      commands[i++] = token;
  }
  int numOfCommands = i;

  for (i = 0; i < numOfCommands; i++) {
    char *command = removeLeadingSpaces(commands[i]);
    char *arguments[100];

    token = strtok(command, " ");
    char *commandName = token;

    int j = 0;

    while (token != NULL) {
      token = strtok(NULL, " ");
      if (token != NULL)
        arguments[j++] = removeLeadingSpaces(token);
    }
    int numOfArguments = j;
    // printf("command name is : %s", commandName);
    // printf("arguments are:\n");
    // for (int sr =0; sr < numOfArguments;sr++ )
    // {
      
    //   printf("%s\n",arguments[sr]);
    // }
    identify(commandName, numOfArguments, arguments,newHome);
    
  }
  return;
}