/*
     //Input the manual code which has extension in file name ".hard":
     main:
          num: a, b;
          scan a, b, c, str;
          num: result = a * b + c;
          print "These are the mathed number: " + a + b + c + "\n";
          if a >= b:
            int d=3;
            a = d + a;
            print a;
        elif b==c:
            int d=6;
            print b;
        endif
     endmain

     main:
        num: a, b;
        bignum: c;
        string str;
        input: a, b, c, str;
        if a==b and b==c:
            print:"These are the mathed number: " + a + b + c + "\n";
        else if a==b or c==d:
            print:"These are the number.\n";
        else
            print: "No matched data. So string is displaying: \n" + str + "\n";
        endif
        loop (i=1:n)
            print: "This is "+ i + "th time.\n";
        endloop
        num: result = a * b + c;
        num: result2 = b / c;
        print: result + result2;
    endmain
*/
/*
    //Token generate, lexical analyzer and compile using c program
    step 1: check "main: " exist first or not
    step 2: if "num: || bignum: || fnum: || string" is declared then the next variables will be stored in c program.
    step 3: check if any variable is called then is it declared or not the checking process will happen in syntax parser;
    step 4: if "input: " exist then input function will be called to take input of the declared variable:
    step 5: if "print: " exist then the data will be printed && if outside of "" any variable exist then that variable will be printed
    step 6: if "if a==b : || else if a==b:" this type of condition exist then it should be executed:
    step 7; if "loop i=1-10: || loop i=1-n: || loop i=x-n: " then the loop will be executed
*/

/*
    //For Error detecting:
    1. if "main: " is not exist
    2. if any variable name is start from digit || specialCharacter
    3. if variable name is matched with any keyword like "num, bignum, fnum, string, if, else if, else, loop, main, input, print, and, or"
    4. if any variable that is not declared but exist in "input" or "print" field
    5. if variable is declared again
    6. if "if, else if, else" is declared after any word except ';'
    6. if "if, else if, else" is declared then there must a condition before ':' or might have multiple condition with "and", "or" but after "and", "or" there must be a condition before ':'
    7. if "else" or "else if" is declared there must be "if" is declared before
    8. check variable type error like: if in any expression string is used to calculation etc.
    9. if loop is declared after any word except ';'
    10. Time limit exit if the code does not compile in 10 second
*/
#include <bits/stdc++.h>
using namespace std;

void printOutput(string input);
string scanInput();
//----------------------Methods in parser.h--------------------
void error(const string &message);
bool isDeclared(string variable);
bool isSetValue(string variable);
int getVariableValue(string variable);
void setVariableValue(string variable, int value);
void parseProgram();
void parseStatement();
int parseExpression();
void parseDeclarations();
void parsePrint();
void parseScan();

// for condition
void onlyCheckIf();
void parseIf();
bool extractCondition();

// for loop
void parseLoop();
int startLoopTokenIndex;
int endLoopTokenIndex;

string scanInput();

bool isInteger(string &str);
void tillRParen();

void transferVariables();
bool checkingCondition = false;
bool withinBlock = false;

bool checkingExpression = false;
bool withinLoop = false;
bool loopVariableDefined = false;
bool loopConditionMatched = false;
bool loopTraversOneTime = false;

bool breakLoop = false;
bool disable = false;
bool disableLoop = false;
bool oneConditionMatched = false;
string lastCondition = "";
//----------------------Methods in parser.h--------------------

#include "tokenGenerate.h"
bool checkCondition(int left, Token opt, int right);
#include "infixToPostfix.h"
#include "parser.h"
void converter();

// #define bool _Bool

// Token types
bool isInteger(string &str)
{
    for (char c : str)
    {
        if (!isdigit(c))
        {
            return false;
        }
    }
    return true;
}
void printOutput(string input)
{
    if (withinBlock && disable)
    {
        return;
    }
    if (withinLoop && disableLoop)
    {
        cerr << "ohoad";
        return;
    }
    if (breakLoop)
    {
        return;
    }
    cout << input;
    // FILE *fp = fopen("./output.txt", "a");
    // if (fp == NULL)
    // {
    //     error("Error opening the file for writing.\n");
    // }
    // // write to the text file
    // // cerr << input << endl;
    // fprintf(fp, "%s", input.c_str());

    // // close the file
    // fclose(fp);
}
string scanInput()
{
    if (withinBlock && disable)
    {
        return "1";
    }
    if (withinLoop && disableLoop)
    {
        return "1";
    }
    if (breakLoop)
    {
        return "1";
    }
    string s;
    cin >> s;
    return s;
}
int main()
{
    freopen("log.txt", "w", stderr);
    /*----------------------------------------*/
    FILE *file_pointer;
    char line_buffer[1000];

    file_pointer = fopen("./input.txt", "r");

    if (file_pointer == NULL)
    {
        // printf("Failed to open the file.\n");
        cerr << "Failed to open the file." << endl;
        return 0;
    }

    bool is_in_quote = false;
    while (fgets(line_buffer, sizeof(line_buffer), file_pointer))
    {
        // printf("%s", line_buffer);
        cerr << "Line: " << line_buffer;
        identifyTokens(line_buffer);
    }
    fclose(file_pointer);

    printTokens();

    parseProgram();

    if (currentToken.type != END)
    {
        string message = "Unexpected token after end of program " + currentToken.name;
        error(message);
    }

    cerr << "The program is valid." << endl;
    /*----------------------------------------*/

    // if (!compile(input))
    // {
    //      printf("At line %d : ", code_index);
    //      printf("Compilation Error\n");
    // }
    // else
    // {
    //      printf("At line %d : ", code_index);
    //      printf("Compilation Success\n");
    // }
    // printGlobalVariable();
    return 0;
}