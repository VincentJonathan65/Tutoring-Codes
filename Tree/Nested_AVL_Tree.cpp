#include<stdio.h>
#include<stdlib.h>

struct Node{
    int value;
    struct Node *left, *right;
    int height;
};

struct NodeLuar{
    int valueLuar;
    struct NodeLuar *leftLuar, *rightLuar;
    int heightLuar;
    
    struct Node *rootDalam;
};

/////////////////////////////////////////////// BALANCING AVL DALAM //////////////////////////////////////////

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

////////////////////////////////////////////////////// MANIPULASI TREE DALAM ///////////////////////////////////////////////////

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
        else if(new_node->value < root->value){ //left child (tree left descendants will more often inserted than right descendants)
            root->left = insert_node(root->left, new_node);
        }
        else{
            printf("Value diinsert sudah ada!"); getchar();
            return root;
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

struct Node *search_nodeDalam(struct Node *rootDalam, int targetDalam){
    if(rootDalam == NULL){
        return NULL;
    }
    else{
        if(rootDalam->value < targetDalam){ //ke kanan
            return search_nodeDalam(rootDalam->right, targetDalam);
        }
        else if(rootDalam->value > targetDalam){ //ke kiri
            return search_nodeDalam(rootDalam->left, targetDalam);
        }
        else if(rootDalam->value == targetDalam){
            return rootDalam;
        }
    }
}

/////////////////////////////////////////////// BALANCING AVL LUAR //////////////////////////////////////////

int getBalanceFactorLuar(struct NodeLuar *rootLuar){
    int bf;
    if(rootLuar->leftLuar == NULL && rootLuar->rightLuar == NULL){
        bf = 1;
    }
    else if(rootLuar->leftLuar != NULL && rootLuar->rightLuar != NULL){
        bf = rootLuar->rightLuar->heightLuar - rootLuar->leftLuar->heightLuar;
    }
    else if(rootLuar->leftLuar != NULL && rootLuar->rightLuar == NULL){
        // bf = 0 - root->left->height;
        bf = -rootLuar->leftLuar->heightLuar;
    }
    else if(rootLuar->leftLuar == NULL && rootLuar->rightLuar != NULL){
        // bf = root->right->height - 0;
        bf = rootLuar->rightLuar->heightLuar;
    }
    return bf;
}

int getHeightLuar(struct NodeLuar *rootLuar){
    int heightLuar;
    if(rootLuar->leftLuar == NULL && rootLuar->rightLuar == NULL){
        heightLuar = 1;
    }
    else if(rootLuar->leftLuar != NULL && rootLuar->rightLuar != NULL){
        if(rootLuar->leftLuar->heightLuar > rootLuar->rightLuar->heightLuar){
            heightLuar = rootLuar->leftLuar->heightLuar + 1;
        }
        else{
            heightLuar = rootLuar->rightLuar->heightLuar + 1;
        }
    }
    else if(rootLuar->leftLuar == NULL && rootLuar->rightLuar != NULL){
        heightLuar = rootLuar->rightLuar->heightLuar + 1;
    }
    else if(rootLuar->leftLuar != NULL && rootLuar->rightLuar == NULL){
        heightLuar = rootLuar->leftLuar->heightLuar + 1;
    }
    return heightLuar;
}

struct NodeLuar *left_rotateLuar(struct NodeLuar *rootLuar){
    struct NodeLuar *pivot = rootLuar->rightLuar;
    rootLuar->rightLuar = pivot->leftLuar;
    pivot->leftLuar = rootLuar;
    rootLuar->heightLuar = getHeightLuar(rootLuar);
    pivot->heightLuar = getHeightLuar(rootLuar);
    return pivot;
}

struct NodeLuar *right_rotateLuar(struct NodeLuar *rootLuar){
    struct NodeLuar *pivot = rootLuar->leftLuar;
    rootLuar->leftLuar = pivot->rightLuar;
    pivot->rightLuar = rootLuar;
    rootLuar->heightLuar = getHeightLuar(rootLuar);
    pivot->heightLuar = getHeightLuar(rootLuar);
    return pivot;
}

struct NodeLuar *balancingLuar(struct NodeLuar *rootLuar){
    int balanceFactor = getBalanceFactorLuar(rootLuar);
    if(balanceFactor <= 1 && balanceFactor >= -1){ //seimbang
        rootLuar->heightLuar = getHeightLuar(rootLuar);
        return rootLuar;
    }
    else if(balanceFactor < -1){ //berat sebelah di kiri
        int childBalanceFactor = getBalanceFactorLuar(rootLuar->leftLuar);
        if(childBalanceFactor >= 0){ //lebih berat di kanan - double rotate (zig zag)
            rootLuar->leftLuar = left_rotateLuar(rootLuar->leftLuar);
            rootLuar = right_rotateLuar(rootLuar);
        }
        else if(childBalanceFactor < 0){ //lebih berat di kiri - single rotate
            rootLuar = right_rotateLuar(rootLuar);
        }
    }
    else if(balanceFactor > 1){ //berat sebelah di kanan
        int childBalanceFactor = getBalanceFactorLuar(rootLuar->rightLuar);
        if(childBalanceFactor >= 0){ //berat dikanan - single rotate
            rootLuar = left_rotateLuar(rootLuar);
        }
        else if(childBalanceFactor < 0){ //berat di kiri (zig-zag) - double rotate
            rootLuar->rightLuar = right_rotateLuar(rootLuar->rightLuar);
            rootLuar = left_rotateLuar(rootLuar);
        }
    }
    rootLuar->heightLuar = getHeightLuar(rootLuar);
    return rootLuar;
}

////////////////////////////////////////////////////// MANIPULASI TREE LUAR ///////////////////////////////////////////////////

struct NodeLuar *createNodeLuar(int valueLuar){
    struct NodeLuar *new_nodeLuar = (struct NodeLuar *) malloc(sizeof(struct NodeLuar));
    new_nodeLuar->valueLuar = valueLuar;
    new_nodeLuar->leftLuar = new_nodeLuar->rightLuar = NULL;
    new_nodeLuar->heightLuar = 1;
    new_nodeLuar->rootDalam = NULL;
    return new_nodeLuar;
}

struct NodeLuar *insert_nodeLuar(struct NodeLuar *rootLuar, struct NodeLuar *new_node){
    if(rootLuar == NULL){
        rootLuar = new_node;
    }
    else{
        if(rootLuar->valueLuar < new_node->valueLuar){ //right child
            rootLuar->rightLuar = insert_nodeLuar(rootLuar->rightLuar, new_node);
        }
        else if(new_node->valueLuar < rootLuar->valueLuar){ //left child (tree left descendants will more often inserted than right descendants)
            rootLuar->leftLuar = insert_nodeLuar(rootLuar->leftLuar, new_node);
        }
        else{
            return rootLuar;
        }
    }
    return balancingLuar(rootLuar);
}

struct NodeLuar *find_predecessorLuar(struct NodeLuar *rootLuar){
    struct NodeLuar *predecessor = (rootLuar)->leftLuar;
    while(predecessor->rightLuar != NULL){
        predecessor = predecessor->rightLuar;
    }
    return predecessor;
}

struct NodeLuar *find_successorLuar(struct NodeLuar *rootLuar){
    struct NodeLuar *successor = (rootLuar)->rightLuar;
    while(successor->leftLuar != NULL){
        successor = successor->leftLuar;
    }
    return successor;
}

struct NodeLuar *delete_nodeLuar(struct NodeLuar *rootLuar, int target){
    if(rootLuar != NULL){
        if(rootLuar->valueLuar < target){
            rootLuar->rightLuar = delete_nodeLuar(rootLuar->rightLuar, target);
        }
        else if(rootLuar->valueLuar > target){
            rootLuar->leftLuar = delete_nodeLuar(rootLuar->leftLuar, target);
        }
        else if(target == rootLuar->valueLuar){ //target found
            if(rootLuar->leftLuar == NULL && rootLuar->rightLuar == NULL){
                rootLuar->rootDalam = delete_all_node(rootLuar->rootDalam);
                free(rootLuar);
                rootLuar = NULL;
            }
            else if(rootLuar->leftLuar != NULL){ //tree left descendants will more often deleted than right descendants
                rootLuar->rootDalam = delete_all_node(rootLuar->rootDalam);
                struct NodeLuar *predecessorLuar = find_predecessorLuar(rootLuar);
                rootLuar->valueLuar = predecessorLuar->valueLuar;
                rootLuar->rootDalam = predecessorLuar->rootDalam;
                predecessorLuar->rootDalam = NULL;
                rootLuar->leftLuar = delete_nodeLuar(rootLuar->leftLuar, predecessorLuar->valueLuar);
            }
            else if(rootLuar->rightLuar != NULL){
                rootLuar->rootDalam = delete_all_node(rootLuar->rootDalam);
                struct NodeLuar *successorLuar = find_successorLuar(rootLuar);
                rootLuar->valueLuar = successorLuar->valueLuar;
                rootLuar->rootDalam = successorLuar->rootDalam;
                successorLuar->rootDalam = NULL;
                rootLuar->rightLuar = delete_nodeLuar(rootLuar->rightLuar, successorLuar->valueLuar);
            }
        }
    }
    if(rootLuar == NULL){
        return rootLuar;
    }
    else{
        return balancingLuar(rootLuar);
    }
}

void preorder_printLuar(struct NodeLuar *rootLuar){
    if(rootLuar != NULL){
        printf("ID Luar: %d - %d\n", rootLuar->valueLuar, rootLuar->heightLuar);
        preorder_print(rootLuar->rootDalam); puts("");
        preorder_printLuar(rootLuar->leftLuar);
        preorder_printLuar(rootLuar->rightLuar);
    }
}

void inorder_printLuar(struct NodeLuar *rootLuar){
    if(rootLuar != NULL){
        inorder_printLuar(rootLuar->leftLuar);
        printf("ID Luar: %d\n", rootLuar->valueLuar);
        inorder_print(rootLuar->rootDalam); puts("");
        inorder_printLuar(rootLuar->rightLuar);
    }
}

void postorder_printLuar(struct NodeLuar *rootLuar){
    if(rootLuar != NULL){
        postorder_printLuar(rootLuar->leftLuar);
        postorder_printLuar(rootLuar->rightLuar);
        printf("ID Luar: %d\n", rootLuar->valueLuar);
        postorder_print(rootLuar->rootDalam); puts("");
    }
}

struct NodeLuar *delete_all_nodeLuar(struct NodeLuar *rootLuar){
    while(rootLuar != NULL){
        rootLuar = delete_nodeLuar(rootLuar, rootLuar->valueLuar);
    }
    return rootLuar;
}

void print_treeLuar(struct NodeLuar *rootLuar){
    printf("======= PRE-ORDER =========\n");
    preorder_printLuar(rootLuar);
    puts("");
    
    printf("======= IN-ORDER =========\n");
    inorder_printLuar(rootLuar);
    puts("");
    
    printf("======= POST-ORDER =========\n");
    postorder_printLuar(rootLuar);
    puts("");
}

struct NodeLuar *search_nodeLuar(struct NodeLuar *rootLuar, int targetLuar){
    if(rootLuar == NULL){
        return NULL;
    }
    else{
        if(rootLuar->valueLuar < targetLuar){ //ke kanan
            return search_nodeLuar(rootLuar->rightLuar, targetLuar);
        }
        else if(rootLuar->valueLuar > targetLuar){ //ke kiri
            return search_nodeLuar(rootLuar->leftLuar, targetLuar);
        }
        else if(rootLuar->valueLuar == targetLuar){
            return rootLuar;
        }
    }
}

/////////////////////////////////////////////// LAINNYA //////////////////////////////////////////

void menu(int *choice){
    system("CLS || clear");
    puts("1. Insert Node Luar");
    puts("2. Insert Node Dalam");
    puts("3. Delete Node Luar");
    puts("4. Delete Node Dalam");
    puts("5. Delete All Nodes Luar");
    puts("6. Delete All Nodes Dalam");
    puts("7. Print Tree Luar");
    puts("8. Update Node Luar");
    puts("9. Update Node Dalam");
    puts("10. Exit Program");
    do{
        printf(">> "); scanf("%d", choice); getchar();
    }while((*choice) < 1 || (*choice) > 10);
}

struct NodeLuar *func_insertNodeLuar(struct NodeLuar *rootLuar, int valueLuar){
    //search dulu ada atau ga
    struct NodeLuar *searchNode = search_nodeLuar(rootLuar, valueLuar);
    if(searchNode == NULL){
        struct NodeLuar *newNodeLuar = createNodeLuar(valueLuar);
        rootLuar = insert_nodeLuar(rootLuar, newNodeLuar);
    }
    else{
        printf("Value sudah ada");
        getchar();
    }
}

int main(){
    int choice, valueLuar, valueDalam;
    struct NodeLuar *rootLuar = NULL;

    while(1 == 1){
        menu(&choice);
        print_treeLuar(rootLuar); puts("");
        if(choice == 1){ //Insert Node Luar
            printf("Insert Value Luar: "); scanf("%d", &valueLuar); getchar();
            rootLuar = func_insertNodeLuar(rootLuar, valueLuar);
        }
        else if(choice == 2){ //Insert Node Dalam
            printf("ID Luar: "); scanf("%d", &valueLuar); getchar();
            struct NodeLuar *searchNode = search_nodeLuar(rootLuar, valueLuar);
            if(searchNode == NULL){
                rootLuar = func_insertNodeLuar(rootLuar, valueLuar);
                searchNode = search_nodeLuar(rootLuar, valueLuar);
            }
            printf("Insert Value Dalam: "); scanf("%d", &valueDalam); getchar();
            struct Node *newNodeDalam = createNode(valueDalam);
            searchNode->rootDalam = insert_node(searchNode->rootDalam, newNodeDalam);
        }
        else if(choice == 3){ //Delete Node Luar
            printf("Delete Value Luar: "); scanf("%d", &valueLuar); getchar();
            rootLuar = delete_nodeLuar(rootLuar, valueLuar);
        }
        else if(choice == 4){ //Delete Node Dalam
            printf("ID Luar: "); scanf("%d", &valueLuar); getchar();
            struct NodeLuar *searchNode = search_nodeLuar(rootLuar, valueLuar);
            if(searchNode != NULL){
                printf("Delete Value Dalam: "); scanf("%d", &valueDalam); getchar();
                searchNode->rootDalam = delete_node(searchNode->rootDalam, valueDalam);
                if(searchNode->rootDalam == NULL){
                    rootLuar = delete_nodeLuar(rootLuar, searchNode->valueLuar);
                }
            }
            else{
                printf("Node dicari tidak ada!");
                getchar();
            }
        }
        else if(choice == 5){ //Delete All Nodes Luar
            rootLuar = delete_all_nodeLuar(rootLuar);
        }
        else if(choice == 6){ //Delete All Nodes Dalam
            printf("ID Luar: "); scanf("%d", &valueLuar); getchar();
            struct NodeLuar *searchNode = search_nodeLuar(rootLuar, valueLuar);
            if(searchNode != NULL){
                searchNode->rootDalam = delete_all_node(searchNode->rootDalam);
            }
            else{
                printf("Node dicari tidak ada!");
                getchar();
            }
        }
        else if(choice == 7){ //Print Node Luar
            print_treeLuar(rootLuar);
            printf("Click Enter to Continue.."); getchar();
        }
        else if(choice == 8){ //Update Luar
            printf("ID Luar: "); scanf("%d", &valueLuar); getchar();
            struct NodeLuar *searchNode = search_nodeLuar(rootLuar, valueLuar);
            if(searchNode != NULL){
                int valueBaru;
                printf("ID Luar Baru: "); scanf("%d", &valueBaru); getchar();
                struct NodeLuar *newNodeLuar = createNodeLuar(valueBaru);
                newNodeLuar->rootDalam = searchNode->rootDalam;
                searchNode->rootDalam = NULL;

                rootLuar = delete_nodeLuar(rootLuar, searchNode->valueLuar);
                rootLuar = insert_nodeLuar(rootLuar, newNodeLuar);
            }
            else{
                printf("Node yang mau diupdate tidak ada!"); getchar();
            }
        }
        else if(choice == 9){ //Update Dalam
            printf("ID Luar: "); scanf("%d", &valueLuar); getchar();
            struct NodeLuar *searchNodeLuar = search_nodeLuar(rootLuar, valueLuar);
            if(searchNodeLuar != NULL){
                printf("ID Dalam: "); scanf("%d", &valueDalam); getchar();
                struct Node *searchNodeDalam = search_nodeDalam(searchNodeLuar->rootDalam, valueDalam);
                if(search_nodeDalam != NULL){
                    int valueBaru;
                    printf("ID Dalam Baru: "); scanf("%d", &valueBaru); getchar();
                    struct Node *newNodeDalam = createNode(valueBaru);
                    searchNodeLuar->rootDalam = delete_node(searchNodeLuar->rootDalam, searchNodeDalam->value);
                    searchNodeLuar->rootDalam = insert_node(searchNodeLuar->rootDalam, newNodeDalam);
                }
                else{
                    printf("Node yang mau diupdate tidak ada!"); getchar();
                }
            }
            else{
                printf("Node yang mau diupdate tidak ada!"); getchar();
            }
        }
        else if(choice == 10){ //Exit
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

/*Langkah bikin nestedTree:
1. Bikin template AVL utk Tree Dalam
2. Ganti Nama
3. Analisis
4. Ngehubungin antara Tree Luar ama Dalam
*/

/* Test Case:
1
1
1
2
1
3
1
4
1
5
1
6
2
5
5
2
5
10
2
5
15
2
5
20
2
5
25
2
5
30
2
6
11
2
6
12
2
6
13
2
6
14
2
6
15
*/