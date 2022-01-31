#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *next, *before;
};

int get_linked_list_index(int value, int hash_table_size){
    value = value - (value % 10);
    int index = (value/10) - 1;
    return index % hash_table_size;
}

int main(){
    int hash_table_size = 5;
    struct Node *head[hash_table_size], *tail[hash_table_size];
    for(int i=0; i<hash_table_size; i++){
        head[i] = NULL;
        tail[i] = NULL;
    }

    int data_insert[10] = {36, 48, 99, 14, 88, 48, 67, 44, 18, 66};
    int data_delete[11] = {36, 66, 48, 67, 99, 14, 48, 88, 18, 44, 100};

    //proses Insert
    for(int i=0; i<10; i++){
        //pembuatan Node
        struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
        new_node->value = data_insert[i];
        new_node->next = NULL;
        new_node->before = NULL;

        //Proses dapetin Index Linked-list
        int index = get_linked_list_index(new_node->value, hash_table_size);

        //Insert selalu pushTail (insert di tail)
        if(head[index] == NULL){ //jika linked-listnya empty
            head[index] = new_node;
            tail[index] = new_node;
        }
        else{ //jika linked-list tidak empty
            new_node->before = tail[index];
            tail[index]->next = new_node;
            tail[index] = new_node;
        }
    }

    //proses Delete
    for(int i=0; i<11; i++){ 
        //proses pencarian index linked-list
        int index = get_linked_list_index(data_delete[i], hash_table_size);

        if(head[index] == NULL){ //jika linked-list kosong/empty
            continue;
        }
        else{ //jika linked-list tidak kosong
            if(head[index]->value == data_delete[i]){ //remove di Head
                if(head[index] == tail[index]){ //jika tersisa satu node di linked-list
                    free(head[index]);
                    head[index] = NULL;
                    tail[index] = NULL;
                    continue;
                }
                else{//jika tersisa lebih dari satu node di linked-list

                    //Head dipindahkan
                    struct Node *target_delete = head[index];
                    head[index] = head[index]->next;

                    //Pemutusan rantai/panah
                    head[index]->before = NULL;
                    target_delete->next = NULL;

                    free(target_delete);
                    target_delete = NULL;
                }
            }
            else{
                struct Node *target_delete = head[index]->next;

                //proses pencarian node yang mau di delete dalam linked-list
                while(target_delete != NULL){

                    //Masuk IF jika node yang mau di delete ditemukan
                    if(target_delete->value == data_delete[i]){
                        if(target_delete == tail[index]){
                            //pemutusan rantai/panah jika hapus di Tail
                            tail[index] = target_delete->before;
                            target_delete->before->next = NULL;
                            target_delete->before = NULL;
                        }
                        else{
                            //pemutusan rantai/panah jika hapus di tengah-tengah
                            target_delete->next->before = target_delete->before;
                            target_delete->before->next = target_delete->next;
                            target_delete->next = NULL;
                            target_delete->before = NULL;
                        }

                        free(target_delete);
                        target_delete = NULL;
                        break;
                    }
                    target_delete = target_delete->next;
                }
            }
        }
    }

    puts("Program Terminated Well");
    return 0;
}