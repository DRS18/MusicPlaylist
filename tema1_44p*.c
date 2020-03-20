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
    struct DoublyLinkedList *playlist;
    FILE *read, *write, *song;
    char buffer[100], c, *p, *com, out_file[50], song_file[50];
    int n = 0, ver, ok = 0;

    // song1 = malloc(sizeof(struct Melody));
    playlist = malloc(sizeof(struct DoublyLinkedList));
    init_list(playlist);

    read = fopen (argv[1], "rt");
    write = fopen (argv[2], "wt");

    if (read == NULL || write == NULL) {
        //printf("Error opening file\n");
        return 1;
    }

    fgets(buffer, 100, read);
    n = atoi(buffer);
    //printf("%s", buffer);

    for (int i = 0; i < n; i++) {
        
        fgets(buffer, 100, read);
        //printf("\n%s", buffer);
        strcpy(song_file, "songs/");
        
        p = strtok(buffer, " ");
        com = p;
        p = strtok(NULL, "\n");
        if (p != NULL) {
            strcpy(out_file, p);
        }

        strcat(song_file, out_file);
        song = fopen (song_file, "rb");
        if(song != NULL) {
            
            
            // //printf("Before_read\n");
            // print_string(playlist);
            ok = 1;
            if (strcmp(com, "ADD_FIRST") == 0 ||  strcmp(com, "ADD_LAST") == 0 ||
            strcmp(com, "ADD_AFTER") == 0 || strcmp(com, "DEL_SONG") == 0) {
                fseek(song, -97, SEEK_END);
                song1 = malloc(sizeof(struct Melody));
                fread(song1, sizeof(struct Melody), 1, song);
            }
            

            // //printf("After_read\n");
            // print_string(playlist);
        
            choose_command(com, playlist, song1, write);
            fclose(song);
            
        }
        
        // if(playlist->cursor != NULL) printf("--->CURSOUL E LA %s\n", playlist->cursor->data->title);
    }

    fclose(read);
    fclose(write);
    // if(ok!=0) free(song1);
    free_list(&playlist);

    // free(playlist);
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
    mynode = malloc(sizeof(struct Node));
    mynode->data = data;
    mynode->next = NULL;
    mynode->prev = NULL;

    if (list->size == 0) {
        
        (list->size)++;
        list->head = mynode;
        list->tail = mynode;
        list->cursor = list->head;
        return;
    }

    if (n == 0) {
        
        mynode->next = list->head;
        list->head->prev = mynode;
        // list->tail->next = NULL;
        // mynode->prev = NULL;
        list->head = mynode;
        (list->size)++;
        // list->cursor = list->head;
        return;
    }

    if (n >= list->size) {
        
        // mynode->next = NULL;
        mynode->prev = list->tail;
        list->tail->next = mynode;
        // list->head->prev = NULL;
        list->tail = mynode;
        // list->cursor = list->tail;
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
    // list->cursor = aux->next;
    (list->size)++;

}

void remove_nth_node(struct DoublyLinkedList *list, int n) {
     if (list == NULL || n < 0 || list->size == 0) {
        // return NULL;
        return;
    }
    
    struct Node *aux;

    if (list->size == 1) {
        //printf("AAAA\n");
        aux = list->head;
        // free(list->head->data);
        (list->size)--;
        list->head = NULL;
        list->tail = NULL;
        free(aux->data);
        free(aux);
        // return aux;
        return;
    }

    if (n == 0) {
        // aux = list->head;
        // list->tail->next = NULL;
        //printf("AAAA\n");
        aux = list->head;
        list->head->next->prev = NULL;
        list->head = list->head->next;
        (list->size)--;
        free(aux->data);
        free(aux);
        // return aux;
        return;
    }

    if (n >= list->size - 1) {
        // list->head->prev = NULL;
        aux = list->tail;
        list->tail->prev->next = NULL;
        list->tail = list->tail->prev;
        (list->size)--;
        free(aux->data);
        free(aux);
        // return aux;
        return;
    }

    aux = list->head;
    for (int i = 1; i < n; i++) {
        aux = aux->next;
    }

    // struct Node *trash = aux->next;
    struct Node *trash;
    trash = aux->next;
    
    aux->next = aux->next->next;
    aux->next->prev = aux->next->prev->prev;
    (list->size)--;
    print_string(list);
    free(trash->data);
    free(trash);

    // return trash;
    return;
}

void free_list(struct DoublyLinkedList **pp_list) {
    struct Node *aux = (*pp_list)->head;
    struct Node *trash;
    int i;
   
    for (i = 0; i < (*pp_list)->size; i++) {
        trash = aux;
        aux = aux->next;
        //printf("TRASH %s\n", trash->data->title);
        free(trash->data);
        free(trash);

    }
    // free(aux);
    free(*pp_list);
}

void print_int_list(struct DoublyLinkedList *list) {
    struct Node *aux = list->head;
    for (int i = 0; i < list->size; i++) {
        //printf("%d ", *((int*)(aux->data)));
        aux = aux->next;
    }
    //printf("\n");
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

void choose_command(char *p, struct DoublyLinkedList *list, struct Melody *song1, FILE *write) {
    int pos = 0, i;
    struct Node *aux;
    
    // //printf("%s\n", p);

    if (strcmp(p, "ADD_FIRST") == 0) {
        // //printf("add inceput\n");
        // print_string(list);
        if (list->size == 0) {
            add_nth_node(list, 0, song1);
            return;
        }
        aux = list->head;
        for (i = 0; i < list->size; i++) {
            if (strcmp(aux->data->title, song1->title) == 0) {
                remove_nth_node(list, i);
                add_nth_node(list, 0, song1);
                return;
            }
            if (aux->next != NULL) {
                aux = aux->next;
            }
        }
        // free(song1);
        // print_string(list);
        add_nth_node(list, 0, song1);
        return;
    }

    if (strcmp(p, "ADD_LAST") == 0) {
        // //printf("add final\n");
        // print_string(list);
        if (list->size == 0) {
            add_nth_node(list, list->size, song1);
            return;
        }
        aux = list->head;
        for (i = 0; i < list->size; i++) {
            if (strcmp(aux->data->title, song1->title) == 0) {
                remove_nth_node(list, i);
                add_nth_node(list, list->size, song1);
                return;
            }
            if (aux->next != NULL) {
                aux = aux->next;
            }
        }
        // free(song1);
        // print_string(list);
        add_nth_node(list, list->size, song1);
        return;
    }

    if (strcmp(p, "ADD_AFTER") == 0) {
        // //printf("add after\n");
        // if (list->cursor->next != NULL) {
        //     if ((strcmp(list->cursor->next->data->title, song1->title) == 0)) {
        //         return;
        //     }
        // }
        char *aux1;
        aux1 = list->cursor->data->title;
        if (list->size == 0 || (strcmp(aux1, song1->title) == 0)) {
            free(song1);
            return;
        }
        aux = list->head;
        for (i = 0; i < list->size; i++) {
            if (strcmp(aux->data->title, song1->title) == 0) {
                remove_nth_node(list, i);
                break;
            }
                aux = aux->next;
        }
        // pos = 0;
        // while (aux != list->cursor->next) {
        //     if(aux->next!=NULL) aux = aux->next;
        //     pos++;
        // }
        // add_nth_node(list, pos - 1, song1);
        aux = list->head;
        for(i = 0; i < list->size; i++) {
            if (strcmp(aux->data->title, list->cursor->data->title) == 0) {
                add_nth_node(list, i + 1, song1);
                return;
            }
            if (aux->next != NULL) {
                aux = aux->next;
            }
        }
        free(song1);
        return;
    }

    if (strcmp(p, "DEL_FIRST\n") == 0) {
        if (list->size == 0) {
            //printf("Error: delete from empty playlist\n");
            fprintf(write, "Error: delete from empty playlist\n");
            return;
        }
        // //printf("del_first\n");

        if (list->cursor == list->head && list->head->next != NULL) {
            list->cursor = list->head->next;
        }

        remove_nth_node(list, 0);
        // free(song1);
        return;
    }

    if (strcmp(p, "DEL_LAST\n") == 0) {
        if (list->size == 0) {
            //printf("Error: delete from empty playlist\n");
            fprintf(write, "Error: delete from empty playlist\n");
            return;
        }
        // //printf("del_last\n");
        
        if (list->cursor == list->tail && list->tail->prev != NULL) {
            list->cursor = list->tail->prev;
        }
        remove_nth_node(list, list->size);
        // free(song1);
        return;
    }

    if (strcmp(p, "DEL_CURR\n") == 0) {
        if (list->size == 0) {
            //printf("Error: delete from empty playlist\n");
            fprintf(write, "Error: no track playing\n");
            return;
        }
        
        // //printf("del_curr\n");
        aux = list->head;

        // //printf("%s\n", list->cursor->data->title);
        // //printf("%s - %s\n", aux->data->title, aux->next->data->title);
        while (strcmp(aux->data->title, list->cursor->data->title) != 0) {
            //printf("%s - %s\n", aux->data->title, list->cursor->data->title);
            if (aux == NULL) {
                break;
            } else {
                aux = aux->next;
                pos++;
            }
        }
        
        if (aux == list->cursor) {
            if (list->cursor->next != NULL) {
                list->cursor = list->cursor->next;
            } else {
                if (list->cursor->prev != NULL) {
                    list->cursor = list->cursor->prev;
                }
            }

            remove_nth_node(list, pos);

            // free(song1);
            // //printf("%s\n", list->cursor->data->title);
            return;
        } else {
            //printf("Error: no track playing\n");
            fprintf(write, "Error: no track playing\n");
            // free(song1);
            return;
        }
        
    }

    if (strcmp(p, "DEL_SONG") == 0) {
        // //printf("del_song\n");
        // //printf("VERIFICARE %s\n", song1->title);
        aux = list->head;

        // if (strcmp(song1->title, aux->data->title) == 0) {
        //     if (strcmp(song1->title, list->cursor->data->title) == 0) {
        //             if (list->cursor->next != NULL) {
        //                 list->cursor = list->cursor->next;
        //             } else {
        //                 if (list->cursor->prev != NULL) {
        //                     list->cursor = list->cursor->prev;
        //                 }
        //             }
        //         }
        //     remove_nth_node(list, 0);
        //     free(song1);
        //     return;
        // }

        for (i = 0; i < list->size; i++) {
            if (strcmp(song1->title, aux->data->title) == 0) {
                if (strcmp(song1->title, list->cursor->data->title) == 0) {
                    if (list->cursor->next != NULL) {
                        list->cursor = list->cursor->next;
                    } else {
                        if (list->cursor->prev != NULL) {
                            list->cursor = list->cursor->prev;
                        }
                    }
                }
                remove_nth_node(list, i);
                free(song1);
                return;
            }
            if (aux->next != NULL) {
                aux = aux->next;
            }
        }
        free(song1);
        fprintf(write, "Error: no song found to delete\n");
        //printf("Error: no song found to delete\n");
        // free(song1);
        return;
    }

    if (strcmp(p, "MOVE_NEXT\n") == 0) {
        // //printf("move next\n");
        if (list->size == 0) {
            //printf("Error: no track playing\n");
            fprintf(write, "Error: no track playing\n");
            return;
        }
        aux = list->head;
        for (i = 0; i < list->size; i++) {
            if (aux == list->cursor) {
                if (list->cursor->next != NULL) {
                    list->cursor = list->cursor->next;
                    return;
                } else {
                    // free(song1);
                    return;
                }
            }
            if (aux->next != NULL) {
                aux = aux->next;
            }
        }
        //printf("Error: no track playing\n");
        fprintf(write, "Error: no track playing\n");
        // free(song1);
        return;
    }

    if (strcmp(p, "MOVE_PREV\n") == 0) {
        // //printf("move prev\n");
        if (list->size == 0) {
            //printf("Error: no track playing\n");
            fprintf(write, "Error: no track playing\n");
            return;
        }
        aux = list->head;
        for (i = 0; i < list->size; i++) {
            if (aux == list->cursor) {
                if (list->cursor->prev != NULL) {
                    list->cursor = list->cursor->prev;
                    return;
                } else {
                    // free(song1);
                    return;
                }
            }
            if (&aux->next != NULL) {
                aux = aux->next;
            }
        }
        //printf("Error: no track playing\n");
        fprintf(write, "Error: no track playing\n");
        // free(song1);
        return;
    }

    if (strcmp(p, "SHOW_FIRST\n") == 0) {
        if (list->size == 0) {
            //printf("Error: show empty playlist\n");
            fprintf(write, "Error: show empty playlist\n");
            // free(song1);
            return;
        }
        print_melody(list->head, write);
        // free(song1);
        return;
    }

    if (strcmp(p, "SHOW_LAST\n") == 0) {
        if (list->size == 0) {
            //printf("Error: show empty playlist\n");
            fprintf(write, "Error: show empty playlist\n");
            return;
        }
        print_melody(list->tail, write);
        // free(song1);
        return;
    }

    if (strcmp(p, "SHOW_CURR\n") == 0) {
        if (list->size == 0) {
            //printf("Error: show empty playlist\n");
            fprintf(write, "Error: show empty playlist\n");
            return;
        }
        if (&list->cursor != NULL) {
            print_melody(list->cursor, write);
            // free(song1);
            return;
        }
        //printf("Error: show empty playlist\n");
        fprintf(write, "Error: show empty playlist\n");
        // free(song1);
        return;
    }

    if (strcmp(p, "SHOW_PLAYLIST\n") == 0) {
        if (list->size == 0) {
            //printf("[]\n");
            fprintf(write, "[]\n");
            return;
        }
        aux = list->head;
        //printf("[");
        fprintf(write, "[");
        for (i = 0; i < list->size; i++) {
            //printf("%s", aux->data->title);
            fprintf(write, "%.30s", aux->data->title);
            if (i != list->size - 1) {
                //printf("; ");
                fprintf(write, "; ");
            }
            aux = aux->next;
        }
        //printf("]\n");
        fprintf(write, "]\n");
        // free(song1);
        return;
    }
}

void print_string(struct DoublyLinkedList *list) {
    struct Node *aux = list->head;
    while (aux != NULL) {
        //printf("%s ", (char*)(aux->data->title));
        aux = aux->next;
    }
    //printf("\n");
}

void print_melody(struct Node *song, FILE *write) {
    //printf("Title: %.30s\n", song->data->title);
    fprintf(write, "Title: %.30s\n", song->data->title);
    //printf("Artist: %.30s\n", song->data->artist);
    fprintf(write, "Artist: %.30s\n", song->data->artist);
    //printf("Album: %.30s\n", song->data->album);
    fprintf(write, "Album: %.30s\n", song->data->album);
    //printf("Year: %.4s\n", song->data->year);
    fprintf(write, "Year: %.4s\n", song->data->year);
    return;
}