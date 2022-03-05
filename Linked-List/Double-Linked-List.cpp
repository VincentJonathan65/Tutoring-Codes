#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *previous, *next;
};

void print_list(struct Node *head){
    struct Node *inspectur = head;
    while(inspectur != NULL){
        printf("%d -> ", inspectur->value);
        inspectur = inspectur->next;
    }
    printf("NULL\n");
}

int main(){
    struct Node *head = NULL, *tail = NULL;

    print_list(head);

    int array_size = 9;
    int insert_value[array_size] = {50, 30, 10, 100, 90, 20, 70, 40, 60};
    for(int i=0; i<array_size; i++){
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
        new_node->value = insert_value[i];
        new_node->next = NULL;
        new_node->previous = NULL;

        if(head == NULL){ //pushFirst
            head = new_node;
            tail = new_node;
        }
        else{
            if(new_node->value < head->value){ //pushHead
                new_node->next = head;
                head->previous = new_node;
                head = new_node;
            }
            else if(tail->value < new_node->value){ //pushTail
                tail->next = new_node;
                new_node->previous = tail;
                tail = new_node;
            }
            else{ //pushMid
                struct Node *inspectur = head;
                while(inspectur != NULL){
                    if(new_node->value < inspectur->value){
                        new_node->next = inspectur;
                        new_node->previous = inspectur->previous;
                        inspectur->previous->next = new_node;
                        inspectur->previous = new_node;
                        break;
                    }
                    inspectur = inspectur->next;
                }
            }
        }

        print_list(head);
    }

    int delete_value[array_size] = {10, 100, 30, 70, 50, 90, 20, 40, 60};
    for(int i=0; i<array_size; i++){
        struct Node *inspectur = head;
        while(inspectur != NULL){
            if(inspectur->value == delete_value[i]){
                if(inspectur == head && inspectur == tail){ //popOne
                    free(inspectur);
                    head = NULL;
                    tail = NULL;
                }
                else if(inspectur == head && inspectur != tail){ //popHead
                    head = head->next;
                    head->previous = NULL;
                    inspectur->next = NULL;
                    free(inspectur);
                }
                else if(inspectur != head && inspectur == tail){ //popTail
                    tail = inspectur->previous;
                    tail->next = NULL;
                    inspectur->previous = NULL;
                    free(inspectur);
                }
                else if(inspectur != head && inspectur != tail){ //popMid
                    inspectur->next->previous = inspectur->previous;
                    inspectur->previous->next = inspectur->next;
                    inspectur->next = NULL;
                    inspectur->previous = NULL;
                    free(inspectur);
                }
                break;
            }
            inspectur = inspectur->next;
        }
        print_list(head);
    }


    return 0;
}
