#include "unity.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>


Json *createJson(JsonType whatJsonType){
  Json *newJson=(Json *)malloc(sizeof(Json));
  newJson->type=whatJsonType;
  (newJson->list).head=NULL;
  (newJson->list).tail=NULL;
  (newJson->list).count=0;
  return newJson;
}


linkedListAddToHead(LinkedList *list, ListItem *itemToAdd){
  ListItem *tempItem=itemToAdd;
  if(list->head == NULL && list->tail == NULL){
    (list->head) = tempItem;
    (list->tail) = tempItem;
    tempItem->next=NULL;
    (list->count) = (list->count)+1;
  }
  else{
    /*
    while(tempItem->next!=NULL){
      tempItem=tempItem->next;
    }
    */
    tempItem->next=list->head;
    list->head=itemToAdd;
    (list->count) = (list->count)+1;
  }
}



linkedListAddToTail(LinkedList *list, ListItem *itemToAdd){
  int i=0;
  ListItem *tempItem=itemToAdd;
  if(list->head == NULL && list->tail == NULL){
    (list->head) = tempItem;
    (list->tail) = tempItem;
    tempItem->next=NULL;
    (list->count) = (list->count)+1;
  }
  else{
    list->tail->next=itemToAdd;
    list->tail=tempItem;
    (list->count) = (list->count)+1;
  }
}


JsonElement *createJsonElement(char *dataName, void *jsonEntity){
  JsonElement *tempElement=(JsonElement *)malloc(sizeof(JsonElement));
  tempElement->type=ELEMENT_TYPE;
  tempElement->name=dataName;
  tempElement->value=jsonEntity;

  return tempElement;
}

JsonNumber *createJsonNumber(double doubledata){
  JsonNumber *tempNumber=(JsonNumber *)malloc(sizeof(JsonNumber));
  tempNumber->type=NUMBER_TYPE;
  tempNumber->number=doubledata;
  return tempNumber;
}

JsonString *createJsonString(char *stringData){
  JsonString *tempString=(JsonString *)malloc(sizeof(JsonString));
  tempString->type=STRING_TYPE;
  tempString->string=stringData;
  return tempString;
}

JsonBoolean *createJsonBoolean(BOOLEANS booleanData){
  JsonBoolean *tempBoolean=(JsonBoolean *)malloc(sizeof(JsonBoolean));
  tempBoolean->type=BOOLEAN_TYPE;
  tempBoolean->boolean=booleanData;
  return tempBoolean;
}


/*
    try to make use of function like:
    JsonNumber *createJsonNumber(double doubledata);
    JsonString *createJsonString(char *stringData);
    JsonBoolean *createJsonBoolean(BOOLEANS booleanData);
    to create array that can take in any type of data
    note: array use the exact same structure
          (include type and linkedlist) as object
*/
addJsonEntityToArray(Json *array, void *jsonEntity){
  ListItem *tempItem=(ListItem *)malloc(sizeof(ListItem));
  tempItem->data=(void *)jsonEntity;
  linkedListAddToTail(&(array->list), tempItem);
}


//this add element to object
addElementIntoObject(Json *object,JsonElement *element){
  ListItem *tempItem=(ListItem *)malloc(sizeof(ListItem));
  tempItem->data=(void *)element;

  linkedListAddToTail(&(object->list),tempItem);
}

addNameAndStringIntoObject(char *name,char *stringData,Json *object){
  JsonString *data=createJsonString(stringData);
  JsonElement *element=createJsonElement(name, (void *)data);
  addElementIntoObject(object,element);
}

addNameAndNumberIntoObject(char *name,double numbers,Json *object){
  JsonNumber *data=createJsonNumber(numbers);
  JsonElement *element=createJsonElement(name, (void *)data);
  addElementIntoObject(object,element);
}

addNameAndBooleanIntoObject(char *name,BOOLEANS booleanData,Json *object){
  JsonBoolean *data=createJsonBoolean(booleanData);
  JsonElement *element=createJsonElement(name, (void *)data);
  addElementIntoObject(object,element);
}
