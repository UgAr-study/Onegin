#include <stdio.h>
#include <stdlib.h>
#include <srting.h>
#include <assert.h>
#include <locale.h>

int Compare(int j, int j + 1, int* index, char* text){                                          //if j-string > (j + 1)-string return 1, else return -1;
    int String_size = min((index[j+1] - index[j]), (index[j+2] - index[j + 1]);
    for (int i = 0; i < String_size; i++){
        if (*(index[j] + i) > *(index[j + 1] + i))  return 1;
        if (*(index[j] + i) < *(index[j + 1] + i))  return -1;
    }
    if ((index[j+1] - index[j]) > (index[j+2] - index[j + 1])) return 1;
    else return -1;
}

int Reading(){
    FILE * Onegin = fopen("Onegin.txt", "r");
    if (Onegin == NULL) printf("Error of file\n");
    else {
        fseek (Onegin, 0, SEEK_END);
        long size_of_file = ftell (Onegin);
    }

    char* text = (char*) calloc (size_of_file + 1, sizeof(char));
    size_t length = fread (text, sizeof(char), Onegin);

    assert (length == size_of_file);

    int string_number = 0;
    long long* index = (long long*) calloc (size_of_file, sizeof(long long));
    index[0] = text;

    for (int i = 1; i < size_of_file; i++){
        for (int j = 0; j < size_of_file; j++)
            if (text[j] == '\n'){                                    //don't forget about /r!!!
                index[i] = (text + j + 1);
                string_number++;
                i++;                                                //write adress
            }
        break;
    }

    index = (int*) realloc (index, (string_number + 1) * sizeof(long long));

    for (int i = 0; i < string_number; i++){
        for (int j = i; j < string_number; j++){
            if (Compare (j, j + 1, index, text) == 1){              //if j-string > (j + 1)-string swap their adresses
                int t = index[j];
                index[j] = index[j + 1];
                index[j + 1] = t;
            }
        }
    }
    return length;
}

void Output (char* text, int* index, ){
    char* Sort_text = (char*) calloc (size_of_file + 1, sizeof(char));
    for (int i = 0; i < ; i++){
        int String_lengh =
        for (j = 0; j < ; j++){

        }
    }
}

int main()
{
    printf("%d", Reading());                                        //check reading



    return 0;
}

