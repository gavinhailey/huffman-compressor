#include <stdio.h>
#include <stdlib.h>
#include "linkedList.h"

typedef struct node {
  int value;
  struct node* next;
} LinkedList;

LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, int newValue);
void llFree(LinkedList* ll);

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

  // Create the new node
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->value = newValue;
  newNode->next = NULL;
  
  // Find the end of the list
  LinkedList* p = *ll;

  if (p == NULL) {  // Add first element
    *ll = newNode;  // This is why we need ll to be a **

  } else {

    while (p->next != NULL) {
      p = p->next;
    }
    
    // Attach it to the end
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

int main() {
  
  LinkedList* l = llCreate();
  llDisplay(l);

  llAdd(&l, 1);
  llDisplay(l);

  llAdd(&l, 2);
  llDisplay(l);

  llAdd(&l, 3);
  llDisplay(l);

  llAdd(&l, 4);
  llDisplay(l);

  llFree(l);
}
