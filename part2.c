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

//Prototypes
void nodePrint(node* someNode);
int isInArray(char* wordToCheck, char* arrayOfStrings[], int len);

//Main method
int main(int argc, char const *argv[])
{
  //Array to keep possible answers for YES
  char* yesAnswers[] = {"yes", "y", "YES", "yeah", "absolutely", "correct"};
  int lenYesAnswers = sizeof(yesAnswers)/sizeof(yesAnswers[0]);

  //Array to keep possible answers for NO
  char* noAnswers[] = {"no", "n", "NO"};
  int lenNoAnswers = sizeof(noAnswers)/sizeof(noAnswers[0]);

  //We need a root node.
  struct node *rootNode = (node *) malloc(sizeof(node));

  rootNode->object_or_question = 0;
  (rootNode->infoOfNode).object_name = "pangolin"; //As is a question node.
  rootNode->yes_ptr = NULL;
  rootNode->no_ptr = NULL;

  struct node *currentNode = rootNode;

  //Boolean variable to know when the game has finished.
  int finished = 0;

  //Buffer to read data from standar input.
  int sizeOfBuffer = 100;
  char* buffer = malloc (sizeOfBuffer);
printf("%zu\n", sizeof(buffer) );
printf("%d\n", sizeof(char) );
  while(finished == 0)
  {
    //If current node is a leaf
    if (currentNode->object_or_question == 0)
    {
      //Guess object
      printf("\033[1mIt is a %s?\033[22m\n", (currentNode->infoOfNode).object_name);

      //Read answer to guess question.
      if(fgets(buffer, sizeof(buffer), stdin) == NULL)
      {
        fprintf( stderr, "Error while reading input");
        exit(-1);
      }

      //If answer is yes.
      if(isInArray(strtok(buffer, "\n"), yesAnswers, lenYesAnswers) == 1)
        printf("\033[1mGood that was soooo easy.\033[22m\n");
      else
      {
        printf("\033[1mOh. Well you win then - What were you thinking of?\033[22m\n");

        //Read name of new object and create it.
        fgets(buffer, sizeof(buffer), stdin);
        char* inputObject = malloc(sizeof(buffer) * sizeof(char));
        strcpy(inputObject, buffer);

        //New object node
        struct node *newObjectNode = (node *) malloc(sizeof(node));
        newObjectNode->object_or_question = 0;
        (newObjectNode->infoOfNode).object_name = inputObject;
        newObjectNode->yes_ptr = NULL;
        newObjectNode->no_ptr = NULL;

        //Ask for a question to this new object
        printf("\033[1mPlease give me a question about %s, so I can tell the difference between %s and %s\033[22m\n", (newObjectNode->infoOfNode).object_name, (newObjectNode->infoOfNode).object_name, (currentNode->infoOfNode).object_name);

        //Read question and create question node.
        fgets(buffer, sizeof(buffer), stdin);
        printf("%d\n", sizeof(buffer) );
        char* inputQuestion = malloc(sizeof(buffer) * sizeof(char));
        strcpy(inputQuestion, buffer);

        //New question node.
        struct node *newQuestionNode = (node *) malloc(sizeof(node));
        newQuestionNode->object_or_question = 1;
        (newQuestionNode->infoOfNode).question = inputQuestion;

        //Ask for answer to the question.
        printf("\033[1mWhat is the answer for %s?\033[22m\n", (newObjectNode->infoOfNode).object_name);

        //Read the answer to the question
        fgets(buffer, sizeof(buffer), stdin);

        //Based on the answer, the object will take the appropiate path
        if(isInArray(strtok(buffer, "\n"), yesAnswers, lenYesAnswers) == 1)
        {
          newQuestionNode->yes_ptr = newObjectNode;
          newQuestionNode->no_ptr = currentNode;
        }
        else if(isInArray(strtok(buffer, "\n"), noAnswers, lenNoAnswers) == 1)
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

      if(isInArray(strtok(buffer, "\n"), noAnswers, lenNoAnswers) == 1)
      {
        printf("\033[1mSee you!\033[22m\n" );
        finished = 1;
      }
      else if(isInArray(strtok(buffer, "\n"), yesAnswers, lenYesAnswers) == 1)
        printf("\033[1mOK! Let's start again!\033[22m\n");

    } //if
    else //When curent node is not a leaf.
    {
      //Ask question
      printf("\033[1m%s\033[22m\n", (currentNode->infoOfNode).question);

      //Read the answer
      fgets(buffer, sizeof(buffer), stdin);

      if(isInArray(strtok(buffer, "\n"), yesAnswers, lenYesAnswers) == 1)
        currentNode = currentNode->yes_ptr;
      else if(isInArray(strtok(buffer, "\n"), noAnswers, lenNoAnswers) == 1)
        currentNode = currentNode->no_ptr;
     } //else
  } //while

  return 0;
}
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

//Method to check if a string is within an array of strings
int isInArray(char* wordToCheck, char* arrayOfStrings[], int len)
{
  int i;
  for(i=0; i < len; i++)
  {
    if(strcmp(arrayOfStrings[i], wordToCheck) == 0)
      return 1;
  }
  return 0;
}
