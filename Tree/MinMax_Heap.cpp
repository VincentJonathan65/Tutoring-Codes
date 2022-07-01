#include<stdio.h>
#include<math.h>

//Start dari index 0

int getDepth(int index){
    return ceil(log(index)/log(2));
}

int getLeftChildIndex(int parentIndex, int n){
    if((parentIndex * 2) - 1 > n || parentIndex < 2){
        return -1;
    }
    return (parentIndex * 2) - 1;
}

int getRightChildIndex(int parentIndex, int n){
    if((parentIndex * 2) > n || parentIndex < 2){
        return -1;
    }
    return (parentIndex * 2);
}

int getParentIndex(int childIndex){
    if(childIndex == 2){
        return 0;
    }
    return ceil((float) childIndex/2);
}

void swapValue(int *value1, int *value2){
    int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

void print(int arr[], int n){
    for(int i=0; i<n; i++){
        printf("[%d] - %d\n", i, arr[i]);
    }
}

void insertHeap(int arr[], int heapArr[], int n){
    for(int i=0; i<n; i++){
        heapArr[i+2] = arr[i];
        int currentIndex = i+2;
        int parentIndex = getParentIndex(currentIndex);
        int grandIndex = getParentIndex(parentIndex);

        if(getDepth(currentIndex) % 2 == 1){ //min
            while(grandIndex != 0){
                if(heapArr[grandIndex] > heapArr[currentIndex]){
                    swapValue(&heapArr[grandIndex], &heapArr[currentIndex]);
                }
                else{
                    break;
                }
                currentIndex = grandIndex;
                parentIndex = getParentIndex(currentIndex);
                grandIndex = getParentIndex(parentIndex);
            }
            if(parentIndex != 0){ //parent pasti max heapx
                if(heapArr[parentIndex] < heapArr[currentIndex]){
                    swapValue(&heapArr[parentIndex], &heapArr[currentIndex]);
                }
            }
        }
        else if(getDepth(currentIndex) % 2 == 0){ //max
            while(grandIndex != 0){
                if(heapArr[grandIndex] < heapArr[currentIndex]){
                    swapValue(&heapArr[grandIndex], &heapArr[currentIndex]);
                }
                else{
                    break;
                }
                currentIndex = grandIndex;
                parentIndex = getParentIndex(currentIndex);
                grandIndex = getParentIndex(parentIndex);
            }
            if(parentIndex != 0){ //parent pasti min heap
                if(heapArr[parentIndex] > heapArr[currentIndex]){
                    swapValue(&heapArr[parentIndex], &heapArr[currentIndex]);
                }
            }
        }
    }
}


int getMinimumIndex(int arr[], int n, int heapArr[]){
    int minimumIndex;
    if(arr[0] == -1){
        return -1;
    }
    else{
        minimumIndex = arr[0];
    }

    int i=1;
    while(arr[i] != -1 && i<n){
        if(heapArr[arr[i]] < heapArr[minimumIndex]){
            minimumIndex = arr[i];
        }
        i++;
    }
    return minimumIndex;
}


int getMaximumIndex(int arr[], int n, int heapArr[]){
    int maximumIndex;
    if(arr[0] <= -1){
        return -1;
    }
    else{
        maximumIndex = arr[0];
    }

    int i=1;
    while(arr[i] > -1 && i<n){
        if(heapArr[arr[i]] > heapArr[maximumIndex]){
            maximumIndex = arr[i];
        }
        i++;
    }
    return maximumIndex;
}

void extractMinHeap(int arr[], int heapArr[], int n, int originalArrayLastSlot){
    arr[originalArrayLastSlot] = heapArr[2];
    int heapLastIndex = (n-1) - originalArrayLastSlot;
    heapArr[2] = heapArr[heapLastIndex];
    heapLastIndex--;

    int currentIndex = 2;
    //anak
    int leftChildIndex = getLeftChildIndex(currentIndex, heapLastIndex);
    int rightChildIndex = getRightChildIndex(currentIndex, heapLastIndex);

    //cucu
    int leftLeftIndex = getLeftChildIndex(leftChildIndex, heapLastIndex);
    int leftRightIndex = getRightChildIndex(leftChildIndex, heapLastIndex);
    int rightLeftIndex = getLeftChildIndex(rightChildIndex, heapLastIndex);
    int rightRightIndex = getRightChildIndex(rightChildIndex, heapLastIndex);

    int arrGrand[4] = {leftLeftIndex, leftRightIndex, rightLeftIndex, rightRightIndex};
    int minimumIndex = getMinimumIndex(arrGrand, 4, heapArr);

    while(minimumIndex != -1){
        if(heapArr[currentIndex] > heapArr[minimumIndex]){
            swapValue(&heapArr[currentIndex], &heapArr[minimumIndex]);
        }
        else{
            break;
        }

        currentIndex = minimumIndex;

        leftChildIndex = getLeftChildIndex(currentIndex, heapLastIndex);
        rightChildIndex = getRightChildIndex(currentIndex, heapLastIndex);

        leftLeftIndex = getLeftChildIndex(leftChildIndex, heapLastIndex);
        leftRightIndex = getRightChildIndex(leftChildIndex, heapLastIndex);
        rightLeftIndex = getLeftChildIndex(rightChildIndex, heapLastIndex);
        rightRightIndex = getRightChildIndex(rightChildIndex, heapLastIndex);

        arrGrand[0] = leftLeftIndex;
        arrGrand[1] = leftRightIndex;
        arrGrand[2] = rightLeftIndex;
        arrGrand[3] = rightRightIndex;
        minimumIndex = getMinimumIndex(arrGrand, 4, heapArr);
    }

    //cek anak
    leftChildIndex = getLeftChildIndex(currentIndex, heapLastIndex);
    rightChildIndex = getRightChildIndex(currentIndex, heapLastIndex);

    int arr2[2] = {leftChildIndex, rightChildIndex};
    minimumIndex = getMinimumIndex(arr2, 2, heapArr);

    if(minimumIndex != -1){
        if(heapArr[currentIndex] > heapArr[minimumIndex]){
            swapValue(&heapArr[currentIndex], &heapArr[minimumIndex]);
        }
    }

    int parentIndex = getParentIndex(currentIndex);

    if(parentIndex != 0){
        if(heapArr[parentIndex] < heapArr[currentIndex]){
            swapValue(&heapArr[parentIndex], &heapArr[currentIndex]);
        }
    }
}

void extractMaxHeap(int arr[], int heapArr[], int n, int originalArrayLastSlot){
    int heapLastIndex = (n-1) - originalArrayLastSlot;
    int currentIndex;

    if(heapLastIndex == 2){
        arr[originalArrayLastSlot] = heapArr[2];
        currentIndex = 2;
    }
    else if(heapLastIndex == 3 || heapArr[3] > heapArr[4]){
        arr[originalArrayLastSlot] = heapArr[3];
        currentIndex = 3;
        heapArr[3] = heapArr[heapLastIndex];
    }
    else{
        arr[originalArrayLastSlot] = heapArr[4];
        currentIndex = 4;
        heapArr[4] = heapArr[heapLastIndex];
    }

    heapLastIndex--;

    //anak
    int leftChildIndex = getLeftChildIndex(currentIndex, heapLastIndex);
    int rightChildIndex = getRightChildIndex(currentIndex, heapLastIndex);

    //cucu
    int leftLeftIndex = getLeftChildIndex(leftChildIndex, heapLastIndex);
    int leftRightIndex = getRightChildIndex(leftChildIndex, heapLastIndex);
    int rightLeftIndex = getLeftChildIndex(rightChildIndex, heapLastIndex);
    int rightRightIndex = getRightChildIndex(rightChildIndex, heapLastIndex);

    int arrGrand[4] = {leftLeftIndex, leftRightIndex, rightLeftIndex, rightRightIndex};
    int maximumIndex = getMaximumIndex(arrGrand, 4, heapArr);

    while(maximumIndex != -1){
        if(heapArr[currentIndex] < heapArr[maximumIndex]){
            swapValue(&heapArr[currentIndex], &heapArr[maximumIndex]);
            
        }
        else{
            break;
        }

        currentIndex = maximumIndex;

        leftChildIndex = getLeftChildIndex(currentIndex, heapLastIndex);
        rightChildIndex = getRightChildIndex(currentIndex, heapLastIndex);

        leftLeftIndex = getLeftChildIndex(leftChildIndex, heapLastIndex);
        leftRightIndex = getRightChildIndex(leftChildIndex, heapLastIndex);
        rightLeftIndex = getLeftChildIndex(rightChildIndex, heapLastIndex);
        rightRightIndex = getRightChildIndex(rightChildIndex, heapLastIndex);

        arrGrand[0] = leftLeftIndex;
        arrGrand[1] = leftRightIndex;
        arrGrand[2] = rightLeftIndex;
        arrGrand[3] = rightRightIndex;
        maximumIndex = getMaximumIndex(arrGrand, 4, heapArr);
    }

    //cek anak
    leftChildIndex = getLeftChildIndex(currentIndex, heapLastIndex);
    rightChildIndex = getRightChildIndex(currentIndex, heapLastIndex);

    int arr2[2] = {leftChildIndex, rightChildIndex};
    maximumIndex = getMaximumIndex(arr2, 2, heapArr);

    if(maximumIndex != -1){
        if(heapArr[currentIndex] < heapArr[maximumIndex]){
            swapValue(&heapArr[currentIndex], &heapArr[maximumIndex]);
        }
    }

    int parentIndex = getParentIndex(currentIndex);

    if(parentIndex != 0){
        if(heapArr[parentIndex] > heapArr[currentIndex]){
            swapValue(&heapArr[parentIndex], &heapArr[currentIndex]);
        }
    }
}

void menu(int *choice){
    puts("1. Extract Min");
    puts("2. Extract Max");
    printf(">> "); scanf("%d", choice); getchar();
}

int main(){
    puts("START");
    int choice;
    int n = 12;
    // int arr[n] = {42, 32, 88, 46, 28, 53, 76, 71, 72, 95, 67, 98, 83, 86, 76, 95, 18, 44, 3, 87, 99, 82, 9, 70, 4, 98, 16, 29, 82, 57, 72, 7, 59, 54, 50, 84, 76, 91, 41, 100, 26, 54, 74, 96, 69, 84, 72, 3, 93, 14, 71, 42, 29, 83, 20, 45, 27, 28, 36, 76, 38, 58, 49, 59, 88, 33, 5, 10, 67, 64, 18, 30, 91, 53, 15, 53, 34, 17, 46, 48, 82, 37, 12, 60, 54, 50, 47, 53, 87, 31, 63, 32, 46, 24, 28, 37, 2, 20, 89, 42};
    int arr[n] = {1, 11, 12, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int heapArr[n+2];
    insertHeap(arr, heapArr, n);
    int originalArrayLastSlot = 0;

    for(int i=0; i<n; i++){
        print(arr, originalArrayLastSlot);
        menu(&choice);
        if(choice == 1){
            extractMinHeap(arr, heapArr, n+2, originalArrayLastSlot);
        }
        else if(choice == 2){
            extractMaxHeap(arr, heapArr, n+2, originalArrayLastSlot);
        }
        else{
            i--;
            continue;
        }
        originalArrayLastSlot++;
    }
    print(arr, originalArrayLastSlot);
    return 0;
}

/*
Insert:
1. Cek Kakek
2. Cek Parent
3. Ulangi nomor 1 hingga nomor 1 dan 2 benar

Delete:
1. Cek Cucu
2. Cek Anak (kalo ga ada anak, cek parent)
3. Ulangi nomor 1 hingga nomor 1 dan 2 benar
*/