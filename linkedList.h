//Header

//structs
typedef struct tnode {
  int weight;
  char c;
  struct tnode* left;
  struct tnode* right;
  struct tnode* parent;
} tnode;

typedef struct node {
  tnode* value;
  struct node* next;
} LinkedList;

//prototypes
LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, tnode* tNode);
void llAddInOrder(LinkedList** ll, tnode* tNode);
void llFree(LinkedList* ll);
