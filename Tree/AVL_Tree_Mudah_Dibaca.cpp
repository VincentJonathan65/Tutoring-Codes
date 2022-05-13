#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *left, *right;
    int height;
};

int getBalanceFactor(struct Node *root){
    int bf;
    if(root->left == NULL && root->right == NULL){
        bf = 1;
    }
    else if(root->left != NULL && root->right != NULL){
        bf = root->right->height - root->left->height;
    }
    else if(root->left != NULL && root->right == NULL){
        // bf = 0 - root->left->height;
        bf = -root->left->height;
    }
    else if(root->left == NULL && root->right != NULL){
        // bf = root->right->height - 0;
        bf = root->right->height;
    }
    return bf;
}

int getHeight(struct Node *root){
    int height;
    if(root->left == NULL && root->right == NULL){
        height = 1;
    }
    else if(root->left != NULL && root->right != NULL){
        if(root->left->height > root->right->height){
            height = root->left->height + 1;
        }
        else{
            height = root->right->height + 1;
        }
    }
    else if(root->left == NULL && root->right != NULL){
        height = root->right->height + 1;
    }
    else if(root->left != NULL && root->right == NULL){
        height = root->left->height + 1;
    }
    return height;
}

struct Node *left_rotate(struct Node *root){
    struct Node *pivot = root->right;
    root->right = pivot->left;
    pivot->left = root;
    root->height = getHeight(root);
    pivot->height = getHeight(root);
    return pivot;
}

struct Node *right_rotate(struct Node *root){
    struct Node *pivot = root->left;
    root->left = pivot->right;
    pivot->right = root;
    root->height = getHeight(root);
    pivot->height = getHeight(root);
    return pivot;
}

struct Node *balancing(struct Node *root){
    int balanceFactor = getBalanceFactor(root);
    if(balanceFactor <= 1 && balanceFactor >= -1){ //seimbang
        root->height = getHeight(root);
        return root;
    }
    else if(balanceFactor < -1){ //berat sebelah di kiri
        int childBalanceFactor = getBalanceFactor(root->left);
        if(childBalanceFactor >= 0){ //lebih berat di kanan - double rotate (zig zag)
            root->left = left_rotate(root->left);
            root = right_rotate(root);
        }
        else if(childBalanceFactor < 0){ //lebih berat di kiri - single rotate
            root = right_rotate(root);
        }
    }
    else if(balanceFactor > 1){ //berat sebelah di kanan
        int childBalanceFactor = getBalanceFactor(root->right);
        if(childBalanceFactor >= 0){ //berat dikanan - single rotate
            root = left_rotate(root);
        }
        else if(childBalanceFactor < 0){ //berat di kiri (zig-zag) - double rotate
            root->right = right_rotate(root->right);
            root = left_rotate(root);
        }
    }
    root->height = getHeight(root);
    return root;
}



///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node *createNode(struct Node *root, int value){
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->left = new_node->right = NULL;
    new_node->height = 1;
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
    return balancing(root);
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
        else if(root->value > target){
            root->left = delete_node(root->left, target);
        }
        else if(target == root->value){ //target found
            if(root->left == NULL && root->right == NULL){
                free(root);
                root = NULL;
                // return root; //problem 1 dari bst -> avl
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
    if(root == NULL){
        return root;
    }
    else{
        return balancing(root);
    }
    // return balancing(root);
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

int main(){
    int choice, value;
    struct Node *root = NULL;

    int init_tree[6] = {5, 10, 15, 20, 25, 30};
    for(int i=0; i<6; i++){
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

/*Test Sample:
- Insert: 5, 10, 15, 20, 25, 30
- Delete: 20, 5
- Insert: 20, 17
- Delete: 30
- Insert: 18
- Delete: 18, 20
- Insert: 5
- Delete: All
*/