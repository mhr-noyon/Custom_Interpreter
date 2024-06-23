
enum TokenType
{
     IDENTIFIER,
     NUMBER,
     COLON,
     SEMICOLON,
     COMMA,
     QUOTE,
     ASSIGN,
     POWER,
     MULTIPLY,
     DEVIDE,
     PLUS,
     MINUS,
     LPAREN,
     RPAREN,
     KEYWORD,
     EQUAL,
     NOT_EQUAL,
     GREATER_THAN,
     LESS_THAN,
     GREATER_THAN_EQUAL,
     LESS_THAN_EQUAL,
     AND,
     OR,
     END
};
// Token structure
struct Token
{
     TokenType type;
     string name;
};

enum VariableType
{
     INT,
     STRING
};
struct Variable
{
     VariableType type;
     string name;
     string value;
};
// Global variables
vector<Token> tokens;
vector<int> codeLine;
vector<Token> loopConditionTokens;
vector<Token> loopExpressionTokens;
vector<Variable> variables;
vector<Variable> tempVariables;
vector<Variable> permanentVariables;
Variable loopControlVariable;

queue<Token> expression;
// size_t pos = 0;
VariableType currentVariableType;
Token currentToken;
Token previousToken;
char buffer[100], currentChar;
bool multiLineCmnt = false;
bool gotQuote = false;
int typeFlag;

bool isKeyword(char *str)
{
     char keywords[14][10] = {"int", "string", "loop", "break", "continue", "main", "if", "elif", "else", "print", "scan", "endif", "endloop", "endmain"};

     for (int i = 0; i < 14; i++)
     {
          if (strcmp(keywords[i], str) == 0)
          {
               if (i == 13)
                    tokens.push_back({END, ""});
               else
                    tokens.push_back({KEYWORD, str});
               return true;
          }
     }
     return false;
}
bool isSpecialSymbol(char c)
{
     switch (currentChar)
     {
     case '+':
          tokens.push_back({PLUS, "+"});
          return true;
     case '-':
          tokens.push_back({MINUS, "-"});
          return true;
     case '*':
          tokens.push_back({MULTIPLY, "*"});
          return true;
     case '/':
          tokens.push_back({DEVIDE, "/"});
          return true;
     case '^':
          tokens.push_back({POWER, "^"});
          return true;
     case '(':
          tokens.push_back({LPAREN, "("});
          return true;
     case ')':
          tokens.push_back({RPAREN, ")"});
          return true;
     case '=':
          tokens.push_back({ASSIGN, "="});
          return true;
     case ';':
          tokens.push_back({SEMICOLON, ";"});
          return true;
     case ',':
          tokens.push_back({COMMA, ","});
          return true;
     case ':':
          tokens.push_back({COLON, ":"});
          return true;
     default:
          return false;
     }
     // char operators[] = "+-*/%=><!&|^";
}

void setTokens(char *buffer, int i)
{
     buffer[i] = '\0';
     if (gotQuote)
     {
          tokens.push_back({QUOTE, buffer});
     }
     else if (typeFlag == 1)
     {
          if (!isKeyword(buffer))
          {
               tokens.push_back({IDENTIFIER, buffer});
          }
     }
     else if (typeFlag == 2)
     {
          tokens.push_back({NUMBER, buffer});
     }
}
void identifyTokens(char *program)
{
     int i = 0;
     typeFlag = 0;

     for (int j = 0; j < strlen(program); j++)
     {
          if (j < strlen(program) - 1 && !multiLineCmnt && program[j] == '/' && program[j + 1] == '/')
          {
               setTokens(buffer, i);
               typeFlag = 0;
               j++;
               return;
          }
          if (j < strlen(program) - 1 && program[j] == '/' && program[j + 1] == '*')
          {
               setTokens(buffer, i);
               i = 0;
               typeFlag = 0;
               multiLineCmnt = true;
               continue;
          }
          if (j < strlen(program) - 1 && multiLineCmnt && program[j] == '*' && program[j + 1] == '/')
          {
               multiLineCmnt = false;
               j++;
               continue;
          }
          if (multiLineCmnt)
               continue;

          if (gotQuote && program[j] != '"')
          {
               buffer[i++] = program[j];
               continue;
          }
          currentChar = program[j];

          if (isalnum(currentChar) || currentChar == '_')
          {
               if (!typeFlag)
               {
                    if (isdigit(currentChar))
                         typeFlag = 2; // constant
                    else
                         typeFlag = 1; // variable
               }
               buffer[i++] = currentChar;
          }
          else
          {
               setTokens(buffer, i);
               i = 0;
               typeFlag = 0;
               if (j + 1 < strlen(program) && currentChar == '=' && program[j + 1] == '=')
               {
                    tokens.push_back({EQUAL, "=="});
                    j++;
                    continue;
               }
               else if (j + 1 < strlen(program) && currentChar == '!' && program[j + 1] == '=')
               {
                    tokens.push_back({NOT_EQUAL, "!="});
                    j++;
                    continue;
               }
               else if (j + 1 < strlen(program) && currentChar == '>' && program[j + 1] == '=')
               {
                    tokens.push_back({GREATER_THAN_EQUAL, ">="});
                    j++;
                    continue;
               }
               else if (j + 1 < strlen(program) && currentChar == '<' && program[j + 1] == '=')
               {
                    tokens.push_back({LESS_THAN_EQUAL, "<="});
                    j++;
                    continue;
               }
               else if (j + 1 < strlen(program) && currentChar == '>' && program[j + 1] != '=')
               {
                    tokens.push_back({GREATER_THAN, ">"});
                    continue;
               }
               else if (j + 1 < strlen(program) && currentChar == '<' && program[j + 1] != '=')
               {
                    tokens.push_back({LESS_THAN, "<"});
                    continue;
               }
               else if (j + 1 < strlen(program) && currentChar == '&' && program[j + 1] == '&')
               {
                    tokens.push_back({AND, "&&"});
                    j++;
                    continue;
               }
               else if (j + 1 < strlen(program) && currentChar == '|' && program[j + 1] == '|')
               {
                    tokens.push_back({OR, "||"});
                    j++;
                    continue;
               }
               isSpecialSymbol(currentChar); // if space then auto skipped
               if (currentChar == '"')
               {
                    if (gotQuote)
                    {
                         gotQuote = false;
                    }
                    else
                    {
                         gotQuote = true;
                    }
               }
          }
     }
}
void printTokens()
{
     cerr << "\n\nTokens: " << endl;
     int i = 0;
     for (Token &token : tokens)
     {
          string type;
          switch (token.type)
          {
          case IDENTIFIER:
               type = "IDENTIFIER";
               break;
          case NUMBER:
               type = "NUMBER";
               break;
          case COLON:
               type = "COLON";
               break;
          case SEMICOLON:
               type = "SEMICOLON";
               break;
          case COMMA:
               type = "COMMA";
               break;
          case QUOTE:
               type = "QUOTE";
               break;
          case ASSIGN:
               type = "ASSIGN";
               break;
          case MULTIPLY:
               type = "MULTIPLY";
               break;
          case DEVIDE:
               type = "DEVIDE";
               break;
          case PLUS:
               type = "PLUS";
               break;
          case MINUS:
               type = "MINUS";
               break;
          case POWER:
               type = "POWER";
               break;
          case LPAREN:
               type = "LPAREN";
               break;
          case RPAREN:
               type = "RPAREN";
               break;
          case KEYWORD:
               type = "KEYWORD";
               break;
          case EQUAL:
               type = "EQUAL";
               break;
          case NOT_EQUAL:
               type = "NOT_EQUAL";
               break;
          case GREATER_THAN:
               type = "GREATER_THAN";
               break;
          case LESS_THAN:
               type = "LESS_THAN";
               break;
          case GREATER_THAN_EQUAL:
               type = "GREATER_THAN_EQUAL";
               break;
          case LESS_THAN_EQUAL:
               type = "LESS_THAN_EQUAL";
               break;
          case AND:
               type = "AND";
               break;
          case OR:
               type = "OR";
               break;
          case END:
               type = "END";
               break;
          default:
               type = "UNKNOWN";
               break;
          }
          cerr << i << "th Token: " << type << ", " << token.name << endl;
          i++;
     }
     cerr << "\n\n";
}
int pos = 0;
int con = 0;
int expr = 0;
Token getNextToken()
{
     if (withinLoop && checkingCondition && !withinBlock)
     {
          cerr << "token number: " << con << " -> " << loopConditionTokens[con].name << " is moved." << endl;
          return loopConditionTokens[con++];
     }
     if (withinLoop && checkingExpression && !withinBlock)
     {
          cerr << "token number: " << expr << " -> " << loopExpressionTokens[expr].name << " is moved." << endl;
          return loopExpressionTokens[expr++];
     }
     // if (pos < tokens.size())
     // {
     cerr << "token number: " << pos << " -> " << tokens[pos].name << " is moved." << endl;
     return tokens[pos++];
     // }
     // else
     // {
     //      return {END, ""};
     // }
}