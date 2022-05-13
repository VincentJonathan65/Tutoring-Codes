#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *left, *right;
    int height; 
};

struct Node *createNode(struct Node *root, int value){
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

int find_bf(struct Node *root){
    if(root->left == NULL && root->right == NULL){
        return 0;
    }
    else if(root->left == NULL || root->right == NULL){
        return root->left != NULL? -root->left->height : root->right->height;
    }
    else{
        return root->right->height - root->left->height;
    }
}

int get_height(struct Node *root){
    if(root->left == NULL && root->right == NULL){
        return 1; //height of leaf node is 1
    }
    else if(root->left == NULL || root->right == NULL){
        return (root->left != NULL? root->left->height : root->right->height) + 1;
    } 
    else{
        return (root->left->height >= root->right->height? root->left->height : root->right->height) + 1;
    }
}

struct Node *left_rotate(struct Node *pivot){
    struct Node *new_pivot = pivot->right;
    pivot->right = new_pivot->left;
    new_pivot->left = pivot;
    pivot->height = get_height(pivot);
    new_pivot->height = get_height(new_pivot);
    return new_pivot;
}

struct Node *right_rotate(struct Node *pivot){
    struct Node *new_pivot = pivot->left;
    pivot->left = new_pivot->right;
    new_pivot->right = pivot;
    pivot->height = get_height(pivot);
    new_pivot->height = get_height(new_pivot);
    return new_pivot;
}

struct Node *AVL_balance(struct Node *root){
    int balance_factor = find_bf(root);
    if(balance_factor > 1){ //right child too weight
        balance_factor = find_bf(root->right);
        if(balance_factor < 0){ //zig-zag case
            root->right = right_rotate(root->right);
        }
        return left_rotate(root);
    }
    else if(balance_factor < -1){ //left child too weight
        balance_factor = find_bf(root->left);
        if(balance_factor > 0){ //zig-zag case
            root->left = left_rotate(root->left);
        }
        return right_rotate(root);
    }
    else{ //balance
        root->height = get_height(root);
        return root;
    }
}

struct Node *insert_node(struct Node *root, struct Node *new_node){
    if(root == NULL){
        new_node->height = 0;
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
    return AVL_balance(root);
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
                return root;
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
        return AVL_balance(root); //for internal nodes
    }
    return root; //for empty tree
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

    // int init_tree[12] = {5, 4, 2, 5, 4, 8, 9, 10, 7, 6, 1, 2};
    // for(int i=0; i<12; i++){
    //     root = insert_node(root, createNode(root, init_tree[i]));
    // }

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