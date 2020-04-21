# 計算機演算法 作業1 - 分析 sorting 時間

> *Forrest Li*

---

### 一、環境

* OS: 18.04.1-Ubuntu LTS
* Prog. language: C
* Libraries:
   * `/stdio.h`
   * `/stdlib.h`
   * `/string.h`
   * `/time.h`
   * `/unistd.h`
   * `/stdbool.h`
* Architecture:
```
┖─ sorting
     ┠─ sort.c
     ┠─ bubble_sort.h
     ┠─ insertion_sort.h
     ┠─ selection_sort.h
     ┠─ quick_sort.h
     ┖─ heap_sort.h
```

---

### 二、做法

**前置作業**

* 進行所有排序動作時，保持電腦不進行其他任務，以達到對全部過程的穩定性能表現
* 所有排序動作都在同一個陣列中進行（不新建立陣列），有需要則通過變數值來指定子陣列範圍；
* 同一個陣列的排序通過 call by address 完成，一個陣列排序完成後釋放記憶體空間 `free(arr)`；
* 完成一個陣列排序動作通過 `sleep(5)` delay 5 秒；
* 隨機數通過 `random();` 生成，通過時間種子 `srandom((unsigned)time(NULL));` 隨機產生；
* 不同排序演算法位於各自的 `.h` header 檔內，便於整理與整合，呼叫演算法的參數統一為 `(int* arr, int number)`（例外：quick sort 多增加一個參數為陣列開始位址的 index `int start`）
* 排序過程中實時顯示當前排序的*演算法名稱*、*此次排序資料筆數*、*進行到第幾次排序（共 25 次）*；25 次排序完成則顯示這輪排序的每次花費的時間

**共用函數**

`void swap(int*, int*);`

> 交換位址，call by address

`int* gen_arr(int);`

> 通過 `calloc(sizeof(int) * number);` 根據指定長度生成隨機整數陣列，並回傳陣列初始位置指標

`void count_n(char*, int);`

> 僅用於印出數字序號用（e.g. 第***一***：回傳 "st"；第二十***二***：回傳 "nd"；第***三***：回傳 "st"...）

**Bubble sort**

* 參考：
   * [Data Structure - Bubble Sort Algorithm](https://www.tutorialspoint.com/data_structures_algorithms/bubble_sort_algorithm.htm "tutorialspoint")
* 邏輯：
   * 排序結果：遞增數列
   * 雙層迴圈結構
   * 外部迴圈：運行 **n-1**（最後一次只有最後一個元素，無需排序）次內層排序動作
   * 內部迴圈：運行 **n-1**（最後一次已經找到最大元素，無法與後面的元素排序）次氣泡排序動作
   * 交換順序條件：前面數值大於後面數值

**Insertion sort**

* 參考：
   * [Data Structure and Algorithms Insertion Sort](https://www.tutorialspoint.com/data_structures_algorithms/insertion_sort_algorithm.htm "tutorialspoint")
* 邏輯：
   * 排序結果：遞增數列
   * 雙層迴圈結構
   * 外部迴圈：模擬每次插入一個元素的過程，跳過插入第一個元素的過程，每次的 index 值為內部迴圈子陣列長度
   * 內部迴圈：每次從子陣列最後一個元素往前調整
   * 交換順序條件：前面數值大於後面數值

**Selection sort**

* 參考：
   * [Data Structure and Algorithms Selection Sort](https://www.tutorialspoint.com/data_structures_algorithms/selection_sort_algorithm.htm "tutorialspoint")
* 邏輯：
   * 排序結果：遞增數列
   * 雙層迴圈結構
   * 外部迴圈：運行 **n-1**（最後一次只剩下一個值，則不需要尋找動作）次尋找最小值動作
   * 內部迴圈：子陣列範圍從排序完成後的第一個值到最後，尋找最小值
   * 交換順序：交換子陣列**最小值**與**第一個值**位址

**Quick sort**

* 參考：
   * [Data Structure and Algorithms - Quick Sort](https://www.tutorialspoint.com/data_structures_algorithms/quick_sort_algorithm.htm "tutorialspoint")
* 邏輯：
   * pivot 位置：陣列第一個值
   * 排序結果：遞增數列
   * 遞迴結構
   * 內部變數：
      * `p` := pivot index
      * `lo` := low value index
      * `hi` := hign value index
      * `flag` := 左側與右側值同時不滿足向中間移動時為 `True`
      * `meetPos` := `lo == hi` 時的 index
   * 終止條件：子陣列長度為 1`(end-1 == start)`
   * 遞迴條件：當左右值相遇時，以兩者相遇點為臨界值將左右兩個子陣列（相遇點屬於右側子陣列）进行遞迴
   * 移動條件：左側值小於 pivot 值向左移動一直到不小於 pivot 值；右側值反之

**Heap sort**

* 參考：
   * [Heap Data Structures](https://www.tutorialspoint.com/data_structures_algorithms/heap_data_structure.htm "tutorialspoint")
   * [C Program to Sort an Array based on Heap Sort Algorithm](https://www.sanfoundry.com/c-program-heap-sort-algorithm/)
* 邏輯：
   * 排序結果：遞增數列
   * 建構過程
      1. 每次新增一個 child 節點，子陣列長度增加一
      2. 該節點向其 parent 比較：如果 child 大於 parent，則交換兩者
      3. 同時 parent 成為新 child，並重複上面步驟，直至大於條件不成立跳出迴圈
   * 輸出過程
      1. 每次交換頂端節點與子陣列的最後一個節點，並設定新子陣列長度減一
      2. 頂端節點向下面節點（**兩個 children 或 一個 child**）比較：如果 parent 小於 child(ren)，則交換兩者
      3. 將 child 作為新 parent，並重複上面步驟，直至小於條件不成立跳出迴圈

> **在輸出過程第 ii 步**：
>
> 如果有兩個 children，要先檢查右 child index 是否超出範圍（我以左 child 作為迴圈判斷條件），且如果 children 都大於 parent，一定要交換較大的 child 與 parent，否則將導致樹的調整錯誤
>
> 如果沒有兩個 children，才要檢查是否只有一個 child


---

### 三、程式碼

```
/* 
 * sort.c
 */

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
    int number[6] = {50000, 100000, 150000, 200000, 250000, 300000};

    sleep(5);
    bubble_sort_process(number);
    sleep(5);
    insertion_sort_process(number);
    sleep(5);
    selection_sort_process(number);
    sleep(5);
    quick_sort_process(number);
    sleep(5);
    heap_sort_process(number);

    printf("\n");
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
```

```
/* 
 * bubble_sort.h
 */

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
```

```
/* 
 * insertion_sort.h
 */

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
```

```
/*
 * selection_sort.h
 */

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
```

```
/*
 * quick_sort.h
 */

#include <stdbool.h>

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
```

```
/* 
 * heap_sort.h
 */

#include <stdbool.h>

void heap_insert(int*, int);
void heap_reshape(int*, int);

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
```

---

### 四、執行結果

```
>>>>>>>>>> BUBBLE SORT STARTS <<<<<<<<<<
>> 50000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 10.703658 secs.
 2nd sort costs: 10.645265 secs.
 3rd sort costs: 10.683796 secs.
 4th sort costs: 10.681255 secs.
 5th sort costs: 10.672771 secs.
 6th sort costs: 10.660044 secs.
 7th sort costs: 10.667650 secs.
 8th sort costs: 10.672359 secs.
 9th sort costs: 10.640214 secs.
10th sort costs: 10.671845 secs.
11th sort costs: 10.688047 secs.
12th sort costs: 10.631487 secs.
13th sort costs: 10.662725 secs.
14th sort costs: 10.680809 secs.
15th sort costs: 10.680085 secs.
16th sort costs: 10.673217 secs.
17th sort costs: 10.640110 secs.
18th sort costs: 10.672430 secs.
19th sort costs: 10.630316 secs.
20th sort costs: 10.675687 secs.
21st sort costs: 10.633632 secs.
22nd sort costs: 10.651963 secs.
23rd sort costs: 10.669086 secs.
24th sort costs: 10.609264 secs.
25th sort costs: 10.624793 secs.
10.703658, 10.645265, 10.683796, 10.681255, 10.672771, 10.660044, 10.667650, 10.672359, 10.640214, 10.671845, 10.688047, 10.631487, 10.662725, 10.680809, 10.680085, 10.673217, 10.640110, 10.672430, 10.630316, 10.675687, 10.633632, 10.651963, 10.669086, 10.609264, 10.624793, 
>> 100000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 42.971071 secs.
 2nd sort costs: 43.036076 secs.
 3rd sort costs: 43.366711 secs.
 4th sort costs: 43.331556 secs.
 5th sort costs: 43.244116 secs.
 6th sort costs: 43.338937 secs.
 7th sort costs: 43.304798 secs.
 8th sort costs: 43.248920 secs.
 9th sort costs: 43.250052 secs.
10th sort costs: 43.284378 secs.
11th sort costs: 43.371807 secs.
12th sort costs: 43.285892 secs.
13th sort costs: 43.246298 secs.
14th sort costs: 43.229659 secs.
15th sort costs: 43.200684 secs.
16th sort costs: 43.286043 secs.
17th sort costs: 43.293463 secs.
18th sort costs: 43.401763 secs.
19th sort costs: 43.319643 secs.
20th sort costs: 43.328246 secs.
21st sort costs: 43.282954 secs.
22nd sort costs: 43.248512 secs.
23rd sort costs: 43.266139 secs.
24th sort costs: 43.283341 secs.
25th sort costs: 43.275726 secs.
42.971071, 43.036076, 43.366711, 43.331556, 43.244116, 43.338937, 43.304798, 43.248920, 43.250052, 43.284378, 43.371807, 43.285892, 43.246298, 43.229659, 43.200684, 43.286043, 43.293463, 43.401763, 43.319643, 43.328246, 43.282954, 43.248512, 43.266139, 43.283341, 43.275726, 
>> 150000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 97.645279 secs.
 2nd sort costs: 96.971435 secs.
 3rd sort costs: 97.199073 secs.
 4th sort costs: 97.314388 secs.
 5th sort costs: 97.466159 secs.
 6th sort costs: 97.247402 secs.
 7th sort costs: 97.455589 secs.
 8th sort costs: 97.452356 secs.
 9th sort costs: 97.631268 secs.
10th sort costs: 97.431999 secs.
11th sort costs: 97.332667 secs.
12th sort costs: 97.451245 secs.
13th sort costs: 97.315017 secs.
14th sort costs: 97.268923 secs.
15th sort costs: 97.412590 secs.
16th sort costs: 97.531561 secs.
17th sort costs: 97.202324 secs.
18th sort costs: 97.298489 secs.
19th sort costs: 97.408863 secs.
20th sort costs: 97.336331 secs.
21st sort costs: 97.310217 secs.
22nd sort costs: 97.442433 secs.
23rd sort costs: 97.178538 secs.
24th sort costs: 97.474879 secs.
25th sort costs: 97.467310 secs.
97.645279, 96.971435, 97.199073, 97.314388, 97.466159, 97.247402, 97.455589, 97.452356, 97.631268, 97.431999, 97.332667, 97.451245, 97.315017, 97.268923, 97.412590, 97.531561, 97.202324, 97.298489, 97.408863, 97.336331, 97.310217, 97.442433, 97.178538, 97.474879, 97.467310,
>> 200000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 172.594701 secs.
 2nd sort costs: 173.376832 secs.
 3rd sort costs: 173.146706 secs.
 4th sort costs: 173.392800 secs.
 5th sort costs: 173.336044 secs.
 6th sort costs: 173.313141 secs.
 7th sort costs: 173.314165 secs.
 8th sort costs: 173.263654 secs.
 9th sort costs: 173.425119 secs.
10th sort costs: 173.102536 secs.
11th sort costs: 173.100359 secs.
12th sort costs: 173.468323 secs.
13th sort costs: 173.603396 secs.
14th sort costs: 172.440947 secs.
15th sort costs: 173.241982 secs.
16th sort costs: 172.864471 secs.
17th sort costs: 173.419188 secs.
18th sort costs: 173.145211 secs.
19th sort costs: 173.308374 secs.
20th sort costs: 173.402692 secs.
21st sort costs: 173.336115 secs.
22nd sort costs: 173.446960 secs.
23rd sort costs: 173.174475 secs.
24th sort costs: 173.262762 secs.
25th sort costs: 173.322625 secs.
172.594701, 173.376832, 173.146706, 173.392800, 173.336044, 173.313141, 173.314165, 173.263654, 173.425119, 173.102536, 173.100359, 173.468323, 173.603396, 172.440947, 173.241982, 172.864471, 173.419188, 173.145211, 173.308374, 173.402692, 173.336115, 173.446960, 173.174475, 173.262762, 173.322625, 
>> 250000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 270.776660 secs.
 2nd sort costs: 270.546880 secs.
 3rd sort costs: 270.648182 secs.
 4th sort costs: 270.755715 secs.
 5th sort costs: 270.454019 secs.
 6th sort costs: 270.798152 secs.
 7th sort costs: 270.360523 secs.
 8th sort costs: 270.713173 secs.
 9th sort costs: 270.611530 secs.
10th sort costs: 270.941198 secs.
11th sort costs: 270.808365 secs.
12th sort costs: 270.940202 secs.
13th sort costs: 270.553013 secs.
14th sort costs: 270.908841 secs.
15th sort costs: 270.455684 secs.
16th sort costs: 270.933344 secs.
17th sort costs: 270.845978 secs.
18th sort costs: 270.748840 secs.
19th sort costs: 270.677660 secs.
20th sort costs: 271.020909 secs.
21st sort costs: 270.627760 secs.
22nd sort costs: 271.145532 secs.
23rd sort costs: 270.950830 secs.
24th sort costs: 270.414742 secs.
25th sort costs: 270.520425 secs.
270.776660, 270.546880, 270.648182, 270.755715, 270.454019, 270.798152, 270.360523, 270.713173, 270.611530, 270.941198, 270.808365, 270.940202, 270.553013, 270.908841, 270.455684, 270.933344, 270.845978, 270.748840, 270.677660, 271.020909, 270.627760, 271.145532, 270.950830, 270.414742, 270.520425, 
>> 300000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 389.937600 secs.
 2nd sort costs: 389.997138 secs.
 3rd sort costs: 389.687579 secs.
 4th sort costs: 390.355695 secs.
 5th sort costs: 390.163875 secs.
 6th sort costs: 390.027575 secs.
 7th sort costs: 390.266334 secs.
 8th sort costs: 390.052402 secs.
 9th sort costs: 389.958057 secs.
10th sort costs: 389.701398 secs.
11th sort costs: 390.249643 secs.
12th sort costs: 390.552833 secs.
13th sort costs: 391.076845 secs.
14th sort costs: 389.822851 secs.
15th sort costs: 389.890735 secs.
16th sort costs: 389.644283 secs.
17th sort costs: 389.772689 secs.
18th sort costs: 389.689140 secs.
19th sort costs: 390.115728 secs.
20th sort costs: 389.993862 secs.
21st sort costs: 390.105645 secs.
22nd sort costs: 390.212392 secs.
23rd sort costs: 389.849858 secs.
24th sort costs: 389.958382 secs.
25th sort costs: 389.902737 secs.
389.937600, 389.997138, 389.687579, 390.355695, 390.163875, 390.027575, 390.266334, 390.052402, 389.958057, 389.701398, 390.249643, 390.552833, 391.076845, 389.822851, 389.890735, 389.644283, 389.772689, 389.689140, 390.115728, 389.993862, 390.105645, 390.212392, 389.849858, 389.958382, 389.902737, 
>>>>>>>>>> BUBBLE SORT ENDS <<<<<<<<<<
>>>>>>>>>> INSERTION SORT STARTS <<<<<<<<<<
>> 50000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 1.624688 secs.
 2nd sort costs: 1.624751 secs.
 3rd sort costs: 1.616410 secs.
 4th sort costs: 1.604901 secs.
 5th sort costs: 1.603601 secs.
 6th sort costs: 1.609675 secs.
 7th sort costs: 1.598381 secs.
 8th sort costs: 1.606975 secs.
 9th sort costs: 1.595609 secs.
10th sort costs: 1.607496 secs.
11th sort costs: 1.612356 secs.
12th sort costs: 1.596607 secs.
13th sort costs: 1.614550 secs.
14th sort costs: 1.614582 secs.
15th sort costs: 1.601490 secs.
16th sort costs: 1.598171 secs.
17th sort costs: 1.613186 secs.
18th sort costs: 1.632891 secs.
19th sort costs: 1.627957 secs.
20th sort costs: 1.626017 secs.
21st sort costs: 1.630045 secs.
22nd sort costs: 1.613904 secs.
23rd sort costs: 1.612080 secs.
24th sort costs: 1.599839 secs.
25th sort costs: 1.623945 secs.
1.624688, 1.624751, 1.616410, 1.604901, 1.603601, 1.609675, 1.598381, 1.606975, 1.595609, 1.607496, 1.612356, 1.596607, 1.614550, 1.614582, 1.601490, 1.598171, 1.613186, 1.632891, 1.627957, 1.626017, 1.630045, 1.613904, 1.612080, 1.599839, 1.623945, 
>> 100000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 6.416114 secs.
 2nd sort costs: 6.397353 secs.
 3rd sort costs: 6.419847 secs.
 4th sort costs: 6.411758 secs.
 5th sort costs: 6.416570 secs.
 6th sort costs: 6.414917 secs.
 7th sort costs: 6.415787 secs.
 8th sort costs: 6.430779 secs.
 9th sort costs: 6.418530 secs.
10th sort costs: 6.408961 secs.
11th sort costs: 6.399844 secs.
12th sort costs: 6.408496 secs.
13th sort costs: 6.387524 secs.
14th sort costs: 6.384011 secs.
15th sort costs: 6.438606 secs.
16th sort costs: 6.413670 secs.
17th sort costs: 6.409755 secs.
18th sort costs: 6.409050 secs.
19th sort costs: 6.406666 secs.
20th sort costs: 6.414101 secs.
21st sort costs: 6.388581 secs.
22nd sort costs: 6.409748 secs.
23rd sort costs: 6.404240 secs.
24th sort costs: 6.406090 secs.
25th sort costs: 6.421006 secs.
6.416114, 6.397353, 6.419847, 6.411758, 6.416570, 6.414917, 6.415787, 6.430779, 6.418530, 6.408961, 6.399844, 6.408496, 6.387524, 6.384011, 6.438606, 6.413670, 6.409755, 6.409050, 6.406666, 6.414101, 6.388581, 6.409748, 6.404240, 6.406090, 6.421006, 
>> 150000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 14.454110 secs.
 2nd sort costs: 14.390018 secs.
 3rd sort costs: 14.451877 secs.
 4th sort costs: 14.395310 secs.
 5th sort costs: 14.432378 secs.
 6th sort costs: 14.408550 secs.
 7th sort costs: 14.441953 secs.
 8th sort costs: 14.461392 secs.
 9th sort costs: 14.390811 secs.
10th sort costs: 14.378959 secs.
11th sort costs: 14.431683 secs.
12th sort costs: 14.379497 secs.
13th sort costs: 14.410792 secs.
14th sort costs: 14.413880 secs.
15th sort costs: 14.435452 secs.
16th sort costs: 14.387723 secs.
17th sort costs: 14.393634 secs.
18th sort costs: 14.431739 secs.
19th sort costs: 14.386736 secs.
20th sort costs: 14.390829 secs.
21st sort costs: 14.404217 secs.
22nd sort costs: 14.428628 secs.
23rd sort costs: 14.461502 secs.
24th sort costs: 14.378559 secs.
25th sort costs: 14.431295 secs.
14.454110, 14.390018, 14.451877, 14.395310, 14.432378, 14.408550, 14.441953, 14.461392, 14.390811, 14.378959, 14.431683, 14.379497, 14.410792, 14.413880, 14.435452, 14.387723, 14.393634, 14.431739, 14.386736, 14.390829, 14.404217, 14.428628, 14.461502, 14.378559, 14.431295,
>> 200000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 25.668683 secs.
 2nd sort costs: 25.634028 secs.
 3rd sort costs: 25.638483 secs.
 4th sort costs: 25.659461 secs.
 5th sort costs: 25.611890 secs.
 6th sort costs: 25.546128 secs.
 7th sort costs: 25.624905 secs.
 8th sort costs: 25.628036 secs.
 9th sort costs: 25.572277 secs.
10th sort costs: 25.612247 secs.
11th sort costs: 25.692820 secs.
12th sort costs: 25.606336 secs.
13th sort costs: 25.596043 secs.
14th sort costs: 25.670569 secs.
15th sort costs: 25.519257 secs.
16th sort costs: 25.618152 secs.
17th sort costs: 25.611454 secs.
18th sort costs: 25.597099 secs.
19th sort costs: 25.588260 secs.
20th sort costs: 25.599722 secs.
21st sort costs: 25.572562 secs.
22nd sort costs: 25.578039 secs.
23rd sort costs: 25.615621 secs.
24th sort costs: 25.607873 secs.
25th sort costs: 25.702839 secs.
25.668683, 25.634028, 25.638483, 25.659461, 25.611890, 25.546128, 25.624905, 25.628036, 25.572277, 25.612247, 25.692820, 25.606336, 25.596043, 25.670569, 25.519257, 25.618152, 25.611454, 25.597099, 25.588260, 25.599722, 25.572562, 25.578039, 25.615621, 25.607873, 25.702839, 
>> 250000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 40.003737 secs.
 2nd sort costs: 39.976368 secs.
 3rd sort costs: 40.059066 secs.
 4th sort costs: 40.021023 secs.
 5th sort costs: 40.087129 secs.
 6th sort costs: 40.064936 secs.
 7th sort costs: 39.934260 secs.
 8th sort costs: 40.078350 secs.
 9th sort costs: 40.070791 secs.
10th sort costs: 40.058359 secs.
11th sort costs: 40.024671 secs.
12th sort costs: 40.172459 secs.
13th sort costs: 40.320582 secs.
14th sort costs: 40.457014 secs.
15th sort costs: 40.278052 secs.
16th sort costs: 40.513023 secs.
17th sort costs: 39.984684 secs.
18th sort costs: 40.082086 secs.
19th sort costs: 40.011352 secs.
20th sort costs: 40.418069 secs.
21st sort costs: 40.019950 secs.
22nd sort costs: 40.032195 secs.
23rd sort costs: 40.106455 secs.
24th sort costs: 40.661023 secs.
25th sort costs: 40.061553 secs.
40.003737, 39.976368, 40.059066, 40.021023, 40.087129, 40.064936, 39.934260, 40.078350, 40.070791, 40.058359, 40.024671, 40.172459, 40.320582, 40.457014, 40.278052, 40.513023, 39.984684, 40.082086, 40.011352, 40.418069, 40.019950, 40.032195, 40.106455, 40.661023, 40.061553, 
>> 300000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 57.652987 secs.
 2nd sort costs: 57.702261 secs.
 3rd sort costs: 57.679415 secs.
 4th sort costs: 57.498354 secs.
 5th sort costs: 57.716768 secs.
 6th sort costs: 57.521683 secs.
 7th sort costs: 57.756628 secs.
 8th sort costs: 57.761381 secs.
 9th sort costs: 57.656565 secs.
10th sort costs: 57.645953 secs.
11th sort costs: 57.654547 secs.
12th sort costs: 57.674189 secs.
13th sort costs: 57.669235 secs.
14th sort costs: 57.770672 secs.
15th sort costs: 57.685189 secs.
16th sort costs: 57.680342 secs.
17th sort costs: 57.669973 secs.
18th sort costs: 57.810920 secs.
19th sort costs: 57.763114 secs.
20th sort costs: 57.508637 secs.
21st sort costs: 57.610175 secs.
22nd sort costs: 57.640647 secs.
23rd sort costs: 57.658764 secs.
24th sort costs: 57.691617 secs.
25th sort costs: 57.663979 secs.
57.652987, 57.702261, 57.679415, 57.498354, 57.716768, 57.521683, 57.756628, 57.761381, 57.656565, 57.645953, 57.654547, 57.674189, 57.669235, 57.770672, 57.685189, 57.680342, 57.669973, 57.810920, 57.763114, 57.508637, 57.610175, 57.640647, 57.658764, 57.691617, 57.663979, 
>>>>>>>>>> INSERTION SORT ENDS <<<<<<<<<<
>>>>>>>>>> SELECTION SORT STARTS <<<<<<<<<<
>> 50000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 2.524525 secs.
 2nd sort costs: 2.532880 secs.
 3rd sort costs: 2.532380 secs.
 4th sort costs: 2.526337 secs.
 5th sort costs: 2.528623 secs.
 6th sort costs: 2.551304 secs.
 7th sort costs: 2.530945 secs.
 8th sort costs: 2.528436 secs.
 9th sort costs: 2.536497 secs.
10th sort costs: 2.528247 secs.
11th sort costs: 2.530482 secs.
12th sort costs: 2.522394 secs.
13th sort costs: 2.527887 secs.
14th sort costs: 2.536030 secs.
15th sort costs: 2.528550 secs.
16th sort costs: 2.522537 secs.
17th sort costs: 2.532438 secs.
18th sort costs: 2.532342 secs.
19th sort costs: 2.534635 secs.
20th sort costs: 2.526453 secs.
21st sort costs: 2.527813 secs.
22nd sort costs: 2.530869 secs.
23rd sort costs: 2.522216 secs.
24th sort costs: 2.524315 secs.
25th sort costs: 2.538047 secs.
2.524525, 2.532880, 2.532380, 2.526337, 2.528623, 2.551304, 2.530945, 2.528436, 2.536497, 2.528247, 2.530482, 2.522394, 2.527887, 2.536030, 2.528550, 2.522537, 2.532438, 2.532342, 2.534635, 2.526453, 2.527813, 2.530869, 2.522216, 2.524315, 2.538047, 
>> 100000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 10.072185 secs.
 2nd sort costs: 10.091023 secs.
 3rd sort costs: 10.109364 secs.
 4th sort costs: 10.055203 secs.
 5th sort costs: 10.105436 secs.
 6th sort costs: 10.092550 secs.
 7th sort costs: 10.107992 secs.
 8th sort costs: 10.105568 secs.
 9th sort costs: 10.092401 secs.
10th sort costs: 10.094175 secs.
11th sort costs: 10.069789 secs.
12th sort costs: 10.083898 secs.
13th sort costs: 10.076528 secs.
14th sort costs: 10.093243 secs.
15th sort costs: 10.106422 secs.
16th sort costs: 10.090144 secs.
17th sort costs: 10.078682 secs.
18th sort costs: 10.096988 secs.
19th sort costs: 10.099458 secs.
20th sort costs: 10.080234 secs.
21st sort costs: 10.084825 secs.
22nd sort costs: 10.050963 secs.
23rd sort costs: 10.092825 secs.
24th sort costs: 10.095464 secs.
25th sort costs: 10.099573 secs.
10.072185, 10.091023, 10.109364, 10.055203, 10.105436, 10.092550, 10.107992, 10.105568, 10.092401, 10.094175, 10.069789, 10.083898, 10.076528, 10.093243, 10.106422, 10.090144, 10.078682, 10.096988, 10.099458, 10.080234, 10.084825, 10.050963, 10.092825, 10.095464, 10.099573, 
>> 150000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 22.676363 secs.
 2nd sort costs: 22.649808 secs.
 3rd sort costs: 22.688992 secs.
 4th sort costs: 22.671991 secs.
 5th sort costs: 22.700311 secs.
 6th sort costs: 22.691603 secs.
 7th sort costs: 22.634559 secs.
 8th sort costs: 22.616514 secs.
 9th sort costs: 22.631698 secs.
10th sort costs: 22.657511 secs.
11th sort costs: 22.696888 secs.
12th sort costs: 22.688412 secs.
13th sort costs: 22.682246 secs.
14th sort costs: 22.686427 secs.
15th sort costs: 22.683648 secs.
16th sort costs: 22.686800 secs.
17th sort costs: 22.688065 secs.
18th sort costs: 22.690710 secs.
19th sort costs: 22.660776 secs.
20th sort costs: 22.664287 secs.
21st sort costs: 22.686382 secs.
22nd sort costs: 22.628597 secs.
23rd sort costs: 22.621860 secs.
24th sort costs: 22.677551 secs.
25th sort costs: 22.663450 secs.
22.676363, 22.649808, 22.688992, 22.671991, 22.700311, 22.691603, 22.634559, 22.616514, 22.631698, 22.657511, 22.696888, 22.688412, 22.682246, 22.686427, 22.683648, 22.686800, 22.688065, 22.690710, 22.660776, 22.664287, 22.686382, 22.628597, 22.621860, 22.677551, 22.663450,
>> 200000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 40.273117 secs.
 2nd sort costs: 40.197811 secs.
 3rd sort costs: 40.276696 secs.
 4th sort costs: 40.276927 secs.
 5th sort costs: 40.167838 secs.
 6th sort costs: 40.198030 secs.
 7th sort costs: 40.233668 secs.
 8th sort costs: 40.310636 secs.
 9th sort costs: 40.292329 secs.
10th sort costs: 40.314417 secs.
11th sort costs: 40.150959 secs.
12th sort costs: 40.213536 secs.
13th sort costs: 40.253668 secs.
14th sort costs: 40.215425 secs.
15th sort costs: 40.300445 secs.
16th sort costs: 40.303908 secs.
17th sort costs: 40.293434 secs.
18th sort costs: 40.314489 secs.
19th sort costs: 40.291953 secs.
20th sort costs: 40.246909 secs.
21st sort costs: 40.309134 secs.
22nd sort costs: 40.192552 secs.
23rd sort costs: 40.289646 secs.
24th sort costs: 40.287690 secs.
25th sort costs: 40.266554 secs.
40.273117, 40.197811, 40.276696, 40.276927, 40.167838, 40.198030, 40.233668, 40.310636, 40.292329, 40.314417, 40.150959, 40.213536, 40.253668, 40.215425, 40.300445, 40.303908, 40.293434, 40.314489, 40.291953, 40.246909, 40.309134, 40.192552, 40.289646, 40.287690, 40.266554, 
>> 250000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 62.921839 secs.
 2nd sort costs: 62.959031 secs.
 3rd sort costs: 62.942206 secs.
 4th sort costs: 62.912638 secs.
 5th sort costs: 62.870892 secs.
 6th sort costs: 62.901938 secs.
 7th sort costs: 62.917824 secs.
 8th sort costs: 62.885537 secs.
 9th sort costs: 62.946004 secs.
10th sort costs: 62.984244 secs.
11th sort costs: 62.950861 secs.
12th sort costs: 62.918722 secs.
13th sort costs: 62.945788 secs.
14th sort costs: 62.974720 secs.
15th sort costs: 63.023274 secs.
16th sort costs: 62.962732 secs.
17th sort costs: 63.032906 secs.
18th sort costs: 62.955369 secs.
19th sort costs: 62.889686 secs.
20th sort costs: 62.886449 secs.
21st sort costs: 62.975505 secs.
22nd sort costs: 63.028783 secs.
23rd sort costs: 62.727501 secs.
24th sort costs: 62.837767 secs.
25th sort costs: 62.901269 secs.
62.921839, 62.959031, 62.942206, 62.912638, 62.870892, 62.901938, 62.917824, 62.885537, 62.946004, 62.984244, 62.950861, 62.918722, 62.945788, 62.974720, 63.023274, 62.962732, 63.032906, 62.955369, 62.889686, 62.886449, 62.975505, 63.028783, 62.727501, 62.837767, 62.901269, 
>> 300000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 90.612499 secs.
 2nd sort costs: 90.611538 secs.
 3rd sort costs: 90.949972 secs.
 4th sort costs: 90.551345 secs.
 5th sort costs: 91.058673 secs.
 6th sort costs: 90.857189 secs.
 7th sort costs: 90.342131 secs.
 8th sort costs: 90.607885 secs.
 9th sort costs: 90.392008 secs.
10th sort costs: 91.233652 secs.
11th sort costs: 90.729364 secs.
12th sort costs: 90.667201 secs.
13th sort costs: 90.677112 secs.
14th sort costs: 90.617824 secs.
15th sort costs: 90.610377 secs.
16th sort costs: 90.612020 secs.
17th sort costs: 90.620547 secs.
18th sort costs: 90.616226 secs.
19th sort costs: 90.662221 secs.
20th sort costs: 90.612185 secs.
21st sort costs: 90.644002 secs.
22nd sort costs: 90.577657 secs.
23rd sort costs: 90.579010 secs.
24th sort costs: 90.661111 secs.
25th sort costs: 90.625309 secs.
90.612499, 90.611538, 90.949972, 90.551345, 91.058673, 90.857189, 90.342131, 90.607885, 90.392008, 91.233652, 90.729364, 90.667201, 90.677112, 90.617824, 90.610377, 90.612020, 90.620547, 90.616226, 90.662221, 90.612185, 90.644002, 90.577657, 90.579010, 90.661111, 90.625309, 
>>>>>>>>>> SELECTION SORT ENDS <<<<<<<<<<
>>>>>>>>>> QUICK SORT STARTS <<<<<<<<<<
>> 50000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.013383 secs.
 2nd sort costs: 0.011342 secs.
 3rd sort costs: 0.012929 secs.
 4th sort costs: 0.031145 secs.
 5th sort costs: 0.012507 secs.
 6th sort costs: 0.012423 secs.
 7th sort costs: 0.011329 secs.
 8th sort costs: 0.013055 secs.
 9th sort costs: 0.016283 secs.
10th sort costs: 0.012851 secs.
11th sort costs: 0.012710 secs.
12th sort costs: 0.012434 secs.
13th sort costs: 0.031385 secs.
14th sort costs: 0.011787 secs.
15th sort costs: 0.011928 secs.
16th sort costs: 0.013105 secs.
17th sort costs: 0.011617 secs.
18th sort costs: 0.011247 secs.
19th sort costs: 0.011607 secs.
20th sort costs: 0.013418 secs.
21st sort costs: 0.013186 secs.
22nd sort costs: 0.011871 secs.
23rd sort costs: 0.009426 secs.
24th sort costs: 0.013242 secs.
25th sort costs: 0.013784 secs.
0.013383, 0.011342, 0.012929, 0.031145, 0.012507, 0.012423, 0.011329, 0.013055, 0.016283, 0.012851, 0.012710, 0.012434, 0.031385, 0.011787, 0.011928, 0.013105, 0.011617, 0.011247, 0.011607, 0.013418, 0.013186, 0.011871, 0.009426, 0.013242, 0.013784, 
>> 100000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.041083 secs.
 2nd sort costs: 0.046965 secs.
 3rd sort costs: 0.022068 secs.
 4th sort costs: 0.025487 secs.
 5th sort costs: 0.024534 secs.
 6th sort costs: 0.049404 secs.
 7th sort costs: 0.041668 secs.
 8th sort costs: 0.020427 secs.
 9th sort costs: 0.023869 secs.
10th sort costs: 0.024954 secs.
11th sort costs: 0.024072 secs.
12th sort costs: 0.023267 secs.
13th sort costs: 0.023891 secs.
14th sort costs: 0.019863 secs.
15th sort costs: 0.024070 secs.
16th sort costs: 0.024513 secs.
17th sort costs: 0.047361 secs.
18th sort costs: 0.023068 secs.
19th sort costs: 0.023802 secs.
20th sort costs: 0.023877 secs.
21st sort costs: 0.022985 secs.
22nd sort costs: 0.045290 secs.
23rd sort costs: 0.023640 secs.
24th sort costs: 0.023471 secs.
25th sort costs: 0.020866 secs.
0.041083, 0.046965, 0.022068, 0.025487, 0.024534, 0.049404, 0.041668, 0.020427, 0.023869, 0.024954, 0.024072, 0.023267, 0.023891, 0.019863, 0.024070, 0.024513, 0.047361, 0.023068, 0.023802, 0.023877, 0.022985, 0.045290, 0.023640, 0.023471, 0.020866, 
>> 150000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.035778 secs.
 2nd sort costs: 0.036045 secs.
 3rd sort costs: 0.034400 secs.
 4th sort costs: 0.033152 secs.
 5th sort costs: 0.035147 secs.
 6th sort costs: 0.033426 secs.
 7th sort costs: 0.052813 secs.
 8th sort costs: 0.033868 secs.
 9th sort costs: 0.035112 secs.
10th sort costs: 0.034085 secs.
11th sort costs: 0.057864 secs.
12th sort costs: 0.051713 secs.
13th sort costs: 0.034277 secs.
14th sort costs: 0.035634 secs.
15th sort costs: 0.034293 secs.
16th sort costs: 0.034345 secs.
17th sort costs: 0.050071 secs.
18th sort costs: 0.033427 secs.
19th sort costs: 0.034451 secs.
20th sort costs: 0.035230 secs.
21st sort costs: 0.034649 secs.
22nd sort costs: 0.052647 secs.
23rd sort costs: 0.032478 secs.
24th sort costs: 0.035986 secs.
25th sort costs: 0.035020 secs.
0.035778, 0.036045, 0.034400, 0.033152, 0.035147, 0.033426, 0.052813, 0.033868, 0.035112, 0.034085, 0.057864, 0.051713, 0.034277, 0.035634, 0.034293, 0.034345, 0.050071, 0.033427, 0.034451, 0.035230, 0.034649, 0.052647, 0.032478, 0.035986, 0.035020,
>> 200000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.044487 secs.
 2nd sort costs: 0.044936 secs.
 3rd sort costs: 0.067426 secs.
 4th sort costs: 0.042247 secs.
 5th sort costs: 0.047531 secs.
 6th sort costs: 0.044537 secs.
 7th sort costs: 0.040499 secs.
 8th sort costs: 0.043448 secs.
 9th sort costs: 0.041403 secs.
10th sort costs: 0.046249 secs.
11th sort costs: 0.044580 secs.
12th sort costs: 0.041692 secs.
13th sort costs: 0.068165 secs.
14th sort costs: 0.042682 secs.
15th sort costs: 0.041427 secs.
16th sort costs: 0.044267 secs.
17th sort costs: 0.040358 secs.
18th sort costs: 0.042077 secs.
19th sort costs: 0.042273 secs.
20th sort costs: 0.050282 secs.
21st sort costs: 0.045492 secs.
22nd sort costs: 0.039761 secs.
23rd sort costs: 0.043104 secs.
24th sort costs: 0.042864 secs.
25th sort costs: 0.042822 secs.
0.044487, 0.044936, 0.067426, 0.042247, 0.047531, 0.044537, 0.040499, 0.043448, 0.041403, 0.046249, 0.044580, 0.041692, 0.068165, 0.042682, 0.041427, 0.044267, 0.040358, 0.042077, 0.042273, 0.050282, 0.045492, 0.039761, 0.043104, 0.042864, 0.042822, 
>> 250000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.061139 secs.
 2nd sort costs: 0.049657 secs.
 3rd sort costs: 0.056131 secs.
 4th sort costs: 0.054629 secs.
 5th sort costs: 0.070222 secs.
 6th sort costs: 0.076109 secs.
 7th sort costs: 0.054787 secs.
 8th sort costs: 0.055379 secs.
 9th sort costs: 0.054654 secs.
10th sort costs: 0.057234 secs.
11th sort costs: 0.077974 secs.
12th sort costs: 0.070413 secs.
13th sort costs: 0.054963 secs.
14th sort costs: 0.054684 secs.
15th sort costs: 0.050467 secs.
16th sort costs: 0.053509 secs.
17th sort costs: 0.075612 secs.
18th sort costs: 0.063949 secs.
19th sort costs: 0.055131 secs.
20th sort costs: 0.051730 secs.
21st sort costs: 0.054553 secs.
22nd sort costs: 0.055689 secs.
23rd sort costs: 0.054527 secs.
24th sort costs: 0.054773 secs.
25th sort costs: 0.054660 secs.
0.061139, 0.049657, 0.056131, 0.054629, 0.070222, 0.076109, 0.054787, 0.055379, 0.054654, 0.057234, 0.077974, 0.070413, 0.054963, 0.054684, 0.050467, 0.053509, 0.075612, 0.063949, 0.055131, 0.051730, 0.054553, 0.055689, 0.054527, 0.054773, 0.054660, 
>> 300000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.065127 secs.
 2nd sort costs: 0.064938 secs.
 3rd sort costs: 0.089512 secs.
 4th sort costs: 0.080909 secs.
 5th sort costs: 0.062380 secs.
 6th sort costs: 0.063737 secs.
 7th sort costs: 0.065594 secs.
 8th sort costs: 0.062502 secs.
 9th sort costs: 0.065469 secs.
10th sort costs: 0.086340 secs.
11th sort costs: 0.073819 secs.
12th sort costs: 0.062480 secs.
13th sort costs: 0.065078 secs.
14th sort costs: 0.066112 secs.
15th sort costs: 0.064560 secs.
16th sort costs: 0.079299 secs.
17th sort costs: 0.059170 secs.
18th sort costs: 0.065464 secs.
19th sort costs: 0.064722 secs.
20th sort costs: 0.062656 secs.
21st sort costs: 0.063724 secs.
22nd sort costs: 0.062055 secs.
23rd sort costs: 0.077487 secs.
24th sort costs: 0.064951 secs.
25th sort costs: 0.061978 secs.
0.065127, 0.064938, 0.089512, 0.080909, 0.062380, 0.063737, 0.065594, 0.062502, 0.065469, 0.086340, 0.073819, 0.062480, 0.065078, 0.066112, 0.064560, 0.079299, 0.059170, 0.065464, 0.064722, 0.062656, 0.063724, 0.062055, 0.077487, 0.064951, 0.061978, 
>>>>>>>>>> QUICK SORT ENDS <<<<<<<<<<
>>>>>>>>>> HEAP SORT STARTS <<<<<<<<<<
>> 50000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.015369 secs.
 2nd sort costs: 0.015383 secs.
 3rd sort costs: 0.016453 secs.
 4th sort costs: 0.015279 secs.
 5th sort costs: 0.015931 secs.
 6th sort costs: 0.015736 secs.
 7th sort costs: 0.014989 secs.
 8th sort costs: 0.015187 secs.
 9th sort costs: 0.015403 secs.
10th sort costs: 0.016044 secs.
11th sort costs: 0.036994 secs.
12th sort costs: 0.016488 secs.
13th sort costs: 0.015733 secs.
14th sort costs: 0.015639 secs.
15th sort costs: 0.035282 secs.
16th sort costs: 0.034047 secs.
17th sort costs: 0.014780 secs.
18th sort costs: 0.015958 secs.
19th sort costs: 0.016291 secs.
20th sort costs: 0.036833 secs.
21st sort costs: 0.015270 secs.
22nd sort costs: 0.016405 secs.
23rd sort costs: 0.015817 secs.
24th sort costs: 0.016525 secs.
25th sort costs: 0.016212 secs.
0.015369, 0.015383, 0.016453, 0.015279, 0.015931, 0.015736, 0.014989, 0.015187, 0.015403, 0.016044, 0.036994, 0.016488, 0.015733, 0.015639, 0.035282, 0.034047, 0.014780, 0.015958, 0.016291, 0.036833, 0.015270, 0.016405, 0.015817, 0.016525, 0.016212, 
>> 100000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.026874 secs.
 2nd sort costs: 0.030160 secs.
 3rd sort costs: 0.031143 secs.
 4th sort costs: 0.053421 secs.
 5th sort costs: 0.030375 secs.
 6th sort costs: 0.032261 secs.
 7th sort costs: 0.030147 secs.
 8th sort costs: 0.032018 secs.
 9th sort costs: 0.027804 secs.
10th sort costs: 0.047559 secs.
11th sort costs: 0.025076 secs.
12th sort costs: 0.029871 secs.
13th sort costs: 0.030460 secs.
14th sort costs: 0.029080 secs.
15th sort costs: 0.047731 secs.
16th sort costs: 0.031612 secs.
17th sort costs: 0.031768 secs.
18th sort costs: 0.030489 secs.
19th sort costs: 0.030399 secs.
20th sort costs: 0.030564 secs.
21st sort costs: 0.024441 secs.
22nd sort costs: 0.030301 secs.
23rd sort costs: 0.030085 secs.
24th sort costs: 0.029590 secs.
25th sort costs: 0.050008 secs.
0.026874, 0.030160, 0.031143, 0.053421, 0.030375, 0.032261, 0.030147, 0.032018, 0.027804, 0.047559, 0.025076, 0.029871, 0.030460, 0.029080, 0.047731, 0.031612, 0.031768, 0.030489, 0.030399, 0.030564, 0.024441, 0.030301, 0.030085, 0.029590, 0.050008, 
>> 150000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.057474 secs.
 2nd sort costs: 0.042956 secs.
 3rd sort costs: 0.044026 secs.
 4th sort costs: 0.044721 secs.
 5th sort costs: 0.060174 secs.
 6th sort costs: 0.056937 secs.
 7th sort costs: 0.042885 secs.
 8th sort costs: 0.044863 secs.
 9th sort costs: 0.043651 secs.
10th sort costs: 0.061609 secs.
11th sort costs: 0.066897 secs.
12th sort costs: 0.041504 secs.
13th sort costs: 0.044124 secs.
14th sort costs: 0.045645 secs.
15th sort costs: 0.057411 secs.
16th sort costs: 0.066937 secs.
17th sort costs: 0.064900 secs.
18th sort costs: 0.044994 secs.
19th sort costs: 0.056434 secs.
20th sort costs: 0.043827 secs.
21st sort costs: 0.043747 secs.
22nd sort costs: 0.043285 secs.
23rd sort costs: 0.041724 secs.
24th sort costs: 0.058251 secs.
25th sort costs: 0.041193 secs.
0.057474, 0.042956, 0.044026, 0.044721, 0.060174, 0.056937, 0.042885, 0.044863, 0.043651, 0.061609, 0.066897, 0.041504, 0.044124, 0.045645, 0.057411, 0.066937, 0.064900, 0.044994, 0.056434, 0.043827, 0.043747, 0.043285, 0.041724, 0.058251, 0.041193,
>> 200000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.054888 secs.
 2nd sort costs: 0.077654 secs.
 3rd sort costs: 0.052875 secs.
 4th sort costs: 0.056140 secs.
 5th sort costs: 0.057553 secs.
 6th sort costs: 0.059201 secs.
 7th sort costs: 0.055150 secs.
 8th sort costs: 0.054952 secs.
 9th sort costs: 0.057197 secs.
10th sort costs: 0.056211 secs.
11th sort costs: 0.054016 secs.
12th sort costs: 0.056151 secs.
13th sort costs: 0.072661 secs.
14th sort costs: 0.052284 secs.
15th sort costs: 0.057899 secs.
16th sort costs: 0.054204 secs.
17th sort costs: 0.056847 secs.
18th sort costs: 0.056655 secs.
19th sort costs: 0.080211 secs.
20th sort costs: 0.052183 secs.
21st sort costs: 0.055187 secs.
22nd sort costs: 0.057405 secs.
23rd sort costs: 0.056991 secs.
24th sort costs: 0.058795 secs.
25th sort costs: 0.055077 secs.
0.054888, 0.077654, 0.052875, 0.056140, 0.057553, 0.059201, 0.055150, 0.054952, 0.057197, 0.056211, 0.054016, 0.056151, 0.072661, 0.052284, 0.057899, 0.054204, 0.056847, 0.056655, 0.080211, 0.052183, 0.055187, 0.057405, 0.056991, 0.058795, 0.055077, 
>> 250000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.065360 secs.
 2nd sort costs: 0.071737 secs.
 3rd sort costs: 0.069449 secs.
 4th sort costs: 0.065511 secs.
 5th sort costs: 0.069094 secs.
 6th sort costs: 0.069163 secs.
 7th sort costs: 0.085857 secs.
 8th sort costs: 0.066372 secs.
 9th sort costs: 0.076037 secs.
10th sort costs: 0.069518 secs.
11th sort costs: 0.070994 secs.
12th sort costs: 0.068830 secs.
13th sort costs: 0.086190 secs.
14th sort costs: 0.083343 secs.
15th sort costs: 0.071751 secs.
16th sort costs: 0.067746 secs.
17th sort costs: 0.069127 secs.
18th sort costs: 0.087332 secs.
19th sort costs: 0.070869 secs.
20th sort costs: 0.071208 secs.
21st sort costs: 0.068124 secs.
22nd sort costs: 0.070243 secs.
23rd sort costs: 0.069717 secs.
24th sort costs: 0.092040 secs.
25th sort costs: 0.091979 secs.
0.065360, 0.071737, 0.069449, 0.065511, 0.069094, 0.069163, 0.085857, 0.066372, 0.076037, 0.069518, 0.070994, 0.068830, 0.086190, 0.083343, 0.071751, 0.067746, 0.069127, 0.087332, 0.070869, 0.071208, 0.068124, 0.070243, 0.069717, 0.092040, 0.091979, 
>> 300000 numbers:
>> Processing  1st sort.
>> Processing  2nd sort.
>> Processing  3rd sort.
>> Processing  4th sort.
>> Processing  5th sort.
>> Processing  6th sort.
>> Processing  7th sort.
>> Processing  8th sort.
>> Processing  9th sort.
>> Processing 10th sort.
>> Processing 11th sort.
>> Processing 12th sort.
>> Processing 13th sort.
>> Processing 14th sort.
>> Processing 15th sort.
>> Processing 16th sort.
>> Processing 17th sort.
>> Processing 18th sort.
>> Processing 19th sort.
>> Processing 20th sort.
>> Processing 21st sort.
>> Processing 22nd sort.
>> Processing 23rd sort.
>> Processing 24th sort.
>> Processing 25th sort.
Sorting costs:
 1st sort costs: 0.080754 secs.
 2nd sort costs: 0.090897 secs.
 3rd sort costs: 0.080238 secs.
 4th sort costs: 0.083508 secs.
 5th sort costs: 0.085163 secs.
 6th sort costs: 0.085314 secs.
 7th sort costs: 0.099786 secs.
 8th sort costs: 0.081539 secs.
 9th sort costs: 0.088761 secs.
10th sort costs: 0.087151 secs.
11th sort costs: 0.080943 secs.
12th sort costs: 0.081856 secs.
13th sort costs: 0.104497 secs.
14th sort costs: 0.085793 secs.
15th sort costs: 0.079422 secs.
16th sort costs: 0.086373 secs.
17th sort costs: 0.083243 secs.
18th sort costs: 0.083100 secs.
19th sort costs: 0.083350 secs.
20th sort costs: 0.106145 secs.
21st sort costs: 0.100546 secs.
22nd sort costs: 0.099786 secs.
23rd sort costs: 0.091039 secs.
24th sort costs: 0.083897 secs.
25th sort costs: 0.088301 secs.
0.080754, 0.090897, 0.080238, 0.083508, 0.085163, 0.085314, 0.099786, 0.081539, 0.088761, 0.087151, 0.080943, 0.081856, 0.104497, 0.085793, 0.079422, 0.086373, 0.083243, 0.083100, 0.083350, 0.106145, 0.100546, 0.099786, 0.091039, 0.083897, 0.088301, 
>>>>>>>>>> HEAP SORT ENDS <<<<<<<<<<
```

**圖表**

5 種 Sorting 演算法

![5 Sorting Algorithms](https://i.imgur.com/tdye901.png) 

Bubble Sort 

![Bubble Sort](https://i.imgur.com/Hmue76o.png)

Insertion Sort 

![Insertion Sort](https://i.imgur.com/FpPXJdM.png)

Selection Sort 

![Selection Sort](https://i.imgur.com/MXjRdAb.png)

Quick Sort 

![Quick Sort](https://i.imgur.com/kqDYHbu.png)

Heap Sort 

![Heap Sort](https://i.imgur.com/pR2Uu0v.png)

---

### 五、討論

**執行結果說明**

* 輔助輸出：
   * 如 `>> Processing 25th sort.` 輸出為了便於檢查當前進度，如有卡在某處排序過程中則可以找出問題所在；
   * 如 `>> 300000 numbers:` 提示當前進行排序的資料筆數，可大致估計在此處排序的時間是否有誤，比如在測試時將筆數錯誤設定為 15000 筆，檢查排序時間都比 100000 筆短，發現到筆數有誤才即時修正
   * 如 `>>>>>>>>>> HEAP SORT STARTS <<<<<<<<<<` 標示當前排序演算法
* 條件輸出：在程式碼中，有設定條件如果排序筆數少於 100 筆會印出每次排序前、後的結果便於程式撰寫初期除錯用途，尤其在 heap sort 部分因為建構與輸出部分常常邏輯錯誤，測試時有將建構、輸出每次步驟的結果輸出
* 時間輸出：排序時間輸出有兩部分，條列式便於查看是否有異常值；逗號分隔輸出便於複製用
```
Sorting costs:
 1st sort costs: 0.080754 secs.
 2nd sort costs: 0.090897 secs.
 3rd sort costs: 0.080238 secs.
 4th sort costs: 0.083508 secs.
 5th sort costs: 0.085163 secs.
 6th sort costs: 0.085314 secs.
 7th sort costs: 0.099786 secs.
 8th sort costs: 0.081539 secs.
 9th sort costs: 0.088761 secs.
10th sort costs: 0.087151 secs.
11th sort costs: 0.080943 secs.
12th sort costs: 0.081856 secs.
13th sort costs: 0.104497 secs.
14th sort costs: 0.085793 secs.
15th sort costs: 0.079422 secs.
16th sort costs: 0.086373 secs.
17th sort costs: 0.083243 secs.
18th sort costs: 0.083100 secs.
19th sort costs: 0.083350 secs.
20th sort costs: 0.106145 secs.
21st sort costs: 0.100546 secs.
22nd sort costs: 0.099786 secs.
23rd sort costs: 0.091039 secs.
24th sort costs: 0.083897 secs.
25th sort costs: 0.088301 secs.
0.080754, 0.090897, 0.080238, 0.083508, 0.085163, 0.085314, 0.099786, 0.081539, 0.088761, 0.087151, 0.080943, 0.081856, 0.104497, 0.085793, 0.079422, 0.086373, 0.083243, 0.083100, 0.083350, 0.106145, 0.100546, 0.099786, 0.091039, 0.083897, 0.088301, 
```

**結果分析**

* 由於 Bubble sort, Insertion sort & Selection sort 的時間複雜度較高 O(n^2)，在大量運算時表現較差，相比平均複雜度為 O(nlog(n)) 的 Quick sort & Heap sort 在 n 很大時，速度差距很大
* 根據觀察，Bubble sort 排序過程速度最慢，Selection sort 其次，Insertion sort 比前兩者快，雖然三者排序都用到兩個迴圈
   * 分析發現 Bubble sort 在內部迴圈每次都跑完陣列所有值，而另外兩者都隨着排序進行內部迴圈需要跑的陣列長度都在變短，感覺我寫的 Bubble sort 也可以把內部迴圈進行優化，因為每次內部迴圈排序都會找到最大值排到末尾，內部迴圈走訪的陣列長度可以逐漸變短；
   * 另外，Selection sort 與 Insertion sort 雖然內部迴圈要走訪的陣列長度都在變短，但 Insertion sort 仍然較快，分析發現原因在於 Selection sort 在尋找子陣列的最大值時一定要走訪整個子陣列才能確定找到最大的值，而 Insertion sort 在每次插入值到子陣列時，只需要找到正確大小的位置就會停止子陣列的走訪，所以總體看來每次內部迴圈走訪時 Insertion sort 進行比較的次數一定少於 Selection sort，速度更快
   * 至於 Quick sort 與 Heap sort，觀察結果 Quick sort 速度比 Heap sort 速度稍微快一點，**猜想**可能是因為 Heap sort 有建構與輸出兩步驟，時間複雜度為 O(n) + O(nlog(n)) = O(nlog(n))，或許會導致速度稍微慢一點？或許原因並沒有這樣簡單，可能也根公式推導過程有關，之後可能要向老師請教一下

---

### 六、心得

* 這次的作業既是實作一下課堂第二章學到的演算法，也更了解了這幾種演算法建構的邏輯；通過排序時間上的差別，更直觀的了解到時間複雜度的差別對演算法速度的影響十分大
* 一開始選擇程式語言時打算用 Python 實作，但當實際用 Bubble sort 跑了 50000 筆資料時才發現電腦短時間根本跑不完，才決定轉移到 C 語言來實作，當時覺得很久沒碰過 C 語言擔心會要寫很久甚至寫不完像 Quick sort 或 Heap sort 這樣的演算法，但完成過程中，不過是遇到問題就 Google 搜尋解決方法，從回憶起最簡單的陣列如何建立、甚至是副程式要如何建立到 header 檔案如何設定、傳址取值方法等等；到後來才發現，只要是想到的邏輯，基本上都可以寫出來，或許程式語言的精髓就在於邏輯，語法什麼的熟悉了就不是難點了
* 這次由於時間有點來不及，本來打算把輸出時間花費的部分輸出 csv 檔，還有打算把五個演算法的 function 通過迴圈或 enumeration 方式跑一遍，現在只是採用五個 function 分別跑過每個演算法與印出 25 次排序的結果
* 另外，在根據演算法的邏輯實作時遇到了許多坑：在完成 Quick sort 時，一開始認為當陣列剩餘 2 個值就排序完成、在分割兩個子陣列時沒有包含相遇點的值；在完成 Heap sort 時，根據第一個參考連結的說明，在輸出過程時 parent 節點未考慮右 child 的存在，導致在測試排序結果時一直沒有找不到錯誤原因，還有，由於我的陣列不像網上許多寫法陣列第一個元素的值為陣列長度，導致取得 parent 的 index 需要 `(child_index - 1) / 2`，這個坑在建構 heap tree 時沒發現，直到檢查建構與輸出每一步過程的陣列時才發現

---
