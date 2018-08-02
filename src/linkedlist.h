#ifndef _LINKEDLIST_H
#define _LINKEDLIST_H


typedef enum {
  ELEMENT_TYPE,
  OBJECT_TYPE,
  BOOLEAN_TYPE,
  NUMBER_TYPE,
  ARRAY_TYPE,
  STRING_TYPE,
} JsonType;

typedef enum {
  TRUE,
  FALSE,
}BOOLEANS;


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
//4.array
typedef struct JsonArray JsonArray;
struct JsonArray{
  JsonType type;
  char array[];
};
//3.string
typedef struct JsonString JsonString;
struct JsonString{
  JsonType type;
  char *string;
};

void linkedListAddToHead(LinkedList *list, ListItem *itemToAdd);
void linkedListAddToTail(LinkedList *list, ListItem *itemToAdd);
ListItem *linkedListRemoveFromHead(LinkedList *list);
ListItem *linkedListRemoveFromTail(LinkedList *list);
#endif // _LINKEDLIST_H
