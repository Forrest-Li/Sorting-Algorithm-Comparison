// Make global
extern void swap(int* x, int* y);
extern void bubble_sort(int* arr, int number);
extern void insertion_sort(int* arr, int number);
extern void selection_sort(int* arr, int number);
extern void quick_sort(int* arr, int start, int end);
extern void heap_sort(int* arr, int number);
extern void heap_insert(int* arr, int add);
extern void heap_reshape(int* arr, int last);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "bubble_sort.h"
#include "insertion_sort.h"
#include "selection_sort.h"
#include "quick_sort.h"
#include "heap_sort.h"

void bubble_sort_process(int*);
void insertion_sort_process(int*);
void selection_sort_process(int*);
void quick_sort_process(int*);
void heap_sort_process(int*);
void swap(int*, int*);
int* gen_arr(int);
void count_n(char*, int);

int main(){
    int number[6] = {150000}; //{50000, 100000, 15000, 200000, 250000, 300000};
    
    // sleep(5);
    // bubble_sort_process(number);
    // sleep(5);
    // insertion_sort_process(number);
    // sleep(5);
    // selection_sort_process(number);
    // sleep(5);
    // quick_sort_process(number);
    // sleep(5);
    heap_sort_process(number);
    
    printf("\n");

    /* generate random numbers
     * not in use now
    int number;
    printf("Number of random numbers: \n>> ");
    scanf("%d", &number);
    srandom((unsigned)time(NULL));
    */

    // main process
    /* Prototype for each sort
    double costs[25] = {0};
    for(int k=0; k<25; k++){
        int* arr = gen_arr(number);

        char* cnt = malloc(2*sizeof(char));
        count_n(cnt, k);

        printf(">> Processing %2d%s sort.\n", k+1, cnt);
        clock_t start = clock();
        // bubble sort process
        // bubble_sort(arr, number);
        // insertion sort process
        // insertion_sort(arr, number);
        // selection sort process
        // selection_sort(arr, number);
        // quick sort process
        // quick_sort(arr, 0, number);
        // heap sort process
        // heap_sort(arr, number);
        clock_t end = clock();
        double interval = (double)(end - start) / CLOCKS_PER_SEC;
        costs[k] = interval;

        // print result if allowed
        if(number <= 100){
            printf("Sorted array:\n");
            for(int j=0; j<number; j++){
                printf("%d, ", arr[j]);
            }
            printf("\n");
        }

        free(cnt);
        free(arr);
    }

    // print time costs
    printf("Sorting costs:\n");
    for(int i=0; i<25; i++){
        char* cnt = malloc(2*sizeof(char));
        count_n(cnt, i);

        printf("%2d%s sort costs: %lf secs.\n", i+1, cnt, costs[i]);
        
        free(cnt);
    }
    */

    return 0;
}


void bubble_sort_process(int* number){
    double costs[25] = {0};

    printf(">>>>>>>>>> BUBBLE SORT STARTS <<<<<<<<<<\n");
    for(int q=0; q<6; q++){
        printf(">> %d numbers:\n", number[q]);
        for(int k=0; k<25; k++){
            int* arr = gen_arr(number[q]);
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, k);
            printf(">> Processing %2d%s sort.\n", k+1, cnt);
            clock_t start = clock();
        
            // bubble sort process
            bubble_sort(arr, number[q]);
        
            clock_t end = clock();
            double interval = (double)(end - start) / CLOCKS_PER_SEC;
            costs[k] = interval;

            free(cnt);
            free(arr);
            
            sleep(5);
        }

        // print time costs
        printf("Sorting costs:\n");
        for(int i=0; i<25; i++){
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, i);
            printf("%2d%s sort costs: %lf secs.\n", i+1, cnt, costs[i]);
            free(cnt);
        }
        for(int i=0; i<25; i++){
            printf("%lf, ", costs[i]);
        }
        printf("\n");
    }
    printf(">>>>>>>>>> BUBBLE SORT ENDS <<<<<<<<<<\n");
}


void insertion_sort_process(int* number){
    double costs[25] = {0};

    printf(">>>>>>>>>> INSERTION SORT STARTS <<<<<<<<<<\n");
    for(int q=0; q<6; q++){
        printf(">> %d numbers:\n", number[q]);
        for(int k=0; k<25; k++){
            int* arr = gen_arr(number[q]);
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, k);
            printf(">> Processing %2d%s sort.\n", k+1, cnt);
            clock_t start = clock();
        
            // insertion sort process
            insertion_sort(arr, number[q]);
        
            clock_t end = clock();
            double interval = (double)(end - start) / CLOCKS_PER_SEC;
            costs[k] = interval;

            free(cnt);
            free(arr);
            
            sleep(5);
        }

        // print time costs
        printf("Sorting costs:\n");
        for(int i=0; i<25; i++){
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, i);
            printf("%2d%s sort costs: %lf secs.\n", i+1, cnt, costs[i]);
            free(cnt);
        }
        for(int i=0; i<25; i++){
            printf("%lf, ", costs[i]);
        }
        printf("\n");
    }
    printf(">>>>>>>>>> INSERTION SORT ENDS <<<<<<<<<<\n");
}


void selection_sort_process(int* number){
    double costs[25] = {0};

    printf(">>>>>>>>>> SELECTION SORT STARTS <<<<<<<<<<\n");
    for(int q=0; q<6; q++){
        printf(">> %d numbers:\n", number[q]);
        for(int k=0; k<25; k++){
            int* arr = gen_arr(number[q]);
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, k);
            printf(">> Processing %2d%s sort.\n", k+1, cnt);
            clock_t start = clock();
        
            // selection sort process
            selection_sort(arr, number[q]);
        
            clock_t end = clock();
            double interval = (double)(end - start) / CLOCKS_PER_SEC;
            costs[k] = interval;

            free(cnt);
            free(arr);
            
            sleep(5);
        }

        // print time costs
        printf("Sorting costs:\n");
        for(int i=0; i<25; i++){
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, i);
            printf("%2d%s sort costs: %lf secs.\n", i+1, cnt, costs[i]);
            free(cnt);
        }
        for(int i=0; i<25; i++){
            printf("%lf, ", costs[i]);
        }
        printf("\n");
    }
    printf(">>>>>>>>>> SELECTION SORT ENDS <<<<<<<<<<\n");
}


void quick_sort_process(int* number){
    double costs[25] = {0};

    printf(">>>>>>>>>> QUICK SORT STARTS <<<<<<<<<<\n");
    for(int q=0; q<6; q++){
        printf(">> %d numbers:\n", number[q]);
        for(int k=0; k<25; k++){
            int* arr = gen_arr(number[q]);
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, k);
            printf(">> Processing %2d%s sort.\n", k+1, cnt);
            clock_t start = clock();
        
            // quick sort process
            quick_sort(arr, 0, number[q]);
        
            clock_t end = clock();
            double interval = (double)(end - start) / CLOCKS_PER_SEC;
            costs[k] = interval;

            free(cnt);
            free(arr);
            
            sleep(5);
        }

        // print time costs
        printf("Sorting costs:\n");
        for(int i=0; i<25; i++){
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, i);
            printf("%2d%s sort costs: %lf secs.\n", i+1, cnt, costs[i]);
            free(cnt);
        }
        for(int i=0; i<25; i++){
            printf("%lf, ", costs[i]);
        }
        printf("\n");
    }
    printf(">>>>>>>>>> QUICK SORT ENDS <<<<<<<<<<\n");
}


void heap_sort_process(int* number){
    double costs[25] = {0};

    printf(">>>>>>>>>> HEAP SORT STARTS <<<<<<<<<<\n");
    for(int q=0; q<6; q++){
        printf(">> %d numbers:\n", number[q]);
        for(int k=0; k<25; k++){
            int* arr = gen_arr(number[q]);
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, k);
            printf(">> Processing %2d%s sort.\n", k+1, cnt);
            clock_t start = clock();
        
            // heap sort process
            heap_sort(arr, number[q]);
        
            clock_t end = clock();
            double interval = (double)(end - start) / CLOCKS_PER_SEC;
            costs[k] = interval;

            free(cnt);
            free(arr);
            
            sleep(5);
        }

        // print time costs
        printf("Sorting costs:\n");
        for(int i=0; i<25; i++){
            char* cnt = malloc(2*sizeof(char));
            count_n(cnt, i);
            printf("%2d%s sort costs: %lf secs.\n", i+1, cnt, costs[i]);
            free(cnt);
        }
        for(int i=0; i<25; i++){
            printf("%lf, ", costs[i]);
        }
        printf("\n");
    }
    printf(">>>>>>>>>> HEAP SORT ENDS <<<<<<<<<<\n");
}


void swap(int* x, int* y){
    int tmp;
    tmp = *x;
    *x = *y;
    *y = tmp;
}


int* gen_arr(int n){
    int* arr = calloc(n, sizeof(int));

    for(int i=0; i<n; i++){
        arr[i] = random();//1000000;
    }
    
    if(n <= 100){
        printf("Array:\n");
        for(int j=0; j<n; j++){
            printf("%d, ", arr[j]);
        }
        printf("\n");
    }

    return arr;
}


void count_n(char* cnt, int k){
    char st[] = "st";
    char nd[] = "nd";
    char rd[] = "rd";
    char th[] = "th";
    //char cnt[] = "";
    switch(k+1){
        case 1:
        case 21:
            strcpy(cnt, st); break;
        case 2:
        case 22:
            strcpy(cnt, nd); break;
        case 3:
        case 23:
            strcpy(cnt, rd); break;
        default:
            strcpy(cnt, th); break;
    }
}
