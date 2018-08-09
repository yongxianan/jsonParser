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
#include "linkedlist.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_detectBooleanWithDataToken______false_____(void){
  CEXCEPTION_T e;
  Token *datatoken;
  Tokenizer *tokenizer;

  char *jsonText= "  false  " ;

  Try{
    tokenizer=createTokenizer(jsonText);
    datatoken=getToken(tokenizer);
    BOOLEANS booleanData=detectBooleanWithDataToken(datatoken);
    TEST_ASSERT_EQUAL(false,booleanData);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_detectBooleanWithDataToken______hello_____expect_fail(void){
  CEXCEPTION_T e;
  Token *datatoken;
  Tokenizer *tokenizer;

  char *jsonText= "  hello  " ;

  Try{
    tokenizer=createTokenizer(jsonText);
    datatoken=getToken(tokenizer);
    BOOLEANS booleanData=detectBooleanWithDataToken(datatoken);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_addAnyDataIntoArrayUsingDataToken______string_again____(void){
  CEXCEPTION_T e;
  Token *datatoken;
  Tokenizer *tokenizer;

  char *jsonText= "  \"string again\"  " ;
  Json *array=createJson(ARRAY_TYPE);

  Try{
    tokenizer=createTokenizer(jsonText);
    addAnyDataIntoArrayUsingDataToken(tokenizer,array);
    TEST_ASSERT_EQUAL(ARRAY_TYPE,array->type);
    TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)((array->list.head)->data))->type);
    TEST_ASSERT_EQUAL_STRING("string again",((JsonString *)((array->list.head)->data))->string);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_addAnyDataIntoArrayUsingDataToken______345point4744____(void){
  CEXCEPTION_T e;
  Token *datatoken;
  Tokenizer *tokenizer;

  char *jsonText= "  345.4744  " ;
  Json *array=createJson(ARRAY_TYPE);

  Try{
    tokenizer=createTokenizer(jsonText);
    addAnyDataIntoArrayUsingDataToken(tokenizer,array);
    TEST_ASSERT_EQUAL(ARRAY_TYPE,array->type);
    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)((array->list.head)->data))->type);
    TEST_ASSERT_EQUAL(345.4744,((JsonNumber *)((array->list.head)->data))->number);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_addAnyDataIntoArrayUsingDataToken______integer_number____(void){
  CEXCEPTION_T e;
  Token *datatoken;
  Tokenizer *tokenizer;

  char *jsonText= "  3458586  " ;
  Json *array=createJson(ARRAY_TYPE);

  Try{
    tokenizer=createTokenizer(jsonText);
    addAnyDataIntoArrayUsingDataToken(tokenizer,array);
    TEST_ASSERT_EQUAL(ARRAY_TYPE,array->type);
    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)((array->list.head)->data))->type);
    TEST_ASSERT_EQUAL(3458586,((JsonNumber *)((array->list.head)->data))->number);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_addAnyDataIntoArrayUsingDataToken______false____(void){
  CEXCEPTION_T e;
  Token *datatoken;
  Tokenizer *tokenizer;

  char *jsonText= "  false  " ;
  Json *array=createJson(ARRAY_TYPE);

  Try{
    tokenizer=createTokenizer(jsonText);
    addAnyDataIntoArrayUsingDataToken(tokenizer,array);
    TEST_ASSERT_EQUAL(ARRAY_TYPE,array->type);
    TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)((array->list.head)->data))->type);
    TEST_ASSERT_EQUAL(false,((JsonBoolean *)((array->list.head)->data))->boolean);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_addAnyDataIntoArrayUsingDataToken______testing____expect_fail(void){
  CEXCEPTION_T e;
  Token *datatoken;
  Tokenizer *tokenizer;

  char *jsonText= "  testing  " ;
  Json *array=createJson(ARRAY_TYPE);

  Try{
    tokenizer=createTokenizer(jsonText);
    addAnyDataIntoArrayUsingDataToken(tokenizer,array);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(ARRAY_TYPE,array->type);
    TEST_ASSERT_EQUAL(0,array->list.count);
    TEST_ASSERT_EQUAL(ARRAY_TYPE,array->type);
    TEST_ASSERT_EQUAL(NULL,array->list.head);
    TEST_ASSERT_EQUAL(NULL,array->list.tail);
  }
  freeTokenizer(tokenizer);
}

//this function test without ':'  because this function will applied on
//another function which will take care of ':'
//this function only get element name from "elementtoken=getToken(tokenizer);"
//which is actually call "array test"
//able to get array data from "Tokenizer *tokenizer;"
void test_addElementNameAndArrayIntoObject_____array_test____number___string_____boolean(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"array test\"  [ 22.55   , \"epic array test\"   ,  false ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object.list.head->data))->type);

    TEST_ASSERT_EQUAL(ARRAY_TYPE,((Json *)(((JsonElement *)(object.list.head->data))->value))->type);
    TEST_ASSERT_EQUAL(3,((Json *)(((JsonElement *)(object.list.head->data))->value))->list.count);

    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->data))->type);
    TEST_ASSERT_EQUAL(22.55,((JsonNumber *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->data))->number);

    TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->next->data))->type);
    TEST_ASSERT_EQUAL_STRING("epic array test",((JsonString *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->next->data))->string);

    TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->next->next->data))->type);
    TEST_ASSERT_EQUAL(false,((JsonBoolean *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->next->next->data))->boolean);

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);

}

void test_addElementNameAndArrayIntoObject_____array_test____integer_number___string_____boolean(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"array test\"  [ 5866   , \"epic array test\"   ,  false ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object.list.head->data))->type);

    TEST_ASSERT_EQUAL(ARRAY_TYPE,((Json *)(((JsonElement *)(object.list.head->data))->value))->type);
    TEST_ASSERT_EQUAL(3,((Json *)(((JsonElement *)(object.list.head->data))->value))->list.count);

    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->data))->type);
    TEST_ASSERT_EQUAL(5866,((JsonNumber *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->data))->number);

    TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->next->data))->type);
    TEST_ASSERT_EQUAL_STRING("epic array test",((JsonString *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->next->data))->string);

    TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->next->next->data))->type);
    TEST_ASSERT_EQUAL(false,((JsonBoolean *)(((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head->next->next->data))->boolean);

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);

}

void test_addElementNameAndArrayIntoObject_____array_test____square_bracket__expect_pass(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"array test\"   [] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object.list.head->data))->type);

    TEST_ASSERT_EQUAL(ARRAY_TYPE,((Json *)(((JsonElement *)(object.list.head->data))->value))->type);
    TEST_ASSERT_EQUAL(0,((Json *)(((JsonElement *)(object.list.head->data))->value))->list.count);
    TEST_ASSERT_EQUAL(NULL,((Json *)(((JsonElement *)(object.list.head->data))->value))->list.head);
    TEST_ASSERT_EQUAL(NULL,((Json *)(((JsonElement *)(object.list.head->data))->value))->list.tail);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);

}

void test_addElementNameAndArrayIntoObject____array_test____number___string____unknown____expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"array test\"   [ 22.55   , \"epic array test\"   ,  fal ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_addElementNameAndArrayIntoObject____array_test____number___string____comma____expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"array test\"  [ 22.55   , \"epic array test\"   ,  ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_addElementNameAndArrayIntoObject____array_test____comma___plus____expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"array test\"  [  ,,,,,+  ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_addElementNameAndArrayIntoObject____array_test____random_symbol____expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"array test\"  [ + _____==== ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}
////////////////////////////////////////
void test_addElementNameAndArrayIntoObject____array_test____random_data_with_square_bracket_missing____expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"random data\"   \"epic array test\" ,  false ,23.655      ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_addElementNameAndArrayIntoObject____array_test____number___comma____Quotation_mark_expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *jsonText= "  \"array test\"  [ 22.55   , \"   ,  ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);

    elementtoken=getToken(tokenizer);   //just to get element name which is "array test"
    addElementNameAndArrayIntoObject(elementtoken->str,tokenizer,&object);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_addElementAndDataIntoObject_______random_data_array(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;

  char *jsonText= "  \"random data\" :[ 5866 , \"epic array test\" ,  false ,23.655      ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=createJson(OBJECT_TYPE);

    elementtoken=getToken(tokenizer);
    addElementAndDataIntoObject(elementtoken,tokenizer,object);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object->list.head->data))->type);

    TEST_ASSERT_EQUAL(ARRAY_TYPE,((Json *)(((JsonElement *)(object->list.head->data))->value))->type);
    TEST_ASSERT_EQUAL(4,((Json *)(((JsonElement *)(object->list.head->data))->value))->list.count);

    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(((Json *)(((JsonElement *)(object->list.head->data))->value))->list.head->data))->type);
    TEST_ASSERT_EQUAL(5866,((JsonNumber *)(((Json *)(((JsonElement *)(object->list.head->data))->value))->list.head->data))->number);

    TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(((Json *)(((JsonElement *)(object->list.head->data))->value))->list.head->next->data))->type);
    TEST_ASSERT_EQUAL_STRING("epic array test",((JsonString *)(((Json *)(((JsonElement *)(object->list.head->data))->value))->list.head->next->data))->string);

    TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)(((Json *)(((JsonElement *)(object->list.head->data))->value))->list.head->next->next->data))->type);
    TEST_ASSERT_EQUAL(false,((JsonBoolean *)(((Json *)(((JsonElement *)(object->list.head->data))->value))->list.head->next->next->data))->boolean);

    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(((Json *)(((JsonElement *)(object->list.head->data))->value))->list.tail->data))->type);
    TEST_ASSERT_EQUAL(23.655,((JsonNumber *)(((Json *)(((JsonElement *)(object->list.head->data))->value))->list.tail->data))->number);

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}



void test_addElementAndDataIntoObject_______random_data_array_with_comma_problem_expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;

  char *jsonText= "  \"random data\" :[ , \"epic array test\" ,  false ,23.655      ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=createJson(OBJECT_TYPE);

    elementtoken=getToken(tokenizer);
    addElementAndDataIntoObject(elementtoken,tokenizer,object);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_addElementAndDataIntoObject_______random_data_array_without_colon____expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;

  char *jsonText= "  \"random data\" [ 5866, \"epic array test\" ,  false ,23.655      ] " ;

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=createJson(OBJECT_TYPE);

    elementtoken=getToken(tokenizer);
    addElementAndDataIntoObject(elementtoken,tokenizer,object);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_addElementAndDataIntoObject_______number_22point55(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;

  char *jsonText= "  \"number\" :22.55  " ;

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=createJson(OBJECT_TYPE);

    elementtoken=getToken(tokenizer);
    addElementAndDataIntoObject(elementtoken,tokenizer,object);

    TEST_ASSERT_EQUAL(1,object->list.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object->type);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object->list.head->data))->type);
    TEST_ASSERT_EQUAL_STRING("number",((JsonElement *)(object->list.head->data))->name);
    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)((JsonElement *)(object->list.head->data))->value)->type);
    TEST_ASSERT_EQUAL(22.55,((JsonNumber *)(((JsonElement *)(object->list.head->data))->value))->number);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}


void test_addElementAndDataIntoObject_______string_my_name(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;

  char *jsonText= "  \"string\" : \"my name\"  " ;

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=createJson(OBJECT_TYPE);

    elementtoken=getToken(tokenizer);
    addElementAndDataIntoObject(elementtoken,tokenizer,object);

    TEST_ASSERT_EQUAL(1,object->list.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object->type);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object->list.head->data))->type);
    TEST_ASSERT_EQUAL_STRING("string",((JsonElement *)(object->list.head->data))->name);
    TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)((JsonElement *)(object->list.head->data))->value)->type);
    TEST_ASSERT_EQUAL_STRING("my name",((JsonString *)(((JsonElement *)(object->list.head->data))->value))->string);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_addElementAndDataIntoObject_______boOlEaN_false(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;

  char *jsonText= "  \"boOlEaN\" : false  " ;

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=createJson(OBJECT_TYPE);

    elementtoken=getToken(tokenizer);
    addElementAndDataIntoObject(elementtoken,tokenizer,object);

    TEST_ASSERT_EQUAL(1,object->list.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object->type);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object->list.head->data))->type);
    TEST_ASSERT_EQUAL_STRING("boOlEaN",((JsonElement *)(object->list.head->data))->name);
    TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)((JsonElement *)(object->list.head->data))->value)->type);
    TEST_ASSERT_EQUAL(false,((JsonBoolean *)(((JsonElement *)(object->list.head->data))->value))->boolean);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_addElementAndDataIntoObject_______boOlEaN_apple____expect_fail(void){
  CEXCEPTION_T e;
  Token *elementtoken;
  Tokenizer *tokenizer;

  char *jsonText= "  \"boOlEaN\" : apple  " ;
  Json *object=createJson(OBJECT_TYPE);
  tokenizer=createTokenizer(jsonText);
  elementtoken=getToken(tokenizer);
  Try{
    addElementAndDataIntoObject(elementtoken,tokenizer,object);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_ASSERT_EQUAL(0,object->list.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object->type);
    TEST_ASSERT_EQUAL(NULL,object->list.head);
    TEST_ASSERT_EQUAL(NULL,object->list.tail);
  }
  freeTokenizer(tokenizer);
}

void test_given_empty_object(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_ASSERT_EQUAL(0,object->list.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object->type);
    TEST_ASSERT_EQUAL(NULL,object->list.head);
    TEST_ASSERT_EQUAL(NULL,object->list.tail);

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

  char *jsonText=
  "{{"
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_first_bracket_missing(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_with_second_bracket_missing(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{ ";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

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

  char *jsonText=
  "   ";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

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

  char *jsonText=
  "{"
     "  age "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_element_name_without_colon(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
     "  \"age\" "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_element_name_without_data(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
     "  \"age\": "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

/////////////////////////////////////////////////////////

void test_element_name_and_integer_number(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
  "  \"age\" :23  "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_ASSERT_EQUAL(1,object->list.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object->type);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object->list.head->data))->type);
    TEST_ASSERT_EQUAL_STRING("age",((JsonElement *)(object->list.head->data))->name);
    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)((JsonElement *)(object->list.head->data))->value)->type);
    TEST_ASSERT_EQUAL(23,((JsonNumber *)(((JsonElement *)(object->list.head->data))->value))->number);

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_given_first_element_name_and_integer_with_comma_expect_next_string(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
  "  \"age\":23,  "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_with_first_set_of_data_then_second_element_expect_colon(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
  "  \"age\":23,  "
  " \"name\"      "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_with_first_set_of_data_then_second_element_expect_data(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
  "  \"age\":23,  "
  " \"name\"  :    "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");

  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}

void test_given_name_not_a_string_expect_fail(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
  "  age :23  "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}


void test_given_2_set_of_data_with_data_type_number_and_string(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
  "  \"age\":23  ,"
  "  \"name\":  \"ali baba \"  "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);

    TEST_ASSERT_EQUAL(2,object->list.count);
    TEST_ASSERT_EQUAL(OBJECT_TYPE,object->type);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object->list.head->data))->type);
    TEST_ASSERT_EQUAL_STRING("age",((JsonElement *)(object->list.head->data))->name);
    TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(((JsonElement *)(object->list.head->data))->value))->type);
    TEST_ASSERT_EQUAL(23,((JsonNumber *)(((JsonElement *)(object->list.head->data))->value))->number);

    TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(object->list.tail->data))->type);
    TEST_ASSERT_EQUAL_STRING("name",((JsonElement *)(object->list.tail->data))->name);
    TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(((JsonElement *)(object->list.tail->data))->value))->type);
    TEST_ASSERT_EQUAL_STRING("ali baba ",((JsonString *)(((JsonElement *)(object->list.tail->data))->value))->string);
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
    TEST_FAIL_MESSAGE("System Error: Don't expect any exception to be thrown!");
  }
  freeTokenizer(tokenizer);
}

void test_given___age_23_______name_ali_baba_________expect_error_comma_missing(void){
  CEXCEPTION_T e;
  Token *token;
  Tokenizer *tokenizer;

  char *jsonText=
  "{"
  "  \"age\":23  "
  "  \"name\":  \"ali baba \"  "
  "}";

  Try{
    tokenizer=createTokenizer(jsonText);
    Json *object=simpleJsonParser(tokenizer);
    TEST_FAIL_MESSAGE("System Error: Expect any exception to be thrown!");
  }
  Catch(e){
    dumpTokenErrorMessage(e, 1);
  }
  freeTokenizer(tokenizer);
}
