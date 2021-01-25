//includes stdio.h which has standard input/output
//type of functions
#include <stdio.h>
//includes assert.h which has funcionality such as
//from man 3 assert:
/*The assert() macro tests the given expression and if 
it is false, the calling process is terminated.
A diagnostic message is written to stderr
and the abort(3) function is called, effectively terminating
the program.If expression is true, the assert() macro does 
nothing.*/
#include <assert.h>
//includes stdlib.h which has funcionality to
//define several macros and type
//here used to define NULL-macro
#include <stdlib.h>
//includes string.h which has funcionality to
//work om strings/characters
#include <string.h>

//Forward declaration
//Defines a struct called person with the variables
//name = array of characters
//age = int
//height = int
//weight = int
struct Person {
    char* name;
    int age;
    int height;
    int weight;
};

//For extra-credit
struct Person2{
    char* name;
    int age;
    int height;
    int weight;
};


//Defines a struct as specified above
struct Person* Person_create(char* name,int age, int height, int weight)
{
    //instance of Person struct called who
    //that allocates memory for struct on heap
    //with malloc the size of a Person struct
    struct Person* who = malloc(sizeof(struct Person));
    
    //asserts that memory has been allocated
    assert(who != NULL);
    
    //what do strdup do?
    //from man 3 strdup:
    //The strdup() function allocates sufficient 
    //memory for a copy of the
    //string s1, does the copy, 
    //and returns a pointer to it.  
    //The pointer may
    //subsequently be used as an 
    //argument to the function free(3).
    who->name = strdup(name);
    //set age of allocated struct to age
    who->age = age;
    //set age of allocated struct to height
    who->height = height;
    //set weight of allocated struct to age
    who->weight = weight;

    return who;
}


//Function to destroy Person
// i.e free up the allocated memory
//takes a reference to struct as argument
void Person_destroy(struct Person* who)
{
    //again assert that who is not null
    //i.e that there is somethin to free up
    assert(who != NULL);

    //free up name
    //why do we have to do this seperatley?
    free(who->name);
    //free up who
    free(who);
}

//Function for printing a Person struct
//again takes ref to Person as argument
void Person_print(struct Person* who)
{
    //Print statements that dereferences
    //pointer and prints with format %p
    printf("Name: %s\n", who->name);
    printf("Age: %d\n", who->age);
    printf("Height: %d\n", who->height);
    printf("Weight: %d\n\n", who->weight);

}



struct Person2 Person_create2 (char* name,
int age, int height, int weight){
    struct Person2 who;
    who.name = name;
    who.age = age;
    who.height = height;
    who.weight = weight;


    return who;
}

//How to print/ pass struct to function in another way
void Person_print2(struct Person2 who)
{
        printf("Name: %s\n", who.name);
        printf("\tAge: %d\n", who.age);
        printf("\tHeight: %d\n", who.height);
        printf("\tWeight: %d\n", who.weight);
}


//Main function
int main(int argc, char* argv[])
{
    // Make two people structs
    //Takes a string and 3 integers as arguments
    struct Person* joe = Person_create(
        "Joe Alex",32,64,100
    );

    struct Person* frank = Person_create(
        "Frank Blank",20,72,180
    );

    // Print where the structs are in memory
    Person_print(joe);
    printf("Joe is at memory location %p\n",joe);
    Person_print(frank);
    printf("Frank is at memory location %p\n",frank);

    //Set boths ages to 20 and print again
    joe->age = 20;
    frank->age = 20;

    Person_print(joe);
    Person_print(frank);

    //destroy both to clean up
    Person_destroy(joe);
    Person_destroy(frank);

    
    //Create struct 2nd way for extra-credit
    struct Person2 viktor = Person_create2(
        "Viktor",28,185,70
    );
    //--
    struct Person2 anna_maria = Person_create2(
        "Anna-Maria",29,167,50
    );

    printf("%s\n",viktor.name);
    printf("%s\n",anna_maria.name);

    Person_print2(viktor);
    Person_print2(anna_maria);



}