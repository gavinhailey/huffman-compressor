//Header

//struct
typedef struct node {
  int value;
  struct node* next;
} LinkedList;

//prototypes
LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, int newValue);
void llFree(LinkedList* ll);
