void selection_sort(int* arr, int number){
    // selection sort process
    int min = 0;
    int curr = 0;
    for(int i=0; i<number-1; i++){
        min = i;
        for(curr=min+1; curr<number; curr++){
            if(arr[min] > arr[curr]){
                 min = curr;
            }
        }
        if(min != i){
            swap(&arr[i], &arr[min]);
        }
    }
}
