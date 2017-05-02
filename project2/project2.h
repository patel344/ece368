#include <stdio.h>
#include <stdlib.h>

int check(int list[], int n){
    int i;
    int count = 0;
    for(i = 1; i < (n / 2 + 1); i++){
	if(list[i-1] > list[i]){
	    count++;
	}
	if(list[n-i] < list[n-i-1]){
	    count++;
	}
    }
    return(count);
}

void myInsertionSort(int list [], int offset, int end) {
int x, y, temp;
 for (x=offset; x<end; ++x) {
     for (y=x; y>offset && list[y-1]>list[y]; y--) {
	 temp = list[y];
	 list[y] = list[y-1];
	 list[y-1] = temp;
     }
 }
}
void radix_sort(int list [], int offset, int end, int shift) {
int x, y, value, temp;
int last[256] = { 0 }, pointer[256];

for (x=offset; x<end; ++x) {
    ++last[(list[x] >> shift) & 0xFF];
}

last[0] += offset;
pointer[0] = offset;

for (x=1; x<256; ++x) {
    pointer[x] = last[x-1];
    last[x] += last[x-1];
}

for (x=0; x<256; ++x) {
     while (pointer[x] != last[x]) {
	 value = list[pointer[x]];
         y = (value >> shift) & 0xFF;
         while (x != y) {
	     temp = list[pointer[y]];
	     list[pointer[y]++] = value;
	     value = temp;
	     y = (value >> shift) & 0xFF;
	 }
         list[pointer[x]++] = value;
    }
}

if (shift > 0) {
    shift -= 8;
    for (x=0; x<256; ++x) {
	temp = x > 0 ? pointer[x] - pointer[x-1] : pointer[0] - offset;
	if (temp > 64) {
	    radix_sort(list, pointer[x] - temp, pointer[x], shift);
	} else if (temp > 1) {
	    myInsertionSort(list, pointer[x] - temp, pointer[x]);
	}
    }
}
}

void sort(int list[], int n){
    if(check(list,n) < 100){ 
    	myInsertionSort(list,0,n-1); 
    } 
    else{
        int i;
        for(i = 0; i<n; i++){
        	list[i] ^= 0x80000000;
        }
        radix_sort(list, 0, n, 24);
        for(i = 0; i<n; i++){
        	list[i] ^= 0x80000000;
        }
    }
    return;
}

