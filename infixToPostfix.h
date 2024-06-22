queue<Token> postfixExpression;
int converterExpression();
bool curGreaterThanPrev(Token a, Token b);
int calc();
bool curGreaterThanPrev(Token a, Token b)
{
     if ((a.type == PLUS || a.type == MINUS) && (b.type == MULTIPLY || b.type == DEVIDE))
          return true;
     if ((a.type == PLUS || a.type == MINUS || a.type == MULTIPLY || a.type == DEVIDE) && b.type == POWER)
          return true;
     if (a.type == LPAREN)
          return true;
     return false;
}

int converterExpression()
{
     if (withinBlock && disable)
     {
          // cout << "here11111\n";
          return 1;
     }
     if (withinLoop && disableLoop)
     {
          // cout << "here2222\n";
          return 1;
     }
     if (breakLoop)
     {
          // cout << "here3\n";
          return 1;
     }
     stack<Token> stk;
     while (!expression.empty())
     {
          // cout << expression.front().name << endl;
          Token cur = expression.front();
          expression.pop();

          if (cur.type == IDENTIFIER || cur.type == NUMBER)
          {
               postfixExpression.push(cur);
          }
          else if (cur.type == RPAREN)
          {
               while (stk.top().type != LPAREN)
               {
                    postfixExpression.push(stk.top());
                    stk.pop();
               }
               stk.pop();
          }
          else if (cur.type == LPAREN)
          {
               stk.push(cur);
          }
          else if (stk.empty() || curGreaterThanPrev(stk.top(), cur))
          {
               stk.push(cur);
          }
          else
          {
               while (!curGreaterThanPrev(stk.top(), cur))
               {
                    postfixExpression.push(stk.top());
                    stk.pop();
                    if (stk.empty())
                         break;
               }
               stk.push(cur);
          }
     }
     while (!stk.empty())
     {
          postfixExpression.push(stk.top());
          stk.pop();
     }
     // cerr << "\n\n";
     int value = calc();
     cerr << "The value of the expression is : " << value << endl;
     return value;
     // cout<<"The postfix expression is : ";
     // while (!postfixExpression.empty())
     // {
     //      cout << postfixExpression.front().name << " ";
     //      postfixExpression.pop();
     // }
}
int calc()
{

     stack<int> operandStack;
     // for (auto it : postfixExpression)
     while (!postfixExpression.empty())
     {
          Token it = postfixExpression.front();
          postfixExpression.pop();
          if (it.type == NUMBER)
          {
               int val = stoi(it.name);
               operandStack.push(val);
          }
          else if (it.type == IDENTIFIER)
          {
               if (!isDeclared(it.name))
               {
                    // cout << "Variable " << it.name << " is not declared\n";
                    error("Variable is used before declaration");
               }
               if (!isSetValue(it.name))
               {
                    // cout<<"Variable "<<it.name<<" is not set\n";
                    error("NULL value is used in expression");
               }
               operandStack.push(getVariableValue(it.name));
          }
          else
          {
               int b = operandStack.top();
               operandStack.pop();
               int a = operandStack.top();
               operandStack.pop();
               if (it.type == PLUS)
               {
                    operandStack.push(a + b);
               }
               else if (it.type == MINUS)
               {
                    operandStack.push(a - b);
               }
               else if (it.type == MULTIPLY)
               {
                    operandStack.push(a * b);
               }
               else if (it.type == DEVIDE)
               {
                    if (b == 0)
                    {
                         error("Division by zero");
                    }
                    operandStack.push(a / b);
               }
               else if (it.type == POWER)
               {
                    operandStack.push(pow(a, b));
               }
          }
     }
     // cout << operandStack.top() << endl;
     int val = operandStack.top();
     operandStack.pop();
     return val;
}
// int main()
// {
//      string s = "5+2*3-2";
//      converter(s);
//      cout << postfixExpression << endl;
//      cout << "The result is : ";
//      calc();
//      return 0;
// }