#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

char* Read(char** index, char* text){

    FILE * Onegin = fopen ("Onegin.txt", "rb");
    //FILE * Onegin_Sort = fopen ("Onegin_Sort.txt", "w");

    long long size_of_file = 0;

    if (Onegin == NULL) printf("Error of file\n");

    else{
        fseek (Onegin, 0, SEEK_END);
        size_of_file = ftell (Onegin);
        fseek (Onegin, 0, SEEK_SET);
    }

    text = (char*) realloc (text, (size_of_file + 1) * sizeof(char));
    assert (text != NULL);

    size_t length = fread (text, sizeof(char), size_of_file, Onegin);
    assert (size_of_file == length);

    printf("size of file = %lld\n", size_of_file);

    index = (char**) realloc (index, size_of_file * sizeof(char*));
    assert (index != NULL);

    *index = text;

    printf("text[seek] = %p\n", index[0]);

//    printf ("\n%d", length);
//    printf ("%s\n", text);

    //fwrite(text, sizeof(char), size_of_file, Onegin_Sort);


    int number_of_strings = 1;

    for(long i = 0; i < size_of_file; i++){
        if(*(text + i) == '\n'){
            *(text + i) = '\0';
            index[number_of_strings] = (text + i + 1);

            int c = *(index[number_of_strings]);
            printf("text[seek] = %p\t char is %c\n", index[number_of_strings], c);

            number_of_strings++;
        }
    }

    index = (char**) realloc (index, number_of_strings * sizeof(char*));

    printf("number of strings = %d\n", number_of_strings);

    printf("text[seek] after realloc = %p\n", index[0]);

    fclose(Onegin);

    return text;
}

int Is_Letter(char c){
    if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return TRUE;
    else {
        printf("%c is not a char\n", c);
        return FALSE;
    }
}

int Compare (int j, char** index){

    !!!!!printf("the beginning of the string is %p\n", index[0]);

    int i = 0;      //i for j-string
    for (int r = 0; ; r++){      //r for (j + 1) - string

        int I = -777, R = -777;
        char c = *(index[j] + i);
        if ((I = Is_Letter (c)) == FALSE){
            while ((I = Is_Letter (c)) == FALSE){

                if ( c == '\r' || c == '\0') return FALSE;
                i++;
                c = *(index[j] + i);
            }
        }

        if ((R = Is_Letter (*(*(index + j + 1) + r * sizeof(char)))) == FALSE){
           while ((R = Is_Letter (* (*(index + j + 1) + r * sizeof(char)))) == FALSE){
                printf("R\n");
                if ( *(*(index + j + 1) + r * sizeof(char)) == '\r' || *(*(index + j + 1) + r * sizeof(char)) == '\0') return TRUE;
                r++;
            }
        }

        if ( *(*(index + j) + i * sizeof(char)) > *(*(index + j + 1) + r * sizeof(char))) return TRUE;
        if ( *(*(index + j) + i * sizeof(char)) < *(*(index + j + 1) + r * sizeof(char))) return FALSE;
        i++;

    }
}

int main()
{

    //FILE * Onegin_Sort = fopen ("Onegin_Sort.txt", "w");

    char* text = (char*) calloc (1, sizeof(char));
    assert (text != NULL);

    char** index = (char**) calloc (1, sizeof(char*));
    assert (index != NULL);

   !!!!!! printf("check theee first add = %p\n", index[0]);

    Read(index, text);

    int y = Compare(0, index);
    printf("Let's compare 1 and 2 strings %d\n", y);
    //Write();


    //fclose(Onegin_Sort);
    //free(text);
    return 0;
}


