
// Function prototypes
// void parseAssignment();

// Get next token

// Error handling function
void error(const string &message)
{
     cerr << "Error: " << message << endl;
     exit(EXIT_FAILURE);
}
bool isDeclared(string variable)
{
     // cout << pos << endl;
     if (withinBlock && disable)
     {
          for (int i = 0; i < tempTokens.size(); i++)
          {
               if (tempTokens[i].type == IDENTIFIER && tempTokens[i].name == variable)
               {
                    return true;
               }
          }
     }
     else if (withinBlock)
     {
          for (int i = 0; i < permanentTokens.size(); i++)
          {
               if (permanentTokens[i].type == IDENTIFIER && permanentTokens[i].name == variable)
               {
                    return true;
               }
          }
     }
     for (int i = 0; i < pos - 1; i++)
     {
          // cout << tokens[i].name << endl;
          if (tokens[i].type == IDENTIFIER && tokens[i].name == variable)
          {
               return true;
          }
     }
     return false;
}
bool isSetValue(string variable)
{
     // cout<<pos<<endl;
     if (withinBlock && disable)
     {
          for (int i = 0; i < tempTokens.size(); i++)
          {
               if (tempTokens[i].type == IDENTIFIER && tempTokens[i].name == variable && tempTokens[i].value != "")
               {
                    return true;
               }
          }
     }
     else if (withinBlock)
     {
          for (int i = 0; i < permanentTokens.size(); i++)
          {
               if (permanentTokens[i].type == IDENTIFIER && permanentTokens[i].name == variable && permanentTokens[i].value != "")
               {
                    return true;
               }
          }
     }
     for (int i = 0; i < pos - 1; i++)
     {
          // cout << tokens[i].name << endl;
          if (tokens[i].type == IDENTIFIER && tokens[i].name == variable && tokens[i].value != "")
          {
               return true;
          }
     }

     return false;
}
int getVariableValue(string variable)
{
     if (withinBlock && disable)
     {
          for (int i = 0; i < tempTokens.size(); i++)
          {
               if (tempTokens[i].type == IDENTIFIER && tempTokens[i].name == variable && tempTokens[i].value != "")
               {
                    return stoi(tempTokens[i].value);
               }
          }
     }
     else if (withinBlock)
     {
          for (int i = 0; i < permanentTokens.size(); i++)
          {
               if (permanentTokens[i].type == IDENTIFIER && permanentTokens[i].name == variable && permanentTokens[i].value != "")
               {
                    return stoi(permanentTokens[i].value);
               }
          }
     }
     for (int i = 0; i < pos - 1; i++)
     {
          if (tokens[i].type == IDENTIFIER && tokens[i].name == variable)
          {
               return stoi(tokens[i].value);
          }
     }
     return 0;
}
void setVariableValue(string variable, int value)
{
     if (withinBlock && disable)
     {
          for (int i = 0; i < tempTokens.size(); i++)
          {
               if (tempTokens[i].type == IDENTIFIER && tempTokens[i].name == variable && tempTokens[i].value != "")
               {
                    tempTokens[i].value = to_string(value);
                    return;
               }
          }
     }
     else if (withinBlock)
     {
          for (int i = 0; i < permanentTokens.size(); i++)
          {
               if (permanentTokens[i].type == IDENTIFIER && permanentTokens[i].name == variable && permanentTokens[i].value != "")
               {
                    permanentTokens[i].value = to_string(value);
                    return;
               }
          }
     }
     for (int i = 0; i < pos - 1; i++)
     {
          if (tokens[i].type == IDENTIFIER && tokens[i].name == variable)
          {
               tokens[i].value = to_string(value);
               return;
          }
     }
     error("Variable not declared");
}
// ---------------Parsing functions----------------
void parseProgram()
{
     currentToken = getNextToken();
     if (currentToken.type == KEYWORD && currentToken.name == "main")
     {
          currentToken = getNextToken();
          if (currentToken.type == COLON)
          {
               currentToken = getNextToken();
          }
          else
          {
               cerr << currentToken.name << endl;
               error("Expected ':' after 'main'");
          }
     }
     else
     {
          error("Expected 'main'");
     }

     while (currentToken.type != END)
     {
          if (currentToken.type == KEYWORD && currentToken.name == "int")
          {
               parseDeclarations();
               currentToken = getNextToken();
          }
          else if (currentToken.type == IDENTIFIER)
          {
               parseStatement();
               currentToken = getNextToken();
          }
          else if (currentToken.type == KEYWORD && currentToken.name == "print")
          {
               parsePrint();
               // cout<<"here"<<endl;
               currentToken = getNextToken();
          }
          else if (currentToken.type == KEYWORD && currentToken.name == "scan")
          {
               parseScan();
               // cout<<"here"<<endl;
               currentToken = getNextToken();
          }
          else if (currentToken.type == KEYWORD && currentToken.name == "if")
          {
               parseIf();
               // cout<<"here"<<endl;
               currentToken = getNextToken();
          }
          else
          {
               cerr << currentToken.name << endl;
               error("Expected 'int', identifier or 'print'");
          }
     }
}
void parseIf()
{
     withinBlock = true;
     while (currentToken.name != "endif")
     {
          if (currentToken.name == "if")
          {
               onlyCheckIf();
          }
          else if (currentToken.name == "elif")
          {
               currentToken = getNextToken();
               onlyCheckIf();
          }
          else if (currentToken.name == "else")
          {
               currentToken = getNextToken();
               onlyCheckIf();
          }
          else if (currentToken.name == "end")
          {
               break;
          }
          else
          {
               currentToken = getNextToken();
          }
          currentToken = getNextToken();
     }
     withinBlock = false;
}
bool checkCondition(int left, Token opt, int right)
{
     if (opt.type == EQUAL)
     {
          return left == right;
     }
     else if (opt.type == NOT_EQUAL)
     {
          return left != right;
     }
     else if (opt.type == LESS_THAN)
     {
          return left < right;
     }
     else if (opt.type == GREATER_THAN)
     {
          return left > right;
     }
     else if (opt.type == LESS_THAN_EQUAL)
     {
          return left <= right;
     }
     else if (opt.type == GREATER_THAN_EQUAL)
     {
          return left >= right;
     }
     return false;
}
bool extractCondition()
{
     Token operation;
     int leftValue, rightValue;
     checkingCondition = true;
     leftValue = parseExpression();

     if (currentToken.type == EQUAL || currentToken.type == NOT_EQUAL || currentToken.type == LESS_THAN || currentToken.type == GREATER_THAN || currentToken.type == LESS_THAN_EQUAL || currentToken.type == GREATER_THAN_EQUAL)
     {
          operation = currentToken; // save the operation
     }
     else
     {
          error("Error in condition");
     }
     rightValue = parseExpression();
     checkingCondition = false;
     bool flag = true;
     if (!checkCondition(leftValue, operation, rightValue))
     {
          disable = true;
          flag = false;
     }
     return flag;
}
void onlyCheckIf()
{
     extractCondition();
     if (currentToken.type == COLON)
     {
          currentToken = getNextToken();
     }
     else
     {
          error("Expected ':' after condition");
     }
     while (currentToken.name != "endif" && currentToken.name != "else" && currentToken.name != "elif")
     {
          if (currentToken.type == KEYWORD && currentToken.name == "int")
          {
               parseDeclarations();
               currentToken = getNextToken();
          }
          else if (currentToken.type == IDENTIFIER)
          {
               parseStatement();
               currentToken = getNextToken();
          }
          else if (currentToken.type == KEYWORD && currentToken.name == "print")
          {
               parsePrint();
               // cout<<"here"<<endl;
               currentToken = getNextToken();
          }
          else if (currentToken.type == KEYWORD && currentToken.name == "scan")
          {
               parseScan();
               // cout<<"here"<<endl;
               currentToken = getNextToken();
          }
          // else if (currentToken.type == KEYWORD && currentToken.name == "if")
          // {
          //      parseIf();
          //      // cout<<"here"<<endl;
          //      currentToken = getNextToken();
          // }
          else
          {
               cerr << currentToken.name << endl;
               error("Expected 'int', identifier or 'print'");
          }
     }
}
void parseDeclarations()
{
     while (currentToken.type != SEMICOLON)
     {
          bool assign = false;
          previousToken = currentToken;
          currentToken = getNextToken();
          if (currentToken.type == IDENTIFIER && (previousToken.type == COMMA || previousToken.type == SEMICOLON || previousToken.type == KEYWORD))
          {
               if (isDeclared(currentToken.name))
               {
                    error("Error variable redefined");
               }
               if (disable)
               {
                    blockTokens.push_back(currentToken);
                    tokens.erase(tokens.begin() + pos - 1);
               }
               continue;
          }
          else if (currentToken.type == ASSIGN && previousToken.type == IDENTIFIER)
          {
               // currentToken = getNextToken();
               Token toAssign = previousToken;
               int value = parseExpression();
               if (disable)
               {
               }
               setVariableValue(toAssign.name, value);
               assign = true;
          }

          if (currentToken.type == SEMICOLON && (previousToken.type == IDENTIFIER || assign))
          {
               // cout << "ok " << endl;
               break;
          }
          else if (currentToken.type == COMMA)
          {
               // cout << "HEre\n";
               continue;
          }
          else
          {
               error("Expected identifier or assignment");
          }
     }
}
void parseStatement()
{
     if (isDeclared(currentToken.name))
     {
          previousToken = currentToken;
          currentToken = getNextToken();
          if (currentToken.type == ASSIGN)
          {
               // currentToken = getNextToken();
               Token toAssign = previousToken;
               int value = parseExpression();
               setVariableValue(toAssign.name, value);
          }
          else if (currentToken.type == SEMICOLON)
          {
               currentToken = getNextToken();
          }
          else
          {
               error("Expected assignment or ';'");
          }
     }
     else
     {
          error("Variable is not defined!");
     }
}
void parsePrint()
{
     bool gotQuote = false;
     while (currentToken.type != SEMICOLON)
     {
          previousToken = currentToken;
          currentToken = getNextToken();
          if (currentToken.type == SEMICOLON || currentToken.type == COMMA)
          {
               if (previousToken.type == IDENTIFIER)
               {
                    if (!isDeclared(previousToken.name))
                    {
                         error("Error variable used before defined");
                    }
                    if (!isSetValue(previousToken.name))
                    {
                         error("NULL value is used in print statement");
                    }
                    int value = getVariableValue(previousToken.name);
                    cerr << "Print Value: " << value << endl;
                    printOutput(to_string(value));
               }
               else if (previousToken.type == NUMBER)
               {
                    cerr << "Print Value: " << previousToken.name << endl;
                    printOutput(previousToken.name);
               }
               else if (previousToken.type == QUOTE)
               {
                    cerr << "Print Value: " << previousToken.name << endl;
                    printOutput(previousToken.name);
               }
               else
               {
                    error("Error in print statement");
               }
               if (currentToken.type == SEMICOLON)
               {
                    break;
               }
               else if (currentToken.type == COMMA)
               {
                    continue;
               }
          }
          else if ((previousToken.type == IDENTIFIER || previousToken.type == NUMBER) && (currentToken.type == PLUS || currentToken.type == MINUS || currentToken.type == MULTIPLY || currentToken.type == DEVIDE || currentToken.type == POWER))
          {
               expression.push(previousToken);
               expression.push(currentToken);
               int value = parseExpression();
               cerr << "Print live expression Value: " << value << endl;
               printOutput(to_string(value));
          }
          else if (currentToken.type == IDENTIFIER || currentToken.type == NUMBER || currentToken.type == QUOTE)
          {
               continue;
          }
          else
          {
               error("Error in print statement");
          }
     }
     printOutput("\n");
}
void parseScan()
{
     while (true)
     {
          previousToken = currentToken;
          currentToken = getNextToken();
          if (currentToken.type == IDENTIFIER)
          {
               if (!isDeclared(currentToken.name))
               {
                    error("Error variable is not defined");
               }
               string value = scanInput();
               if (!isInteger(value))
               {
                    error("Error input is not an integer");
               }
               setVariableValue(currentToken.name, stoi(value));
          }
          else if (currentToken.type == COMMA && previousToken.type == IDENTIFIER)
          {
               continue;
          }
          else if (currentToken.type == SEMICOLON && previousToken.type == IDENTIFIER)
          {
               break;
          }
          else
          {
               error("Error in scan statement");
          }
     }
}
int parseExpression()
{
     currentToken = getNextToken();
     if (currentToken.type == IDENTIFIER || currentToken.type == NUMBER)
     {
          expression.push(currentToken);
          while (true)
          {
               previousToken = currentToken;
               currentToken = getNextToken();
               if ((previousToken.type == IDENTIFIER || previousToken.type == NUMBER || previousToken.type == RPAREN) && (currentToken.type == PLUS || currentToken.type == MINUS || currentToken.type == MULTIPLY || currentToken.type == DEVIDE || currentToken.type == POWER))
               {
                    expression.push(currentToken);
                    continue;
               }
               else if ((currentToken.type == IDENTIFIER || currentToken.type == NUMBER) && (previousToken.type == PLUS || previousToken.type == MINUS || previousToken.type == MULTIPLY || previousToken.type == DEVIDE || previousToken.type == POWER))
               {
                    if (currentToken.type == IDENTIFIER && !isDeclared(currentToken.name))
                    {
                         error("Error variable used before defined");
                    }
                    expression.push(currentToken);
                    continue;
               }
               else if (currentToken.type == LPAREN && (previousToken.type == PLUS || previousToken.type == MINUS || previousToken.type == MULTIPLY || previousToken.type == DEVIDE || previousToken.type == POWER))
               {
                    expression.push(currentToken);
                    tillRParen();
               }
               else if ((currentToken.type == SEMICOLON || currentToken.type == COMMA) && (previousToken.type == IDENTIFIER || previousToken.type == NUMBER || previousToken.type == RPAREN))
               {
                    break;
               }
               else if (checkingCondition && (currentToken.type == EQUAL || currentToken.type == NOT_EQUAL || currentToken.type == LESS_THAN || currentToken.type == GREATER_THAN || currentToken.type == LESS_THAN_EQUAL || currentToken.type == GREATER_THAN_EQUAL || currentToken.type == COLON))
               {
                    break;
               }
               else
               {
                    error("Error in expression");
               }
          }
     }
     else
     {
          error("Expected identifier or number in expression");
     }
     int value = converterExpression();
     cerr << "Expression done\n";
     return value;
}
void tillRParen()
{
     while (true)
     {
          previousToken = currentToken;
          currentToken = getNextToken();
          if ((currentToken.type == IDENTIFIER || currentToken.type == NUMBER) && (previousToken.type == PLUS || previousToken.type == MINUS || previousToken.type == MULTIPLY || previousToken.type == DEVIDE || previousToken.type == POWER || previousToken.type == LPAREN))
          {
               if (currentToken.type == IDENTIFIER && !isDeclared(currentToken.name))
               {
                    error("Error variable used before defined");
               }
               expression.push(currentToken);
               continue;
          }
          else if ((previousToken.type == IDENTIFIER || previousToken.type == NUMBER || previousToken.type == RPAREN) && (currentToken.type == PLUS || currentToken.type == MINUS || currentToken.type == MULTIPLY || currentToken.type == DEVIDE || currentToken.type == POWER))
          {
               expression.push(currentToken);
               continue;
          }
          else if (currentToken.type == LPAREN && (previousToken.type == PLUS || previousToken.type == MINUS || previousToken.type == MULTIPLY || previousToken.type == DEVIDE || previousToken.type == POWER))
          {
               expression.push(currentToken);
               tillRParen();
          }
          else if (currentToken.type == RPAREN && (previousToken.type == IDENTIFIER || previousToken.type == NUMBER))
          {
               expression.push(currentToken);
               return;
          }
          else
          {
               error("Error in expression");
          }
     }
}
