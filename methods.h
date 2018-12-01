//Node structure
typedef struct node
{
  char* question;
  char* object_name;
  struct node *yes_ptr;
  struct node *no_ptr;
} node;

//Protoypes
void nodePrint(node* someNode);
