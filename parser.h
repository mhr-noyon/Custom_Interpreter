
// Function prototypes
// void parseAssignment();

// Get next token

// Error handling function
void error(const string &message)
{
     cerr << "Error: " << message << " in " << pos - 1 << "no. token: " << currentToken.name << endl;
     cout << "Error: " << message << " in " << pos - 1 << "no. token: " << currentToken.name << endl;
     exit(EXIT_FAILURE);
}
bool isDeclared(string variable)
{
     // cout << pos << endl;
     if (withinLoop)
     {
          if (loopControlVariable.name == variable)
          {
               return true;
          }
     }
     if (withinLoop && disableLoop)
     {
          for (int i = 0; i < tempVariables.size(); i++)
          {
               if (tempVariables[i].type == INT && tempVariables[i].name == variable)
               {
                    return true;
               }
          }
     }
     else if (withinLoop && !disableLoop)
     {
          for (int i = 0; i < permanentVariables.size(); i++)
          {
               if (permanentVariables[i].type == INT && permanentVariables[i].name == variable)
               {
                    return true;
               }
          }
          for (int i = 0; i < variables.size(); i++)
          {
               if (variables[i].type == INT && variables[i].name == variable)
               {
                    return true;
               }
          }

          return false;
     }
     if (withinBlock && disable)
     {
          for (int i = 0; i < tempVariables.size(); i++)
          {
               if (tempVariables[i].type == INT && tempVariables[i].name == variable)
               {
                    return true;
               }
          }
     }
     else if (withinBlock && !disable)
     {
          for (int i = 0; i < permanentVariables.size(); i++)
          {
               if (permanentVariables[i].type == INT && permanentVariables[i].name == variable)
               {
                    return true;
               }
          }
     }
     for (int i = 0; i < variables.size(); i++)
     {
          // cout << tokens[i].name << endl;
          if (variables[i].type == INT && variables[i].name == variable)
          {
               return true;
          }
     }
     return false;
}
bool isSetValue(string variable)
{
     // cout<<pos<<endl;
     if (withinLoop)
     {
          if (loopControlVariable.name == variable)
          {
               return true;
          }
     }
     if (withinLoop && !disableLoop)
     {
          for (int i = 0; i < permanentVariables.size(); i++)
          {
               if (permanentVariables[i].type == INT && permanentVariables[i].name == variable && permanentVariables[i].value != "")
               {
                    return true;
               }
          }
          for (int i = 0; i < variables.size(); i++)
          {
               if (variables[i].type == INT && variables[i].name == variable && variables[i].value != "")
               {
                    return true;
               }
          }
          return false;
     }
     else if (withinLoop && disableLoop)
     {
          for (int i = 0; i < tempVariables.size(); i++)
          {
               if (tempVariables[i].type == INT && tempVariables[i].name == variable && tempVariables[i].value != "")
               {
                    return true;
               }
          }
     }
     if (withinBlock && disable)
     {
          for (int i = 0; i < tempVariables.size(); i++)
          {
               if (tempVariables[i].type == INT && tempVariables[i].name == variable && tempVariables[i].value != "")
               {
                    return true;
               }
          }
     }
     else if (withinBlock && !disable)
     {
          for (int i = 0; i < permanentVariables.size(); i++)
          {
               if (permanentVariables[i].type == INT && permanentVariables[i].name == variable && permanentVariables[i].value != "")
               {
                    return true;
               }
          }
     }
     for (int i = 0; i < variables.size(); i++)
     {
          // cout << tokens[i].name << endl;
          if (variables[i].type == INT && variables[i].name == variable && variables[i].value != "")
          {
               return true;
          }
     }

     return false;
}
int getVariableValue(string variable)
{
     // cout << "FOR: " << variable << endl;
     // cout << withinBlock << " " << disable << endl;
     // cout << withinLoop << " " << disableLoop << endl;
     if (withinLoop)
     {
          if (loopControlVariable.name == variable)
          {
               return stoi(loopControlVariable.value);
          }
     }
     if (withinLoop && !disableLoop)
     {
          for (int i = 0; i < permanentVariables.size(); i++)
          {
               if (permanentVariables[i].type == INT && permanentVariables[i].name == variable && permanentVariables[i].value != "")
               {
                    return stoi(permanentVariables[i].value);
               }
          }
          for (int i = 0; i < variables.size(); i++)
          {
               if (variables[i].type == INT && variables[i].name == variable)
               {
                    cerr << "---------Variable: " << variables[i].name << " " << variables[i].value << endl;
                    return stoi(variables[i].value);
               }
          }
          return false;
     }
     else if (withinLoop && disableLoop)
     {
          for (int i = 0; i < tempVariables.size(); i++)
          {
               if (tempVariables[i].type == INT && tempVariables[i].name == variable && tempVariables[i].value != "")
               {
                    return stoi(tempVariables[i].value);
               }
          }
     }
     if (withinBlock && disable)
     {
          for (int i = 0; i < tempVariables.size(); i++)
          {
               if (tempVariables[i].type == INT && tempVariables[i].name == variable && tempVariables[i].value != "")
               {
                    return stoi(tempVariables[i].value);
               }
          }
     }
     else if (withinBlock && !disable)
     {
          for (int i = 0; i < permanentVariables.size(); i++)
          {
               if (permanentVariables[i].type == INT && permanentVariables[i].name == variable && permanentVariables[i].value != "")
               {
                    return stoi(permanentVariables[i].value);
               }
          }
     }
     for (int i = 0; i < variables.size(); i++)
     {
          if (variables[i].type == INT && variables[i].name == variable)
          {
               return stoi(variables[i].value);
          }
     }
     return 0;
}
void setVariableValue(string variable, int value)
{
     // cerr<<"Variable: "<<variable<<" Value: "<<value<<endl;
     // cerr<<"----------------------------------\n ";
     cerr << withinLoop << " " << disableLoop << endl;

     if (withinBlock && disable)
     {
          for (int i = 0; i < tempVariables.size(); i++)
          {
               if (tempVariables[i].type == INT && tempVariables[i].name == variable)
               {
                    tempVariables[i].value = to_string(value);
                    return;
               }
          }
          tempVariables.push_back({INT, variable, to_string(value)});
          return;
     }
     else if (withinBlock && !disable)
     {
          for (int i = 0; i < permanentVariables.size(); i++)
          {
               if (permanentVariables[i].type == INT && permanentVariables[i].name == variable && permanentVariables[i].value != "")
               {
                    permanentVariables[i].value = to_string(value);
                    return;
               }
          }
          permanentVariables.push_back({INT, variable, to_string(value)});
          return;
     }
     if (withinLoop)
     {
          if (loopControlVariable.name == variable)
          {
               loopControlVariable.value = to_string(value);
               return;
          }
     }
     // cerr<<"----------------------------------\n ";
     if (withinLoop && !disableLoop)
     {
          // cerr<<"ENtered\n";
          for (int i = 0; i < permanentVariables.size(); i++)
          {
               cerr << permanentVariables[i].name << " " << permanentVariables[i].value << endl;
               if (permanentVariables[i].type == INT && permanentVariables[i].name == variable)
               {
                    permanentVariables[i].value = to_string(value);
                    cerr << "Value set: " << permanentVariables[i].name << " " << permanentVariables[i].value << endl;
                    return;
               }
          }
          for (int i = 0; i < variables.size(); i++)
          {
               if (variables[i].type == INT && variables[i].name == variable)
               {
                    variables[i].value = to_string(value);
                    return;
               }
          }
          // permanentVariables.push_back({INT, variable, to_string(value)});
          return;
     }
     // cerr<<"----------------------------------\n ";
     if (withinLoop && disableLoop)
     {
          for (int i = 0; i < tempVariables.size(); i++)
          {
               if (tempVariables[i].type == INT && tempVariables[i].name == variable)
               {
                    tempVariables[i].value = to_string(value);
                    return;
               }
          }
          tempVariables.push_back({INT, variable, to_string(value)});
          return;
     }
     for (int i = 0; i < variables.size(); i++)
     {
          if (variables[i].type == INT && variables[i].name == variable)
          {
               variables[i].value = to_string(value);
               return;
          }
     }
     error("Variable not declared");
}
void transferVariables()
{
     cerr << loopControlVariable.value << "-----------" << endl;
     cerr << loopControlVariable.name << "-----------" << endl;

     for (int i = 0; i < variables.size(); i++)
     {
          // cout << variables[i].name << " for trans " << variables[i].value << endl;
     }
     for (int i = 0; i < variables.size(); i++)
     {
          bool flag = false;
          cerr << "ghurtaseeeeeeee\n";
          if (loopControlVariable.name == variables[i].name && !loopVariableDefined)
          {
               variables[i].value = loopControlVariable.value;
               flag = true;
               continue;
          }
          for (int j = 0; j < permanentVariables.size(); j++)
          {
               if (permanentVariables[j].name == variables[i].name)
               {
                    // cout << "MILLLLLLSEEEEEEEEEEEEEE";
                    variables[i].value = permanentVariables[j].value;
                    flag = true;
                    break;
               }
          }
          if (flag)
               continue;
          // variables.push_back(permanentVariables[i]);
     }
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
               currentVariableType = INT;
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
               cerr << " herer------------------" << endl;
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
               // for(int i=0;i<variables.size();i++){
               //      cout<<variables[i].name<<" "<<variables[i].value<<endl;
               // }
               parseIf();
               if (oneConditionMatched)
               {
                    transferVariables();
                    oneConditionMatched = false;
               }
               permanentVariables.clear();
               disable = false;
               lastCondition = "";
               // cout<<"here"<<endl;
               currentToken = getNextToken();
          }
          else if (currentToken.type == KEYWORD && currentToken.name == "loop")
          {
               parseLoop();
               cerr << "Loop done\n";
               withinLoop = false;
               loopVariableDefined = false;
               loopConditionMatched = false;
               loopTraversOneTime = false;
               loopControlVariable = {INT, "", ""};
               loopConditionTokens.clear();
               loopExpressionTokens.clear();

               currentToken = getNextToken();
          }
          else
          {
               cerr << currentToken.name << endl;
               error("Expected 'int', identifier or 'print'");
          }
     }
}
void parseLoop()
{
     loopVariableDefined = false;
     withinLoop = true;
     currentToken = getNextToken();

     Token toAssign;
     if (currentToken.type == KEYWORD && currentToken.name == "int")
     {
          loopVariableDefined = true;
          currentVariableType = INT;
          currentToken = getNextToken();
          if (currentToken.type == IDENTIFIER)
          {
               toAssign = currentToken;
               loopControlVariable.type = INT;
               loopControlVariable.name = currentToken.name;
               loopControlVariable.value = "";
          }
          else
          {
               error("Expected identifier after 'int'");
          }
     }
     else if (currentToken.type == IDENTIFIER)
     {
          toAssign = currentToken;
          withinLoop = false;
          if (!isDeclared(currentToken.name))
          {
               error("Variable is not defined");
          }
          withinLoop = true;
          if (isSetValue(currentToken.name))
          {
               int value = getVariableValue(currentToken.name);
               loopControlVariable.type = INT;
               loopControlVariable.name = currentToken.name;
               loopControlVariable.value = to_string(value);
          }
          else
          {
               loopControlVariable.type = INT;
               loopControlVariable.name = currentToken.name;
               loopControlVariable.value = "";
          }
     }
     else
     {
          error("Expected 'int' or IDENTIFIER after 'loop'");
     }
     currentToken = getNextToken();
     if (currentToken.type == ASSIGN)
     {
          int value = parseExpression();
          setVariableValue(toAssign.name, value);
     }
     else
     {
          error("Expected assignment after loop variable");
     }
     // cerr << "now token: " << currentToken.name << endl;
     if (currentToken.type == COLON)
     {
          currentToken = getNextToken();
          while (currentToken.type != COLON)
          {
               loopConditionTokens.push_back(currentToken);
               if (currentToken.type != IDENTIFIER && currentToken.type != NUMBER && currentToken.type != PLUS && currentToken.type != MINUS && currentToken.type != MULTIPLY && currentToken.type != DEVIDE && currentToken.type != POWER && currentToken.type != LPAREN && currentToken.type != RPAREN && currentToken.type != EQUAL && currentToken.type != NOT_EQUAL && currentToken.type != LESS_THAN && currentToken.type != GREATER_THAN && currentToken.type != LESS_THAN_EQUAL && currentToken.type != GREATER_THAN_EQUAL && currentToken.type != COLON)
               {
                    error("Something wrong in loop condition");
               }
               // cout << "Loop condition: " << currentToken.name << endl;
               currentToken = getNextToken();
          }
          loopConditionTokens.push_back(currentToken);
          // for (int i = 0; i < loopConditionTokens.size(); i++)
          // {
          //      cout << loopConditionTokens[i].name << endl;
          // }
     }
     else
     {
          error("Expected ':' after loop variable");
     }
     currentToken = getNextToken();
     while (currentToken.type != COLON)
     {
          loopExpressionTokens.push_back(currentToken);
          if (currentToken.type != IDENTIFIER && currentToken.type != NUMBER && currentToken.type != PLUS && currentToken.type != MINUS && currentToken.type != MULTIPLY && currentToken.type != DEVIDE && currentToken.type != POWER && currentToken.type != LPAREN && currentToken.type != RPAREN && currentToken.type != ASSIGN && currentToken.type != COLON)
          {
               error("Something wrong in loop condition");
          }
          // cout << "Loop condition: " << currentToken.name << endl;
          currentToken = getNextToken();
     }
     loopExpressionTokens.push_back(currentToken);
     // for (int i = 0; i < loopExpressionTokens.size(); i++)
     // {
     //      cout << loopExpressionTokens[i].name << endl;
     // }
     startLoopTokenIndex = pos;
     con = 0;
     checkingCondition = true;
     cerr << "Start Loop: " << pos << endl;
     while (true)
     {
          if (extractCondition())
          {
               // loopTraversOneTime = false;
          }
          else if (!loopTraversOneTime)
          {
               // cout<<"loop manually started\n";
               loopTraversOneTime = true;
               disableLoop = true;
          }
          else
          {
               break;
          }
          checkingCondition = false;
          pos = startLoopTokenIndex;
          currentToken = getNextToken();
          cerr << "Start nested Loop: " << pos << endl;
          cerr << " token: " << currentToken.name << endl;
          while (currentToken.name != "endloop")
          {
               if (currentToken.type == KEYWORD && currentToken.name == "int")
               {
                    parseDeclarations();
                    currentToken = getNextToken();
                    for (int i = 0; i < permanentVariables.size(); i++)
                    {
                         cerr << permanentVariables[i].name << " " << permanentVariables[i].value << endl;
                    }
               }
               else if (currentToken.type == IDENTIFIER)
               {
                    // cerr<<"Here\n";
                    parseStatement();
                    currentToken = getNextToken();
               }
               else if (currentToken.type == KEYWORD && currentToken.name == "print")
               {
                    parsePrint();
                    // cout << "here" << endl;
                    // cout << currentToken.name << endl;
                    // cout<<"here"<<endl;
                    currentToken = getNextToken();
                    // cout << currentToken.name << endl;
               }
               else if (currentToken.type == KEYWORD && currentToken.name == "scan")
               {
                    parseScan();
                    // cout<<"here"<<endl;
                    currentToken = getNextToken();
               }
               else if (currentToken.type == KEYWORD && currentToken.name == "if")
               {
                    cerr << "here" << endl;
                    parseIf();
                    // cout<<"here"<<endl;
                    if (oneConditionMatched)
                    {
                         transferVariables();
                         oneConditionMatched = false;
                    }
                    disable = false;
                    lastCondition = "";
                    currentToken = getNextToken();
               }
               else if (currentToken.type == KEYWORD && currentToken.name == "break")
               {
                    disableLoop = true;
                    for (int i = 0; i < permanentVariables.size(); i++)
                    {
                         tempVariables.push_back(permanentVariables[i]);
                    }
                    cerr << "Break Loop\n";
                    breakLoop = true;
                    currentToken = getNextToken();
                    if (currentToken.type == SEMICOLON)
                    {
                         currentToken = getNextToken();
                    }
                    else
                    {
                         error("Expected ';' after 'break'");
                    }
               }
               else
               {
                    error("Expected 'int', identifier,'scan' or 'print'");
               }
          }
          endLoopTokenIndex = pos;
          cerr << "end nested Loop: " << pos << endl;
          loopTraversOneTime = true;
          checkingExpression = true;
          expr = 0;
          currentToken = getNextToken();
          if (currentToken.type == IDENTIFIER)
          {
               toAssign = currentToken;
               currentToken = getNextToken();
               if (currentToken.type == ASSIGN)
               {
                    int value = parseExpression();
                    setVariableValue(toAssign.name, value);
               }
               else
               {
                    error("Expected assignment after loop variable");
               }
          }
          else
          {
               error("Expected identifier after 'endloop'");
          }
          con = 0;
          checkingExpression = false;
          checkingCondition = true;
          transferVariables();
          permanentVariables.clear();
          if (breakLoop)
          {
               break;
          }
          // for (int i = 0; i < variables.size(); i++)
          // {
          //      cout << variables[i].name << " for inter " << variables[i].value << endl;
          // }
     }
     // cout << "End Loop\n";

     transferVariables();
     // for (int i = 0; i < variables.size(); i++)
     // {
     //      cout << variables[i].name << " for var " << variables[i].value << endl;
     // }
     loopVariableDefined = false;
     cerr << "End Loop: " << pos << endl;
     breakLoop = false;
     withinLoop = false;
     disableLoop = false;
     withinBlock = false;
     disable = false;
     pos = endLoopTokenIndex;
     breakLoop = false;
}
void parseIf()
{
     withinBlock = true;
     while (currentToken.name != "endif")
     {
          disable = false;
          tempVariables.clear();
          if (currentToken.name == "if" && lastCondition == "")
          {
               lastCondition = "if";
               cerr << "Here2\n";
               onlyCheckIf();
          }
          else if (currentToken.name == "elif" && (lastCondition == "if" || lastCondition == "elif"))
          {
               lastCondition = "elif";
               onlyCheckIf();
          }
          else if (currentToken.name == "else" && (lastCondition == "if" || lastCondition == "elif"))
          {
               // cout << "Okay\n";
               // cout << "Checking: " << getVariableValue("x") << endl;
               currentToken = getNextToken();
               lastCondition = "else";
               onlyCheckIf();
               continue;
          }
          else if (currentToken.name == "end")
          {
               break;
          }
          else
          {
               currentToken = getNextToken();
          }
          // currentToken = getNextToken();
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
          // cerr << "Operation: " << operation.name << endl;
     }
     else
     {
          error("something wrong in condition");
     }
     rightValue = parseExpression();
     checkingCondition = false;
     bool flag = true;
     if (!checkCondition(leftValue, operation, rightValue) || oneConditionMatched)
     {
          if (withinBlock)
               disable = true;
          else if (withinLoop)
               disableLoop = true;
          flag = false;
     }
     if (!disable && withinBlock)
     {
          oneConditionMatched = true;
     }
     cerr << "condition: " << flag << endl;

     return flag;
}
void onlyCheckIf()
{
     // cout << lastCondition << endl;
     if (lastCondition != "else")
     {
          extractCondition();
     }
     else if (lastCondition == "else" && !oneConditionMatched)
     {
          disable = false;
          oneConditionMatched = true;
     }
     else if (lastCondition == "else" && oneConditionMatched)
     {
          disable = true;
     }

     if (currentToken.type == COLON)
     {
          // cout << "COLON\n";
          currentToken = getNextToken();
     }
     else
     {
          error("Expected ':' to start if-elif-else block");
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
               // cerr<<"Here\n";
               parseStatement();
               currentToken = getNextToken();
          }
          else if (currentToken.type == KEYWORD && currentToken.name == "print")
          {
               parsePrint();
               // cout << "here" << endl;
               // cout << currentToken.name << endl;
               // cout<<"here"<<endl;
               currentToken = getNextToken();
               // cout << currentToken.name << endl;
          }
          else if (currentToken.type == KEYWORD && currentToken.name == "scan")
          {
               parseScan();
               // cout<<"here"<<endl;
               currentToken = getNextToken();
          }
          else if (withinLoop && !disable && currentToken.type == KEYWORD && currentToken.name == "break")
          {
               disableLoop = true;
               disable = true;
               transferVariables();
               for (int i = 0; i < permanentVariables.size(); i++)
               {
                    tempVariables.push_back(permanentVariables[i]);
               }
               cerr << "Break Loop from IF CONDITION-----\n";
               breakLoop = true;
               currentToken = getNextToken();
               if (currentToken.type == SEMICOLON)
               {
                    currentToken = getNextToken();
               }
               else
               {
                    error("Expected ';' after 'break'");
               }
          }
          else if (withinLoop && disable && currentToken.type == KEYWORD && currentToken.name == "break")
          {
               currentToken = getNextToken();
               if (currentToken.type == SEMICOLON)
               {
                    currentToken = getNextToken();
               }
               else
               {
                    error("Expected ';' after 'break'");
               }
               continue;
          }
          // else if (currentToken.type == KEYWORD && currentToken.name == "if")
          // {
          //      parseIf();
          //      // cout<<"here"<<endl;
          //      currentToken = getNextToken();
          // }
          else
          {
               error("Expected 'int', identifier,'scan' or 'print'");
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
                    error("Variable redefined");
               }
               if (withinBlock && disable)
               {
                    tempVariables.push_back({INT, currentToken.name, ""});
               }
               else if (withinBlock)
               {
                    permanentVariables.push_back({INT, currentToken.name, ""});
               }
               else if (withinLoop && disableLoop)
               {
                    tempVariables.push_back({INT, currentToken.name, ""});
               }
               else if (withinLoop && !disableLoop)
               {
                    permanentVariables.push_back({INT, currentToken.name, ""});
               }
               else
               {
                    variables.push_back({INT, currentToken.name, ""});
               }
               continue;
          }
          else if (currentToken.type == ASSIGN && previousToken.type == IDENTIFIER)
          {
               // currentToken = getNextToken();
               Token toAssign = previousToken;
               int value = parseExpression();
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
          // cout << "YES\n";
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

               // cout << withinBlock << disable << endl;
               // cout << withinLoop << disableLoop << endl;
               if (previousToken.type == IDENTIFIER)
               {
                    if (!isDeclared(previousToken.name))
                    {
                         error("Variable used before defined");
                    }
                    if (!isSetValue(previousToken.name))
                    {
                         error("NULL value is used in print statement");
                    }

                    int value = getVariableValue(previousToken.name);
                    // cout << "Name: " << previousToken.name << " Value: " << value << endl;
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
                    error("Something in print statement");
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
               error("Something wrong in print statement");
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
                    error("Variable is not defined");
               }
               string value = scanInput();
               if (!isInteger(value))
               {
                    error("Input is not an integer");
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
               error("Something wrong in scan statement");
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
                         error("Variable used before defined");
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
               else if (withinLoop && currentToken.type == COLON)
               {
                    break;
               }
               else if (checkingCondition && (currentToken.type == EQUAL || currentToken.type == NOT_EQUAL || currentToken.type == LESS_THAN || currentToken.type == GREATER_THAN || currentToken.type == LESS_THAN_EQUAL || currentToken.type == GREATER_THAN_EQUAL || currentToken.type == COLON))
               {
                    break;
               }
               else
               {
                    error("Something wrong in expression");
               }
          }
     }
     else
     {
          error("Expected identifier or number in expression");
     }
     int value = converterExpression();
     while (!expression.empty())
     {
          expression.pop();
     }
     cerr << value << "Expression done\n";
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
                    error("Variable used before defined");
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
               error("Something wrong in expression");
          }
     }
}
