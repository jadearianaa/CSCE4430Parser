# CSCE4430Parser
README- Project 2 ; CSCE.4430.001;  
HOW TO COMPILE:
For reference- I have been compiling everything using Windows Command Prompt.

Before you begin compilation, please have an input file ready that has a
simple mathematical expression written in it. I have included an input file called "inputme.txt"

The simple mathematical lexical analyzer made with flex is named "jam1375Mathlex.l"

To run jam1375Mathlex.l :

Type:- flex jam1375Mathlex.l

This command should create a lex.yy.c file.

The parser file made with bison is named "jam1375parser.y"

To run jam1375parser.y :

Type:- bison jam1375parser.y

This command should create a jam1375parser.tab.c and jam1375parser.tab.h file.

To compile the flex and bison files together :

Type:- gcc lex.yy.c jam1375parser.tab.c

Once they are compiled, you can execute using a.exe or a.
Once program is executed, you will be prompted to enter the name of an input file.
Once you have entered the file name, it should print out the AST.
If there are any syntax errors, the program should print out an error message.



