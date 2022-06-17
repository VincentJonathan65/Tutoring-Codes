#include<stdio.h>

//Start dari index 0

int getLeftChildIndex(int parentIndex){
    return (parentIndex * 2) + 1;
}

int getRightChildIndex(int parentIndex){
    return (parentIndex * 2) + 2;
}

int getParentIndex(int childIndex){
    if(childIndex == 0){
        return 0;
    }
    return (childIndex-1)/2;
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
        // print(heapArr, i);
        heapArr[i] = arr[i];
        int currentIndex = i;
        int parentIndex = getParentIndex(currentIndex);

        //kalo break rules, maka masuk ke while buat difix hingga ga break rules
        while(heapArr[parentIndex] > heapArr[currentIndex] && currentIndex != 0){
            swapValue(&heapArr[parentIndex], &heapArr[currentIndex]);
            currentIndex = parentIndex;
            parentIndex = getParentIndex(currentIndex);
        }
    }
}

void extractHeap(int arr[], int heapArr[], int n){
    for(int i=0; i<n; i++){
        arr[i] = heapArr[0];
        int heapLastIndex = (n-1) - i;
        heapArr[0] = heapArr[heapLastIndex];
        heapLastIndex--;

        int currentIndex = 0;
        int leftChildIndex = getLeftChildIndex(currentIndex);
        int rightChildIndex = getRightChildIndex(currentIndex);
        while(leftChildIndex <= heapLastIndex || rightChildIndex <= heapLastIndex){ //selama masi ada anak

            if(leftChildIndex <= heapLastIndex && rightChildIndex <= heapLastIndex){ //ada 2 anak
                if(heapArr[leftChildIndex] < heapArr[currentIndex] || heapArr[rightChildIndex] < heapArr[currentIndex]){ //salah satu anak valuenya lebih kecil
                    if(heapArr[leftChildIndex] < heapArr[rightChildIndex]){
                        swapValue(&heapArr[leftChildIndex], &heapArr[currentIndex]);
                        currentIndex = leftChildIndex;
                    }
                    else{
                        swapValue(&heapArr[rightChildIndex], &heapArr[currentIndex]);
                        currentIndex = rightChildIndex;
                    }
                }
                else{
                    break;
                }
            }
            else if(leftChildIndex <= heapLastIndex && rightChildIndex > heapLastIndex){ //ada 1 anak (anak kiri aja)
                if(heapArr[leftChildIndex] < heapArr[currentIndex]){
                    swapValue(&heapArr[leftChildIndex], &heapArr[currentIndex]);
                    currentIndex = leftChildIndex;
                }
                else{
                    break;
                }
            }
            else{ //tidak ada anak
                break;
            }
            
            leftChildIndex = getLeftChildIndex(currentIndex);
            rightChildIndex = getRightChildIndex(currentIndex);
        }
    }
}

int main(){
    puts("START");
    int n = 100;
    int arr[n] = {42, 32, 88, 46, 28, 53, 76, 71, 72, 95, 67, 98, 83, 86, 76, 95, 18, 44, 3, 87, 99, 82, 9, 70, 4, 98, 16, 29, 82, 57, 72, 7, 59, 54, 50, 84, 76, 91, 41, 100, 26, 54, 74, 96, 69, 84, 72, 3, 93, 14, 71, 42, 29, 83, 20, 45, 27, 28, 36, 76, 38, 58, 49, 59, 88, 33, 5, 10, 67, 64, 18, 30, 91, 53, 15, 53, 34, 17, 46, 48, 82, 37, 12, 60, 54, 50, 47, 53, 87, 31, 63, 32, 46, 24, 28, 37, 2, 20, 89, 42};
    int heapArr[n];
    insertHeap(arr, heapArr, n);
    extractHeap(arr, heapArr, n);
    print(arr, n);
    return 0;
}