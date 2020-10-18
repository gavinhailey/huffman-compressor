#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

LinkedList* llCreate() {
  return NULL;
}

int llIsEmpty(LinkedList* ll) {
  return ll == NULL;
}

void llDisplay(LinkedList* ll) {
  LinkedList* p = ll;
  printf("[");
  while (p != NULL) {
    printf("%c, %d\n", (*p).value->c, (*p).value->weight);
    p = p->next;
  }
  printf("]\n");
}


void llAdd(LinkedList** ll, tnode* tNode) {
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->value = tNode;
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

void llAddInOrder(LinkedList** ll, tnode* tNode) {
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->value = tNode;
  newNode->next = NULL;

  LinkedList* p = *ll;

  if (p == NULL) {
    *ll = newNode;
    llAddInOrder(ll, tNode);
  } else {
    while (p->next != NULL && p->next->value->weight < tNode->weight) {
      p = p->next;
    }
    LinkedList* tmp = p->next;
    p->next = newNode;
    newNode->next = tmp;
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
