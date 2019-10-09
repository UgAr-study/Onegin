#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

char* Read(char*** index, char** text){

    FILE * Onegin = fopen ("Onegin.txt", "rb");
    //FILE * Onegin_Sort = fopen ("Onegin_Sort.txt", "w");

    long long size_of_file = 0;

    if (Onegin == NULL) printf("Error of file\n");

    else{
        fseek (Onegin, 0, SEEK_END);
        size_of_file = ftell (Onegin);
        fseek (Onegin, 0, SEEK_SET);
    }

    *text = (char*) realloc (*text, (size_of_file + 1) * sizeof(char));
    assert (text != NULL);

    size_t length = fread (*text, sizeof(char), size_of_file, Onegin);
    assert (size_of_file == length);

    printf("size of file = %lld\n", size_of_file);

    *index = (char**) calloc (size_of_file, sizeof(char*));
    assert (index != NULL);

    *index[0] = *text;

    //printf ("%s\n", *text);
    //printf("text[seek] = %p\t char is %c\n", *index[0], **index[0]);

    //fwrite(text, sizeof(char), size_of_file, Onegin_Sort);


    int number_of_strings = 1;

    for(long i = 0; i < size_of_file; i++){

        //printf("I came to 'for' in Read! %c\n", (*text)[i]);

        if((*text)[i] == '\n'){
            //printf("I came to 'if' in 'for' in Read!\n");

            (*text)[i] = '\0';
            (*index)[number_of_strings] = *text + i + 1;

            char c = *((*index)[number_of_strings]);
            //printf("text[seek] = %p\t char is %c\n", (*index)[number_of_strings], c);

            number_of_strings++;
        }

        //printf("I came out to 'for' in Read!\n\n");
    }

    *index = (char**) realloc (*index, number_of_strings * sizeof(char*));

    //printf("number of strings = %d\n", number_of_strings);

    //printf("index[1] after realloc = %p\n", (*index)[1]);

    fclose(Onegin);

    return *text;
}

int Is_Letter(char c){
    if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)) return TRUE;
    else {
        printf("%c is not a char\n", c);
        return FALSE;
    }
}

int Compare (int j, char*** index){

    //printf("the beginning of 2 string in 'Compare' is %p\n", (*index)[1]);        //!!!!!!!!!!

    int i = 0;      //i for j-string
    for (int r = 0; ; r++){      //r for (j + 1) - string

        int I = -777, R = -777;

        char c = *((*index)[j] + i);

        if ((I = Is_Letter (c)) == FALSE){
            while ((I = Is_Letter (c)) == FALSE){

                if ( c == '\r' || c == '\0') return FALSE;
                i++;
                c = *((*index)[j] + i);
            }
        }

        c = *((*index)[j + 1] + r);

        if ((R = Is_Letter (c)) == FALSE){
           while ((R = Is_Letter (c)) == FALSE){
                printf("R\n");
                if (c == '\r' || c == '\0') return TRUE;
                r++;
                c = *((*index)[j + 1] + r);
            }
        }

        if (*((*index)[j] + i) > *((*index)[j + 1] + r)) return TRUE;
        if (*((*index)[j] + i) < *((*index)[j + 1] + r)) return FALSE;
        i++;

    }
}

int main()
{

    //FILE * Onegin_Sort = fopen ("Onegin_Sort.txt", "w");

    char* text = NULL;

    char** index = NULL;

    Read(&index, &text);

    Compare(, &index);
    //printf("Let's compare 1 and 2 strings %d\n", y);
    //Write();


    //fclose(Onegin_Sort);
    free(text);
    free(index);
    return 0;
}


