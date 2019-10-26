#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define TRUE 1
#define FALSE 0

char* Read(char*** index, char** text, int* index_size, int* text_size){

    FILE * Onegin = fopen ("Onegin.txt", "rb");

    long long size_of_file = 0;

    if (Onegin == NULL) printf("Error of file\n");

    else{
        fseek (Onegin, 0, SEEK_END);
        //size_of_file = filelenght (fileno (Onegin));
        size_of_file = ftell (Onegin);
        fseek (Onegin, 0, SEEK_SET);
    }

    *text = (char*) calloc ((++size_of_file), sizeof(char));
    assert (text != NULL);


    size_t length = fread (*text, sizeof(char), size_of_file, Onegin);
    assert (size_of_file == length + 1);

    for (int i = 0; i < size_of_file; i++)
        printf ("text[%d] = %d\n", i, (*text)[i]);

    printf("size of file = %lld\n", size_of_file);

    *index = (char**) calloc (size_of_file, sizeof(char*));
    assert (index != NULL);

    (*index)[0] = *text;

    printf ("text is:\n%s\n", *text);

    int number_of_strings = 1;

    for(long i = 0; i < size_of_file; i++){

        if((*text)[i] == '\r'){

            (*text)[i] = '\0';
            (*index)[number_of_strings] = *text + i + 2;

            number_of_strings ++;
        }

    }

    *index_size = number_of_strings;
    *text_size = size_of_file;

    *index = (char**) realloc (*index, number_of_strings * sizeof(char*));

    printf("number of strings = %d\n", number_of_strings);

    fclose(Onegin);

    return *text;
}

int Is_Letter(char* c){
    if(*c >= 65 && *c <= 90) *c = *c + 32;
    if((*c >= 65 && *c <= 90) || (*c >= 97 && *c <= 122)) return TRUE;
    else return FALSE;

}

int Compare (int j, int k, char** index){      //TRUE if j-string > k-string

    int i = 0;      //i for j-string
    for (int r = 0; ; r++){      //r for k - string

        char c = *(index[j] + i);
        printf("c = %c\n", c);

        while (!Is_Letter (&c)){
            if (c == '\0') return FALSE;
            i++;
            c = *(index[j] + i);
        }

        char ch = *(index[k] + r);
        printf("ch = %c\n", ch);

        while (!Is_Letter (&ch)){
            if (ch == '\0') return TRUE;
            r++;
            ch = *(index[k] + r);
        }

        if (c > ch) return TRUE;
        if (c < ch) return FALSE;
        i++;

    }
}

void Qsort(char*** index, int a_begin, int a_end, int (*Compare) (int j, int k, char** index)){

    int arr_size = a_end - a_begin + 1;
    //printf("I came to qsort index[arr_size - 1] = %d\t leftboarder = %d\n", (*index)[arr_size - 1], a_begin);

    int left = a_begin;
    int right = a_end;

    //printf("index[left] = %d\t index[right] = %d\n", (*index)[left], (*index)[right]);

    if(arr_size == 1) return;

    if (arr_size == 2){
        if (Compare(left, right, *index)){
            char* t = (*index)[right];
            (*index)[right] = (*index)[left];
            (*index)[left] = t;
        }

        return;
    }

    if (arr_size == 3){

        if (Compare(left, left + 1, *index)){
            char* t = (*index)[left + 1];
            (*index)[left + 1] = (*index)[left];
            (*index)[left] = t;
        }

        if (Compare(left + 1, left + 2, *index)){
            char* t = (*index)[left + 2];
            (*index)[left + 2] = (*index)[left + 1];
            (*index)[left + 1] = t;
        }

        if (Compare(left, left + 1, *index)){
            char* t = (*index)[left + 1];
            (*index)[left + 1] = (*index)[left];
            (*index)[left] = t;
        }

        return;
    }

    int middle = a_begin + arr_size / 2;
    printf("middle = ");
    puts((*index)[middle]);
    printf("\n");

    while (right >= left) {
        //printf("In high while\n");
        //printf("left = %d\n", left);
        while (Compare(middle, left, *index)){

            printf("In low while for left\t index[%d] = %c\n\n", left, *(*index)[left]);
            left++;
        }

        while (Compare(right, middle, *index)){

            printf("In low while for right\t index[%d] = %c\n\n", right, *(*index)[right]);
            right--;
        }

        if(right >= left){

            if(left == middle){
                char* t = (*index)[right];
                (*index)[right] = (*index)[left];
                (*index)[left] = t;

                middle = right;
                printf("\nmiddle = ");
                puts((*index)[middle]);
                printf("\n");

                printf("after swap in l = m: index[%d] = %c index[%d] = %c\n", left, *(*index)[left], right, *(*index)[right]);
                left++;
                right--;
                continue;
            }

            if(right == middle){
                char* t = (*index)[right];
                (*index)[right] = (*index)[left];
                (*index)[left] = t;

                middle = left;
                printf("middle = ");
                puts((*index)[middle]);
                printf("\n");

                printf("after swap in r = m: index[%d] = %c index[%d] = %c\n", left, *(*index)[left], right, *(*index)[right]);
                left++;
                right--;
            } else {

                char* t = (*index)[right];
                (*index)[right] = (*index)[left];
                (*index)[left] = t;
                printf("after swap: index[%d] = %c index[%d] = %c\n", left, *(*index)[left], right, *(*index)[right]);
                left++;
                right--;
            }
        }
    }

    //printf("left = %d\t right = %d\n", left, right);
    if(left - right == 2){
        printf("left - right = 2");
        if(Compare(right + 1, middle, *index))
            left--;
        else right++;
    }

    Qsort (index, a_begin, right, Compare);
    Qsort (index, left, a_end, Compare);

    return;
}

int Revers_Compare (int j, int k, char** index){

    int j_size = 0;

    while (*(index[j] + j_size) != '\0')
        j_size++;

    int k_size = 0;

    while (*(index[k] + k_size) != '\0')
        k_size++;

    int i = j_size - 1;      //i for j-string
    for (int r = k_size - 1; r >= 0 ; r--){      //r for k - string

        char c = *(index[j] + i);
        printf("c = %c\n", c);

        while (!Is_Letter (&c)){
            if (i == 0) return FALSE;
            i--;
            c = *(index[j] + i);
        }

        char ch = *(index[k] + r);
        printf("ch = %c\n", ch);

        while (!Is_Letter (&ch)){
            if (r == 0) return TRUE;
            r--;
            ch = *(index[k] + r);
        }

        if (c > ch) return TRUE;
        if (c < ch) return FALSE;
        i--;
        if(i == 0) return FALSE;

    }
}

void Writing(char** index, int index_size){
    FILE * Onegin_Sort = fopen ("Onegin_Sort.txt", "w");
    for(int i = 0; i < index_size; i++){
        //fputs(index[i], Onegin_Sort);
        fprintf(Onegin_Sort, "%s\n", index[i]);
    }
    fclose(Onegin_Sort);
}

void Revers_Writing(char** index, int index_size){
    FILE * Onegin_Revers_Sort = fopen ("Onegin_Revers_Sort.txt", "w");
    for(int i = 0; i < index_size; i++){
        //fputs(index[i], Onegin_Sort);
        fprintf(Onegin_Revers_Sort, "%s\n", index[i]);
    }
    fclose(Onegin_Revers_Sort);
}

int main(){
    char* text = NULL;
    char** index = NULL;

    int index_size = 0;
    int text_size = 0;

    Read(&index, &text, &index_size, &text_size);
    Qsort(&index, 0, index_size - 1, Compare);
    Writing(index, index_size);

    printf("\nRevers begin\n");

    Qsort(&index, 0, index_size - 1, Revers_Compare);
    Revers_Writing(index, index_size);

    free(text);
    free(index);
    return 0;
}


