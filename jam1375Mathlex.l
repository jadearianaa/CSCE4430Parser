/* Name: Jade Mitchell                                                                              */
/* EUID: jam1375                                                                                    */ 
/* Class: 4430.001                                                                                  */
/* Description: This is a lexical analyzer that identifies tokens in simple mathmatical expressions */

%{
    #include <stdio.h>
    #include <stdlib.h>
/* Declaring a file pointer for the file it will be outputted to */

    FILE *output;

%}

%%
[0-9]+                   { fprintf(output, "%s,integer\n", yytext); } //matches integers
["+"|"/"|"*"]            { fprintf(output, "%s,operator\n", yytext); }  // matches 3 operators
[-]                      { fprintf(output, "%s,operator\n", yytext); } // matches the subtraction operator
["("]                    { fprintf(output, "%s,lparenthesis\n", yytext); } //matches left parenthesis
[")"]                    { fprintf(output, "%s,rparenthesis\n", yytext); } // matches right parenthesis
[. | \n]                 {  }
%%

int yywrap()
{
    return 1; //indicates EOF
}

int main(void)
{
    char inputname[100]; 
    char outputname[100];
    FILE *input; //declaring file pointer for input file

    //user chooses the name of the input file
    printf("Enter name of input file: ");
    scanf("%s", &inputname);
    fflush(stdin); // gets rid of any extra input

    // user chooses name of output file
    printf("Enter name of output file: ");
    scanf("%s", &outputname);
    fflush(stdin);

    //opens the input file to read from
    input = fopen(inputname, "r");
    if(!input)
    {
        //if the input/output file fails to open returns error message
        printf("Failed to open input file.\n");
        return 1;
    }

    output = fopen(outputname, "w");
    if(!output)
    {
        printf("Failed to open output file.\n");
        return 1;
    }

    yyin = input; // is the input for the lexer
    yylex(); // does the lexical analysis

    //closes both files
    fclose(input);
    fclose(output);

    return 0;

}
