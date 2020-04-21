void insertion_sort(int* arr, int number){
    // insertion sort process
    int value = arr[0];
    int pos = 0;
    for(int i=1; i<number; i++){
        value = arr[i];
        for(pos=i-1; pos>=0; pos--){
            if(arr[pos] > value){
                arr[pos+1] = arr[pos];
            }
            else{
                break;    
            }
        }
        arr[pos+1] = value;
    }
}
