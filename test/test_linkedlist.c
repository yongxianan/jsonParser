#include "unity.h"
#include "linkedlist.h"

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
  TEST_ASSERT_EQUAL(22.545454,newJsonNumber->number);
}

void test_createJsonString___hello_____(void){
  char *str="hello";
  JsonString *newJsonString=createJsonString(str);
  TEST_ASSERT_EQUAL(STRING_TYPE,newJsonString->type);
  TEST_ASSERT_EQUAL_STRING("hello",newJsonString->string);
}

void test_createJsonBoolean___true_____(void){
  BOOLEANS boolean=true;
  JsonBoolean *newJsonBoolean=createJsonBoolean(boolean);
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE,newJsonBoolean->type);
  TEST_ASSERT_EQUAL(true,newJsonBoolean->boolean);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//insert array[0]=123.123 , array[1]="string" , array[2]=false

void test_addJsonEntityToArray_____123point123____string_______false_____(void){

  JsonNumber newJsonNumber={.type=NUMBER_TYPE,.number=123.123};
  JsonString newJsonString={.type=STRING_TYPE,.string="merry christmas"};
  JsonBoolean newJsonBoolean={.type=BOOLEAN_TYPE,.boolean=false};

  Json *array=createJson(ARRAY_TYPE);

  addJsonEntityToArray(array, (void *)(&newJsonNumber));
  addJsonEntityToArray(array, (void *)(&newJsonString));
  addJsonEntityToArray(array, (void *)(&newJsonBoolean));

  ListItem *li;
  li=(array->list.head);
  TEST_ASSERT_EQUAL(ARRAY_TYPE,array->type);
  TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(li->data))->type);
  TEST_ASSERT_EQUAL(123.123,((JsonNumber *)(li->data))->number);

  li=li->next;
  TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("merry christmas",((JsonString *)(li->data))->string);

  li=li->next;
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)(li->data))->type);
  TEST_ASSERT_EQUAL(false,((JsonBoolean *)(li->data))->boolean);

}

void test_createJsonElement_for_array__________123point123____string_______false_____(void){
  char *dataName="array with number, boolean, string";
  JsonNumber newJsonNumber={.type=NUMBER_TYPE,.number=123.123};
  JsonString newJsonString={.type=STRING_TYPE,.string="merry christmas"};
  JsonBoolean newJsonBoolean={.type=BOOLEAN_TYPE,.boolean=false};

  Json *array=createJson(ARRAY_TYPE);

  addJsonEntityToArray(array, (void *)(&newJsonNumber));
  addJsonEntityToArray(array, (void *)(&newJsonString));
  addJsonEntityToArray(array, (void *)(&newJsonBoolean));

  JsonElement *element=createJsonElement("array with number, boolean, string", (void *)(array));
  ListItem *li;
  li=(array->list.head)->next;
  TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(li->data))->type);

  ListItem *li2;
  li2=((Json *)(element->value))->list.head;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE,element->type);

  TEST_ASSERT_EQUAL(ARRAY_TYPE,((Json *)(element->value))->type);
  TEST_ASSERT_EQUAL(3,((Json *)(element->value))->list.count);
  TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(li2->data))->type);
  TEST_ASSERT_EQUAL(123.123,((JsonNumber *)(li2->data))->number);

  li2=li2->next;
  TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(li2->data))->type);
  TEST_ASSERT_EQUAL_STRING("merry christmas",((JsonString *)(li2->data))->string);

  li2=li2->next;
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)(li2->data))->type);
  TEST_ASSERT_EQUAL(false,((JsonBoolean *)(li2->data))->boolean);

}

void test_createJsonElement_______double_number_22point545454____(void){
  char *dataName="double number";
  JsonNumber newJsonNumber={.type=NUMBER_TYPE,.number=22.545454};
  JsonElement *element=createJsonElement(dataName, (void *)(&newJsonNumber));
  TEST_ASSERT_EQUAL(ELEMENT_TYPE,element->type);
  TEST_ASSERT_EQUAL_STRING("double number",element->name);
  TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(element->value))->type);
  TEST_ASSERT_EQUAL(22.545454,((JsonNumber *)(element->value))->number);
}


void test_createJsonElement_______string_hello______(void){
  char *dataName="string";
  JsonString newJsonString={.type=STRING_TYPE,.string="string"};
  JsonElement *element=createJsonElement(dataName, (void *)(&newJsonString));
  TEST_ASSERT_EQUAL(ELEMENT_TYPE,element->type);
  TEST_ASSERT_EQUAL_STRING("string",element->name);
  TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(element->value))->type);
  TEST_ASSERT_EQUAL("string",((JsonString *)(element->value))->string);
}

void test_createJsonElement_______boolean_true______(void){
  char *dataName="boolean";
  JsonBoolean newJsonBoolean={.type=BOOLEAN_TYPE,.boolean=true};
  JsonElement *element=createJsonElement(dataName, (void *)(&newJsonBoolean));
  TEST_ASSERT_EQUAL(ELEMENT_TYPE,element->type);
  TEST_ASSERT_EQUAL_STRING("boolean",element->name);
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)(element->value))->type);
  TEST_ASSERT_EQUAL(true,((JsonBoolean *)(element->value))->boolean);
}


void test_addElementIntoObject_for_array______123point123____string_______false_____(void){
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  char *dataName="array with number, boolean, string";
  JsonNumber newJsonNumber={.type=NUMBER_TYPE,.number=123.123};
  JsonString newJsonString={.type=STRING_TYPE,.string="merry christmas"};
  JsonBoolean newJsonBoolean={.type=BOOLEAN_TYPE,.boolean=false};

  Json *array=createJson(ARRAY_TYPE);

  addJsonEntityToArray(array, (void *)(&newJsonNumber));
  addJsonEntityToArray(array, (void *)(&newJsonString));
  addJsonEntityToArray(array, (void *)(&newJsonBoolean));

  JsonElement *element=createJsonElement("array with number, boolean, string", (void *)(array));
  addElementIntoObject(&object,element);
  ListItem *li2;
  li2=(array->list.head)->next;
  TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(li2->data))->type);

  ListItem *li;
  li=object.list.head;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE,((JsonElement *)(li->data))->type);

  TEST_ASSERT_EQUAL(ARRAY_TYPE,((Json *)(((JsonElement *)(li->data))->value))->type);
  TEST_ASSERT_EQUAL(3,((Json *)(((JsonElement *)(li->data))->value))->list.count);

  li=((Json *)(((JsonElement *)(li->data))->value))->list.head;
  TEST_ASSERT_EQUAL(NUMBER_TYPE,((JsonNumber *)(li->data))->type);
  TEST_ASSERT_EQUAL(123.123,((JsonNumber *)(li->data))->number);

  li=li->next;
  TEST_ASSERT_EQUAL(STRING_TYPE,((JsonString *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("merry christmas",((JsonString *)(li->data))->string);

  li=li->next;
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE,((JsonBoolean *)(li->data))->type);
  TEST_ASSERT_EQUAL(false,((JsonBoolean *)(li->data))->boolean);

}


void test_addElementIntoObject_______string_hello_________(void){
  char *dataName="string";
  char *stringData="hello";
  Json JsonWithStringHello = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  JsonString *newJsonString=createJsonString("hello");
  JsonElement *newJsonElement=createJsonElement("string", (void *)newJsonString);

  addElementIntoObject(&JsonWithStringHello,newJsonElement);

  ListItem *li;
  li=JsonWithStringHello.list.tail;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("string", ((JsonElement *)(li->data))->name);
  TEST_ASSERT_EQUAL(STRING_TYPE, ((JsonString *)(((JsonElement *)(li->data))->value))->type);
  TEST_ASSERT_EQUAL_STRING("hello", ((JsonString *)(((JsonElement *)(li->data))->value))->string);
}

void test_addElementIntoObject_______bool_test_true_________(void){
  char *dataName="bool test";
  BOOLEANS boolData=true;
  Json JsonWithBoolTest = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  JsonBoolean *newJsonBoolean=createJsonBoolean(boolData);
  JsonElement *newJsonElement=createJsonElement("bool test", (void *)newJsonBoolean);

  addElementIntoObject(&JsonWithBoolTest,newJsonElement);

  ListItem *li;
  li=JsonWithBoolTest.list.tail;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("bool test", ((JsonElement *)(li->data))->name);
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE, ((JsonBoolean *)(((JsonElement *)(li->data))->value))->type);
  TEST_ASSERT_EQUAL(true, ((JsonBoolean *)(((JsonElement *)(li->data))->value))->boolean);
}

void test_addElementIntoObject_______double_number_22point545454__________(void){
  char *dataName="double_number";
  double doublenumber=22.545454;
  Json JsonWithDoubleNumberTest = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  JsonNumber *newJsonNumber=createJsonNumber(doublenumber);
  JsonElement *newJsonElement=createJsonElement("double_number", (void *)newJsonNumber);

  addElementIntoObject(&JsonWithDoubleNumberTest,newJsonElement);

  ListItem *li;
  li=JsonWithDoubleNumberTest.list.tail;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("double_number", ((JsonElement *)(li->data))->name);
  TEST_ASSERT_EQUAL(NUMBER_TYPE, ((JsonNumber *)(((JsonElement *)(li->data))->value))->type);
  TEST_ASSERT_EQUAL(22.545454, ((JsonNumber *)(((JsonElement *)(li->data))->value))->number);
}

void test_addNameAndBooleanIntoObject(void){
  char *name="boolean testing";
  BOOLEANS booleanData=false;
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};
  addNameAndBooleanIntoObject(name,booleanData,&object);

  ListItem *li;
  li=object.list.tail;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("boolean testing", ((JsonElement *)(li->data))->name);
  TEST_ASSERT_EQUAL(BOOLEAN_TYPE, ((JsonBoolean *)(((JsonElement *)(li->data))->value))->type);
  TEST_ASSERT_EQUAL(false, ((JsonBoolean *)(((JsonElement *)(li->data))->value))->boolean);
}

void test_addNameAndStringIntoObject(void){
  char *name="string testing";
  char *stringData="what kind of string";
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};

  addNameAndStringIntoObject(name,stringData,&object);


  TEST_ASSERT_EQUAL(1, object.list.count);

  ListItem *li;
  li=object.list.tail;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("string testing", ((JsonElement *)(li->data))->name);
  TEST_ASSERT_EQUAL(STRING_TYPE, ((JsonString *)(((JsonElement *)(li->data))->value))->type);
  TEST_ASSERT_EQUAL_STRING("what kind of string", ((JsonString *)(((JsonElement *)(li->data))->value))->string);
}

void test_addNameAndNumberIntoObject(void){
  char *name1="double_number";
  double numbers=22.545454;
  char *name2="string testing";
  char *stringData="what kind of string";
  Json object = {.type=OBJECT_TYPE, .list.head=NULL, .list.tail=NULL, .list.count=0};

  addNameAndNumberIntoObject(name1,numbers,&object);
  addNameAndStringIntoObject(name2,stringData,&object);

  TEST_ASSERT_EQUAL(2, object.list.count);

  ListItem *li;
  li=object.list.head;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("double_number", ((JsonElement *)(li->data))->name);
  TEST_ASSERT_EQUAL(NUMBER_TYPE, ((JsonNumber *)(((JsonElement *)(li->data))->value))->type);
  TEST_ASSERT_EQUAL(22.545454, ((JsonNumber *)(((JsonElement *)(li->data))->value))->number);

  li=li->next;
  TEST_ASSERT_EQUAL(ELEMENT_TYPE, ((JsonElement *)(li->data))->type);
  TEST_ASSERT_EQUAL_STRING("string testing", ((JsonElement *)(li->data))->name);
  TEST_ASSERT_EQUAL(STRING_TYPE, ((JsonString *)(((JsonElement *)(li->data))->value))->type);
  TEST_ASSERT_EQUAL_STRING("what kind of string", ((JsonString *)(((JsonElement *)(li->data))->value))->string);
}
