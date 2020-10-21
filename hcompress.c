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
  tnode* leafNodes = createFreqTable("alien.txt");

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
  unsigned int huffCode[127];
  memset(huffCode, 0, sizeof(huffCode));
  int c = 0;
  int height = 0;
  unsigned char byte = 0;
  while (fscanf(file, "%c", &tmp) != EOF) {
    tnode* t = &leafNodes[(int) tmp];
    while (t->parent != NULL) {
      if (t == t->parent->right)
        huffCode[height] = 1;
      else
        huffCode[height] = 0;

      height++;
      if (t->parent != NULL)
        t = t->parent;
    }
    for(int i = 0; i < height; i++){
      printf("%d", huffCode[i]);
    }
    printf("\n");
    for (int i = height - 1; i >= 0 ; i--){
      if(c == 8){
        for (int j = 0; j < 8; j++) {
         printf("%d", !!((byte << j) & 0x80));
        }
        printf("\n");
        fprintf(writeFile, "%c", byte);
        byte = 0;
        c = 0;
      }

      byte = byte | (huffCode[i] << (7 - c));

      c++;
    }



    height = 0;
  }
//  fprintf(writeFile, "%c", byte);
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
  tnode* t = treeRoot;
  while (fscanf(file, "%c", &tmp) != EOF) {
    unsigned char byte = tmp;
    for (int j = 0; j < 8; j++) {
     printf("%d", !!((byte << j) & 0x80));
    }
    printf("\n");
    for (int i = 7; i >= 0; i--) {
      if (((byte & (1 << i)) >> i) == 1 && t->right != NULL) {
        printf("1\n");
        t = t->right;
      } else if (((byte & (1 << i)) >> i) == 0 && t->left != NULL) {
        printf("0\n");
        t = t->left;
      } else if (t->right == NULL && t->left == NULL){
        printf("DONE\n");
        fprintf(writeFile, "%c", t->c);
        t = treeRoot;
        i++;
      }
    }
  }
}
