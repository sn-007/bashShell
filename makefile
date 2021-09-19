main:
	gcc -g -lreadline  main.c prompt.c cleaningFunctions.c getCommand.c identify.c pinfo.c ls.c systemCommands.c -lhistory
