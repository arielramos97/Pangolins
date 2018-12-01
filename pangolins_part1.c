#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

//Use an enum to define object and question node.
enum typeOfNode{object, question};
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
  enum typeOfNode object_or_question;
  struct node *yes_ptr;
  struct node *no_ptr;
} node;

//Protoypes
void nodePrint(node* someNode);
void treePrint(struct node* someNode);

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

  //Left side of question3
  struct node* object3 = malloc(sizeof(node));
  object3->object_or_question = 0;
  (object3->infoOfNode).object_name = "a biscuit";
  object3->yes_ptr = NULL;
  object3->no_ptr = NULL;

  //Right side of question2
  struct node* object2 = malloc(sizeof(node));
  object2->object_or_question = 0;
  (object2->infoOfNode).object_name = "Pete";
  object2->yes_ptr = NULL;
  object2->no_ptr = NULL;

  //Left side of question2
  struct node* question3 = malloc(sizeof(node));
  question3->object_or_question = 1;
  (question3->infoOfNode).question = "Can you dip it in your tea?";
  question3->yes_ptr = object3;
  question3->no_ptr = object4;

  //Right side of question1
  struct node* question2 = malloc(sizeof(node));
  question2->object_or_question = 1;
  (question2->infoOfNode).question = "Is it flat, round and edible?";
  question2->yes_ptr = question3;
  question2->no_ptr = object2;

  //Left side of question1
  struct node* object1 = malloc(sizeof(node));
  object1->object_or_question = 0;
  (object1->infoOfNode).object_name = "pangolin";
  object1->yes_ptr = NULL;
  object1->no_ptr = NULL;

  //Root
  struct node* question1 = malloc(sizeof(node));
  question1->object_or_question = 1;
  (question1->infoOfNode).question = "Does it have a tail?";
  question1->yes_ptr = object1;
  question1->no_ptr = question2;

  //Print the whole three
  treePrint(question1);
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

    //Yes path
    if((someNode->yes_ptr)->object_or_question == 0)
      printf("Yes: %s\n", (someNode->yes_ptr)->infoOfNode.object_name);
    else
      printf("Yes: %s\n", (someNode->yes_ptr)->infoOfNode.question);

    //No path
    if((someNode->no_ptr)->object_or_question == 0)
      printf("No: %s\n", (someNode->no_ptr)->infoOfNode.object_name);
    else
      printf("No: %s\n", (someNode->no_ptr)->infoOfNode.question);
  }
  else //Object Node
  {
    printf("Object: %s\n", (someNode->infoOfNode).object_name);
    printf("Question: [NOTHING]\n");
  }
} //node

//treePrint method: prints the whole game tree.
void treePrint(struct node* someNode)
{
  if(someNode == NULL){} //do nothing
  else
  {
    nodePrint(someNode);
    treePrint(someNode->no_ptr);
    treePrint(someNode->yes_ptr);
  }//else
}
