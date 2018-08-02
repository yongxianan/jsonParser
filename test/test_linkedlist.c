#include "unity.h"
#include "linkedlist.h"

void setUp(void)
{
}

void tearDown(void)
{
}

//test 1
void test_linkedlist_AddToHead_given_1_expect_item_inserted(void){
  LinkedList list={ .head=NULL, .tail=NULL, .count=0};
  int value=1;
  ListItem itemData = {.next=NULL, .data=(void *)&value};
  ListItem *item = &itemData;
  
  linkedListAddToHead(&list,item);
  
  TEST_ASSERT_EQUAL(item, list.head);
  TEST_ASSERT_EQUAL(item, list.tail);
  TEST_ASSERT_EQUAL(1, list.count);
}

//test 2
void test_linkedListAddToHead_given_linked_list_with_item_1_add_item_2_expect_item_2_then_1(void){
  int value1=1, value2=2;
  ListItem item1Data = {.next=NULL, .data=(void *)&value1};
  ListItem item2Data = {.next=NULL, .data=(void *)&value2};
  ListItem *item1 = &item1Data;
  ListItem *item2 = &item2Data;
  LinkedList list = {.head=item1, .tail=item1, .count=1};
  
  linkedListAddToHead(&list, item2);
  
  TEST_ASSERT_EQUAL(item2, list.head);
  TEST_ASSERT_EQUAL(item1, list.tail);
  TEST_ASSERT_EQUAL(item1, item2->next);
  TEST_ASSERT_EQUAL(NULL, item1->next);
  TEST_ASSERT_EQUAL(2, list.count);
}


void test_linkedListAddToHead_given_linked_list_with_item_1_add_item_2_expect_item_1_then_2(void){
  int value1=1, value2=2;
  ListItem item1Data = {.next=NULL, .data=(void *)&value1};
  ListItem item2Data = {.next=NULL, .data=(void *)&value2};
  ListItem *item1 = &item1Data;
  ListItem *item2 = &item2Data;
  LinkedList list = {.head=item1, .tail=item1, .count=1};
  
  linkedListAddToTail(&list, item2);
  
  TEST_ASSERT_EQUAL(item1, list.head);
  TEST_ASSERT_EQUAL(item2, list.tail);
  TEST_ASSERT_EQUAL(item2, item1->next);
  TEST_ASSERT_EQUAL(NULL, item2->next);
  TEST_ASSERT_EQUAL(2, list.count);
}

void test_linkedListAddToHead_given_linked_list_with_item_1_add_item_2_check_value1_and_value2(void){
  int value1=1, value2=2;
  ListItem item1Data = {.next=NULL, .data=(void *)&value1};
  ListItem item2Data = {.next=NULL, .data=(void *)&value2};
  ListItem *item1 = &item1Data;
  ListItem *item2 = &item2Data;
  LinkedList list = {.head=item1, .tail=item1, .count=1};
  
  linkedListAddToTail(&list, item2);
  
  TEST_ASSERT_EQUAL(2,*(int*)(item2->data));
  TEST_ASSERT_EQUAL(1,*(int*)(item1->data));
  
}

void test_createJsonNumber___22point545454_____(void){
  double doubledata=22.545454;
  JsonNumber *newJsonNumber=createJsonNumber(doubledata);
  TEST_ASSERT_EQUAL(NUMBER_TYPE,newJsonNumber->type);
  
/*
void test_createStringElement______string_hello_____(void){
  char *dataName="string";
  char *stringData="hello";
  JsonElement *element=createJsonElement(dataName,stringData);
  TEST_ASSERT_EQUAL(ELEMENT_TYPE,element->type);
  TEST_ASSERT_EQUAL_STRING("string",element->name);
  TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(element->value))->type);
  TEST_ASSERT_EQUAL_STRING("hello",((JsonString *)(element->value))->string);
}
  
void test_createBooleanElement______boolean_true_____(void){
  char *dataName="boolean";
  BOOLEANS booleanData=TRUE;
  JsonElement *element=createBooleanElement(dataName,booleanData);
  TEST_ASSERT_EQUAL(ELEMENT_TYPE,element->type);
  TEST_ASSERT_EQUAL_STRING("boolean",element->name);
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)(element->value))->type);
  TEST_ASSERT_EQUAL(TRUE,((JsonBoolean *)(element->value))->boolean);
}

void test_createBooleanElement______double_number_22point5454_____(void){
  char *dataName="double number";
  double doubleData=22.5454;
  JsonElement *element=createNumberElement(dataName,doubleData);
  TEST_ASSERT_EQUAL(ELEMENT_TYPE,element->type);
  TEST_ASSERT_EQUAL_STRING("double number",element->name);
  TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(element->value))->type);
  TEST_ASSERT_EQUAL(22.5454,((JsonNumber *)(element->value))->number);
}



void test_created_new_ListItem_with______string_hello_____and_add_to_tail(void){
  JsonType datatype=STRING_TYPE;
  char *stringData="hello";
  char *dataName="string";
  LinkedList list = {.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  createdListItemWithStringType(&list,datatype,dataName,stringData);
  
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(list.tail->data))->type);
  TEST_ASSERT_EQUAL_STRING("string", ((JsonElement *)(list.tail->data))->name);
  TEST_ASSERT_EQUAL(STRING_TYPE, ((JsonString *)(((JsonElement *)(list.tail->data))->value))->type);
  TEST_ASSERT_EQUAL_STRING("hello", ((JsonString *)(((JsonElement *)(list.tail->data))->value))->string);
}

void test_created_new_ListItem_with______boolean_TRUE_____and_add_to_tail(void){
  JsonType datatype=BOOLEAN_TYPE;
  BOOLEANS booleanData=TRUE;
  char *dataName="boolean";
  LinkedList list = {.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  createdListItemWithBooleanType(&list,datatype,dataName,booleanData);
  
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(list.tail->data))->type);
  TEST_ASSERT_EQUAL_STRING("boolean", ((JsonElement *)(list.tail->data))->name);
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE, ((JsonBoolean *)(((JsonElement *)(list.tail->data))->value))->type);
  TEST_ASSERT_EQUAL(TRUE, ((JsonBoolean *)(((JsonElement *)(list.tail->data))->value))->boolean);
}


void test_created_new_ListItem_with______floating_number_22point5454_____and_add_to_tail(void){
  JsonType datatype=NUMBER_TYPE;
  double doubleData=22.5454;
  char *dataName="floating number";
  LinkedList list = {.type=OBJECT_TYPE, .head=NULL, .tail=NULL, .count=0};
  
  createdListItemWithFloatingType(&list,datatype,dataName,doubleData);
  
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(list.tail->data))->type);
  TEST_ASSERT_EQUAL_STRING("floating number", ((JsonElement *)(list.tail->data))->name);
  TEST_ASSERT_EQUAL(NUMBER_TYPE, ((JsonNumber *)(((JsonElement *)(list.tail->data))->value))->type);
  TEST_ASSERT_EQUAL(22.5454, ((JsonNumber *)(((JsonElement *)(list.tail->data))->value))->number);
}


*/
