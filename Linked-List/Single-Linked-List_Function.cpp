#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *next;
};

void print_list(struct Node *head){
    struct Node *inspectur = head;
    while(inspectur != NULL){
        printf("%d -> ", inspectur->value);
        inspectur = inspectur->next;
    }
    printf("NULL\n");
}

struct Node *create_node(int insert_value){
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = insert_value;
    new_node->next = NULL;
    return new_node;
}

void insert_node(struct Node **head, struct Node **tail, int insert_value){
    struct Node *new_node = create_node(insert_value);

    if(*head == NULL){ //pushFirst
        *head = new_node;
        *tail = new_node;
    }
    else{
        if(new_node->value < (*head)->value){ //pushHead
            new_node->next = *head;
            *head = new_node;
        }
        else if((*tail)->value < new_node->value){ //pushTail
            (*tail)->next = new_node;
            *tail = new_node;
        }
        else{ //pushMid
            struct Node *inspectur2 = *head, *inspectur1 = (*head)->next;
            while(inspectur1 != NULL){
                if(new_node->value < inspectur1->value){
                    inspectur2->next = new_node;
                    new_node->next = inspectur1;
                    break;
                }
                inspectur2 = inspectur1;
                inspectur1 = inspectur1->next;
            }
        }
    }
}

void delete_node(struct Node **head, struct Node **tail, int delete_value){
    struct Node *inspectur2 = NULL, *inspectur1 = *head;
    while(inspectur1 != NULL){
        if(inspectur1->value == delete_value){
            if(inspectur1 == *head && inspectur1 == *tail){ //popOne
                free(inspectur1);
                *head = NULL;
                *tail = NULL;
            }
            else if(inspectur1 == *head && inspectur1 != *tail){ //popHead
                *head = (*head)->next;
                inspectur1->next = NULL;
                free(inspectur1);
            }
            else if(inspectur1 != *head && inspectur1 == *tail){ //popTail
                *tail = inspectur2;
                (*tail)->next = NULL;
                free(inspectur1);
            }
            else if(inspectur1 != *head && inspectur1 != *tail){ //popMid
                inspectur2->next = inspectur1->next;
                inspectur1->next = NULL;
                free(inspectur1);
            }
            break;
        }
        inspectur2 = inspectur1;
        inspectur1 = inspectur1->next;
    }
}

int main(){
    struct Node *head = NULL, *tail = NULL;

    print_list(head);

    int array_size = 9;
    int insert_value[array_size] = {50, 30, 10, 100, 90, 20, 70, 40, 60};
    for(int i=0; i<array_size; i++){
        insert_node(&head, &tail, insert_value[i]);
        print_list(head);
    }

    int delete_value[array_size] = {10, 100, 30, 70, 50, 90, 20, 40, 60};
    for(int i=0; i<array_size; i++){
        delete_node(&head, &tail, delete_value[i]);
        print_list(head);
    }

    puts("Program Terminated Well!");
    return 0;
}
