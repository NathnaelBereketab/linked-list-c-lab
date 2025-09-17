#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

// ===== allocation =====
list_t *list_alloc(void) {
    list_t *l = malloc(sizeof(list_t));
    if (!l) { perror("malloc"); exit(1); }
    l->head = NULL;
    return l;
}

void list_free(list_t *l) {
    if (!l) return;
    node_t *cur = l->head;
    while (cur) {
        node_t *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
    free(l);
}

// ===== utilities =====
int list_length(list_t *l) {
    int count = 0;
    node_t *cur = l ? l->head : NULL;
    while (cur) {
        count++;
        cur = cur->next;
    }
    return count;
}

void list_print(list_t *l) {
    if (!l || !l->head) {
        printf("NULL\n");
        return;
    }
    node_t *cur = l->head;
    while (cur) {
        printf("%d -> ", cur->data);
        cur = cur->next;
    }
    printf("NULL\n");
}

char *listToString(list_t *l) {
    char *buf = malloc(1024);
    buf[0] = '\0';
    node_t *cur = l ? l->head : NULL;
    while (cur) {
        char tmp[32];
        sprintf(tmp, "%d->", cur->data);
        strcat(buf, tmp);
        cur = cur->next;
    }
    strcat(buf, "NULL");
    return buf;
}

// ===== insertion =====
void list_add_to_front(list_t *l, elem value) {
    node_t *n = malloc(sizeof(node_t));
    n->data = value;
    n->next = l->head;
    l->head = n;
}

void list_add_to_back(list_t *l, elem value) {
    node_t *n = malloc(sizeof(node_t));
    n->data = value;
    n->next = NULL;

    if (!l->head) {
        l->head = n;
        return;
    }
    node_t *cur = l->head;
    while (cur->next) cur = cur->next;
    cur->next = n;
}

void list_add_at_index(list_t *l, elem value, int index) {
    if (index <= 0) return;
    if (index == 1) {
        list_add_to_front(l, value);
        return;
    }
    node_t *cur = l->head;
    int pos = 1;
    while (cur && pos < index - 1) {
        cur = cur->next;
        pos++;
    }
    if (!cur) return;
    node_t *n = malloc(sizeof(node_t));
    n->data = value;
    n->next = cur->next;
    cur->next = n;
}

// ===== removal =====
elem list_remove_from_front(list_t *l) {
    if (!l || !l->head) return -1;
    node_t *tmp = l->head;
    elem val = tmp->data;
    l->head = tmp->next;
    free(tmp);
    return val;
}

elem list_remove_from_back(list_t *l) {
    if (!l || !l->head) return -1;
    if (!l->head->next) return list_remove_from_front(l);

    node_t *cur = l->head;
    while (cur->next->next) cur = cur->next;

    elem val = cur->next->data;
    free(cur->next);
    cur->next = NULL;
    return val;
}

elem list_remove_at_index(list_t *l, int index) {
    if (!l || index <= 0 || !l->head) return -1;
    if (index == 1) return list_remove_from_front(l);

    node_t *cur = l->head;
    int pos = 1;
    while (cur && pos < index - 1) {
        cur = cur->next;
        pos++;
    }
    if (!cur || !cur->next) return -1;

    node_t *tmp = cur->next;
    elem val = tmp->data;
    cur->next = tmp->next;
    free(tmp);
    return val;
}

// ===== queries =====
bool list_is_in(list_t *l, elem value) {
    node_t *cur = l ? l->head : NULL;
    while (cur) {
        if (cur->data == value) return true;
        cur = cur->next;
    }
    return false;
}

elem list_get_elem_at(list_t *l, int index) {
    if (!l || index <= 0) return -1;
    node_t *cur = l->head;
    int pos = 1;
    while (cur && pos < index) {
        cur = cur->next;
        pos++;
    }
    return cur ? cur->data : -1;
}

int list_get_index_of(list_t *l, elem value) {
    int pos = 1;
    node_t *cur = l ? l->head : NULL;
    while (cur) {
        if (cur->data == value) return pos;
        cur = cur->next;
        pos++;
    }
    return -1;
}
