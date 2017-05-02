#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void quick_sort(int list [],int n);
void quick_sort2(int list[], int lower, int upper);;
void sort(int list [], int n);

int getRandomNumber(){
    int randNum = rand();
    //if((randNum % 10) == 8){
	//return(-1*randNum);
	//}
    //else{
	return(randNum);
	//}
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
	fprintf(fp, "%d\n", array[i]);
    }
    return;
}

int cmpfunc (const void * a, const void * b)
{
    return ( *(int*)a - *(int*)b );
}

int main(int argc, char** argv){
    srand(time(NULL));
    time_t start, finish;
    int array1[10000];
    int array2[10000];

    //Create Arrays
    initializeArray(array1,10000);
    randomArrayFill(array1,10000);

    initializeArray(array2,10000);
    randomArrayFill(array2,10000);

    //METHOD 1
    FILE* fp1 = fopen("mySort", "wb");
    start = clock();
    sort(array1,0,10000-1);
    finish = clock();
    printf("Sorting Time: %7.21f\n", (double)(finish - start) / CLOCKS_PER_SEC);
    outputArray(array1, 10000, fp1);
    fclose(fp1);

    //METHOD 1 TEST
    FILE* fp1_test = fopen("testSort", "wb");
    qsort(array1,10000,sizeof(int), cmpfunc);
    outputArray(array1,10000,fp1_test);
    fclose(fp1_test);

    //MEDTHOD 2
    /* FILE* fp2 = fopen("mySort", "wb");
    start = clock();
    quick_sort2(array2,0,9);
    finish = clock();
    printf("Sorting Time: %7.21f\n", (double)(finish - start) / CLOCKS_PER_SEC);
    outputArray(array2, 10000, fp2);
    fclose(fp2);*/
    return 0;

}
