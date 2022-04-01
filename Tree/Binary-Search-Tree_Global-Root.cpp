#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *left_child, *right_child;
} *root; //otomatis NULL

void get_enter(){
    printf(" Enter to Continue..."); getchar();
}

int menu(){
    int choice;
    for(;;){ //endless loop
    // while(1 == 1){
        system("CLS || clear");
        puts("1. Insert");
        puts("2. Delete");
        puts("3. Print");
        puts("4. Update");
        puts("5. Clear All");
        puts("0. Exit");
        printf(">> "); scanf("%d", &choice); getchar();

        if(choice >= 0 && choice <= 5){
            return choice;
        }
        else{
            printf("Menu doesn't exist!"); get_enter();
        }
    }
}

struct Node *create_node(int value){
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->left_child = new_node->right_child = NULL;
    return new_node;
}

// [GAGAL]
// void insert(struct Node *new_node){
//     struct Node *current_node = root;
//     for(;;){
//         if(current_node == NULL){ //tempat yang pas untuk insert
//             current_node = new_node;
//             return;
//         }
//         else{ //ada isinya
//             if(new_node->value < current_node->value){
//                 current_node = current_node->left_child;
//             }
//             else if(new_node->value > current_node->value){
//                 current_node = current_node->right_child;
//             }
//             else{
//                 printf("Value already exist!"); get_enter();
//                 return;
//             }
//         }
//     }
// }

struct Node *insert(struct Node *new_node, struct Node *current_node){
    if(current_node == NULL){ //tempat yang pas untuk insert
        current_node = new_node;
        return current_node;
    }
    else{ //ada isinya
        if(new_node->value < current_node->value){
            current_node->left_child = insert(new_node, current_node->left_child);
        }
        else if(new_node->value > current_node->value){
            current_node->right_child = insert(new_node, current_node->right_child);
        }
        else{
            printf("Value already exist!"); get_enter();
        }
        return current_node;
    }
}

void pre_order(struct Node *current_node){
    if(current_node == NULL){
        return;
    }
    printf("%d ", current_node->value);
    pre_order(current_node->left_child);
    pre_order(current_node->right_child);
    // return;
}

void in_order(struct Node *current_node){
    if(current_node == NULL){
        return;
    }
    in_order(current_node->left_child);
    printf("%d ", current_node->value);
    in_order(current_node->right_child);
    // return;
}

void post_order(struct Node *current_node){
    if(current_node == NULL){
        return;
    }
    post_order(current_node->left_child);
    post_order(current_node->right_child);
    printf("%d ", current_node->value);
    // return;
}

void print(){
    printf("Pre-Order: "); pre_order(root); puts("");
    printf("In-Order: "); in_order(root); puts("");
    printf("Post-Order: "); post_order(root); puts("");
    get_enter();
}

struct Node *predecessor(struct Node *target_delete){
    //di kiri tapi paling besar
    struct Node *predecessor_node = target_delete->left_child;
    while(predecessor_node->right_child != NULL){
        predecessor_node = predecessor_node->right_child;
    }
    return predecessor_node;
}

struct Node *successor(struct Node *target_delete){
    //di kanan tapi paling kecil
    struct Node *successor_node = target_delete->right_child;
    while(successor_node->left_child != NULL){
        successor_node = successor_node->left_child;
    }
    return successor_node;
}

struct Node *delete_node(struct Node *current_node, int target_value){
    if(current_node == NULL){
        return current_node;
        // return NULL;
    }
    if(target_value < current_node->value){
        current_node->left_child = delete_node(current_node->left_child, target_value);
    }
    else if(target_value > current_node->value){
        current_node->right_child = delete_node(current_node->right_child, target_value);
    }
    else if(target_value == current_node->value){ //ketemu
        if(current_node->left_child == NULL && current_node->right_child == NULL){
            free(current_node);
            return NULL;
        }
        else if(current_node->left_child == NULL || current_node->right_child == NULL){
            struct Node *child;
            if(current_node->left_child != NULL){
                child = current_node->left_child;
            }
            else if(current_node->right_child != NULL){
                child = current_node->right_child;
            }
            free(current_node);
            return child;
        }
        else if(current_node->left_child != NULL && current_node->right_child != NULL){
            //========== Teknik Predecessor ============
            // struct Node *penerus = predecessor(current_node);

            // //swap
            // int temp = penerus->value;
            // penerus->value = current_node->value;
            // current_node->value = temp;

            // current_node->left_child = delete_node(current_node->left_child, target_value);


            //========== Teknik Successor ============
            struct Node *penerus = successor(current_node);

            //swap
            int temp = penerus->value;
            penerus->value = current_node->value;
            current_node->value = temp;

            current_node->right_child = delete_node(current_node->right_child, target_value);
        }
    }
    return current_node;
}

int main(){
    while(1 == 1){
        int choice = menu();
        switch(choice){
            case 1:{ //insert
                int target;
                printf("Isi Value: "); scanf("%d", &target); getchar();
                struct Node *newNode = create_node(target);
                root = insert(newNode, root);
                break;
            }
            case 2:{ //delete
                int target;
                printf("Target Delete: "); scanf("%d", &target); getchar();
                root = delete_node(root, target);
                break;
            }
            case 3:{ //print
                print();
                break;
            }
            case 4:{ //update
                int target_lama;
                printf("Target Update: "); scanf("%d", &target_lama); getchar();
                root = delete_node(root, target_lama);
                
                int target_baru;
                printf("New Value: "); scanf("%d", &target_baru); getchar();
                struct Node *new_node = create_node(target_baru);
                root = insert(new_node, root);
                break;
            }
            case 5:{ //clear all
                while(root != NULL){
                    root = delete_node(root, root->value);
                }
                break;
            }
            case 0:{ //exit
                printf("Program Terminated Well!");
                return 0;
            }
        }
    }
}