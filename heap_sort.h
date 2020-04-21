#include <stdbool.h>

void heap_insert(int*, int);
void heap_reshape(int*, int);

/* Construct tree
 * Step 1 − Create a new node at the end of heap.
 * Step 2 − Assign new value to the node.
 * Step 3 − Compare the value of this child node with its parent.
 * Step 4 − If value of parent is less than child, then swap them.
 * Step 5 − Repeat step 3 & 4 until Heap property holds.
 */

/*
p = floor(c/2)
-1
3  5  1  4  2  6
p--2
1 <5  3  4  2  6
5  1  3  4  2  6
p-----3
5  1  3  4  2  6
---p-----4
5  1  3 <4  2  6
5  4  3  1  2  6
5 >4  3  1  2  6
---p--------5
5  4  3  1 >2  6
------p--------6
5 >4  3  1  2 <6
5  4 >6  1  2  3
6  4  5  1  2  3
*/

/* Output / Deletion
 * Step 1 − Remove root node.
 * Step 2 − Move the last element of last level to root.
 * Step 3 − Compare the value of this child node with its parent.
 * Step 4 − If value of parent is less than child, then swap them.
 * Step 5 − Repeat step 3 & 4 until Heap property holds.
 */

void heap_sort(int* arr, int number){
    // heap sort process
    // Construct tree
    int p = 0;
    for(int k=1; k<number; k++){
        heap_insert(arr, k);
        /* test construct process
        for(int kk=0; kk<number; kk++){
            printf("%d, ", arr[kk]);
        }
        printf("\n");
        */
    }
    // printf("Construct done.\n");
    // Output
    for(int k=number-1; k>0; k--){
        swap(&arr[0], &arr[k]);
        heap_reshape(arr, k-1);
        /* test output process
        for(int kk=0; kk<number; kk++){
            printf("%d, ", arr[kk]);
        }
        printf("\n");
        */
    }
    // printf("\n");
}

void heap_insert(int* arr, int add){
    int p = (add - 1) / 2;
    do{
        if(arr[add] > arr[p]){
            swap(&arr[add], &arr[p]);
            add = p;
            p = (add - 1) / 2;
        }
        else{
            break;
        }
    }while(add != 0);
}

void heap_reshape(int* arr, int last){
    int curr = 0;
    int lc = 1; //0 * 2 + 1;
    while(lc <= last){
        if(lc + 1 <= last && (arr[curr] < arr[lc] || arr[curr] < arr[lc + 1])){ // left & right child both exist
            if(arr[lc] >= arr[lc + 1]){
                swap(&arr[curr], &arr[lc]);
                curr = lc;
            }
            else{
                swap(&arr[curr], &arr[lc + 1]);
                curr = lc + 1;
            }
            lc = curr * 2 + 1;
        }
        else if(arr[curr] < arr[lc]){ // only left child exists
            swap(&arr[curr], &arr[lc]);
            curr = lc;
            lc = curr * 2 + 1;
        }
        else{
            break;
        }
    }
}
