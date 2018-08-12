#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "jsonParser.h"
#include "Error.h"
#include "Exception.h"

BOOLEANS detectBooleanWithDataToken(Token *datatoken){
  if(strcmp(datatoken->str,"true")==0){
    return true;
  }
  else if(strcmp(datatoken->str,"false")==0){
    return false;
  }
  else{
    throwException(ERR_EXPECTING_COLON, datatoken, "Expect 'string','number','NULL','true','false'.... ");
  }
}



/*
/////////////////////experiment to achiece recursive call/////////////////////////////////////////////////////////
//this function code modify from function:
//addElementNameAndArrayIntoObject(char *name,Tokenizer *tokenizer,Json *object);

Json *createObjectOrArrayWithinArrayAccordingToTokenizer(Tokenizer *tokenizer){
  Token  *optoken;
  Json *array;
  Json *arrayWithinArray;
  Json *objectWithinArray;
  optoken=getToken(tokenizer);  //detect '['
  if(((OperatorToken *)optoken)->str[0]=='['){
    freeToken(optoken);
    array=createJson(ARRAY_TYPE);
    optoken=getToken(tokenizer);  //detect ']' or 'data'
    if(((OperatorToken *)optoken)->str[0]==']'){
    }
    else if(((OperatorToken *)optoken)->str[0]=='['){
      pushBackToken(tokenizer, optoken);    //need to push back 'data' for other function
      arrayWithinArray=createJsonObjectAndJsonArrayAccordingToTokenizer(tokenizer); //recursive call to create array inside an array
      addJsonEntityToArray(array, (void *)(arrayWithinArray));
    }
    else if(((OperatorToken *)optoken)->str[0]=='{'){
      pushBackToken(tokenizer, optoken);    //need to push back 'data' for other function
      objectWithinArray=simpleJsonParser(tokenizer);       //recursive call to create object inside an array
      addJsonEntityToArray(array, (void *)(objectWithinArray));
    }
    else{
      pushBackToken(tokenizer, optoken);    //need to push back 'data' for other function
      addAnyDataIntoArrayUsingDataToken(tokenizer,array);
      optoken=getToken(tokenizer);    //detect ','
      while(((OperatorToken *)optoken)->str[0]==','){
        freeToken(optoken);
        addAnyDataIntoArrayUsingDataToken(tokenizer,array);
        optoken=getToken(tokenizer);
      }
    }
  }

  else{
    throwException(ERR_EXPECTING_COLON, optoken, "Expect '['  ");
  }



  if(((OperatorToken *)optoken)->str[0]==']'){
    freeToken(optoken);
    return array;
  }
  else{
    throwException(ERR_EXPECTING_COLON, optoken, "Expect ']' , ','  ");
  }
}




/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

*/

addElementNameAndArrayIntoObject(char *name,Tokenizer *tokenizer,Json *object){
  Token  *optoken;
  JsonElement *element;
  BOOLEANS booleanData;
  Json *array=createJson(ARRAY_TYPE);
  optoken=getToken(tokenizer);    //detect '['
  if(((OperatorToken *)optoken)->str[0]=='['){
    freeToken(optoken);
    optoken=getToken(tokenizer);    //detect ']' or 'data'
    if(((OperatorToken *)optoken)->str[0]==']'){
    }
    else{
      pushBackToken(tokenizer, optoken);    //need to push back 'data' for other function
      addAnyDataIntoArrayUsingDataToken(tokenizer,array);
      optoken=getToken(tokenizer);    //detect ','
      while(((OperatorToken *)optoken)->str[0]==','){
        freeToken(optoken);
        addAnyDataIntoArrayUsingDataToken(tokenizer,array);
        optoken=getToken(tokenizer);
      }
    }
  }
  else{
    throwException(ERR_EXPECTING_COLON, optoken, "Expect '['  ");
  }



  if(((OperatorToken *)optoken)->str[0]==']'){
    freeToken(optoken);
    element=createJsonElement(name, (void *)(array));
    addElementIntoObject(object,element);
  }
  else{
    throwException(ERR_EXPECTING_COLON, optoken, "Expect ']' , ','  ");
  }

}


//use this to input data(number,string,boolean) through (tokenizer)
//this function only add any type data for one time
//not for adding object because this function adding data directly without the element name (element struct)
addAnyDataIntoArrayUsingDataToken(Tokenizer *tokenizer,Json *array){
  JsonNumber *newJsonNumber;
  JsonString *newJsonString;
  JsonBoolean *newJsonBoolean;
  BOOLEANS booleanData;
  Token *datatoken=getToken(tokenizer);
  if(datatoken->type==TOKEN_FLOAT_TYPE){
    newJsonNumber=createJsonNumber(((FloatToken *)datatoken)->value);
    addJsonEntityToArray(array, (void *)(newJsonNumber));
    freeToken(datatoken);
  }
  else if(datatoken->type == TOKEN_INTEGER_TYPE){
    newJsonNumber=createJsonNumber((double)((IntegerToken *)datatoken)->value);
    addJsonEntityToArray(array, (void *)(newJsonNumber));
    freeToken(datatoken);
  }
  else if(datatoken->type == TOKEN_STRING_TYPE){
    newJsonString=createJsonString(((StringToken *)datatoken)->str);
    addJsonEntityToArray(array, (void *)(newJsonString));
    freeToken(datatoken);
  }
  else if(datatoken->type == TOKEN_IDENTIFIER_TYPE){
    booleanData=detectBooleanWithDataToken(datatoken);
    newJsonBoolean=createJsonBoolean(booleanData);
    addJsonEntityToArray(array, (void *)(newJsonBoolean));
    freeToken(datatoken);
  }
  else{
    throwException(ERR_EXPECTING_COLON, datatoken, "Expect 'string','number','NULL','true','false'.... ");
  }
}





addElementAndDataIntoObject(Token *elementtoken,Tokenizer *tokenizer,Json *object){
  Token *datatoken, *token;
  BOOLEANS booleanData;
  JsonElement *element;
  Json *objectWithinObject;
  //this if else just to detect whether it is a string
  if(elementtoken->type == TOKEN_STRING_TYPE){
  }
  else{
    throwException(ERR_EXPECTING_STRING_TYPE_OR_CLOSED_CURLY_BRACKET, elementtoken, "Expect 'string'  ");
  }

  token=getToken(tokenizer);      //detect ':' symbol
  if((token->type == TOKEN_OPERATOR_TYPE) && (((OperatorToken *)token)->str[0]==':')){
    freeToken(token);
  }
  else{
    throwException(ERR_EXPECTING_COLON, token, "Expect ':' ");
  }

  datatoken=getToken(tokenizer);     //detect data and data type after getting element name
  if(datatoken->type == TOKEN_FLOAT_TYPE){
    addNameAndNumberIntoObject(elementtoken->str,((FloatToken *)datatoken)->value,object);
    freeToken(elementtoken);
    freeToken(datatoken);
  }
  else if(datatoken->type == TOKEN_INTEGER_TYPE){
    addNameAndNumberIntoObject(elementtoken->str,((double)((IntegerToken *)datatoken)->value),object);
    freeToken(elementtoken);
    freeToken(datatoken);
  }
  else if(datatoken->type == TOKEN_STRING_TYPE){
    addNameAndStringIntoObject(elementtoken->str,((StringToken *)datatoken)->str,object);
    freeToken(elementtoken);
    freeToken(datatoken);
  }
  else if(((OperatorToken *)datatoken)->str[0]=='['){
    pushBackToken(tokenizer, datatoken);
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,object);
    //Json *createJsonObjectAndJsonArrayAccordingToTokenizer(tokenizer);
    //element=createJsonElement(name, (void *)(array));
    //addElementIntoObject(object,element);
    freeToken(elementtoken);
  }
  else if(((OperatorToken *)datatoken)->str[0]=='{'){
    pushBackToken(tokenizer, datatoken);    //need to push back 'data' for other function
    objectWithinObject=simpleJsonParser(tokenizer);       //recursive call to create object inside an array
    element=createJsonElement(elementtoken->str, (void *)(objectWithinObject));
    addElementIntoObject(object,element);
  }
  else if(datatoken->type == TOKEN_IDENTIFIER_TYPE){
    BOOLEANS booleanData=detectBooleanWithDataToken(datatoken);
    addNameAndBooleanIntoObject(elementtoken->str,booleanData,object);
    freeToken(elementtoken);
    freeToken(datatoken);
  }
  else{
    throwException(ERR_EXPECTING_COLON, datatoken, "Expect 'string','number','NULL','true','false'.... ");
  }
}

Json *simpleJsonParser(Tokenizer *tokenizer){
  Token *elementtoken, *datatoken, *token;

  token=getToken(tokenizer);    //detect '{' symbol to decide whether to create object
  if((token->type == TOKEN_OPERATOR_TYPE) && (((OperatorToken *)token)->str[0]=='{')){
    //Json *object=createJson(OBJECT_TYPE);
    freeToken(token);
  }
  else{
    throwException(ERR_EXPECTING_CORRECT_CURLY_BRACKET, token, "Expect operator '{' ");
  }
  Json *object=createJson(OBJECT_TYPE);


  elementtoken=getToken(tokenizer);       //detect element name or '}' to return object
  if((elementtoken->type == TOKEN_OPERATOR_TYPE) && (((OperatorToken *)elementtoken)->str[0]=='}')){
    freeToken(elementtoken);
    return object;
  }
  else{
    addElementAndDataIntoObject(elementtoken,tokenizer,object);
  }

  token=getToken(tokenizer);      //detect ',' operator
  while(((OperatorToken *)token)->str[0]==','){
    freeToken(token);
    elementtoken=getToken(tokenizer);       //detect element name or '}' to return object
    addElementAndDataIntoObject(elementtoken,tokenizer,object);
    token=getToken(tokenizer);      //detect ',' operator
  }


  if((token->type == TOKEN_OPERATOR_TYPE) && (((OperatorToken *)token)->str[0]=='}')){
    freeToken(token);
    return object;
  }
  else{
    throwException(ERR_EXPECTING_STRING_TYPE_OR_CLOSED_CURLY_BRACKET, token, "Expect   ',' , '}'  ");
  }
}
