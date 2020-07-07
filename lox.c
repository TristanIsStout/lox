#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define MAX_SOURCE_CHARS 10000
#define MAX_TOKEN_LITERAL_CHARS 100
#define MAX_INSTRUCTION_PER_LINE 1000
#define MAX_INSTRUCTIONS 100000

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

int tokenCount = 0;
struct Token tokens[MAX_SOURCE_CHARS];

void printToken(int tokenIndex) {
      char* typeString;

      if (tokens[tokenIndex].tokenType == LEFT_PAREN) typeString = "LEFT_PAREN";
      else if (tokens[tokenIndex].tokenType == RIGHT_PAREN) typeString = "RIGHT_PAREN";
      else if (tokens[tokenIndex].tokenType == LEFT_BRACE) typeString = "LEFT_BRACE";
      else if (tokens[tokenIndex].tokenType == RIGHT_BRACE) typeString = "RIGHT_BRACE";
      else if (tokens[tokenIndex].tokenType == COMMA) typeString = "COMMA";
      else if (tokens[tokenIndex].tokenType == DOT) typeString = "DOT";
      else if (tokens[tokenIndex].tokenType == MINUS) typeString = "MINUS";
      else if (tokens[tokenIndex].tokenType == PLUS) typeString = "PLUS";
      else if (tokens[tokenIndex].tokenType == SEMICOLON) typeString = "SEMICOLON";
      else if (tokens[tokenIndex].tokenType == SLASH) typeString = "SLASH";
      else if (tokens[tokenIndex].tokenType == STAR) typeString = "STAR";
      else if (tokens[tokenIndex].tokenType == BANG) typeString = "BANG";
      else if (tokens[tokenIndex].tokenType == BANG_EQUAL) typeString = "BANG_EQUAL";
      else if (tokens[tokenIndex].tokenType == EQUAL) typeString = "EQUAL";
      else if (tokens[tokenIndex].tokenType == EQUAL_EQUAL) typeString = "EQUAL_EQUAL";
      else if (tokens[tokenIndex].tokenType == GREATER) typeString = "GREATER";
      else if (tokens[tokenIndex].tokenType == GREATER_EQUAL) typeString = "GREATER_EQUAL";
      else if (tokens[tokenIndex].tokenType == LESS) typeString = "LESS";
      else if (tokens[tokenIndex].tokenType == LESS_EQUAL) typeString = "LESS_EQUAL";
      else if (tokens[tokenIndex].tokenType == IDENTIFIER) typeString = "IDENTIFIER";
      else if (tokens[tokenIndex].tokenType == STRING) typeString = "STRING";
      else if (tokens[tokenIndex].tokenType == NUMBER) typeString = "NUMBER";
      else if (tokens[tokenIndex].tokenType == AND) typeString = "AND";
      else if (tokens[tokenIndex].tokenType == CLASS) typeString = "CLASS";
      else if (tokens[tokenIndex].tokenType == ELSE) typeString = "ELSE";
      else if (tokens[tokenIndex].tokenType == FALSE) typeString = "FALSE";
      else if (tokens[tokenIndex].tokenType == FUN) typeString = "FUN";
      else if (tokens[tokenIndex].tokenType == FOR) typeString = "FOR";
      else if (tokens[tokenIndex].tokenType == IF) typeString = "IF";
      else if (tokens[tokenIndex].tokenType == NIL) typeString = "NIL";
      else if (tokens[tokenIndex].tokenType == OR) typeString = "OR";
      else if (tokens[tokenIndex].tokenType == PRINT) typeString = "PRINT";
      else if (tokens[tokenIndex].tokenType == RETURN) typeString = "RETURN";
      else if (tokens[tokenIndex].tokenType == SUPER) typeString = "SUPER";
      else if (tokens[tokenIndex].tokenType == THIS) typeString = "THIS";
      else if (tokens[tokenIndex].tokenType == TRUE) typeString = "TRUE";
      else if (tokens[tokenIndex].tokenType == VAR) typeString = "VAR";
      else if (tokens[tokenIndex].tokenType == WHILE) typeString = "WHILE";
      else typeString = "bad token";

      char* literal = "";
      if (tokens[tokenIndex].tokenType == STRING
          || tokens[tokenIndex].tokenType == IDENTIFIER
          || tokens[tokenIndex].tokenType == NUMBER) {
        literal = tokens[tokenIndex].literal;
      }

      printf("token:\n\ttype: %s\n\tliteral: %s\n\tline: %d\n\tstart: %d\n\tend: %d\n",
          typeString,
          literal,
          tokens[tokenIndex].lineNumber,
          tokens[tokenIndex].startIndex,
          tokens[tokenIndex].endIndex);
}


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

int getPrecedence(enum InstructionType instructionType) {
  int precedence = -1;

  if (NEG) precedence = 250;
  else if (MULT) precedence = 200;
  else if (DIV) precedence = 150;
  else if (SUB) precedence = 100;
  else if (ADD) precedence = 50;

  return precedence;
}

struct Instruction {
  enum InstructionType instructionType;
  int tokenIndex;;
};

struct Instruction parseInstructionStack[MAX_INSTRUCTION_PER_LINE + 50];
int parseInstructionStackIndex = 0;

struct Instruction instructions[MAX_INSTRUCTIONS + 10];
int instructionCount = 0;

void printInstruction(int instructionIndex) {
  char* instructionTypeString;
  if (instructions[instructionIndex].instructionType == NEG) instructionTypeString = "NEG";
  else if (instructions[instructionIndex].instructionType == MULT) instructionTypeString = "MULT";
  else if (instructions[instructionIndex].instructionType == DIV) instructionTypeString = "DIV";
  else if (instructions[instructionIndex].instructionType == SUB) instructionTypeString = "SUB";
  else if (instructions[instructionIndex].instructionType == ADD) instructionTypeString = "ADD";
  else if (instructions[instructionIndex].instructionType == START_LINE) instructionTypeString = "START_LINE";
  else if (instructions[instructionIndex].instructionType == END_LINE) instructionTypeString = "END_LINE";
  else if (instructions[instructionIndex].instructionType == START_GROUP) instructionTypeString = "START_GROUP";
  else if (instructions[instructionIndex].instructionType == END_GROUP) instructionTypeString = "END_GROUP";
  else if (instructions[instructionIndex].instructionType == ASSIGN) instructionTypeString = "ASSIGN";
  else if (instructions[instructionIndex].instructionType == DECLARE) instructionTypeString = "DECLARE";
  else if (instructions[instructionIndex].instructionType == LITERAL) instructionTypeString = "LITERAL";
  else if (instructions[instructionIndex].instructionType == IDENT) instructionTypeString = "IDENT";

  printf("Instruction\n");
  printf("\ttype: %s\n", instructionTypeString);
  printToken(instructions[instructionIndex].tokenIndex);
  printf("\n");
  
}


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
  
  int lineNumber = 1;
  int sourceIndex = 0;
  indexChar = *sourceString;
  bool hasTokenizerError = false;

  while (indexChar != '\0') {
    if (tokenCount > MAX_SOURCE_CHARS) {
      printf("too many tokens in the source file");
      hasTokenizerError = true;
      break;
    }

    if (indexChar == '(') {
      tokens[tokenCount].tokenType = LEFT_PAREN;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == ')')  {
      tokens[tokenCount].tokenType = RIGHT_PAREN;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar ==  '{') {
      tokens[tokenCount].tokenType = LEFT_BRACE;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '}') {
      tokens[tokenCount].tokenType = RIGHT_BRACE;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == ',') {
      tokens[tokenCount].tokenType = COMMA;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '.') {
      tokens[tokenCount].tokenType = DOT;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '-') {
      tokens[tokenCount].tokenType = MINUS;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '+') {
      tokens[tokenCount].tokenType = PLUS;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == ';') {
      tokens[tokenCount].tokenType = SEMICOLON;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '*') {
      tokens[tokenCount].tokenType = STAR;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '!' && *(sourceString + sourceIndex + 1) == '=') {
      tokens[tokenCount].tokenType = BANG_EQUAL;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex + 1;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;
      // todo tks do this guy
      sourceIndex++;

    } else if (indexChar == '!' && *(sourceString + sourceIndex + 1) != '=') {
      tokens[tokenCount].tokenType = BANG;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '<' && *(sourceString + sourceIndex + 1) == '=') {
      tokens[tokenCount].tokenType = LESS_EQUAL;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex + 1;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;
      // todo tks do this guy
      sourceIndex++;

    } else if (indexChar == '<' && *(sourceString + sourceIndex + 1) != '=') {
      tokens[tokenCount].tokenType = LESS;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '>' && *(sourceString + sourceIndex + 1) == '=') {
      tokens[tokenCount].tokenType = GREATER_EQUAL;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex + 1;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;
      // todo tks do this guy
      sourceIndex++;

    } else if (indexChar == '>' && *(sourceString + sourceIndex + 1) != '=') {
      tokens[tokenCount].tokenType = GREATER;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

    } else if (indexChar == '=' && *(sourceString + sourceIndex + 1) == '=') {
      tokens[tokenCount].tokenType = EQUAL_EQUAL;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex + 1;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;
      // todo tks do this guy
      sourceIndex++;

    } else if (indexChar == '=' && *(sourceString + sourceIndex + 1) != '=') {
      tokens[tokenCount].tokenType = EQUAL;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].endIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;
      tokenCount++;

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
      tokens[tokenCount].tokenType = STRING;
      tokens[tokenCount].lineNumber = lineNumber;
      tokens[tokenCount].startIndex = sourceIndex;

      // iterate through the end of the string
      indexChar = *(sourceString + sourceIndex + 1);
      while (indexChar != '"') {
        if (indexChar == '\n') {
          lineNumber++;
        }
        sourceIndex++;
        indexChar = *(sourceString + sourceIndex);
      }
      tokens[tokenCount].endIndex = sourceIndex;

      // store the string in the literal value (do not store the quotes)
      memcpy(
          tokens[tokenCount].literal,
          (sourceString + tokens[tokenCount].startIndex + 1),
          (tokens[tokenCount].endIndex - tokens[tokenCount].startIndex) - 2);

      tokenCount++;

    } else if (indexChar >= '0' && indexChar <= '9') {
      // the token is anumber
      tokens[tokenCount].tokenType = NUMBER;
      tokens[tokenCount].startIndex = sourceIndex;
      tokens[tokenCount].lineNumber = lineNumber;

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
      tokens[tokenCount].endIndex = sourceIndex;
      memcpy(
          tokens[tokenCount].literal,
          sourceString + tokens[tokenCount].startIndex,
          (tokens[tokenCount].endIndex - tokens[tokenCount].startIndex) + 1);

      tokenCount++;

    } else if ((indexChar >= 'a' && indexChar <= 'z') || (indexChar >= 'A' && indexChar <= 'Z')) {
      // this is either an identifier or a keyword
      tokens[tokenCount].lineNumber = lineNumber;
      tokens[tokenCount].startIndex = sourceIndex;

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
      tokens[tokenCount].endIndex = sourceIndex;

      memcpy(
          tokens[tokenCount].literal,
          sourceString + tokens[tokenCount].startIndex,
          (tokens[tokenCount].endIndex - tokens[tokenCount].startIndex) + 1);

      // if the literal matches a reserved keyword, set it to the appropriate token type
      if (strcmp("and", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = AND;

      } else if (strcmp("class", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = CLASS;

      } else if (strcmp("else", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = ELSE;

      } else if (strcmp("false", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = FALSE;

      } else if (strcmp("for", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = FOR;

      } else if (strcmp("fun", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = FUN;

      } else if (strcmp("if", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = IF;

      } else if (strcmp("nil", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = NIL;

      } else if (strcmp("or", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = OR;

      } else if (strcmp("print", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = PRINT;

      } else if (strcmp("return", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = RETURN;

      } else if (strcmp("super", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = SUPER;

      } else if (strcmp("this", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = THIS;

      } else if (strcmp("true", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = TRUE;

      } else if (strcmp("var", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = VAR;

      } else if (strcmp("while", tokens[tokenCount].literal) == 0) {
        tokens[tokenCount].tokenType = WHILE;

      } else {
        // if it isn't a reserved keyword, then default ot an identifier
        tokens[tokenCount].tokenType = IDENTIFIER;
      }

      sourceIndex++;
      tokenCount++;

    } else {
      printf("Unexpected character '%c' on line %d.\n", indexChar, lineNumber + 1);
      hasTokenizerError = true;
    }

    sourceIndex++;
    indexChar = *(sourceString + sourceIndex);
  }

  if (false) {
    // set to true if we want to print out the tokens to ensure that they were spit out correctly
    printf("printing the tokens...\n");
    for (int tokenIndex = 0; tokenIndex < tokenCount; tokenIndex++) {
      printToken(tokenIndex);
    }
    printf("\n");
  }

  if (hasTokenizerError) exit(1);

  printf("Parsing the Tokens into the Instructions\n");
  bool hasParseError = false;

  for (int parseTokenIndex = 0; parseTokenIndex < tokenCount; parseTokenIndex++) {
    // loop through each token

    if (instructionCount >= MAX_INSTRUCTIONS) {
      printf("too many instructions to be parsed...\n");
      hasParseError = true;;
    }

    if (parseInstructionStackIndex == 0) {
      // add a start of line instruction at the very beginning, and whenever the stack is cleared by end line
      parseInstructionStack[parseInstructionStackIndex].instructionType = START_LINE;
      parseInstructionStack[parseInstructionStackIndex].tokenIndex = parseTokenIndex;
      parseInstructionStackIndex++;
    }

    if (parseInstructionStackIndex >= MAX_INSTRUCTION_PER_LINE) {
      printf("too many instructions on line %d. pleass abbreviate\n", tokens[parseTokenIndex].lineNumber);
      hasParseError = true;
      parseInstructionStackIndex = 0;
    }

    if (tokens[parseTokenIndex].tokenType == NUMBER) {
      printf("delteme num\n");
      // numbers are just a literal
      instructions[instructionCount].instructionType = LITERAL;
      instructions[instructionCount].tokenIndex = parseTokenIndex;
      instructionCount++;

    } else if (tokens[parseTokenIndex].tokenType == LEFT_PAREN) {
      printf("delteme stack (\n");
      // lparens are just a marker for the instruction stack they sit there until the right parent chews through the stack
      parseInstructionStack[parseInstructionStackIndex].instructionType = START_GROUP;
      parseInstructionStack[parseInstructionStackIndex].tokenIndex = parseTokenIndex;
      parseInstructionStackIndex++;

    } else if (tokens[parseTokenIndex].tokenType == RIGHT_PAREN) {
      printf("delteme found )\n");
      // the stack is popped and instructions are written until the first left paren is found
      while (parseInstructionStackIndex != 0
          && parseInstructionStack[parseInstructionStackIndex].instructionType != START_GROUP) {
        printf("deleteme stack pop");
        instructions[instructionCount].instructionType = parseInstructionStack[parseInstructionStackIndex].instructionType;
        instructions[instructionCount].tokenIndex = parseInstructionStack[parseInstructionStackIndex].tokenIndex;
        instructionCount++;
        parseInstructionStackIndex--;
      }
      if (parseInstructionStackIndex == 0) {
        printf("unmatched righ parens on line %d\n", tokens[parseTokenIndex].lineNumber);
        hasParseError = true;
      } else {
        // the loop stops on the first l paren. pop the l paren as it is no longer used
        parseInstructionStackIndex--;
      }

    //} else if (tokens[parseTokenIndex].tokenType == LEFT_BRACE) { 
    //} else if (tokens[parseTokenIndex].tokenType == RIGHT_BRACE) { 
    //} else if (tokens[parseTokenIndex].tokenType == COMMA) { 
    //} else if (tokens[parseTokenIndex].tokenType == DOT) { 

    // todo tks if this is the unary operator, how the heck am I planning on checking for that...

    } else if (tokens[parseTokenIndex].tokenType == MINUS) {
      if (parseInstructionStackIndex == 0
          || getPrecedence(parseInstructionStack[parseInstructionStackIndex].instructionType) < getPrecedence(SUB)) {
        printf("delteme stack -\n");
        instructions[instructionCount].instructionType = SUB;
        instructions[instructionCount].tokenIndex = parseTokenIndex;
        instructionCount++;

      } else {
        printf("delteme -\n");
        parseInstructionStackIndex++;
        parseInstructionStack[parseInstructionStackIndex].instructionType = SUB;
        parseInstructionStack[parseInstructionStackIndex].tokenIndex = parseTokenIndex;
      }


    } else if (tokens[parseTokenIndex].tokenType == PLUS) {
      if (parseInstructionStackIndex == 0
          || getPrecedence(parseInstructionStack[parseInstructionStackIndex].instructionType) < getPrecedence(ADD)) {
        printf("delteme stack +\n");
        instructions[instructionCount].instructionType = ADD;
        instructions[instructionCount].tokenIndex = parseTokenIndex;
        instructionCount++;

      } else {
        printf("delteme +\n");
        parseInstructionStackIndex++;
        parseInstructionStack[parseInstructionStackIndex].instructionType = ADD;
        parseInstructionStack[parseInstructionStackIndex].tokenIndex = parseTokenIndex;
      }

    } else if (tokens[parseTokenIndex].tokenType == SLASH) {
      if (parseInstructionStackIndex == 0
          || getPrecedence(parseInstructionStack[parseInstructionStackIndex].instructionType) < getPrecedence(DIV)) {
        printf("delteme stack +\n");
        instructions[instructionCount].instructionType = DIV;
        instructions[instructionCount].tokenIndex = parseTokenIndex;
        instructionCount++;

      } else {
        printf("delteme +\n");
        parseInstructionStackIndex++;
        parseInstructionStack[parseInstructionStackIndex].instructionType = DIV;
        parseInstructionStack[parseInstructionStackIndex].tokenIndex = parseTokenIndex;
      }

    } else if (tokens[parseTokenIndex].tokenType == STAR) {
      if (parseInstructionStackIndex == 0
          || getPrecedence(parseInstructionStack[parseInstructionStackIndex].instructionType) < getPrecedence(MULT)) {
        printf("delteme stack *\n");
        instructions[instructionCount].instructionType = MULT;
        instructions[instructionCount].tokenIndex = parseTokenIndex;
        instructionCount++;

      } else {
        printf("delteme *\n");
        parseInstructionStackIndex++;
        parseInstructionStack[parseInstructionStackIndex].instructionType = MULT;
        parseInstructionStack[parseInstructionStackIndex].tokenIndex = parseTokenIndex;
      }

    } else if (tokens[parseTokenIndex].tokenType == SEMICOLON) {
      printf("deleteme ;\n");
      // the stack is popped and instructions are written until the start line instruction is found
      while (parseInstructionStackIndex != 0
          && parseInstructionStack[parseInstructionStackIndex].instructionType != START_LINE) {

        if (parseInstructionStack[parseInstructionStackIndex].instructionType == START_GROUP
            || parseInstructionStack[parseInstructionStackIndex].instructionType == END_GROUP) {
          // the groupings should 
          printf("unexpected parenthesis on line %d\n", tokens[parseTokenIndex].lineNumber);
          hasParseError = true;
        }

        printf("popping the stack\n");
        instructions[instructionCount].instructionType = parseInstructionStack[parseInstructionStackIndex].instructionType;
        instructions[instructionCount].tokenIndex = parseInstructionStack[parseInstructionStackIndex].tokenIndex;
        parseInstructionStackIndex--;
        instructionCount++;
      }

      if (parseInstructionStackIndex == 0) {
        printf("error terminating line %d\n", tokens[parseTokenIndex].lineNumber);
        hasParseError = true;

      } else {
        // the loop stops on the first start line. pop the start line as it is no longer used
        parseInstructionStackIndex--;
      }

      printf("start line written\n");
      // push a start line instruction after pushing to the stack
      parseInstructionStack[parseInstructionStackIndex].instructionType = START_LINE;
      parseInstructionStack[parseInstructionStackIndex].tokenIndex = parseTokenIndex;
      parseInstructionStackIndex++;

      //} else if (tokens[parseTokenIndex].tokenType == BANG) { 
      //} else if (tokens[parseTokenIndex].tokenType == BANG_EQUAL) { 
      //} else if (tokens[parseTokenIndex].tokenType == EQUAL) { 
      //} else if (tokens[parseTokenIndex].tokenType == EQUAL_EQUAL) { 
      //} else if (tokens[parseTokenIndex].tokenType == GREATER) { 
      //} else if (tokens[parseTokenIndex].tokenType == GREATER_EQUAL) { 
      //} else if (tokens[parseTokenIndex].tokenType == LESS) { 
      //} else if (tokens[parseTokenIndex].tokenType == LESS_EQUAL) { 
      //} else if (tokens[parseTokenIndex].tokenType == IDENTIFIER) { 
      //} else if (tokens[parseTokenIndex].tokenType == STRING) { 
      //} else if (tokens[parseTokenIndex].tokenType == NUMBER) { 
      //} else if (tokens[parseTokenIndex].tokenType == AND) { 
      //} else if (tokens[parseTokenIndex].tokenType == CLASS) { 
      //} else if (tokens[parseTokenIndex].tokenType == ELSE) { 
      //} else if (tokens[parseTokenIndex].tokenType == FALSE) { 
      //} else if (tokens[parseTokenIndex].tokenType == FUN) { 
      //} else if (tokens[parseTokenIndex].tokenType == FOR) { 
      //} else if (tokens[parseTokenIndex].tokenType == IF) { 
      //} else if (tokens[parseTokenIndex].tokenType == NIL) { 
      //} else if (tokens[parseTokenIndex].tokenType == OR) { 
      //} else if (tokens[parseTokenIndex].tokenType == PRINT) { 
      //} else if (tokens[parseTokenIndex].tokenType == RETURN) { 
      //} else if (tokens[parseTokenIndex].tokenType == SUPER) { 
      //} else if (tokens[parseTokenIndex].tokenType == THIS) { 
      //} else if (tokens[parseTokenIndex].tokenType == TRUE) { 
      //} else if (tokens[parseTokenIndex].tokenType == VAR) { 
      //} else if (tokens[parseTokenIndex].tokenType == WHILE) { 

    } else {
      printf("unexpected token on line %d\n", tokens[parseTokenIndex].lineNumber);
      hasParseError = true;
    }


  }


  if (parseInstructionStackIndex != 0) {
    printf("the file did not end properly, there was an error parsing the tokens\n");
    hasParseError = true;
  }

  if (true) {
    printf("printing the instructions...\n");
    for (int instructionIndex = 0; instructionIndex < instructionCount; instructionIndex++) {
      printInstruction(instructionIndex);
    }
  }

  if (hasParseError) exit(1);




  return 0;
}


















