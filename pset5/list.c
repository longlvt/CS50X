#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    int *list = malloc(3 * sizeof(int));
    if (list == NULL)
    {
        return 1;
    }
    list[0] = 1;
    list[1] = 2;
    list[2] = 3;
    printf("FIST MEMORY ADDRESS: %p\n", list);

    // int *tmp = malloc(4 * sizeof(int));
    int *tmp = realloc(list, 4 * sizeof(int)); // Re-allocate the memory, which takes all the values on the original memory
    printf("NEW MEMORY ADDRESS: %p\n", tmp);
    if (tmp == NULL)
    {
        free(list);
        return 1;
    }
    // for (int i = 0; i < 4; i++)
    // {
    //     tmp[i] = list[i];
    // }
    tmp[3] = 4;
    // free(list); // free the old memory of 'list'

    list = tmp; // Assign new address of memory to 'list'

    for (int j = 0; j < 4; j++)
    {
        printf("%i\n", list[j]);
    }

    free(list); // Only need to free 'list', becasue 'tmp' is just another pointer to the same memory as 'list'.

}