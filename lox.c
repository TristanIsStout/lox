#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MAX_SOURCE_CHARS 10000
#define MAX_TOKEN_LITERAL_CHARS 100
#define MAX_INSTRUCTION_PER_LINE 1000
#define MAX_INSTRUCTIONS 100000

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
  bool hasTokenizerError = false;

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
      // skip comment lines, just increment the line count when we're done
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

      // iterate through the end of the string
      indexChar = *(sourceString + sourceIndex + 1);
      while (indexChar != '"') {
        if (indexChar == '\n') {
          lineNumber++;
        }
        sourceIndex++;
        indexChar = *(sourceString + sourceIndex);
      }
      tokens[tokenIndex].endIndex = sourceIndex;

      // store the string in the literal value (do not store the quotes)
      memcpy(
          tokens[tokenIndex].literal,
          (sourceString + tokens[tokenIndex].startIndex + 1),
          (tokens[tokenIndex].endIndex - tokens[tokenIndex].startIndex) - 2);

      tokenIndex++;

    } else if (indexChar >= '0' && indexChar <= '9') {
      // the token is anumber
      tokens[tokenIndex].tokenType = NUMBER;
      tokens[tokenIndex].startIndex = sourceIndex;
      tokens[tokenIndex].lineNumber = lineNumber;

      // iterate through the rest of the non-decimal side of the number
      char nextChar = *(sourceString + sourceIndex + 1);
      while (nextChar >= '0' && nextChar <= '9') {
        sourceIndex++;
        indexChar = *(sourceString + sourceIndex);
        nextChar = *(sourceString + sourceIndex + 1);
      }
      // if there is a decimal, than iterate through the decimal side of the number
      if (nextChar == '.') {
        sourceIndex++;
        char nextChar = *(sourceString + sourceIndex + 1);
        if (!(nextChar >= '0' && nextChar <= '9')) {
          // if ther eis a decimal point that isn't followed by a decimal side, then we have a tokenizer error
          printf("Number has a dangling decimal point on line %d\n", lineNumber);
          hasTokenizerError = true;
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

      // iterate until we find the end of the identifier or keyword
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

      // if the literal matches a reserved keyword, set it to the appropriate token type
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
        // if it isn't a reserved keyword, then default ot an identifier
        tokens[tokenIndex].tokenType = IDENTIFIER;
      }

      sourceIndex++;
      tokenIndex++;

    } else {
      printf("Unexpected character '%c' on line %d.\n", indexChar, lineNumber + 1);
      hasTokenizerError = true;
    }


    sourceIndex++;
    indexChar = *(sourceString + sourceIndex);
  }

  if (false) {
    // set to true if we want 
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

  if (hasTokenizerError) exit(1);

  printf("Parsing the Tokens into the Instructions\n");

  enum InstructionType {
    NEG,
    MULT,
    DIV,
    SUB,
    ADD,
    START_LINE,
    END_LINE,
    START_GROUP,
    END_GROUP,
    ASSIGN,
    DECLARE,
    LITERAL,
    IDENT
  };

  struct Instruction {
    enum InstructionType instructionType;
    // todo tks why does this keep doing this? It doesn't make sense why this seg faults...
    char* literal;
    // char literal[MAX_TOKEN_LITERAL_CHARS];
  };

  struct Instruction instructionStack[MAX_INSTRUCTION_PER_LINE + 50];
  int instructionStackIndex = 0;

  struct Instruction instructions[MAX_INSTRUCTIONS + 10];
  int instructionIndex = 0;

  bool hasParseError = false;

  for (int index = 0; index < tokenIndex; index++) {
    // loop through each token

    if (instructionIndex >= MAX_INSTRUCTIONS) {
      printf("too many instructions to be parsed...\n");
      hasParseError = true;;
    }

    if (instructionStackIndex == 0) {
      // add a start of line instruction at the very beginning, and whenever the stack is cleared by end line
      instructionStack[instructionStackIndex].instructionType = START_LINE;
      instructionStackIndex++;
    }

    if (instructionStackIndex >= MAX_INSTRUCTION_PER_LINE) {
      printf("too many instructions on line %d. pleass abbreviate\n", tokens[index].lineNumber);
      hasParseError = true;
      instructionStackIndex = 0;
    }

    if (tokens[index].tokenType == NUMBER) {
      // numbers are just a literal
      instructions[instructionIndex].instructionType = LITERAL;
      // todo tks copy over the value
      instructionIndex++;

    } else if (tokens[index].tokenType == LEFT_PAREN) {
      // lparens are just a marker for the instruction stack they sit there until the right parent chews through the stack
      instructionStackIndex++;
      instructionStack[instructionStackIndex].instructionType = START_GROUP;

    } else if (tokens[index].tokenType == RIGHT_PAREN) {
      // the stack is popped and instructions are written until the first left paren is found
      while (instructionStackIndex != 0
          && instructionStack[instructionStackIndex].instructionType != START_GROUP) {
        instructions[instructionIndex].instructionType = instructionStack[instructionStackIndex].instructionType;
        instructionIndex++;
        instructionStackIndex--;
      }
      if (instructionStackIndex == 0) {
        printf("unmatched righ parens on line %d\n", tokens[index].lineNumber);
        hasParseError = true;

      } else {
        // the loop stops on the first l paren. pop the l paren as it is no longer used
        instructionStackIndex--;
      }

    } else if (tokens[index].tokenType == SEMICOLON) {
      // the stack is popped and instructions are written until the start line instruction is found
      while (instructionStackIndex != 0
          && instructionStack[instructionStackIndex].instructionType != START_LINE) {

        if (instructionStack[instructionStackIndex].instructionType == START_GROUP
            || instructionStack[instructionStackIndex].instructionType == END_GROUP) {
          // the groupings should 
          printf("unexpected parenthesis on line %d\n", tokens[index].lineNumber);
          hasParseError = true;
        }

        instructions[instructionIndex].instructionType = instructionStack[instructionStackIndex].instructionType;
        instructionStackIndex--;
        instructionIndex++;
      }

      if (instructionStackIndex == 0) {
        printf("error terminating line %d\n", tokens[index].lineNumber);
        hasParseError = true;

      } else {
        // the loop stops on the first start line. pop the start line as it is no longer used
        instructionStackIndex--;
      }

      // push a start line instruction after pushing to the stack
      instructionStack[instructionStackIndex].instructionType = START_LINE;
      instructionStackIndex++;

    } else if (tokens[index].tokenType == MINUS) {

    } else {
      printf("unexpected token on line %d\n", tokens[index].lineNumber);
      hasParseError = true;
    }

    if (instructionStackIndex != 0) {
      printf("the file did not end properly, there was an error parsign the tokens\n");
      hasParseError = true;
    }

    if (true) {
      printf("printing the instructions...\n");
      for (int index = 0; index < instructionIndex; index++) {

        char* instructionType;
        if (instructions[index].instructionType == NEG) instructionType = "NEG";
        else if (instructions[index].instructionType == MULT) instructionType = "MULT";
        else if (instructions[index].instructionType == DIV) instructionType = "DIV";
        else if (instructions[index].instructionType == SUB) instructionType = "SUB";
        else if (instructions[index].instructionType == ADD) instructionType = "ADD";
        else if (instructions[index].instructionType == START_LINE) instructionType = "START_LINE";
        else if (instructions[index].instructionType == END_LINE) instructionType = "END_LINE";
        else if (instructions[index].instructionType == START_GROUP) instructionType = "START_GROUP";
        else if (instructions[index].instructionType == END_GROUP) instructionType = "END_GROUP";
        else if (instructions[index].instructionType == ASSIGN) instructionType = "ASSIGN";
        else if (instructions[index].instructionType == DECLARE) instructionType = "DECLARE";
        else if (instructions[index].instructionType == LITERAL) instructionType = "LITERAL";
        else if (instructions[index].instructionType == IDENT) instructionType = "IDENT";
    
        printf("type: %s, value: \n", instructionType);
      }

    }

    if (hasParseError) return 1;


  }





  return 0;
}


















