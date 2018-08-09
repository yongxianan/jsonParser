#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H

#include "Tokenizer.h"

///////////////linkedlist component//////////////////
typedef struct ListItem ListItem;
struct ListItem{
  ListItem *next;
  void *data;
};



typedef struct LinkedList LinkedList;
struct LinkedList{
  ListItem *head;
  ListItem *tail;
  int count;
};
////////////////////////////////////////////////////////

//////////////////////structure for Json///////////////////
typedef enum {
  ELEMENT_TYPE,
  OBJECT_TYPE,
  BOOLEAN_TYPE,
  NUMBER_TYPE,
  ARRAY_TYPE,
  STRING_TYPE,
} JsonType;

typedef enum {
  true,
  false,
}BOOLEANS;

typedef struct Json Json;
struct Json{
  JsonType type;
  LinkedList list;
};

typedef struct JsonElement JsonElement;
struct JsonElement{
  JsonType type;
  char *name;
  void *value;
};
/////////////////////////////////////////////////////////////////////////////////

//////////////////struct for different data///////////////////////////////////////////////////
//1.double
typedef struct JsonNumber JsonNumber;
struct JsonNumber{
  JsonType type;
  double number;
};
//2.boolean
typedef struct JsonBoolean JsonBoolean;
struct JsonBoolean{
  JsonType type;
  BOOLEANS boolean;
};
//3.array

//4.string
typedef struct JsonString JsonString;
struct JsonString{
  JsonType type;
  char *string;
};
//////////////////////////////////////////////////////////////////////////

Json *createJson(JsonType whatJsonType);
void linkedListAddToHead(LinkedList *list, ListItem *itemToAdd);
void linkedListAddToTail(LinkedList *list, ListItem *itemToAdd);
JsonElement *createJsonElement(char *dataName, void *jsonEntity);
JsonNumber *createJsonNumber(double doubledata);
JsonString *createJsonString(char *stringData);
JsonBoolean *createJsonBoolean(BOOLEANS booleanData);
void addElementIntoObject(Json *object,JsonElement *element);

//ListItem *linkedListRemoveFromHead(LinkedList *list);
//ListItem *linkedListRemoveFromTail(LinkedList *list);
#endif // _LINKEDLIST_H
