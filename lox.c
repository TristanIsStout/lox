#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MAX_SOURCE_CHARS 10000
#define MAX_TOKEN_LITERAL_CHARS 100

int main(int argCount, char* args[]) {
  if (argCount != 2) {
    // validate command line args
    printf("Usage: lox [script.lox]\n");
    exit(1);
  } 


  // open the argument file
  printf("opening the file\n");
  FILE* sourceFile = fopen(args[1], "r");
  if (sourceFile == NULL) {
    printf("Error opening the file %s\n", args[1]);
    exit(1);
  }

  // read the source file into the source string
  printf("reading the file\n");

  // create a source string of all nulls at the max size
  char* sourceString = (char*) malloc(sizeof(char) * MAX_SOURCE_CHARS);
  memset(sourceString, '\0', MAX_SOURCE_CHARS);

  // loop through the file and add characters to the source string
  int charCount = 0;
  char indexChar = fgetc(sourceFile);
  while (indexChar != EOF && (charCount + 1) < MAX_SOURCE_CHARS) {
    *(sourceString + charCount) = indexChar;

    charCount++;
    indexChar = fgetc(sourceFile);
  }

  // close the file
  printf("closing the file\n");
  fclose(sourceFile);


  printf("Tokenizing the source string\n");


  enum TokenType {
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,
    IDENTIFIER,
    STRING,
    NUMBER,
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE
  };

  struct Token {
    enum TokenType tokenType;
    int startIndex;
    int endIndex;
    int lineNumber;
    char literal[MAX_TOKEN_LITERAL_CHARS];
  };

  int tokenIndex = 0;
  struct Token tokens[MAX_SOURCE_CHARS];

  
  int lineNumber = 1;
  int sourceIndex = 0;
  indexChar = *sourceString;
  bool hasParseError = false;
  while (indexChar != '\0') {
    if (indexChar == '(') {
      tokens[tokenIndex].tokenType = LEFT_PAREN;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == ')')  {
      tokens[tokenIndex].tokenType = RIGHT_PAREN;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar ==  '{') {
      tokens[tokenIndex].tokenType = LEFT_BRACE;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '}') {
      tokens[tokenIndex].tokenType = RIGHT_BRACE;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == ',') {
      tokens[tokenIndex].tokenType = COMMA;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '.') {
      tokens[tokenIndex].tokenType = DOT;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '-') {
      tokens[tokenIndex].tokenType = MINUS;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '+') {
      tokens[tokenIndex].tokenType = PLUS;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == ';') {
      tokens[tokenIndex].tokenType = SEMICOLON;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '*') {
      tokens[tokenIndex].tokenType = STAR;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '!' && *(sourceString + sourceIndex + 1) == '=') {
      tokens[tokenIndex].tokenType = BANG_EQUAL;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex + 1;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;
      // todo tks do this guy
      sourceIndex++;

    } else if (indexChar == '!' && *(sourceString + sourceIndex + 1) != '=') {
      tokens[tokenIndex].tokenType = BANG;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '<' && *(sourceString + sourceIndex + 1) == '=') {
      tokens[tokenIndex].tokenType = LESS_EQUAL;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex + 1;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;
      // todo tks do this guy
      sourceIndex++;

    } else if (indexChar == '<' && *(sourceString + sourceIndex + 1) != '=') {
      tokens[tokenIndex].tokenType = LESS;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '>' && *(sourceString + sourceIndex + 1) == '=') {
      tokens[tokenIndex].tokenType = GREATER_EQUAL;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex + 1;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;
      // todo tks do this guy
      sourceIndex++;

    } else if (indexChar == '>' && *(sourceString + sourceIndex + 1) != '=') {
      tokens[tokenIndex].tokenType = GREATER;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '=' && *(sourceString + sourceIndex + 1) == '=') {
      tokens[tokenIndex].tokenType = EQUAL_EQUAL;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex + 1;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;
      // todo tks do this guy
      sourceIndex++;

    } else if (indexChar == '=' && *(sourceString + sourceIndex + 1) != '=') {
      tokens[tokenIndex].tokenType = EQUAL;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].endIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokenIndex++;

    } else if (indexChar == '/') {
      while (indexChar != '\n') {
          sourceIndex++;
          indexChar = *(sourceString + sourceIndex);
      }
      lineNumber++;

    } else if (indexChar == ' ' || indexChar == '\t' || indexChar == '\r') {
      // no op

    } else if (indexChar == '\n') {
      lineNumber++;

    } else if (indexChar == '"') {
      tokens[tokenIndex].tokenType = STRING;
      tokens[tokenIndex].lineNumber = lineNumber;
      tokens[tokenIndex].startIndex = sourceIndex;

      indexChar = *(sourceString + sourceIndex + 1);
      while (indexChar != '"') {
        if (indexChar == '\n') {
          lineNumber++;
        }
        sourceIndex++;
        indexChar = *(sourceString + sourceIndex);
      }
      tokens[tokenIndex].endIndex = sourceIndex;

      memcpy(
          tokens[tokenIndex].literal,
          (sourceString + tokens[tokenIndex].startIndex + 1),
          (tokens[tokenIndex].endIndex - tokens[tokenIndex].startIndex) - 2);

      tokenIndex++;

    } else if (indexChar >= '0' && indexChar <= '9') {
      tokens[tokenIndex].tokenType = NUMBER;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;

      char nextChar = *(sourceString + sourceIndex + 1);
      while (nextChar >= '0' && nextChar <= '9') {
        sourceIndex++;
        indexChar = *(sourceString + sourceIndex);
        nextChar = *(sourceString + sourceIndex + 1);
      }
      if (nextChar == '.') {
        sourceIndex++;
        char nextChar = *(sourceString + sourceIndex + 1);
        if (!(nextChar >= '0' && nextChar <= '9')) {
          printf("Number has a dangling decimal point on line %d\n", lineNumber);
          hasParseError = true;
        } else {
          while (nextChar >= '0' && nextChar <= '9') {
            sourceIndex++;
            indexChar = *(sourceString + sourceIndex);
            nextChar = *(sourceString + sourceIndex + 1);
          }
        }

      }
      tokens[tokenIndex].endIndex = sourceIndex;
      memcpy(
          tokens[tokenIndex].literal,
          sourceString + tokens[tokenIndex].startIndex,
          (tokens[tokenIndex].endIndex - tokens[tokenIndex].startIndex) + 1);

      tokenIndex++;

    } else if ((indexChar >= 'a' && indexChar <= 'z') || (indexChar >= 'A' && indexChar <= 'Z')) {
      // this is either an identifier or a keyword
      tokens[tokenIndex].lineNumber = lineNumber;
      tokens[tokenIndex].startIndex = sourceIndex;

      char nextChar = *(sourceString + sourceIndex + 1);
      while ((nextChar >= 'a' && nextChar <= 'z') 
          || (nextChar >= 'A' && nextChar <= 'Z') 
          || (nextChar >= '0' && nextChar <= '9')
          || (nextChar == '_')) {
        sourceIndex++;
        indexChar = *(sourceString + sourceIndex);
        nextChar = *(sourceString + sourceIndex + 1);
      }
      tokens[tokenIndex].endIndex = sourceIndex;

      memcpy(
          tokens[tokenIndex].literal,
          sourceString + tokens[tokenIndex].startIndex,
          (tokens[tokenIndex].endIndex - tokens[tokenIndex].startIndex) + 1);

      if (strcmp("and", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = AND;

      } else if (strcmp("class", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = CLASS;

      } else if (strcmp("else", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = ELSE;

      } else if (strcmp("false", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = FALSE;

      } else if (strcmp("for", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = FOR;

      } else if (strcmp("fun", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = FUN;

      } else if (strcmp("if", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = IF;

      } else if (strcmp("nil", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = NIL;

      } else if (strcmp("or", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = OR;

      } else if (strcmp("print", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = PRINT;

      } else if (strcmp("return", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = RETURN;

      } else if (strcmp("super", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = SUPER;

      } else if (strcmp("this", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = THIS;

      } else if (strcmp("true", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = TRUE;

      } else if (strcmp("var", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = VAR;

      } else if (strcmp("while", tokens[tokenIndex].literal) == 0) {
        tokens[tokenIndex].tokenType = WHILE;

      } else {
        tokens[tokenIndex].tokenType = IDENTIFIER;
      }

      sourceIndex++;
      tokenIndex++;

    } else {
      printf("Unexpected character '%c' on line %d.\n", indexChar, lineNumber + 1);
      hasParseError = true;
    }


    sourceIndex++;
    indexChar = *(sourceString + sourceIndex);
  }

  if (false) {
    printf("printing the tokens...\n");

    for (int index = 0; index < tokenIndex; index++) {
      char* typeString;

      if (tokens[index].tokenType == LEFT_PAREN) typeString = "LEFT_PAREN";
      else if (tokens[index].tokenType == RIGHT_PAREN) typeString = "RIGHT_PAREN";
      else if (tokens[index].tokenType == LEFT_BRACE) typeString = "LEFT_BRACE";
      else if (tokens[index].tokenType == RIGHT_BRACE) typeString = "RIGHT_BRACE";
      else if (tokens[index].tokenType == COMMA) typeString = "COMMA";
      else if (tokens[index].tokenType == DOT) typeString = "DOT";
      else if (tokens[index].tokenType == MINUS) typeString = "MINUS";
      else if (tokens[index].tokenType == PLUS) typeString = "PLUS";
      else if (tokens[index].tokenType == SEMICOLON) typeString = "SEMICOLON";
      else if (tokens[index].tokenType == SLASH) typeString = "SLASH";
      else if (tokens[index].tokenType == STAR) typeString = "STAR";
      else if (tokens[index].tokenType == BANG) typeString = "BANG";
      else if (tokens[index].tokenType == BANG_EQUAL) typeString = "BANG_EQUAL";
      else if (tokens[index].tokenType == EQUAL) typeString = "EQUAL";
      else if (tokens[index].tokenType == EQUAL_EQUAL) typeString = "EQUAL_EQUAL";
      else if (tokens[index].tokenType == GREATER) typeString = "GREATER";
      else if (tokens[index].tokenType == GREATER_EQUAL) typeString = "GREATER_EQUAL";
      else if (tokens[index].tokenType == LESS) typeString = "LESS";
      else if (tokens[index].tokenType == LESS_EQUAL) typeString = "LESS_EQUAL";
      else if (tokens[index].tokenType == IDENTIFIER) typeString = "IDENTIFIER";
      else if (tokens[index].tokenType == STRING) typeString = "STRING";
      else if (tokens[index].tokenType == NUMBER) typeString = "NUMBER";
      else if (tokens[index].tokenType == AND) typeString = "AND";
      else if (tokens[index].tokenType == CLASS) typeString = "CLASS";
      else if (tokens[index].tokenType == ELSE) typeString = "ELSE";
      else if (tokens[index].tokenType == FALSE) typeString = "FALSE";
      else if (tokens[index].tokenType == FUN) typeString = "FUN";
      else if (tokens[index].tokenType == FOR) typeString = "FOR";
      else if (tokens[index].tokenType == IF) typeString = "IF";
      else if (tokens[index].tokenType == NIL) typeString = "NIL";
      else if (tokens[index].tokenType == OR) typeString = "OR";
      else if (tokens[index].tokenType == PRINT) typeString = "PRINT";
      else if (tokens[index].tokenType == RETURN) typeString = "RETURN";
      else if (tokens[index].tokenType == SUPER) typeString = "SUPER";
      else if (tokens[index].tokenType == THIS) typeString = "THIS";
      else if (tokens[index].tokenType == TRUE) typeString = "TRUE";
      else if (tokens[index].tokenType == VAR) typeString = "VAR";
      else if (tokens[index].tokenType == WHILE) typeString = "WHILE";
      else typeString = "bad token";

      char* literal = "";
      if (tokens[index].tokenType == STRING
          || tokens[index].tokenType == IDENTIFIER
          || tokens[index].tokenType == NUMBER) {
        literal = tokens[index].literal;
      }

      printf("token:\n\ttype: %s\n\tliteral: %s\n\tline: %d\n\tstart: %d\n\tend: %d\n",
          typeString,
          literal,
          tokens[index].lineNumber,
          tokens[index].startIndex,
          tokens[index].endIndex);

    }
  }




  return 0;
}


















