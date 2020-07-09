#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define PRINT_TOKENS true
#define PRINT_INSTRUCTIONS true

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
  #define MAX_SOURCE_CHARS 10000
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
  
  #define MAX_TOKEN_LITERAL_CHARS 100

  typedef enum {
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
  } TokenType;

  typedef struct {
    TokenType tokenType;
    int startIndex;
    int endIndex;
    int lineNumber;
    char literal[MAX_TOKEN_LITERAL_CHARS];
  } Token;


  Token prevToken;
  Token indexToken;
  Token nextToken;

  int tokenCount = 0;

  int sourceIndex = 0;
  char indexChar = sourceString[sourceIndex];
  while (indexChar != '\0') {
      
    charCount++;
    indexChar = sourceString[charCount];
  }

  return 0;
}



























