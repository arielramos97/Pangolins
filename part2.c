#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "methods.h"

//Main method
int main(int argc, char const *argv[])
{
  //We need a root node.
  struct node *rootNode = (node *) malloc(sizeof(node));

  rootNode->question = NULL;
  rootNode->object_name = "pangolin"; //As is a question node.
  rootNode->yes_ptr = NULL;
  rootNode->no_ptr = NULL;

  struct node *currentNode = rootNode;

  //Boolean variable to know when the game has finished.
  int finished = 0;

  //Buffer to read data from standar input.
  int sizeOfBuffer = 100;
  char* buffer = malloc (sizeOfBuffer * sizeof(char));

  while(finished == 0)
  {
    //A node is a leaf node if the question paramater is NULL.
    if (currentNode->question == NULL)
    {
      //Guess object
      printf("\033[1mIt is a %s?\033[22m\n", currentNode->object_name);

      //Read answer to guess question.
      if(fgets(buffer, sizeof(buffer), stdin) == NULL)
      {
        fprintf( stderr, "Error while reading input");
        exit(-1);
      }

      //If answer is yes.
      if (strcmp(strtok(buffer, "\n"), "yes") == 0)
        printf("\033[1mGood that was soooo easy.\033[22m\n");
      else
      {
        printf("\033[1mOh. Well you win then - What were you thinking of?\033[22m\n");

        //Read name of new object and create it.
        fgets(buffer, sizeof(buffer), stdin);

        //New object node
        struct node *newObjectNode = (node *) malloc(sizeof(node));
        newObjectNode->question = NULL;
        char* object = malloc(sizeof(buffer) * sizeof(char));
        strcpy(object, buffer);
        newObjectNode->object_name = object;
        newObjectNode->yes_ptr = NULL;
        newObjectNode->no_ptr = NULL;

        nodePrint(newObjectNode);
        printf("\n");

        //Ask for a question to this new object
        printf("\033[1mPlease give me a question about %s, so I can tell the difference between %s and %s\033[22m\n", newObjectNode->object_name, newObjectNode->object_name, currentNode->object_name);

        //Read question and create question node.
        fgets(buffer, sizeof(buffer), stdin);
        //New question node.
        struct node *newQuestionNode = (node *) malloc(sizeof(node));
        newQuestionNode->question = buffer;
        newQuestionNode->object_name = NULL;

        //Ask for answer to the question.
        printf("\033[1mWhat is the answer for %s?\033[22m\n", newObjectNode->object_name);

        //Read the answer to the question
        fgets(buffer, sizeof(buffer), stdin);

        //Based on the answer, the object will take the appropiate path
        if(strcmp(strtok(buffer, "\n"), "yes") == 0)
        {
          newQuestionNode->yes_ptr = newObjectNode;
          newQuestionNode->no_ptr = currentNode;
        }
        else if(strcmp(strtok(buffer, "\n"), "no") == 0)
        {
          newQuestionNode->no_ptr = newObjectNode;
          newQuestionNode->yes_ptr = currentNode;
        }

        printf("\033[1mThanks!\033[22m\n");

        //Now modidy the tree properly.
        currentNode = newQuestionNode;
        nodePrint(currentNode);
      } //else

      //Ask if player wants to continue playing.
      printf("\033[1mWould you like to play again?\033[22m\n");

      //Read answer
      fgets(buffer, sizeof(buffer), stdin);

      if (strcmp(strtok(buffer, "\n"), "no") == 0)
      {
        printf("\033[1mSee you!\033[22m\n" );
        finished = 1;
      }
      else
        printf("\033[1mOK! Let's start again!\033[22m\n");

    } //if
    else //When curent node is not a leaf.
    {
      //Ask question
      printf("\033[1m%s\033[22m\n", currentNode->question);

      printf("arrives here\n" );
      //Read the answer
      fgets(buffer, sizeof(buffer), stdin);

      if(strcmp(strtok(buffer, "\n"), "yes") == 0)
        currentNode = currentNode->yes_ptr;
      else if(strcmp(strtok(buffer, "\n"), "no") == 0)
        currentNode = currentNode->no_ptr;
     } //else
  } //while

  return 0;
}
