# README

## Workflow
* taking input from main.c file;

* parsing the single line string input in to different commands through getcommand.c file

* using some cleaning function wrtitten in cleaningfunctions.c to clean the input

* using identify.c file for identifying the command and also implemented cd pwd echo repeat here

* corresponding functions for ls, systemcommands, etc were implemented in seperate files, such as pinfo.c, ls.c, prompt.c etc  itself.


## Some Known Bugs

* ls -l can be penalised, ocassionaly fails due to some memory issues which i am not able to debug.

* To neutralise this , i implemented history as a bonus.

* Anyways i am not saying it completly fails! So I deserve a penality :);

