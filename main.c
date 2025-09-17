#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

int main() {
    list_t *lst = list_alloc();

    printf("=== Tests ===\n");

    list_add_to_back(lst, 5);
    list_add_to_back(lst, 15);
    list_add_to_back(lst, 25);
    list_print(lst);

    list_add_to_front(lst, 1);
    list_add_to_front(lst, 0);
    list_print(lst);

    list_add_at_index(lst, 99, 3);
    list_print(lst);

    printf("Length: %d\n", list_length(lst));

    printf("Elem at 2: %d\n", list_get_elem_at(lst, 2));
    printf("Index of 25: %d\n", list_get_index_of(lst, 25));

    printf("Remove front: %d\n", list_remove_from_front(lst));
    list_print(lst);

    printf("Remove back: %d\n", list_remove_from_back(lst));
    list_print(lst);

    printf("Remove at 3: %d\n", list_remove_at_index(lst, 3));
    list_print(lst);

    char *s = listToString(lst);
    printf("As string: %s\n", s);
    free(s);

    list_free(lst);
    return 0;
}
