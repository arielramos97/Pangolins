#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "methods.h"

//Function nodePrint that will print the status of a single node of the tree
void nodePrint(node* someNode)
{
  //Question Node.
  if(someNode->object_name == NULL)
  {
    printf("Object: [NOTHING]\n");
    printf("Question: %s\n", someNode->question);
    printf("Yes: %s\n", (someNode->yes_ptr)->object_name);
    printf("No: %s\n", (someNode->no_ptr)->object_name);
  }
  else //Object Node
  {
    printf("Object: %s\n", someNode->object_name);
    printf("Question: [NOTHING]\n");
  }
} //node
