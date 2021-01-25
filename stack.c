#include <limits.h>
#include <stdio.h>
#include <stdlib.h>


//Struct to represent the stack
struct Stack {
    int top;
    unsigned capacity;
    int* array;
};

//create an empty stack
//returns address to empty stack
struct Stack* createStack(
    /*Takes capacity as arg*/unsigned capacity)
{
    //Allocate memory the size of our stack struct
    struct Stack* stack = malloc(sizeof(struct Stack));
    //Set the capacity of the stack to capacity arg
    stack->capacity = capacity;
    //Set top to -1
    stack->top = -1;
    //allocate memory for the size of the array
    //that holds the items on the stack
    stack->array = malloc(stack->capacity * sizeof(int));

    //return address to stack
    return stack;
}

//Function to check if the stack is full
int isFull(struct Stack* stack){
    //compare top to the capacity
    return stack->top == stack->capacity - 1;
}

//Check if stack is empty
int isEmpty(struct Stack* stack){
    //if top is -1 no item is on the stack
    return stack->top == - 1;
}

//Push item onto stack
void push(
    /*Takes struct address*/struct Stack* stack, 
    /*And item to be pushed onto stack*/int item)
{
    //It the stack is full
    if(isFull(stack))
        //return without adding item
        return;
    //Else set the array[top + 1] to item
    stack->array[++stack->top] = item;
    printf("%d pushed to stack\n", item);
}

//Function to pop from stack
int pop(struct Stack* stack)
{   
    //If the stack is empty
    if(isEmpty(stack))
        return;
    //decrement top and set top to this value 
    return stack->array[stack->top--];
}

//Function to look at the top value in the stack
int peek(struct Stack* stack)
{
    if(isEmpty(stack))
        return INT_MIN;
    return stack->array[stack->top];
}

int main()
{
    struct Stack* stack = createStack(100);

    push(stack,10);
    push(stack,20);
    push(stack,30);

    printf("%d popped from stack\n", pop(stack));

    return 0;
}

