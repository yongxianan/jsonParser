# jsonParser

Inside the linkedlist.c file store function code that didn't use the tokenizer like gettoken(Tokenizer *tokenizer), freeToken(Token *token) and pushBackToken(Tokenizer *tokenizer, Token *token) .

And the jsonParser.c file store function code that did use the tokenizer like gettoken(Tokenizer *tokenizer), freeToken(Token *token) and pushBackToken(Tokenizer *tokenizer, Token *token) .

jsonParser.h file have #include "linkedlist.h", so all the structure code actually place in linkedlist.h.

Both jsonParser.c and linkedlist.c file require by simpleJsonParser(Tokenizer *tokenizer) function.

All the important test code is place in test_jsonParser.c and test_linkedlist.c file, these test code test the function use by simpleJsonParser(Tokenizer *tokenizer) function.
