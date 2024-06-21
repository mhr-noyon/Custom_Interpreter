#include <bits/stdc++.h>
using namespace std;

// Function prototypes
void parseProgram();
void parseDeclarations();
void parseStatements();
void parseStatement();
void parseAssignment();
void parseExpression();
void parseTerm();
void parseFactor();

// Get next token

// Error handling function
void error(const string &message)
{
     cerr << "Error: " << message << endl;
     exit(EXIT_FAILURE);
}

// Parsing functions
void parseProgram()
{
     if (pos == 0 && tokens[pos].type == KEYWORD && tokens[pos].value == "main")
     {
          currentToken = getNextToken();
          if (currentToken.type == COLON)
          {
               currentToken = getNextToken();
               parseStatements();
          }
          else
          {
               error("Expected ':' after 'main'");
          }
     }
     else if (pos == 0)
     {
          error("Expected 'main'");
     }

     if (currentToken.type == KEYWORD && currentToken.value == "main")
     {
          currentToken = getNextToken();
          if (currentToken.type == COLON)
          {
               currentToken = getNextToken();
               parseDeclarations();
               parseStatements();
          }
          else
          {
               error("Expected ':' after 'main'");
          }
     }
     else
     {
          error("Expected 'main'");
     }
}
void parseStatements()
{
     while (currentToken.type == IDENTIFIER)
     {
          parseStatement();
     }
}

void parseDeclarations()
{
     if (currentToken.type == KEYWORD && currentToken.value == "int")
     {
          currentToken = getNextToken();
          while (currentToken.type == IDENTIFIER)
          {
               currentToken = getNextToken();
               if (currentToken.type == COMMA)
               {
                    currentToken = getNextToken();
               }
               else if (currentToken.type == SEMICOLON)
               {
                    currentToken = getNextToken();
                    break;
               }
               else if (currentToken.type == ASSIGN)
               {
                    currentToken = getNextToken();
                    parseExpression();
                    if (currentToken.type == SEMICOLON)
                    {
                         currentToken = getNextToken();
                         break;
                    }
                    else if (currentToken.type == COMMA)
                    {
                         currentToken = getNextToken();
                    }
                    else
                    {
                         error("Expected ';' after assignment");
                    }
               }
               else
               {
                    error("Expected ',' or ';' in declarations");
               }
          }
     }
     else
     {
          error("Expected 'int' in declarations");
     }
}

void parseStatements()
{
     while (currentToken.type == IDENTIFIER)
     {
          parseStatement();
     }
}

void parseStatement()
{
     parseAssignment();
     if (currentToken.type == SEMICOLON)
     {
          currentToken = getNextToken();
     }
     else
     {
          error("Expected ';' after assignment");
     }
}

void parseAssignment()
{
     if (currentToken.type == IDENTIFIER)
     {
          currentToken = getNextToken();
          if (currentToken.type == ASSIGN)
          {
               currentToken = getNextToken();
               parseExpression();
          }
          else
          {
               error("Expected '=' in assignment");
          }
     }
     else
     {
          error("Expected identifier in assignment");
     }
}

void parseExpression()
{
     parseTerm();
     while (currentToken.type == PLUS || currentToken.type == MINUS)
     {
          currentToken = getNextToken();
          parseTerm();
     }
}

void parseTerm()
{
     parseFactor();
     while (currentToken.type == MULTIPLY || currentToken.type == DEVIDE)
     {
          currentToken = getNextToken();
          parseFactor();
     }
}

void parseFactor()
{
     if (currentToken.type == NUMBER)
     {
          currentToken = getNextToken();
     }
     else if (currentToken.type == IDENTIFIER)
     {
          currentToken = getNextToken();
     }
     else if (currentToken.type == LPAREN)
     {
          currentToken = getNextToken();
          parseExpression();
          if (currentToken.type == RPAREN)
          {
               currentToken = getNextToken();
          }
          else
          {
               error("Expected ')' after expression");
          }
     }
     else
     {
          error("Expected number, identifier, or '(' in factor");
     }
}
