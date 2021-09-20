#ifndef __IDENTIFY_H
#define __IDENTIFY_H

void executeSystemCommand(char * name, int numOfArguments, char*arguments[], char * newHome );
extern char * bgProcessnames[100005];
extern long long int bgProcessIDS[100005];
extern long long int bgProcessCount;

#endif