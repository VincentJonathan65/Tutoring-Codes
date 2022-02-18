#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *left, *right;
};

struct Node *createNode(struct Node *root, int value){
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

struct Node *insert_node(struct Node *root, struct Node *new_node){
    if(root == NULL){
        root = new_node;
    }
    else{
        if(root->value < new_node->value){ //right child
            root->right = insert_node(root->right, new_node);
        }
        else if(new_node->value <= root->value){ //left child (tree left descendants will more often inserted than right descendants)
            root->left = insert_node(root->left, new_node);
        }
    }
    return root;
}

struct Node *find_predecessor(struct Node *root){
    struct Node *predecessor = (root)->left;
    while(predecessor->right != NULL){
        predecessor = predecessor->right;
    }
    return predecessor;
}

struct Node *find_successor(struct Node *root){
    struct Node *successor = (root)->right;
    while(successor->left != NULL){
        successor = successor->left;
    }
    return successor;
}

struct Node *delete_node(struct Node *root, int target){
    if(root != NULL){
        if(root->value < target){
            root->right = delete_node(root->right, target);
        }
        else if(target < root->value){
            root->left = delete_node(root->left, target);
        }
        else if(target == root->value){ //target found
            if(root->left == NULL && root->right == NULL){
                free(root);
                root = NULL;
            }
            else if(root->left != NULL){ //tree left descendants will more often deleted than right descendants
                struct Node *predecessor = find_predecessor(root);
                root->value = predecessor->value;
                root->left = delete_node(root->left, predecessor->value);
            }
            else if(root->right != NULL){
                struct Node *successor = find_successor(root);
                root->value = successor->value;
                root->right = delete_node(root->right, successor->value);
            }
        }
    }
    return root;
}

void preorder_print(struct Node *root){
    if(root != NULL){
        printf("%d ", root->value);
        preorder_print(root->left);
        preorder_print(root->right);
    }
}

void inorder_print(struct Node *root){
    if(root != NULL){
        inorder_print(root->left);
        printf("%d ", root->value);
        inorder_print(root->right);
    }
}

void postorder_print(struct Node *root){
    if(root != NULL){
        postorder_print(root->left);
        postorder_print(root->right);
        printf("%d ", root->value);
    }
}

struct Node *delete_all_node(struct Node *root){
    if(root != NULL){
        root->left = delete_all_node(root->left);
        root->right = delete_all_node(root->right);
        free(root);
        root = NULL;
    }
    return root;
}

void print_tree(struct Node *root);
void menu(int *choice);

int main(){
    int choice, value;
    struct Node *root = NULL;

    int init_tree[12] = {5, 4, 2, 5, 4, 8, 9, 10, 7, 6, 1, 2};
    for(int i=0; i<12; i++){
        root = insert_node(root, createNode(root, init_tree[i]));
    }

    for(;;){
        menu(&choice);
        if(choice == 1){
            print_tree(root); puts("");
            printf("Insert Value: "); scanf("%d", &value); getchar();
            root = insert_node(root, createNode(root, value));
        }
        else if(choice == 2){
            print_tree(root); puts("");
            printf("Delete Value: "); scanf("%d", &value); getchar();
            root = delete_node(root, value);
        }
        else if(choice == 3){
            root = delete_all_node(root);
        }
        else if(choice == 4){
            print_tree(root);
            printf("Click Enter to Continue.."); getchar();
        }
        else if(choice == 5){
            puts("Program Terminated!");
            return 0;
        }
    }
}

void menu(int *choice){
    system("CLS || clear");
    puts("1. Insert Node");
    puts("2. Delete Node");
    puts("3. Delete All Nodes");
    puts("4. Print Tree");
    puts("5. Exit Program");
    do{
        printf(">> "); scanf("%d", choice); getchar();
    }while((*choice) < 1 || (*choice) > 5);
}

void print_tree(struct Node *root){
    printf("Pre-Order: "); preorder_print(root); puts("");
    printf("In-Order: "); inorder_print(root); puts("");
    printf("Post-Order: "); postorder_print(root); puts("");
}
