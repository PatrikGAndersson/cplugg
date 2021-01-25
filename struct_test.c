#include <stdio.h>

struct foo10 {
    char c;
    int z;
    short x;
};

struct foo11 {
    int z;
    short x;
    char c;
};

int main(int argc, char* argv[]){


printf("%zu %zu %zu\n",sizeof(char),sizeof(short),sizeof(int));


printf("%zu %zu",sizeof(struct foo10),sizeof(struct foo11));

return 0;

}




