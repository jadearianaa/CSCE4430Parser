 /* Name: Jade Mitchell                                                                             
   EUID: jam1375                                                                                    
   Class: 4430.001                                                                          
   Description: This is a recursive descent parser that takes input from a file
                that has already been through a mathematical lexer, and uses 
                recursive functions to return an Abtract Syntax Tree
*/

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctype.h>

using namespace std;

// Abstract Syntax Tree node types
enum nodeType { INT, ADD, SUB, MUL, DIV };

//structure for each node
struct Node 
{
    nodeType type; // Type of node (the enum types)
    string value; // the value of the token
    Node* left; // left child
    Node* right; // right child
};

//Vector used to hold tokens received from the input file
vector<string> tokens;

//function used to get the next token from the input 
void nextToken() 
{
    if(tokens.empty())
    {
        cout<< "Error: No valid tokens" << endl;
        exit(1);
    }
    string token = tokens[0];
    tokens.erase(tokens.begin());
}


// Parsing Functions / The grammar used
Node* expression(); 
Node* expressionSuffix(Node* left);
Node* term();
Node* termSuffix(Node* left);
Node* factor();
bool isDigit();
Node* integer();
string getNode(Node* node);
void printAST(Node* node, int indent);
void parseTokens();

// parses a full expression
Node* expression() 
{
    //parses a term
    Node* left = term();

    //parses the expression suffix
    return expressionSuffix(left);
}

//parses the suffix of an expression
Node* expressionSuffix(Node* left) 
{
    //if next token is +, parse the suffix
    if ((!tokens.empty()) && (tokens[0] == "+")) 
    {
        nextToken();
        Node* right = term();
        Node* node = new Node{ADD, "", left, right}; //create a new node for the operator
        return expressionSuffix(node);

       //if next token is -, parse the suffix  
    } else if ((!tokens.empty()) && (tokens[0] == "-")) 
    {
        nextToken();
        Node* right = term();
        Node* node = new Node{SUB, "", left, right}; // creates a new node for the operator

        return expressionSuffix(node); //recursively parsinh
    } else 
    {
        return left;
    }
}

//parses a term
Node* term() 
{
    //parses a factor
    Node* left = factor();

    //parses the term suffix
    return termSuffix(left);
}

//parses the suffix of a term
Node* termSuffix(Node* left) 
{
    //if the next token is *, parse the suffix
    if ((!tokens.empty()) && (tokens[0] == "*")) 
    {
        nextToken();
        Node* right = factor();
        Node* node = new Node{MUL, "", left, right}; // creates a new node for the *
        return termSuffix(node);

        ////if the next token is /, parse the suffix
    } else if ((!tokens.empty()) && (tokens[0] == "/")) 
    {
        nextToken();
        Node* right = factor();
        Node* node = new Node{DIV, "", left, right}; //creates a new node for the /
        return termSuffix(node);
    } else 
    {
        return left;
    }
}

//parses a factor (parenthesis and integers)
Node* factor() 
{
    //if the next token is (), parse the expression
    if ((!tokens.empty()) && (tokens[0] == "(")) 
    {
        nextToken();
        Node* node = expression();

        //checks for the second ) to match
        if((!tokens.empty()) && (tokens[0] == ")"))
        {
            nextToken();
        }
        else
        {
            cout<< "Syntax Error" << endl;
            exit(1);
        }

        return node;

    } else 
    {   
        //if next token is an integer, integer parse
        return integer();
    }
}

//checks if the token is a digit
bool isDigit(const string &token)
{
        for (char c : token) 
        {
            if (!isdigit(c)) 
            {
                return false;
            }
        }
       
        return true;
}

//parses a node if it is of integer type
Node* integer() 
{
    //checks if next token is an integer
    if (!tokens.empty() && (isDigit(tokens[0])))
    {
        string token = tokens[0];
        nextToken();
        Node* node = new Node{INT, token, nullptr, nullptr}; //creates a node for the integer
        return node;
    } else 
    {
        cout<< "Error: Unexpected Character " << endl;
        exit(1);
    }
}

// retrieves the node information
string getNode(Node* node) 
{
    switch (node->type) 
    {
        case INT:
            return node->value + " (int)";
            break;
        case ADD:
            return "+ (ADD)";
            break;
        case SUB:
            return "- (MINUS)";
            break;
        case MUL:
            return "* (MUTIPLY)";
            break;
        case DIV:
            return "/ (DIVIDE";
            break;
        default:
            return " ";
    }
}

//function that recursively prints the AST
void printAST(Node* node, int indent) 
{
    for (int i = 0; i < indent; i++) 
    {
        cout << "  ";
    }
        cout << getNode(node) << endl;

    if (node->left) 
    {
        printAST(node->left, indent + 1);
    }
    if (node->right) 
    {
        printAST(node->right, indent + 1);
    }
} 


//function parses the tokens inputted and starts the printing of the AST
void parseTokens()
{
    int indent = -1;
    while(!tokens.empty())
    {
        Node *ast = expression();
        printAST(ast, indent + 1);
        indent++;
    }
}

int main() 
{
    string input;
    string line;
    string value;
    string token;

    //user chooses input file name
    cout<<"Enter name of input file: ";
    cin>>input;

    ifstream fin(input);

    //error message if input file isn't opened correctly
    if(!fin.is_open())
    {
        cout<<"Failed to open input file."<<endl;
        exit(1);
    }

    //reads the input file and inputs the tokens into the tokens vector
    while(getline(fin, line))
    {
        istringstream iss(line);
        getline(iss, token, ',');
        getline(iss, value);
        tokens.push_back(token);
    }
    


    fin.close();

    if(tokens.empty())
    {
        cout<< "Error: No valid tokens" << endl;
        exit(1);
    }

    //begins parsing
    parseTokens();
   

    return 0;
}