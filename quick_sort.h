#include <stdbool.h>

/*
 * Step 1 − Choose the highest index value has pivot
 * Step 2 − Take two variables to point left and right of the list excluding pivot
 * Step 3 − left points to the low index
 * Step 4 − right points to the high
 **Step 5 − while value at left is less than pivot move right
 **Step 6 − while value at right is greater than pivot move left
 **Step 7 − if both step 5 and step 6 does not match swap left and right
 * Step 8 − if left ≥ right, the point where they met is new pivot
 */

void quick_sort(int* arr, int start, int end){
    // quick sort process
    // Pivot on the left side / start of arr
    if(end-1 == start) {return;}

    int p = start;
    int lo = start + 1;
    int hi = end-1;
    bool flag = true;
    int meetPos = -1;

    while(true){
        flag = true;
        
        // Step 5
        while(arr[lo] <= arr[p] && lo < end-1){
            lo++;
            flag = false;
        }
        // Step 6
        while(arr[hi] > arr[p] && hi > start){
            hi--;
            flag = false;
        }
        // Step 7
        if(flag == true && lo != hi){
            swap(&arr[lo], &arr[hi]);
        }
        // Step 8
        if(lo >= hi){// && meetPos >= 0){
            meetPos = lo; // CRUCIAL STEP
            if(arr[meetPos] < arr[p]){
                swap(&arr[meetPos], &arr[p]);
            }
            quick_sort(arr, start, meetPos);
            quick_sort(arr, meetPos, end);
            break;
        }
    }
}
