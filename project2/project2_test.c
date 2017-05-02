#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<time.h>
#define NUM_ELE 1000000

void quick_sort(int list [],int n);
void quick_sort2(int list[], int lower, int upper);
void sort(int list [], int n);
void myInsertionSort(int list[], int, int);
void sort3(int input[], int lowIndex, int highIndex);
void radix_sort(int *array, int offset, int end, int shift);
int getRandomNumber(){
    int randNum = rand();
    if((randNum % 10) == 8){
	return(-1*randNum);
	}
    else{
	return(randNum);
	}
}
void initializeArray(int* array, int size){
    int i;
    for(i = 0; i < size; i++){
	array[i] = 0;
    }
    return;
}
void randomArrayFill(int* array, int size){
    int i;
    for(i = 0; i < size; i++){
	array[i] = getRandomNumber();
    }
    return;
}
void outputArray(int* array, int size, FILE* fp){
    int i;
    for(i = 0; i < size; i++){
	fprintf(fp,"%d\n", array[i]);
    }
    return;
}

int cmpfunc (const void * a, const void * b)
{
    if((*(int*)a) <= (*(int*)b)){
	return -1;
    }
    else{
	return 1;
    }
    //return ( *(int*)a - *(int*)b );
}

int main(int argc, char** argv){
    srand(time(NULL));
    time_t start, finish;
    int* array1 = malloc(sizeof(int) * NUM_ELE);
    int* array3 = malloc(sizeof(int) * NUM_ELE);
    //int array4[7] = {3, -1, 2, 31, 4, 1, 0};
    //int* array5 = malloc(sizeof(int) * NUM_ELE);
    int* array6 = malloc(sizeof(int) * NUM_ELE);
    int i;
    FILE* fp1_intial = fopen("array6","wb");
    FILE* fp3_intial = fopen("array3", "wb");
    //Create Arrays
    initializeArray(array1,NUM_ELE);
    initializeArray(array6,NUM_ELE);
    randomArrayFill(array1,NUM_ELE);
    /* qsort(array6, NUM_ELE, sizeof(int), cmpfunc); */
    /* outputArray(array6,NUM_ELE,fp1_intial); */
    
    for(i = 0; i < NUM_ELE; i++){
    	array3[i] = array1[i];
    }
    for(i = 0; i < NUM_ELE; i++){
    	array6[i] = 498384;
	/* if(i > 990000){ */
	/*     array6[i] = rand(); */
	/* } */
    }
    //qsort(array6, NUM_ELE, sizeof(int), cmpfunc);
    //int counter = 0;
    /* for(i = 0; i < NUM_ELE; i++){ */
    /* 	int index1 = rand() % NUM_ELE; */
    /* 	int index2 = rand() % NUM_ELE; */
    /* 	int temp; */
    /* 	temp = array6[index1]; */
    /* 	array6[index1] = array6[index2]; */
    /* 	array6[index2] = temp; */
    /* 	counter++; */
    /* 	if(counter >= 200){ */
    /* 	    break; */
    /* 	} */
    /*  }	  */
    // memcpy(array3,array6,sizeof(int) * NUM_ELE);
    outputArray(array6,NUM_ELE,fp3_intial);
    fclose(fp1_intial);
    fclose(fp3_intial);
    
    //METHOD 1
    FILE* fp1 = fopen("mySort", "wb");
    start = clock();
    sort(array1,NUM_ELE);
    //quick_sort2(array1,0,NUM_ELE-1);
    //sort3(array1,0,NUM_ELE  - 1);
    /* for(i = 0; i<NUM_ELE; i++){ */
    /* 	array1[i] ^= 0x80000000; */
    /* } */
    /* radix_sort(array1, 0, NUM_ELE, 24); */
    /*  for(i = 0; i<NUM_ELE; i++){ */
    /* 	array1[i] ^= 0x80000000; */
    /* } */
    finish = clock();
    printf("Sorting Time: %7.21f\n", (double)(finish - start) / CLOCKS_PER_SEC);
    outputArray(array1, NUM_ELE, fp1);
    fclose(fp1);

    //METHOD 1 TEST
    FILE* fp1_test = fopen("testSort", "wb");
    start = clock();
    qsort(array3,NUM_ELE,sizeof(int), cmpfunc);
    finish = clock();
    printf("Sorting Time library: %7.21f\n", (double)(finish-start) / CLOCKS_PER_SEC);
    outputArray(array3,NUM_ELE,fp1_test);
    fclose(fp1_test);
    return 0;

}
/* void quick_sort2(int list[], int lower, int upper){ */
/*     int left = lower; */
/*     int lt = lower; */
/*     int gt = upper; */
/*     int right = upper; */
/*     int i = lower + 1; */
/*     if(upper <= 1){ */
/* 	 return; */
/*     } */
/*     if(upper <= lower){ */
/* 	return; */
/*     } */
/* 	int center = (lower + upper) / 2; */
/* 	int temp = 0; */
/* 	if(list[center] < list[lower]){ */
/* 	    temp = list[center]; */
/* 	    list[center] = list[lower]; */
/* 	    list[lower] = temp; */
/* 	} */
/* 	if(list[upper] < list[lower]){ */
/* 	    temp = list[upper]; */
/* 	    list[upper] = list[lower]; */
/* 	    list[lower] = temp; */
/* 	} */
/* 	if(list[upper] < list[center]){ */
/* 	    temp = list[upper]; */
/* 	    list[upper] = list[center]; */
/* 	    list[center] = temp; */
/* 	} */

/* 	temp = list[center]; */
/* 	list[center] = list[lower]; */
/* 	list[lower] = temp; */
/* 	int swivel = list[lower]; */

/* 	while(i <= gt){ */
/* 	    if(list[i] < swivel){ */
/* 		temp = list[lt++]; */
/* 		list[lt++] = list[i++]; */
/* 		list[i++] = temp; */
/* 	    } */
/* 	    else if(list[i] > swivel){ */
/* 		temp = list[i]; */
/* 		list[i] = list[--gt]; */
/* 		list[--gt] = temp; */
/* 	    } */
/* 	    else{ */
/* 		i++; */
/* 	    } */
/* 	} */
/* 	quick_sort2(list, lower, lt-1); */
/* 	quick_sort2(list, gt+1, upper); */
/* 	   /\*  while(left < upper && list[++left] <= swivel){} *\/ */
/* 	/\*     while(right > 0 && swivel < list[--right]){} *\/ */
/* 	/\*     if(left >= right){ *\/ */
/* 	/\* 	break; *\/ */
/* 	/\*     } *\/ */
/* 	/\*     temp = list[left]; *\/ */
/* 	/\*     list[left] = list[right]; *\/ */
/* 	/\*     list[right] = temp; *\/ */
/* 	/\* } *\/ */
/* 	/\* temp = list[right]; *\/ */
/* 	/\* list[right] = list[lower]; *\/ */
/* 	/\* list[lower] = temp; *\/ */

/*         /\* quick_sort2(list,lower,right-1);  *\/ */
/*         /\* quick_sort2(list,right+1,upper);  *\/ */
/* 	return; */
/* } */



/* /\* void quick_sort(int list[], int n){ *\/ */
  
/* /\*     if(n < 2){   //base case *\/ */
/* /\* 	return; *\/ */
/* /\*     } *\/ */
/* /\*     int lower = 0; *\/ */
/* /\*     int upper = n - 1; *\/ */
/* /\*     int temp = 0; *\/ */
/* /\*     int swivel = list[0];; *\/ */
/* /\*     while(1){ *\/ */
/* /\* 	while(lower < n && list[lower] <= swivel){ //Should it be less than or equal to swivel? *\/ */
/* /\* 	    lower++; *\/ */
/* /\* 	} *\/ */
/* /\* 	while(list[upper] > swivel){ *\/ */
/* /\* 	    upper--; *\/ */
/* /\* 	} *\/ */
/* /\* 	if(lower >= upper){ *\/ */
/* /\* 	    break; *\/ */
/* /\* 	} *\/ */
/* /\* 	temp = list[lower]; *\/ */
/* /\* 	list[lower] = list[upper]; *\/ */
/* /\* 	list[upper] = temp;  *\/ */
/* /\* 	//swap(&list[lower],&list[upper]); *\/ */
/* /\*     } *\/ */
/* /\*     temp = list[lower - 1]; *\/ */
/* /\*     list[lower - 1] = list[0]; *\/ */
/* /\*     list[0] = temp; *\/ */
/* /\*     //swap(&list[lower - 1], &list[0]); *\/ */
/* /\*     quick_sort(list, lower - 1); *\/ */
/* /\*     quick_sort(list + lower, n - lower); *\/ */
/* /\*     return; *\/ */
/* /\* } *\/ */

/* void exchange(int list[], int x, int y){ */
/*     int temp = list[x]; */
/*     list[x] = list[y]; */
/*     list[y] = temp; */
/* } */

/*  void sort3(int input[], int lowIndex, int highIndex) { */

/*         if (highIndex<=lowIndex) return; */

/*         int pivot1=input[lowIndex]; */
/*         int pivot2=input[highIndex]; */


/*         if (pivot1>pivot2){ */
/*             exchange(input, lowIndex, highIndex); */
/*             pivot1=input[lowIndex]; */
/*             pivot2=input[highIndex]; */
/*             //sort(input, lowIndex, highIndex); */
/*         } */
/*         else if (pivot1==pivot2){ */
/*             while (pivot1==pivot2 && lowIndex<highIndex){ */
/*                 lowIndex++; */
/*                 pivot1=input[lowIndex]; */
/*             } */
/*         } */


/*         int i=lowIndex+1; */
/*         int lt=lowIndex+1; */
/*         int gt=highIndex-1; */

/*         while (i<=gt){ */

/*             if ((input[i] < pivot1)){ */
/*                 exchange(input, i++, lt++); */
/*             } */
/*             else if ((pivot2 < input[i])){ */
/*                 exchange(input, i, gt--); */
/*             } */
/*             else{ */
/*                 i++; */
/*             } */

/*         } */


/*         exchange(input, lowIndex, --lt); */
/*         exchange(input, highIndex, ++gt); */

/*         sort3(input, lowIndex, lt-1); */
/*         sort3(input, lt+1, gt-1); */
/*         sort3(input, gt+1, highIndex); */

/*     } */


/* void insertion_sort(int *array, int offset, int end) { */
/* int x, y, temp; */
/* for (x=offset; x<end; ++x) { */
/* for (y=x; y>offset && array[y-1]>array[y]; y--) { */
/* temp = array[y]; */
/* array[y] = array[y-1]; */
/* array[y-1] = temp; */
/* } */
/* } */
/* } */
/* void radix_sort(int *array, int offset, int end, int shift) { */
/* int x, y, value, temp; */
/* int last[256] = { 0 }, pointer[256]; */
/* for (x=offset; x<end; ++x) { */
/* ++last[(array[x] >> shift) & 0xFF]; */
/* } */
/* last[0] += offset; */
/* pointer[0] = offset; */
/* for (x=1; x<256; ++x) { */
/* pointer[x] = last[x-1]; */
/* last[x] += last[x-1]; */
/* } */
/* for (x=0; x<256; ++x) { */
/* while (pointer[x] != last[x]) { */
/* value = array[pointer[x]]; */
/* y = (value >> shift) & 0xFF; */
/* while (x != y) { */
/* temp = array[pointer[y]]; */
/* array[pointer[y]++] = value; */
/* value = temp; */
/* y = (value >> shift) & 0xFF; */
/* } */
/* array[pointer[x]++] = value; */
/* } */
/* } */
/* if (shift > 0) { */
/* shift -= 8; */
/* for (x=0; x<256; ++x) { */
/* temp = x > 0 ? pointer[x] - pointer[x-1] : pointer[0] - offset; */
/* if (temp > 64) { */
/* radix_sort(array, pointer[x] - temp, pointer[x], shift); */
/* } else if (temp > 1) { */
/* // std::sort(array + (pointer[x] - temp), array + pointer[x]); */
/* insertion_sort(array, pointer[x] - temp, pointer[x]); */
/* } */
/* } */
/* } */
/* } */

/* inline void swap(int a [], int i, int j) { */
/*         int temp = a[i]; */
/*         a[i] = a[j]; */
/*         a[j] = temp; */
/* } */

/* void dualPivotQuicksort(int list [], int left, int right, int div) { */
/*         int len = right - left; */

/*         if (len < 10) { // insertion sort for tiny array */
/* 	    int i,j; */
/*             for (i = left + 1; i <= right; i++) { */
/*                 for (j = i; j > left && list[j] < list[j - 1]; j--) { */
/*                     swap(list, j, j - 1); */
/*                 } */
/*             } */
/*             return; */
/*         } */
/*         int third = len / div; */

/*         // "medians" */
/*         int m1 = left  + third; */
/*         int m2 = right - third; */

/*         if (m1 <= left) { */
/*             m1 = left + 1; */
/*         } */
/*         if (m2 >= right) { */
/*             m2 = right - 1; */
/*         } */
/*         if (list[m1] < list[m2]) { */
/*             swap(list, m1, left); */
/*             swap(list, m2, right); */
/*         } */
/*         else { */
/*             swap(list, m1, right); */
/*             swap(list, m2, left); */
/*         } */
/*         // pivots */
/*         int pivot1 = list[left]; */
/*         int pivot2 = list[right]; */

/*         // pointers */
/*         int less  = left  + 1; */
/*         int great = right - 1; */

/*         // sorting */
/* 	int k; */
/*         for (k = less; k <= great; k++) { */
/*             if (list[k] < pivot1) { */
/*                 swap(list, k, less++); */
/*             }  */
/*             else if (list[k] > pivot2) { */
/*                 while (k < great && list[great] > pivot2) { */
/*                     great--; */
/*                 } */
/* 		swap(list, k, great--); */

/*                 if (list[k] < pivot1) { */
/*                     swap(list, k, less++); */
/*                 } */
/*             } */
/*         } */
/*         // swaps */
/*         int dist = great - less; */

/*         if (dist < 13) { */
/*            div++; */
/*         } */
/*         swap(list, less  - 1, left); */
/*         swap(list, great + 1, right); */

/*         // subarrays */
/*         dualPivotQuicksort(list, left,   less - 2, div); */
/*         dualPivotQuicksort(list, great + 2, right, div); */

/*         // equal elements */
/*         if (dist > len - 13 && pivot1 != pivot2) { */
/*             for (k = less; k <= great; k++) { */
/*                 if (list[k] == pivot1) { */
/*                     swap(list, k, less++); */
/*                 } */
/*                 else if (list[k] == pivot2) { */
/*                     swap(list, k, great--); */

/*                     if (list[k] == pivot1) { */
/*                         swap(list, k, less++); */
/*                     } */
/*                 } */
/*             } */
/*         } */
/*         // subarray */
/*         if (pivot1 < pivot2) { */
/*             dualPivotQuicksort(list, less, great, div); */
/*         } */
/* } */
/* void sort_2(int list [], int fromIndex, int toIndex) { */
/*         dualPivotQuicksort(list, fromIndex, toIndex - 1, 3); */
/* } */
/* /\* void sort_1(int a [], int n) { *\/ */
/* /\*     sort_2(a, 0, n); *\/ */
/* /\* } *\/ */
/* void insertion_sort(int *array, int offset, int end) { */
/* int x, y, temp; */
/*  for (x=offset; x<end; ++x) { */
/*      for (y=x; y>offset && array[y-1]>array[y]; y--) { */
/* 	 temp = array[y]; */
/* 	 array[y] = array[y-1]; */
/* 	 array[y-1] = temp; */
/*      } */
/*  } */
/* } */
