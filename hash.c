#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "hash.h"

HASH_NODE *Table[HASH_SIZE];

void hashInit(void) {
    for (int i=0; i<HASH_SIZE; ++i) {
        Table[i] = 0;
    }
};

int hashAddress(char *text) {
    int i;
    int address = 1;
    for (int i=0; i<strlen(text); ++i) {
        address = (address * text[i]) % HASH_SIZE + 1;
    }
    return address - 1;
}

HASH_NODE* hashInsert(int type, char *text) {
    HASH_NODE *newnode;
    int address;
    address = hashAddress(text);

    if (newnode = hashFind(text))
        return newnode;

    newnode = (HASH_NODE*) calloc(1, sizeof(HASH_NODE));
    newnode->type = type;
    newnode->text = calloc(strlen(text)+1, sizeof(char));
    strcpy(newnode->text, text);

    newnode->next = Table[address];
    Table[address] = newnode;
    return newnode;
}

HASH_NODE* hashFind(char *text) {
    HASH_NODE *node;
    int address;
    address = hashAddress(text);

    for (node = Table[address]; node; node = node->next) {
        if (!strcmp(text, node->text))
            return node;
    }
    return 0;
}

void hashPrint(void) {
    HASH_NODE *node;
    printf("\n------------Hash table:-----------\n");
    for (int i=0; i<HASH_SIZE; ++i) {
        for (node = Table[i]; node; node = node->next) {
            fprintf(stderr, "Table[%d] has %s\n", i, node->text);
        }
    }
}

int checkUndeclared() {
    int i;
    HASH_NODE *node;

    for (i = 0; i < HASH_SIZE; i++) {
        for (node = Table[i]; node != NULL; node = node->next) {
            if (node->type == SYMBOL_IDENTIFIER)
            {
                fprintf(stderr, "Semantic ERROR: symbol %s not declared.\n", node->text);
                return 1;
            }
        }
    }
    return 0;
}

HASH_NODE* hashCreateTemp()
{
    static int tempCount = 0;
    char buffer[256];
    
    sprintf(buffer, "__temp%d", tempCount);
    tempCount++;

    HASH_NODE* result =  hashInsert(TYPE_SCALAR, buffer);
    result->dataType = DATATYPE_TEMP;

    return result;
}

HASH_NODE* hashCreateLabel()
{
    static int labelCount = 0;
    static char buffer[256];

    sprintf(buffer, "__label%d", labelCount);
    labelCount++;

    HASH_NODE* result =  hashInsert(TYPE_LABEL, buffer);
    result->dataType = DATATYPE_LABEL;

    return result;
}