#include "standardHeaders.h"
#include "identify.h"
#include "cleaningFunctions.h"


void breakAndProcess(char *commandText, char *newHome) {
  char *commands[1024];

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
    char *arguments[1024];

    token = strtok(command, " ");
    char *commandName = token;

    int j = 0;

    while (token != NULL) {
      token = strtok(NULL, " ");
      if (token != NULL)
        arguments[j++] = removeLeadingSpaces(token);
    }
    int numOfArguments = j;
    identify(commandName, numOfArguments, arguments,newHome);
  }
}