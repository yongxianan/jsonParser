#include "unity.h"
#include "linkedlist.h"
#include <stdlib.h>
#include <stdio.h>

linkedListAddToHead(LinkedList *list, ListItem *itemToAdd){
  ListItem *tempItem=itemToAdd;
  if(list->head == NULL && list->tail == NULL){
    (list->head) = tempItem;
    (list->tail) = tempItem;
    (list->count) = (list->count)+1;
  }
  else{
    while(tempItem->next!=NULL){
      tempItem=tempItem->next;
    }
    tempItem->next=list->head;
    list->head=itemToAdd;
    (list->count) = (list->count)+1;
  }
}

linkedListAddToTail(LinkedList *list, ListItem *itemToAdd){
  ListItem *tempItem=itemToAdd;
  if(list->head == NULL && list->tail == NULL){
    (list->head) = tempItem;
    (list->tail) = tempItem;
    (list->count) = (list->count)+1;
  }
  else{
    while(tempItem->next!=NULL){
      tempItem=tempItem->next;
    }
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
  tempNumber->number=doubleData;
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
createdListItemWithBooleanType(Json *object,JsonType datatype,char *dataName,BOOLEANS data){
  ListItem *tempItem=(ListItem *)malloc(sizeof(ListItem));
  
  JsonBoolean *tempBoolean=(JsonBoolean *)malloc(sizeof(JsonBoolean));
  tempBoolean->type=datatype;
  tempBoolean->boolean=data;
  
  JsonElement *tempElement=(JsonElement *)malloc(sizeof(JsonElement));
  tempElement->type=ELEMENT_TYPE;
  tempElement->name=dataName;
  tempElement->value=tempBoolean;
  
  tempItem->data=(void *)tempElement;
  
  linkedListAddToTail(list, tempItem);
}


createdListItemWithFloatingType(LinkedList *list,JsonType datatype,char *dataName,double data){
  ListItem *tempItem=(ListItem *)malloc(sizeof(ListItem));
  
  JsonNumber *tempNumber=(JsonNumber *)malloc(sizeof(JsonNumber));
  tempNumber->type=datatype;
  tempNumber->number=data;
  
  JsonElement *tempElement=(JsonElement *)malloc(sizeof(JsonElement));
  tempElement->type=ELEMENT_TYPE;
  tempElement->name=dataName;
  tempElement->value=tempNumber;
  
  tempItem->data=(void *)tempElement;
  
  linkedListAddToTail(list, tempItem);
}


createdListItemWithStringType(LinkedList *list,JsonType datatype,char *dataName,char *data){
  ListItem *tempItem=(ListItem *)malloc(sizeof(ListItem));
  
  JsonString *tempString=(JsonString *)malloc(sizeof(JsonString));
  tempString->type=datatype;
  tempString->string=data;
  
  JsonElement *tempElement=(JsonElement *)malloc(sizeof(JsonElement));
  tempElement->type=ELEMENT_TYPE;
  tempElement->name=dataName;
  tempElement->value=tempString;
  
  tempItem->data=(void *)tempElement;
  
  linkedListAddToTail(list, tempItem);
}
*/