#ifndef __MUSICPLAYLIST_h__
#define __MUSICPLAYLIST_h__

struct Melody {
    char TAG[3];
    char title[30];
    char artist[30];
    char album[30];
    char year[4];
};

struct Node {
    struct Melody *data;
    // void *data;
    struct Node *next;
    struct Node *prev;
};

struct DoublyLinkedList {
    struct Node *head;
    struct Node *tail;
    struct Node *cursor;
    int size;
};

void init_list(struct DoublyLinkedList *list);

void add_nth_node(struct DoublyLinkedList *list, int n, struct Melody *data);

struct Node* remove_nth_node(struct DoublyLinkedList *list, int n);

void free_list(struct DoublyLinkedList **pp_list);

void print_int_list(struct DoublyLinkedList *list);

struct Node* get_nth_node(struct DoublyLinkedList *list, int n);

int get_size(struct DoublyLinkedList *list);

void choose_command(char *p, struct DoublyLinkedList *list, struct Melody *song1);

#endif