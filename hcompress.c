#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <strings.h>
#include "linkedList.h"

typedef struct tnode {
  int weight;
  char c;
  struct tnode* left;
  struct tnode* right;
  struct tnode* parent;
} tnode;

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

  for (int i = 0; i < 127; i++) {
    printf("%c %d\n", leafNodes[i].c, leafNodes[i].weight);
  }

  // //Create the huffman tree from the frequency table
  // tnode* treeRoot = createHuffmanTree(leafNodes);
  //
  // // encode
  // if (strcmp(argv[1], "-e") == 0) {
  //   // Pass the leafNodes since it will process bottom up
  //   encodeFile(argv[2], leafNodes);
  // } else { // decode
  //   // Pass the tree root since it will process top down
  //   decodeFile(argv[2], treeRoot);
  // }

  return 0;
}

tnode* createFreqTable(char* filename) {
  tnode* leafNodes = (tnode*) malloc(127 * sizeof(tnode));
  FILE* file = fopen(filename, "r");
  char tmp = 0;
  while (fscanf(file, "%c", &tmp) != EOF) {
    leafNodes[(int) tmp].weight += 1;
    leafNodes[(int) tmp].c = tmp;
  }
  sortFreqTable(leafNodes);
  return leafNodes;
}

void sortFreqTable(tnode* leafNodes) {
  for (int i = 0; i < 126; i++)
    for (int j = 0; j < 126 - i; j++)
      if ((leafNodes[j]).weight > leafNodes[j+1].weight)
        swap(&leafNodes[j], &leafNodes[j+1]);
}

void swap(tnode* x, tnode* y) {
    tnode tmp = *x;
    *x = *y;
    *y = tmp;
}

tnode* createHuffmanTree(tnode* leafNodes) {

}

void encodeFile(char* filename, tnode* leafNodes) {

}

void decodeFile(char* filename, tnode* treeRoot) {

}
