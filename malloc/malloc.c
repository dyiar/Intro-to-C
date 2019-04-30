// #ifdef __STDC_ALLOC_LIB__
// #define __STDC_WANT_LIB_EXT2__ 1
// #else
// #define _POSIX_C_SOURCE 200809L
// #endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"
// #include <string.h>
// #include <assert.h>

/*
    Duplicates the input string by dynamically allocating memory for 
    the duplicate string using `malloc` and then copying the string
    into the allocated memory. Returns a pointer to the allocated memory.
    You may want to use the string_length function to figure out the
    length of the input string.
*/
char *string_dup(char *src)
{
    // char *ptr = strdup(src);
    // ptr = (char*) realloc(ptr, 2*strlen(src) + 1);
    // strcat(ptr, src);

    // return ptr;

    // size_t len = strlen(src);
    // char *ret = realloc(src, 2*len+1);
    // if(ret) {
    //     memcpy(ret+len, ret, len);
    //     ret[2*len]=0;
    // }
    // return ret;

    int size = string_length(src);
    char *output = malloc(size + 1);
    for (int i = 0; i <= size; i++) {
        output[i] = src[i];
    }
    output[size] = '\0';

    return output;

}

/*
    A generic version of string_copy, mem_copy receives a block of memory
    of any type and copies its contents to the destination pointer (dest).
    You may want to cast the input pointers to char pointers first before
    performing the copying. `n` is the amount of data that should be copied
    from `src` to `dest`. 
*/
void mem_copy(void *dest, const void *src, int n)
{
    char *cast_src = (char *) src;
    char *cast_dest = (char *) dest;

    while (n > 0) {
        *cast_dest = *cast_src;
        cast_dest++;
        cast_src++;
        n--;
    }

    *cast_dest = '\0';
}

/*
    Given a pointer of `malloc`'d memory, this function will 
    attempt to resize the allocated memory to the new specified
    size. Any data that was previously in the old `malloc`'d 
    memory should be intact in the new resized block of memory. 
    Some edge cases to consider: how should resizing be handled
    in the case when old_size < new_size? What about when 
    old_size > new_size?
    
    Do not use the `realloc` function from the standard libary.
*/
void *resize_memory(void *ptr, int old_size, int new_size)
{
    char *new = (char *) malloc(new_size);
    char *pointer = ptr;
    for (int i = 0; i <= old_size; i++) {
        if (i == new_size) {
            break;
        }
        new[i] = pointer[i];
    }

    return new;


}

#ifndef TESTING
int main(void)
{
    char *s = "Some string to duplicate.";
    char *dup = string_dup(s);

    printf("Duplicated string: %s\n", dup);

    int numbers[] = {100, 55, 4, 98, 10, 18, 90, 95, 43, 11, 47, 67, 89, 42, 49, 79};
    int n = sizeof(numbers) / sizeof(numbers[0]);
    int *target = malloc(n * sizeof(int));
    
    mem_copy(target, numbers, n * sizeof(int));

    printf("Copied array: ");

    for (int i = 0; i < n; i++) {
        printf("%d ", target[i]);
    }

    printf("\n");

    char *url = string_dup("http://lambdaschool.com");
    char *path = string_dup("/students/");
    int url_length = string_length(url);
    int path_length = string_length(path);
    
    int new_length = url_length - 1 + path_length;
    char *new_url = resize_memory(url, url_length, new_length);
    char *p = new_url + url_length;

    while (*path != '\0') {
        *p = *path;
        p++;
        path++;
    }

    printf("Full path string: %s\n", new_url);

    return 0;
}
#endif