//   Name: Jade Mitchell                                                                             
//   EUID: jam1375                                                                                    
//   Class: 4430.001                                                                          
//   Description: This is a parser that takes input from the flex file output
//                and uses the context-free grammar provided to return an AST

%{
    #include <stdio.h>
    #include <stdlib.h>
    #include "jam1375parser.tab.h"

    extern int yylex();
    extern int yyparse();
    void yyerror(const char *c);

    struct Node
    {
        int type;
        struct Node *left;
        struct Node *right;
        char *value;
    };
    
    struct Node* getNode(int type, struct Node* left, struct Node* right, char* value);
    void printAST(struct Node* node, int indent);

    #define INTEGER 1
    #define VARIABLE 2
    #define ASSIGN 3
    #define EXPR 4
    #define TERM 5
    

    struct Node* root;

    %}

    %union
    {
        int ival;
        char* sval;
        struct Node* node;
    }

    %token <ival> INTEGER ADD SUB DIV MUL LPAREN RPAREN ASSIGN EXP
    %token <sval> VARIABLE
    %type <node> program statement assignment expr term factor

    %%

program: statement { root = $1;};

statement: assignment | expr { $$ = $1; };

assignment: VARIABLE ASSIGN expr { $$ = getNode(ASSIGN, getNode(VARIABLE, NULL, NULL, $1), $3, "="); };

expr: term 
    | expr ADD term { $$ = getNode(EXPR, $1, $3, "+"); }
    | expr SUB term { $$ = getNode(EXPR, $1, $3, "-"); }

term: factor 
    | term MUL factor { $$ = getNode(TERM, $1, $3, "*"); }
    | term DIV factor { $$ = getNode(TERM, $1, $3, "/"); } 
    | term EXP factor { $$ = getNode(TERM, $1, $3, "^"); } ;

factor: INTEGER { 
        char *strValue = malloc(20);
        snprintf(strValue, 20, "%d", $1);
        $$ = getNode(INTEGER, NULL, NULL, strValue); }
      | VARIABLE { $$ = getNode(VARIABLE, NULL, NULL, $1); }
      | LPAREN expr RPAREN { $$ = $2;} ;

%%

void yyerror(const char *c)
{
    fprintf(stderr, "Error: %s\n", c );
}

    struct Node* getNode(int type, struct Node* left, struct Node* right, char* value)
    {
        struct Node* node = (struct Node*)malloc(sizeof(struct Node));
        node->type = type;
        node->left = left;
        node->right = right;
        node->value = value;
        return node;
    }

    void printAST(struct Node* node, int indent)
    {
        if (node == NULL) 
            { return; }
        for(int i = 0; i < indent; i++)
        {
            printf(" ");
        }

        switch (node->type) 
        {
            case EXPR:
                if(node->value == "+")
                {
                    printf("+ (ADD)\n");
                }
                else if(node->value == "-")
                {
                    printf("- (MINUS)\n");
                }
                    break;
            case TERM:
                if(node->value == "*")
                {
                   printf("* (MULTIPLY)\n");
                }
                else if(node->value == "/")
                {
                    printf("/ (DIVIDE)\n");
                }
                else
                {
                    printf("^ (EXP)\n");
                }
                break;
            case ASSIGN:
                printf("= (ASSIGNMENT)\n");
                break;
            case INTEGER:
                printf("%s (INT)\n", node->value); 
                break;
            case VARIABLE:
                printf("%s (VARIABLE)\n", node->value); 
                break;
            default:
                printf("Unknown node type\n");
                break;
        }

        printAST(node->left, indent +1);
        printAST(node->right, indent +1);

    }


int main()
{
    char inputname[100];
    printf("Enter name of input file: ");
    scanf("%s", inputname);
    FILE* input = fopen(inputname, "r");
    if (!input) {
        printf("Failed to open input file\n");
        return 1;
    }

    extern FILE* yyin ;
     yyin = input;

     yyparse();

    fclose(input);

    printAST(root, 0);

    return 0;
}
