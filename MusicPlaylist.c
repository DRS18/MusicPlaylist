#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "MusicPlaylist.h"

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 0;
    }

    struct Melody *song1;
    song1 = malloc(sizeof(struct Melody));
    struct DoublyLinkedList *playlist;
    playlist = malloc(sizeof(struct DoublyLinkedList));
    init_list(playlist);

    FILE *read, *write, *song;
    char buffer[80], c, *p, *com, out_file[20], song_file[30];
    int n = 0, ver;

    strcpy(song_file, "songs/");

    read = fopen (argv[1], "rt");
    write = fopen (argv[2], "wt");
    if (read == NULL || write == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    fgets(buffer, 100, read);
    n = atoi(buffer);
    printf("%s", buffer);

    for (int i = 0; i < 1; i++) {
        fgets(buffer, 100, read);
        printf("%s", buffer);

        p = strtok(buffer, " ");
        com = p;

        p = strtok(NULL, "\n");
        if (p != NULL) {
            strcpy(out_file, p);
        }
        
        strcat(song_file, out_file);

        song = fopen (song_file, "rb");
        fseek(song, -97, SEEK_END);
        fread(song1, sizeof(struct Melody), 1, song);

        choose_command(com, playlist, song1);
        printf("%s\n", playlist->head->data->title);

        fclose(song);

        // printf("%s\n", out_file);
    }

    fclose(read);
    fclose(write);
    free(song1);
    free(playlist);

    return 0;
}

void init_list(struct DoublyLinkedList *list) {
    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->cursor = NULL;
}

void add_nth_node(struct DoublyLinkedList *list, int n, struct Melody *data) {
    if (list == NULL || n < 0) {
        return;
    }

    struct Node *mynode;
    mynode = malloc(sizeof(struct Melody));
    mynode->data = data;
    mynode->next = NULL;
    mynode->prev = NULL;

    if (list->size == 0) {
        (list->size)++;
        list->head = mynode;
        list->tail = mynode;
        return;
    }

    if (n == 0) {
        mynode->next = list->head;
        list->head->prev = mynode;
        list->tail->next = NULL;
        mynode->prev = NULL;
        list->head = mynode;
        (list->size)++;
        list->cursor = list->head;
        return;
    }

    if (n >= list->size - 1) {
        mynode->next = NULL;
        mynode->prev = list->tail;
        list->tail->next = mynode;
        list->head->prev = NULL;
        list->tail = mynode;
        (list->size)++;
        return;
    }

    struct Node *aux = list->head;
    for (int i = 1; i < n; i++) {
        aux = aux->next;
    }

    mynode->next = aux->next;
    aux->next = mynode;
    mynode->prev = aux;
    mynode->next->prev = mynode;
    (list->size)++;

}

struct Node* remove_nth_node(struct DoublyLinkedList *list, int n) {
     if (list == NULL || n < 0 || list->size == 0) {
        return NULL;
    }

    struct Node *aux;

    if (list->size == 1) {
        aux = list->head;
        (list->size)--;
        list->head = NULL;
        list->tail = NULL;
        return aux;
    }

    if (n == 0) {
        aux = list->head;
        list->tail->next = NULL;
        list->head->next->prev = NULL;
        list->head = list->head->next;
        (list->size)--;
        return aux;
    }

    if (n >= list->size - 1) {
        aux = list->tail;
        list->head->prev = NULL;
        list->tail->prev->next = NULL;
        list->tail = list->tail->prev;
        (list->size)--;
        return aux;
    }

    aux = list->head;
    for (int i = 1; i < n; i++) {
        aux = aux->next;
    }

    struct Node *trash = aux->next;
    aux->next = aux->next->next;
    aux->next->prev = aux->next->prev->prev;
    (list->size)--;
    
    return trash;
}

void free_list(struct DoublyLinkedList **pp_list) {
    struct Node *aux = (*pp_list)->head;
    int i;
    for (i = 0; i < (*pp_list)->size; i++) {
        struct Node *trash = aux;
        aux = aux->next;
        free(trash);

    }
    free(*pp_list);
}

void print_int_list(struct DoublyLinkedList *list) {
    struct Node *aux = list->head;
    for (int i = 0; i < list->size; i++) {
        printf("%d ", *((int*)(aux->data)));
        aux = aux->next;
    }
    printf("\n");
}

struct Node* get_nth_node(struct DoublyLinkedList *list, int n) {
    if (list == NULL || n < 0) {
        return NULL;
    }
    
    int i = 0;
    struct Node *aux = list->head;
    
    if (n >= list->size) {
        return list->tail;
    }

    for (i = 0; i < n; i++) {
        aux = aux->next;
    }

    return aux;
}

int get_size(struct DoublyLinkedList *list) {
    return list->size;
}

void choose_command(char *p, struct DoublyLinkedList *list, struct Melody *song1) {
    if (strcmp(p, "ADD_FIRST") == 0) {
        printf("in regula\n");
        add_nth_node(list, 0, song1);
        return;
    }

    if (strcmp(p, "ADD_LAST") == 0) {
        return;
    }

    if (strcmp(p, "ADD_AFTER") == 0) {
        return;
    }

    if (strcmp(p, "DEL_FIRST") == 0) {
        return;
    }

    if (strcmp(p, "DEL_LAST") == 0) {
        return;
    }

    if (strcmp(p, "DEL_CURR") == 0) {
        return;
    }

    if (strcmp(p, "DEL_SONG") == 0) {
        return;
    }

    if (strcmp(p, "MOVE_NEXT") == 0) {
        return;
    }

    if (strcmp(p, "MOVE_PREV") == 0) {
        return;
    }

    if (strcmp(p, "SHOW_FIRST") == 0) {
        return;
    }

    if (strcmp(p, "SHOW_LAST") == 0) {
        return;
    }

    if (strcmp(p, "SHOW_CURR") == 0) {
        return;
    }

    if (strcmp(p, "SHOW_PLAYLIST") == 0) {
        return;
    }
}