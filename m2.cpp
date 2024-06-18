/*
 * FILE:m2.cpp
 * PROJECT:DS2
 * PROGRAMMER:MANREET THIND (Student ID:8982315)
 * FIRSTVERSION:17/06/24
 * DESCRIPTION :
 * The functions in this file  implement simplified web browser history manager using “stacks” and “queues”.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//Struct for stack nodes
typedef struct StackNode
{
    char* url;
    struct StackNode* next;
};

//Struct for stack
typedef struct Stack
{
    StackNode* top;
};

/*
Function: push
Parameters:
Stack* stack: pointer to a Stack where the new URL will be pushed.
const char* newUrl: pointer to a C-style string containing the URL to be pushed onto the stack.
Return Value: void
Description: This function pushes a new URL onto the top of the stack. Memory is dynamically allocated to store the URL.
*/
void push(Stack* stack, const char* newUrl)
{
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    if (!newNode)
    {
        printf("Mmemory allocation failed.\n");
        exit(1);
    }
    newNode->url = (char*)malloc(strlen(newUrl) + 1); //Allocate memory for URL string
    if (!newNode->url)
    {
        printf("Mmemory allocation failed.\n");
        exit(1);
    }
    strcpy_s(newNode->url,strlen(newUrl) + 1, newUrl);//Link new node to the previous top node
    newNode->next = stack->top;// Update the top* to the new node
    stack->top = newNode;
}
/*
Function: pop
Parameters:
Stack* stack: pointer to a Stack from which the top URL will be popped.
Return Value: char* : pointer to a C-style string containing the URL that was popped from the stack.
Description: This function pops the top URL from the stack and returns it. Memory for the URL is not freed; it is the caller's responsibility to free it.
*/
char* pop(Stack* stack)
{
    //check if stack is empty
    if (stack->top == NULL)
    {
        //return NULL if stack is empty
        return NULL;
    }
    StackNode* temp = stack->top; //Store the top node temporily
    stack->top = stack->top->next;//Update the top* to the next node
    char* url = temp->url;//Store the URL to return
    free(temp);//Free the memory of the old top node
    return url;//Return the URL
}
/*
Function: peek
Parameters:
Stack* stack: pointer to a Stack from which the top URL will be peeked.
Return Value: char* : pointer to a C-style string containing the URL at the top of the stack.
Description: This function returns the URL at the top of the stack without removing it.
*/
char* peek(Stack* stack)
{
    //Check if the stack is empty
    if (stack->top == NULL)
    {
        //return NULL if the stack is empyty
        return NULL;
    }
    //Return the URL at the top of the stack
    return stack->top->url;
}
/*
Function: isEmpty
Parameters:
Stack* stack: pointer to a Stack to be checked for emptiness.
Return Value: bool : true if the stack is empty, false otherwise.
Description: This function checks if the stack is empty.
*/
bool isEmpty(Stack* stack)
{
    //Return true if the stack is empty
    return stack->top == NULL;
}

//Struct for queue nodes
typedef struct QueueNode
{
    char* url;//URL stored in the queue node
    struct QueueNode* next;//Pointer to the next node in the queue
};
//Struct for queue
typedef struct Queue
{
    //Pointer to the front node in the queue
    QueueNode* front;
    //Pointer ro the rear node in the queue
    QueueNode* rear;
};

/*
Function: enqueue
Parameters:
Queue* queue: pointer to a Queue where the new URL will be enqueued.
const char* newUrl: pointer to a C-style string containing the URL to be enqueued.
Return Value: void
Description: This function enqueues a new URL at the rear of the queue. Memory is dynamically allocated to store the URL.
*/
void enqueue(Queue* queue, const char* newUrl)
{
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));//Allocate memory for a new queue node
    if (!newNode)
    {
        printf("Mmemory allocation failed.\n");
        exit(1);
    }
    newNode->url = (char*)malloc(strlen(newUrl) + 1); //Allocate memory for the URL string
    if (!newNode->url)
    {
        printf("Mmemory allocation failed.\n");
        exit(1);
    }
    strcpy_s(newNode->url,strlen(newUrl) + 1, newUrl); //Copy the URL into the new code
    newNode->next = NULL; //New node will be the last, so next is NULL
    if (queue->rear != NULL) // check if queue is empty
    {
        queue->rear->next = newNode;
    }
    queue->rear = newNode;
    if (queue->front == NULL)//check is queue is empty
    {
        queue->front = newNode;
    }
}
/*
Function: dequeue
Parameters:
Queue* queue: pointer to a Queue from which the front URL will be dequeued.
Return Value: char* : pointer to a C-style string containing the URL that was dequeued from the queue.
Description: This function dequeues the front URL from the queue and returns it. Memory for the URL is not freed; it is the caller's responsibility to free it.
*/
char* dequeue(Queue* queue)
{
    if (queue->front == NULL)//check if queue is empty
    {
        return NULL;
    }
    QueueNode* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)//check if the queue is empty
    {
        queue->rear = NULL;
    }
    char* url = temp->url;
    free(temp);
    return url;//return URL
}

/*
Function: peekQueue
Parameters:
Queue* queue: pointer to a Queue from which the front URL will be peeked.
Return Value: char* : pointer to a C-style string containing the URL at the front of the queue.
Description: This function returns the URL at the front of the queue without removing it.
*/
char* peekQueue(Queue* queue)
{
    if (queue->front == NULL)//check if queue is empty
    {
        return  NULL;
    }
    return queue->front->url;//return URL at the front of the queue
}
/*
Function: isEmptyQueue
Parameters:
Queue* queue: pointer to a Queue to be checked for emptiness.
Return Value: bool : true if the queue is empty, false otherwise.
Description: This function checks if the queue is empty.
*/
bool isEmptyQueue(Queue* queue)
{
    return queue->front == NULL;//return true if queue is empty
}

/*
Function: displayHistory
Parameters:
Stack* backStack: pointer to a Stack representing the back navigation history.
Queue* forwardQueue: pointer to a Queue representing the forward navigation history.
Return Value: void
Description: This function displays the current page, backward history, and forward history.
*/
void displayHistory(Stack* backStack, Queue* forwardQueue)
{
    printf("Current Page: %s\n", (peek(backStack) ? peek(backStack) : "No current page"));
    printf("Backward History:\n");
    StackNode* temp = backStack->top;//start from th top of the back stack
    while (temp != NULL)
    {
        printf("%s\n", temp->url);//print each URL
        temp = temp->next;
    }
    printf("Forward History:\n");
    QueueNode* tempQueue = forwardQueue->front;//start from the front of the forward queue
    while (tempQueue != NULL)
    {
        printf("%s\n", tempQueue->url);//print each URL
        tempQueue = tempQueue->next;
    }
}

int main()
{
    Stack backStack = { NULL };//initilize back stack
    Queue forwardQueue = { NULL,NULL };//initialize the forward queue
    char choice;//variable to store user's choice
    char url[100];//buffer to store url input

    while (1)
    {
        printf("Menu:\n");
        printf("1. Visit New Web Page\n");
        printf("2. Navigte Backward\n");
        printf("3. Navigte Forward\n");
        printf("4. Display Current Page and History\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf_s("%c", &choice, 1);//read user's choice
        getchar();//clear the \n from input buffer

        switch (choice)
        {
         case '1':
             //Visit a new webpage
            printf("Enter the URL of the webpage: ");
            fgets(url, sizeof(url), stdin);//read URL
            url[strcspn(url, "\n")] = '\0';
            if (!isEmpty(&backStack))
            {
                while (!isEmptyQueue(&forwardQueue))
                {
                    free(dequeue(&forwardQueue));//free up the memory
                }
            }
            push(&backStack, url);//push the new URL onto the back stack
            printf("Visited: %s\n", url);
            break;
         case '2':
             //Navigate backward
             if (isEmpty(&backStack))
             {
                 printf("No previous pages to navigate back to.\n");
             }
             else
             {
                 char* currentPage = pop(&backStack);//pop the top URL from stack
                 if (currentPage)
                 {
                     enqueue(&forwardQueue, currentPage);
                     free(currentPage);//free up the memory
                 }
                 if (peek(&backStack))
                 {
                     printf("Previous Page: %s\n", peek(&backStack));
                 }
                 else
                 {
                     printf("No previous pages to navigate back to.\n");
                 }
             }
             break;
         case '3':
             //Navigate forward
             if (isEmptyQueue(&forwardQueue))
             {
                 printf("No forward pages to navigate to.\n");
             }
             else
             {
                 char* forwardUrl = dequeue(&forwardQueue);
                 if (forwardUrl)
                 {
                     push(&backStack, forwardUrl);
                     printf("Next Page: %s", forwardUrl);
                     free(forwardUrl);//free the memory of URL
                 }
             }
             break;
         case '4':
             //Display current page and history
             displayHistory(&backStack, &forwardQueue);
             break;
         case '5':
             //Exit the program
             printf("Thank you for using the web browser. Goodbye!\n");

             while (!isEmpty(&backStack))
             {
                 free(pop(&backStack));//free up the memory
             }
             while (!isEmptyQueue(&forwardQueue))
             {
                 free(dequeue(&forwardQueue));//free up the memory
             }
             return 0;
         default:
             //Invalid choice
             printf("Invalid choice. Please try again.\n");
            break;
        }
    }
}