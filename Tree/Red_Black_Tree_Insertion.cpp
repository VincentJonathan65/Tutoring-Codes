#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *left, *right, *parent;
    char color; //R red, B black, D Double black
};

struct Node *createNode(struct Node *root, int value){
    struct Node *new_node = (struct Node *) malloc(sizeof(struct Node));
    new_node->value = value;
    new_node->left = new_node->right = NULL;
    new_node->parent = NULL;
    new_node->color = 'R';
    return new_node;
}

char getColor(struct Node *root){
    if(root == NULL){
        return 'B';
    }
    else{
        return root->color;
    }
}

struct Node *rightRotate(struct Node *root){
    struct Node *pivot = root->left;
    root->left = pivot->right;
    pivot->right = root;
    pivot->parent = root->parent;
    root->parent = pivot;
    return pivot;
}

struct Node *leftRotate(struct Node *root){
    struct Node *pivot = root->right;
    root->right = pivot->left;
    pivot->left = root;
    pivot->parent = root->parent;
    root->parent = pivot;
    return pivot;
}

void swapColor(char *color1, char *color2){
    char temp = *color1;
    *color1 = *color2;
    *color2 = temp;
}

struct Node *balancingInsert(struct Node *root){
    if(root != NULL){
        if(root->left != NULL){
            if(root->left->left != NULL){// left-left
                if(getColor(root->left) == 'R' && getColor(root->left->left) == 'R'){
                    if(getColor(root->left) == 'R' && getColor(root->right) == 'R'){
                        root->left->color = 'B';
                        root->right->color = 'B';
                        root->color = 'R';
                    }
                    else{
                        swapColor(&(root->color), &(root->left->color));
                        root = rightRotate(root);
                    }
                }
            }
            if(root->left->right != NULL){// left-right
                if(getColor(root->left) == 'R' && getColor(root->left->right) == 'R'){
                    if(getColor(root->left) == 'R' && getColor(root->right) == 'R'){
                        root->left->color = 'B';
                        root->right->color = 'B';
                        root->color = 'R';
                    }
                    else{
                        root->left = leftRotate(root->left);
                        swapColor(&(root->color), &(root->left->color));
                        root = rightRotate(root);
                    }
                }
            }
        }
        if(root->right != NULL){
            if(root->right->left != NULL){// right-left
                if(getColor(root->right) == 'R' && getColor(root->right->left) == 'R'){
                    if(getColor(root->left) == 'R' && getColor(root->right) == 'R'){
                        root->left->color = 'B';
                        root->right->color = 'B';
                        root->color = 'R';
                    }
                    else{
                        root->right = rightRotate(root->right);
                        swapColor(&(root->color), &(root->right->color));
                        root = leftRotate(root);
                    }
                }
            }
            if(root->right->right != NULL){// right-right
                if(getColor(root->right) == 'R' && getColor(root->right->right) == 'R'){
                    if(getColor(root->left) == 'R' && getColor(root->right) == 'R'){
                        root->left->color = 'B';
                        root->right->color = 'B';
                        root->color = 'R';
                    }
                    else{
                        swapColor(&(root->color), &(root->right->color));
                        puts("before rotate");
                        root = leftRotate(root);
                        puts("after rotate");
                    }
                }
            }
        }
    }
    return root;
}

struct Node *insert_node(struct Node *root, struct Node *new_node, struct Node *parent){
    if(root == NULL){
        root = new_node;
        new_node->parent = parent;
        return root;
    }
    else{
        if(root->value < new_node->value){ //right child
            root->right = insert_node(root->right, new_node, root);
        }
        else if(new_node->value <= root->value){ //left child (tree left descendants will more often inserted than right descendants)
            root->left = insert_node(root->left, new_node, root);
        }
    }
    return balancingInsert(root);
}

void preorder_print(struct Node *root){
    if(root != NULL){
        printf("%d - %c\n", root->value, root->color);
        preorder_print(root->left);
        preorder_print(root->right);
    }
}

void print_tree(struct Node *root){
    printf("Pre-Order: \n");
    preorder_print(root);
    puts("");
}

int main(){
    int choice, value;
    struct Node *root = NULL;

    for(;;){
        print_tree(root);
        printf("Insert: "); scanf("%d", &value); getchar();
        struct Node *newNode = createNode(root, value);
        root = insert_node(root, newNode, root);
        root->color = 'B';
    }
}