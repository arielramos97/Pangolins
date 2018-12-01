#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

//Use an enum to define object and question node.
enum typesOfNode{object, question};
//object = 0
//question =1

//Union structure
union data
{
  char* question;
  char* object_name;
} data;


//Node structure
typedef struct node
{
  union data infoOfNode;
  enum typesOfNode object_or_question;
  struct node *yes_ptr;
  struct node *no_ptr;
} node;

//Protoypes
void nodePrint(node* someNode);

//Main method
int main(int argc, char const *argv[])
{
  //Hard-code a small tree.
  //Tree from figure 4 (4th round)

  //Right side of question3
  struct node* object4 = malloc(sizeof(node));
  object4->object_or_question = 0;
  (object4->infoOfNode).object_name = "a pizza";
  object4->yes_ptr = NULL;
  object4->no_ptr = NULL;
  nodePrint(object4);

  // //Left side of question3
  // struct node* object3 = malloc(sizeof(node));
  // object3->question = NULL;
  // object3->object_name = "a biscuit";
  // object3->yes_ptr = NULL;
  // object3->no_ptr = NULL;
  // nodePrint(object3);

  // //Right side of question2
  // struct node* object2 = malloc(sizeof(node));
  // object2->question = NULL;
  // object2->object_name = "Pete";
  // object2->yes_ptr = NULL;
  // object2->no_ptr = NULL;
  // nodePrint(object2);
  //
  // //Left side of question2
  // struct node* question3 = malloc(sizeof(node));
  // question3->question = "Can you dip it in your tea?";
  // question3->object_name = NULL;
  // question3->yes_ptr = object3;
  // question3->no_ptr = object4;
  // nodePrint(question3);
  //
  // //Right side of question1
  // struct node* question2 = malloc(sizeof(node));
  // question2->question = "Is it flat, round and edible?";
  // question2->object_name = NULL;
  // question2->yes_ptr = question3;
  // question2->no_ptr = object2;
  // nodePrint(question2);
  //
  // //Left side of question1
  // struct node* object1 = malloc(sizeof(node));
  // object1->question = NULL;
  // object1->object_name = "pangolin";
  // object1->yes_ptr = NULL;
  // object1->no_ptr = NULL;
  // nodePrint(object1);
  //
  // //Root
  // struct node* question1 = malloc(sizeof(node));
  // question1->question = "Does it have a tail?";
  // question1->object_name = NULL;
  // question1->yes_ptr = object1;
  // question1->no_ptr = question2;
  // nodePrint(question1);

  return 0;
} //main

//Function nodePrint that will print the status of a single node of the tree
void nodePrint(node* someNode)
{
  //Question Node.
  if(someNode->object_or_question == 1)
  {
    printf("Object: [NOTHING]\n");
    printf("Question: %s\n", (someNode->infoOfNode).question);
    printf("Yes: %s\n", (someNode->yes_ptr)->infoOfNode);
    printf("No: %s\n", (someNode->no_ptr)->infoOfNode);
  }
  else //Object Node
  {
    printf("Object: %s\n", someNode->infoOfNode);
    printf("Question: [NOTHING]\n");
  }
} //node
