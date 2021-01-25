#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

//For handling errors
void die(const char* message)
{
    if(errno) {
        perror(message);
    } else {
        printf("ERROR:%s\n",message);
    }

    exit(1);
}

//compare_cb is a function pointer that
//returns and int and take two ints as input
//typedef makes this name for this complex type of functions
typedef int (*compare_cb) (int a, int b);

//sort_cb is pointer to a function pointer
//returns an int array
//takes an array of ints, count and a callback 
//comparison function
typedef int*(*sort_cb)(int* numbers,int count,compare_cb);

//classic bubble sort that uses compare_cb for the sorting
int* bubble_sort(int* numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");

    memcpy(target,numbers,count * sizeof(int));

    for(i = 0; i < count; i++) {
        for(j = 0; j <count -1;j++) {
            //if the compare function 
            //returns a positive value
            //switch places
            if(cmp(target[j],target[j+1]) > 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }
    return target;
}

int* bubble_sort_inverse(int* numbers, int count, compare_cb cmp)
{
    int temp = 0;
    int i = 0;
    int j = 0;
    int *target = malloc(count * sizeof(int));

    if(!target) die("Memory error.");

    memcpy(target,numbers,count * sizeof(int));

    for(i = 0; i < count; i++) {
        for(j = 0; j <count -1;j++) {
            //if the compare function 
            //returns a positive value
            //switch places
            if(cmp(target[j],target[j+1]) < 0) {
                temp = target[j+1];
                target[j+1] = target[j];
                target[j] = temp;
            }
        }
    }

    return target;
}

//The 3 functions below are all
//can be used as callbacks as their
//signature matches that of compare_cb
int sorted_order(int a, int b)
{
    return a - b;
}

int reverse_order(int a, int b)
{
    return b - a;
}

int strange_order(int a, int b)
{
    if(a == 0 || b == 0){
        return 0;
    } else {
        return a % b;
    }
}


//Function to test
void test_sorting(int* numbers, int count, sort_cb sort, compare_cb cmp)
{
    int i = 0;

    //Make array sorted to store result of bubblesort
    int* sorted = sort(numbers,count,cmp);
    //bubble_sort(numbers, count, cmp);
    //If something went wront throw an error
    if(!sorted) die("Sorting failed!");

    //Loop over the sorted array and print all elements
    for(i = 0; i < count; i++) {
        printf("%d  ", sorted[i]);
    }
    printf("\n");
    //Free up memory which stored sorted array
    free(sorted);

    unsigned char *data = (unsigned char *)cmp;
    for(i = 0; i < 25; i++) {
        printf("%02x:", data[i]);
}
    printf("\n");
}

int main(int argc, char* argv[])
{
    if(argc < 2) die("USAGE: ex18 4 3 1 5 6");

    int count = argc - 1;
    int i = 0;
    char** inputs = argv +1;

    //allocate meory for array size of number of inputs
    int* numbers = malloc(count * sizeof(int));
    if(!numbers) die("Memory error!");

    //and populate array with the inputed numbers
    for(i = 0; i < count; i++) {
        numbers[i] = atoi(inputs[i]);
    }

    //Run test_sorting with
    //the array, count for bubble sort, and
    //the type of compare function
    test_sorting(numbers,count,bubble_sort,sorted_order);
    test_sorting(numbers,count,bubble_sort_inverse,sorted_order);
   

    return 0;

}