#ifndef hash_h
#define hash_h

#define HASH_SIZE 997

#define SYMBOL_LIT_INTEGER	1
#define SYMBOL_LIT_FLOAT	2
#define SYMBOL_LIT_CHAR		3
#define SYMBOL_LIT_STRING	4
#define SYMBOL_IDENTIFIER	5

#define TYPE_SCALAR     	6
#define TYPE_VECTOR     	7
#define TYPE_FUNCTION		8

#define DATATYPE_UNDEFINED 9
#define DATATYPE_INTEGER 10
#define DATATYPE_FLOAT 11
#define DATATYPE_BOOL 12

typedef struct hash_node {
    int type;
    int dataType;
    char *text;
    struct hash_node *next;
} HASH_NODE;

void hashInit(void);
int hashAddress(char *text);
HASH_NODE* hashInsert(int type, char *text);
HASH_NODE* hashFind(char *text);
void hashPrint(void);
int checkUndeclared();

#endif