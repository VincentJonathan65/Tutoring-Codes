#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *left, *right;
    int height;
};

struct NodeLuar{
    int valueLuar;
    struct NodeLuar *left, *right;
    int height;
    struct Node *rootDalam;
};

///////////////////////////////////////////////////// Balancing Tree Dalam ///////////////////////////////////////////////////

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

///////////////////////////////////////////////////// Manipulasi Tree Dalam ///////////////////////////////////////////////////

struct Node *createNode(int value){
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

void print_tree(struct Node *root){
    printf("Pre-Order: "); preorder_print(root); puts("");
    printf("In-Order: "); inorder_print(root); puts("");
    printf("Post-Order: "); postorder_print(root); puts("");
}

///////////////////////////////////////////////////// Balancing Tree Luar ///////////////////////////////////////////////////

int getBalanceFactorLuar(struct NodeLuar *root){
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

int getHeightLuar(struct NodeLuar *root){
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

struct NodeLuar *left_rotateLuar(struct NodeLuar *root){
    struct NodeLuar *pivot = root->right;
    root->right = pivot->left;
    pivot->left = root;
    root->height = getHeightLuar(root);
    pivot->height = getHeightLuar(root);
    return pivot;
}

struct NodeLuar *right_rotateLuar(struct NodeLuar *root){
    struct NodeLuar *pivot = root->left;
    root->left = pivot->right;
    pivot->right = root;
    root->height = getHeightLuar(root);
    pivot->height = getHeightLuar(root);
    return pivot;
}

struct NodeLuar *balancingLuar(struct NodeLuar *root){
    int balanceFactor = getBalanceFactorLuar(root);
    if(balanceFactor <= 1 && balanceFactor >= -1){ //seimbang
        root->height = getHeightLuar(root);
        return root;
    }
    else if(balanceFactor < -1){ //berat sebelah di kiri
        int childBalanceFactor = getBalanceFactorLuar(root->left);
        if(childBalanceFactor >= 0){ //lebih berat di kanan - double rotate (zig zag)
            root->left = left_rotateLuar(root->left);
            root = right_rotateLuar(root);
        }
        else if(childBalanceFactor < 0){ //lebih berat di kiri - single rotate
            root = right_rotateLuar(root);
        }
    }
    else if(balanceFactor > 1){ //berat sebelah di kanan
        int childBalanceFactor = getBalanceFactorLuar(root->right);
        if(childBalanceFactor >= 0){ //berat dikanan - single rotate
            root = left_rotateLuar(root);
        }
        else if(childBalanceFactor < 0){ //berat di kiri (zig-zag) - double rotate
            root->right = right_rotateLuar(root->right);
            root = left_rotateLuar(root);
        }
    }
    root->height = getHeightLuar(root);
    return root;
}

///////////////////////////////////////////////////// Manipulasi Tree Luar ///////////////////////////////////////////////////

/*PR
balancing di insert dan delete
*/

struct NodeLuar *createNodeLuar(int valueLuar, int valueDalam){
    struct NodeLuar *new_node = (struct NodeLuar *) malloc(sizeof(struct NodeLuar));
    new_node->valueLuar = valueLuar;
    new_node->left = new_node->right = NULL;
    new_node->height = 1;
    new_node->rootDalam = createNode(valueDalam);
    return new_node;
}

struct NodeLuar *insert_nodeLuar(struct NodeLuar *root, struct NodeLuar *new_node){
    if(root == NULL){
        root = new_node;
    }
    else{
        if(root->valueLuar < new_node->valueLuar){ //right child
            root->right = insert_nodeLuar(root->right, new_node);
        }
        else if(new_node->valueLuar <= root->valueLuar){ //left child (tree left descendants will more often inserted than right descendants)
            root->left = insert_nodeLuar(root->left, new_node);
        }
    }
    return balancingLuar(root);
}

struct NodeLuar *find_predecessorLuar(struct NodeLuar *root){
    struct NodeLuar *predecessor = (root)->left;
    while(predecessor->right != NULL){
        predecessor = predecessor->right;
    }
    return predecessor;
}

struct NodeLuar *find_successorLuar(struct NodeLuar *root){
    struct NodeLuar *successor = (root)->right;
    while(successor->left != NULL){
        successor = successor->left;
    }
    return successor;
}

struct NodeLuar *delete_nodeLuar(struct NodeLuar *root, int target){
    if(root != NULL){
        if(root->valueLuar < target){
            root->right = delete_nodeLuar(root->right, target);
        }
        else if(root->valueLuar > target){
            root->left = delete_nodeLuar(root->left, target);
        }
        else if(target == root->valueLuar){ //target found
            if(root->left == NULL && root->right == NULL){
                delete_all_node(root->rootDalam);
                free(root);
                root = NULL;
                // return root; //problem 1 dari bst -> avl
            }
            else if(root->left != NULL){ //tree left descendants will more often deleted than right descendants
                struct NodeLuar *predecessor = find_predecessorLuar(root);
                root->valueLuar = predecessor->valueLuar;
                root->rootDalam = predecessor->rootDalam;
                predecessor->rootDalam = NULL;
                root->left = delete_nodeLuar(root->left, predecessor->valueLuar);
            }
            else if(root->right != NULL){
                struct NodeLuar *successor = find_successorLuar(root);
                root->valueLuar = successor->valueLuar;
                root->rootDalam = successor->rootDalam;
                successor->rootDalam = NULL;
                root->right = delete_nodeLuar(root->right, successor->valueLuar);
            }
        }
    }
    if(root == NULL){
        return root;
    }
    else{
        return balancingLuar(root);
    }
}

void preorder_printLuar(struct NodeLuar *root){
    if(root != NULL){
        printf("%d\n", root->valueLuar);
        preorder_print(root->rootDalam);
        preorder_printLuar(root->left);
        preorder_printLuar(root->right);
    }
}

void inorder_printLuar(struct NodeLuar *root){
    if(root != NULL){
        inorder_printLuar(root->left);
        printf("%d\n", root->valueLuar);
        inorder_print(root->rootDalam);
        inorder_printLuar(root->right);
    }
}

void postorder_printLuar(struct NodeLuar *root){
    if(root != NULL){
        postorder_printLuar(root->left);
        postorder_printLuar(root->right);
        printf("%d\n", root->valueLuar);
        postorder_print(root->rootDalam);
    }
}

struct NodeLuar *delete_all_nodeLuar(struct NodeLuar *root){
    while(root != NULL){
        root = delete_nodeLuar(root, root->valueLuar);
    }
    return root;
}

void print_treeLuar(struct NodeLuar *root){
    printf("Pre-Order:\n"); preorder_printLuar(root); puts("");
    printf("In-Order:\n"); inorder_printLuar(root); puts("");
    printf("Post-Order:\n"); postorder_printLuar(root); puts("");
}

struct NodeLuar *search_nodeLuar(struct NodeLuar *root, int target){
    if(root == NULL){
        return NULL;
    }
    else{
        if(root->valueLuar > target){
            return search_nodeLuar(root->left, target);
        }
        else if(root->valueLuar < target){
            return search_nodeLuar(root->right, target);
        }
        else{
            return root;
        }
    }
}

///////////////////////////////////////////////////// Lainnya ///////////////////////////////////////////////////

void menu(int *choice){
    system("CLS || clear");
    puts("1. Insert Node Dalam");
    puts("2. Delete Node Dalam");
    puts("3. Delete All Nodes");
    puts("4. Print Tree");
    puts("5. Exit Program");
    do{
        printf(">> "); scanf("%d", choice); getchar();
    }while((*choice) < 1 || (*choice) > 5);
}

int main(){
    int choice, valueLuar, valueDalam;
    struct NodeLuar *rootLuar = NULL;

    // int init_tree[6] = {5, 10, 15, 20, 25, 30};
    // for(int i=0; i<6; i++){
    //     root = insert_node(root, createNode(root, init_tree[i]));
    // }

    for(;;){
        menu(&choice);
        if(choice == 1){
            print_treeLuar(rootLuar); puts("");
            printf("Insert Value Luar: "); scanf("%d", &valueLuar); getchar();
            printf("Insert Value Dalam: "); scanf("%d", &valueDalam); getchar();
            struct NodeLuar *nodeLuar = search_nodeLuar(rootLuar, valueLuar);
            if(nodeLuar == NULL){
                nodeLuar = createNodeLuar(valueLuar, valueDalam);
                rootLuar = insert_nodeLuar(rootLuar, nodeLuar);
            }
            else{
                struct Node *new_nodeDalam = createNode(valueDalam);
                nodeLuar->rootDalam = insert_node(nodeLuar->rootDalam, new_nodeDalam);
            }
        }
        else if(choice == 2){
            print_treeLuar(rootLuar); puts("");
            printf("Value Luar: "); scanf("%d", &valueLuar); getchar();
            printf("Delete Value Dalam: "); scanf("%d", &valueDalam); getchar();
            struct NodeLuar *nodeLuar = search_nodeLuar(rootLuar, valueLuar);
            rootLuar->rootDalam = delete_node(rootLuar->rootDalam, valueDalam);
        }
        else if(choice == 3){
            rootLuar = delete_all_nodeLuar(rootLuar);
        }
        else if(choice == 4){
            print_treeLuar(rootLuar);
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