#include <stdio.h>

int main(int argc, char* argv[])
{
    if(argc != 2) {
        printf("ERROR: You need atleast one argument.\n");
        return 1;
    }
    int number_of_vowels = 0;

    int i = 0;
    for(i = 0; argv[1][i] != '\0'; i++) {
        char letter = argv[1][i];
        

        switch(letter) {
            case 'a':
            case 'A':
            printf("%d: 'A'\n",i);
            number_of_vowels++;
            break;

            case 'e':
            case 'E':
            printf("%d: 'E'\n",i);
            number_of_vowels++;
            break;

            case 'i':
            case 'I':
            printf("%d: 'I'\n",i);
            number_of_vowels++;
            break;

            case 'o':
            case 'O':
            printf("%d: 'O'\n",i);
            number_of_vowels++;
            break;

            case 'u':
            case 'U':
            printf("%d: 'U'\n",i);
            number_of_vowels++;
            break;

            case 'y':
            case 'Y':
                if(i >2){
                    printf("%d: 'Y'\n",i);
                }
                number_of_vowels++;
                break;
            
            default:
                printf("%d: %c is not a vowel\n", i, letter);


        }
    }
    printf("\nTotal number of vowels: %d", number_of_vowels);
    return 0;
}