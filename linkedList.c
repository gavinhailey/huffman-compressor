#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

typedef struct node {
  int value;
  struct node* next;
} LinkedList;

LinkedList* llCreate() {
  return NULL;
}

int llIsEmpty(LinkedList* ll) {
  return (ll == NULL);
}

void llDisplay(LinkedList* ll) {

  LinkedList* p = ll;

  printf("[");

  while (p != NULL) {
    printf("%d, ", (*p).value);
    p = p->next;
  }

  printf("]\n");
}


void llAdd(LinkedList** ll, int newValue) {
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->value = newValue;
  newNode->next = NULL;

  LinkedList* p = *ll;

  if (p == NULL) {
    *ll = newNode;
  } else {
    while (p->next != NULL) {
      p = p->next;
    }
    p->next = newNode;
  }
}

void llFree(LinkedList* ll) {
  LinkedList* p = ll;
  while (p != NULL) {
    LinkedList* oldP = p;
    p = p->next;
    free(oldP);
  }
}
