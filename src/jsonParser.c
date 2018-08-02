#include <stdio.h>
#include "jsonParser.h"
#include "Error.h"
#include "Exception.h"

Json *createJson(JsonType whatJsonType){
  Json *newJson=(Json *)malloc(sizeof(Json));
  newJson->type=whatJsonType;
  (newJson->list).head=NULL;
  (newJson->list).tail=NULL;
  (newJson->list).count=0;
  return newJson;
}


void simpleJsonParser(Tokenizer *tokenizer,LinkedList *object){
  Token *token;
  char operator;
  char *elementName;
  char *string;
  
  token=getToken(tokenizer);
  if((token->type != TOKEN_OPERATOR_TYPE) || (((OperatorToken *)token)->str[0]!='{')){
    throwException(ERR_EXPECTING_CORRECT_CURLY_BRACKET, token, "Expect operator '{' ");
  }
  freeToken(token);
  
  Json *object=createJson(OBJECT_TYPE);
  
  token=getToken(tokenizer);
  if((token->type == TOKEN_OPERATOR_TYPE) && (((OperatorToken *)token)->str[0]=='}')){
  }
  else if(token->type != TOKEN_STRING_TYPE){
    throwException(ERR_EXPECTING_STRING_TYPE_OR_CLOSED_CURLY_BRACKET, token, "Expect 'string' or '}' ");
  }
  else{
    if(token->type == TOKEN_STRING_TYPE){
      elementName=token->str;
      freeToken(token);
      token=getToken(tokenizer);
      if((token->type == TOKEN_OPERATOR_TYPE) && (((OperatorToken *)token)->str[0]==':')){
        freeToken(token);
        token=getToken(tokenizer);
        if(token->type == TOKEN_INTEGER_TYPE || token->type == TOKEN_FLOAT_TYPE){
        }
        else if(token->type == TOKEN_STRING_TYPE){
        }
        else if(token->type == TOKEN_IDENTIFIER_TYPE){
        }
        else{
          throwException(ERR_EXPECTING_COLON, token, "Expect 'string','number','NULL','true','false'.... ");
        }
      }
      else{
        throwException(ERR_EXPECTING_COLON, token, "Expect ':' ");
      }
    }
  }
  freeToken(token);
}
