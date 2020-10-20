#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "linkedList.h"

tnode* createFreqTable(char* filename);

void sortFreqTable(tnode* leafNodes);

void swap(tnode* x, tnode* y);

tnode* createHuffmanTree(tnode* leafNodes);

void encodeFile(char* filename, tnode* leafNodes);

void decodeFile(char* filename, tnode* treeRoot);

int main(int argc, char *argv[]) {
   if (argc != 3) {
      printf("Error: The correct format is \"hcompress -e filename\" or \"hcompress -d filename.huf\"\n"); fflush(stdout);
    exit(1);
  }

  // Create the frequency table by reading the generic file
  tnode* leafNodes = createFreqTable("test.txt");

  //Create the huffman tree from the frequency table
  tnode* treeRoot = createHuffmanTree(leafNodes);

  // encode
  if (strcmp(argv[1], "-e") == 0) {
    // Pass the leafNodes since it will process bottom up
    encodeFile(argv[2], leafNodes);
  } else { // decode
    // Pass the tree root since it will process top down
    decodeFile(argv[2], treeRoot);
  }

  return 0;
}

tnode* createFreqTable(char* filename) {
  tnode* leafNodes = (tnode*) malloc(127 * sizeof(tnode));
  FILE* file = fopen(filename, "r");
  if (file == NULL) {
    printf("Invalid File\n");
    exit(1);
  }
  char tmp = 0;
  while (fscanf(file, "%c", &tmp) != EOF) {
    leafNodes[(int) tmp].weight += 1;
    leafNodes[(int) tmp].c = tmp;
  }
  fclose(file);
  return leafNodes;
}

tnode* createHuffmanTree(tnode* leafNodes) {
  tnode* root;
  LinkedList* p;
  LinkedList* list = llCreate();
  for (int i = 0; i < 127; i++) {
    if (leafNodes[i].weight != 0)
      llAddInOrder(&list, &leafNodes[i]);
  }
  p = list;

  while (p->next != NULL) {
    tnode* newNode = (tnode*) malloc(1*sizeof(tnode));
    newNode->c = 0;
    p->value->parent = newNode;
    newNode->left = p->value;
    p->next->value->parent = newNode;
    newNode->right = p->next->value;
    newNode->weight = newNode->right->weight + newNode->left->weight;
    llAddInOrder(&list, newNode);
    root = newNode;
    if (p->next->next != NULL)
      p = p->next->next;
  }

  llDisplay(list);

  p = list;
  while (p->next != NULL) {
    LinkedList* tmp = p;
    p = p->next;
    free(tmp);
  }

  return root;
}

void encodeFile(char* filename, tnode* leafNodes) {
  FILE* file = fopen(filename, "r");
  FILE* writeFile = fopen(strcat(filename, ".huf"), "w");
  if (file == NULL) {
    printf("Invalid File\n");
    exit(1);
  }
  char tmp = 0;
  unsigned char huffCode[8];
  memset(huffCode, 0, sizeof(huffCode));
  int c = 0;
  unsigned char byte = 0;
  while (fscanf(file, "%c", &tmp) != EOF) {
    tnode* t = &leafNodes[(int) tmp];
    while (t->parent != NULL && c < 8) {
      if (t == t->parent->right)
        huffCode[c] = 1;
      else
        huffCode[c] = 0;
      c++; //lol
      if (c == 8) {
        for (int i = 0; i < 8; i++)
          byte = byte | huffCode[i] << i;
        fprintf(writeFile, "%c", byte);
        c = 0;
        memset(huffCode, 0, sizeof(huffCode));
      }
      if (t->parent != NULL)
        t = t->parent;
    }
  }
  fclose(file);
  fclose(writeFile);
}

void decodeFile(char* filename, tnode* treeRoot) {
  FILE* file = fopen(filename, "r");
  FILE* writeFile = fopen(strcat(filename, ".dec"), "w");
  if (file == NULL) {
    printf("Invalid File\n");
    exit(1);
  }
  unsigned char tmp = 0;
  unsigned int huffCode[8];
  memset(huffCode, 0, sizeof(huffCode));
  tnode* t = treeRoot;
  while (fscanf(file, "%c", &tmp) != EOF) {
    unsigned char byte = tmp;
    for (int i = 0; i < 8; i++) {
      if (((byte & (1 << i)) >> i) == 1 && t->right != NULL) {
        t = t->right;
      } else if (t->left != NULL) {
        t = t->left;
      } else {
        fprintf(writeFile, "%c", t->c);
        t = treeRoot;
      }
    }
  }
}
