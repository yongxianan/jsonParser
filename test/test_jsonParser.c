#include <stdlib.h>
#include <errno.h>
#include "unity.h"
#include "jsonParser.h"
#include "Common.h"
#include "Error.h"
#include "Token.h"
#include "tokenizer.h"
#include "CException.h"
#include "Exception.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_createJson_for_new_object(void){
  Json *object=createJson(OBJECT_TYPE);
  TEST_ASSERT_EQUAL(0,object->list.count);
  TEST_ASSERT_EQUAL(OBJECT_TYPE,object->type);
  TEST_ASSERT_EQUAL(NULL,object->list.head);
  TEST_ASSERT_EQUAL(NULL,object->list.tail);
}

void test_createJson_for_new_array(void){
  Json *object=createJson(ARRAY_TYPE);
  TEST_ASSERT_EQUAL(0,object->list.count);
  TEST_ASSERT_EQUAL(ARRAY_TYPE,object->type);
  TEST_ASSERT_EQUAL(NULL,object->list.head);
  TEST_ASSERT_EQUAL(NULL,object->list.tail);
}
/*
void test_given_empty_object(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  //LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_ASSERT_EQUAL(0,object.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object.type);
    TEST_ASSERT_EQUAL(NULL,object.head);
    TEST_ASSERT_EQUAL(NULL,object.tail);
    
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_given_with_incorrect_curly_bracket_format(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{{"
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!"); 
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_without_first_bracket_missing(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!"); 
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_without_second_bracket_missing(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{ ";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!"); 
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_without_anything(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "   ";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!"); 
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_age_that_not_a_string(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
     "  age "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_3_element_with_name_without_colon(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
     "  \"age\" "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
    
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_3_element_with_name_without_value(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
     "  \"age\": "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
    
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}
*/
/*
void test_given_3_element_with__age:23_(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
  "  \"age\":23  "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_ASSERT_EQUAL(1,object.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object.type);
    
    TEST_ASSERT_EQUAL(ELEMENT_TYPE,object.head->data->type);
    TEST_ASSERT_EQUAL_STRING("age",object.head->data->name);
    TEST_ASSERT_EQUAL(NUMBER_TYPE,object.head->data->value->type);
    TEST_ASSERT_EQUAL(23,object.head->data->value->number);
    
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_given_3_element_with__age:23_comma_expect_string(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
  "  \"age\":23,  "ZsztasaW
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
    
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_3_element_with__age:23_comma_name__expect_colon(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
  "  \"age\":23,  "
  " \"name\"      "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
    
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_3_element_with__age:23_comma_name_comma__expect_string(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
  "  \"age\":23,  "
  " \"name\"  :    "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
    
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_3_element_with__age:23__age_not_string_expect_fail(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
  "  age :23  "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}


void test_given_3_element_with__age:23_comma_name:ali_baba__(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
  "  \"age\":23  ,"
  "  \"name\":  \"ali baba \"  "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    
    TEST_ASSERT_EQUAL(2,object.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object.type);
    
    TEST_ASSERT_EQUAL(ELEMENT_TYPE,object.head->data->type);
    TEST_ASSERT_EQUAL_STRING("age",object.head->data->name);
    TEST_ASSERT_EQUAL(NUMBER_TYPE,object.head->data->value->type);
    TEST_ASSERT_EQUAL(23,object.head->data->value->number);
    
    TEST_ASSERT_EQUAL(ELEMENT_TYPE,object.tail->data->type);
    TEST_ASSERT_EQUAL_STRING("name",object.tail->data->name);
    TEST_ASSERT_EQUAL(STRING_TYPE,object.head->data->value->type);
    TEST_ASSERT_EQUAL_STRING("ali baba ",object.tail->data->value->name)
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_given_3_element_with__age:23__name:ali_baba__expect_error_comma_missing(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;
  LinkedList object={.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  char *jsonText=
  "{"
  "  \"age\":23  "
  "  \"name\":  \"ali baba \"  "
  "}";
  
  Try{
    tokenizer=createTokenizer(jsonText);
    simpleJsonParser(tokenizer,&object);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}
*/
    
  