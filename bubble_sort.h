void bubble_sort(int* arr, int number){
    // bubble sort process
    for(int i=0; i<number-1; i++){
        for(int j=0; j<number-1; j++){
            if(arr[j] > arr[j+1]){
                swap(&arr[j], &arr[j+1]);
            }
        }
    }
}
