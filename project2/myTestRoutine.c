#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "project2.c"

void randList(int * list, int length);
void inOrderList(int * list, int length);
void reverseOrderList(int  * list, int length);
int inOrder(int * list, int length);


int main(int argc, char ** argv)
{
    /*int i;
  for(i = 0; i < argc;i++)
  {
    printf("%s ",argv[i]);
  }
  printf("\n");*/
    int listSize;
    int reState, inState, randState;
    //double intime, retime, randtime;
    int inResult, reResult, randResult;
    if(argc == 1)
	{
	    listSize = 10000;
	    reState = 1;
	    inState = 1;
	    randState = 1;
	}
    else if(argc == 5)
	{
	    listSize = atoi(argv[4]);
	    inState = atoi(argv[1]);
	    reState = atoi(argv[2]);
	    randState = atoi(argv[3]);
	}
    else if(argc == 2)
	{
	    listSize = atoi(argv[1]);
	    inState = 1;
	    reState = 1;
	    randState = 1;
	}
    else if(argc == 4)
	{
	    inState = atoi(argv[1]);
	    reState = atoi(argv[2]);
	    randState = atoi(argv[3]);
	    listSize = 10000;
	    if((inState > 1) || (reState > 1) || (randState > 1))
		{
		    printf("Usage: a.out inState reState randState\n");
		    return 1;
		}
	}
    else
	{
	    return 1;
	}
    srand(time(NULL));
    int * reverseList;
    int * orderedList;
    int * randomList;
    if(reState)
	{
	    reverseList = malloc(sizeof(int) * listSize);
	    reverseOrderList(reverseList, listSize);
	}
    if(inState)
	{
	    orderedList = malloc(sizeof(int) * listSize);
	    inOrderList(orderedList, listSize);
	}
    if(randState)
	{
	    randomList = malloc(sizeof(int) * listSize);
	    randList(randomList, listSize);
	}
    double before = clock();
    double lapse = clock();
    double prepTime = clock();
    printf("Prep Time = %lf seconds\n", (prepTime / CLOCKS_PER_SEC));
    if(inState)
	{
	    printf("-----In Order List-----\n");
	    before = clock();
	    sort(orderedList, listSize);
	    lapse = clock() - before;
	    printf("sort time: %lf\n", (lapse / CLOCKS_PER_SEC));
	    inResult = inOrder(orderedList, listSize);
	    if(!inResult)
		{
		    printf("************ERROR: was not sorted\n");
		}
	    free(orderedList);
	}
    if(reState)
	{
	    printf("-----Reverse Order List-----\n");
	    before = clock();
	    sort(reverseList, listSize);
	    lapse = clock() - before;
	    printf("sort time: %lf\n", (lapse / CLOCKS_PER_SEC));
	    reResult = inOrder(reverseList, listSize);
	    if(!reResult)
		{
		    printf("************ERROR: was not sorted\n");
		}
	    free(reverseList);
	}
    if(randState)
	{
	    printf("-----Random Order List-----\n");
	    before = clock();
	    sort(randomList, listSize);
	    lapse = clock() - before;
	    printf("sort time: %lf\n", (lapse / CLOCKS_PER_SEC));
	    randResult = inOrder(randomList, listSize);
	    if(!randResult)
		{
		    printf("************ERROR: was not sorted\n");
		}
	    free(randomList);
	} 
    return 0;
}

void reverseOrderList(int * list, int length)
{
    int i;
    for(i = 0; i < length; i++)
	{
	    list[i] = (length - i);
	}
}

void inOrderList(int * list, int length)
{
    int i;
    for(i=0; i < length; i++)
	{
	    list[i] = i + 1;
	}
}

void randList(int * list, int length)
{
    int i;
    for(i=0; i < length; i++)
	{
	    list[i] = ((double)rand() / (double)RAND_MAX) * length;
	}
}

int inOrder(int * list, int length)
{
    int ret = 1;
    int i;
    for(i=0; i < (length - 1); i++)
	{
	    if(list[i] > list[i + 1])
		{
		    ret = 0;
		}
	}
    return ret;
}
