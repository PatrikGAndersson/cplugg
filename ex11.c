#include <stdio.h>


//print arguments from argv
int main(int argc, char* argv[])
{
    int i = 0;
    while(i < argc) {
        printf("arg %d: %s\n",i, argv[i]);
        i++;
    }

char* states[argc]; 


//copy arguments from argv into states
int num_states = argc;
i = 0;
while(i < num_states){
    states[i] = argv[i];
    i++;
};

//print states
i = 0;
while(i < num_states){
    printf("arg %d: %s\n",i, states[i]);
    i++;
};

printf("\n");

//print states in reverse
i = num_states -1;
while(i > 0){
    printf("arg %d: %s\n",i, states[i]);
    i--;
};



return 0;

}