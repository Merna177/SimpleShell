#include <iostream>
#include <pthread.h>
using namespace std;
int MAX;
int arr[20000];
void inputFromFile(){
   scanf("%d",&MAX);
   for(int i=0;i<MAX;i++)
      scanf("%d",&arr[i]);
}
void mergeit(int l,int m,int r)
{
    int i, j, k;
    ///length of first subarray
    int n1 = m - l + 1;
///length of second subarray;
    int n2 =  r - m;

    /* create temp arrays */
    int L[n1], R[n2];

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1+ j];

    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void *mergeSortUsingThreads(void* threadrange)
{
    pair<int,int> ThreadPair= *(pair<int,int> *)threadrange;
///base case is that my range contain only one element
    if(ThreadPair.first==ThreadPair.second)return NULL;
///get middle of array to divide it to 2 subarrays;
    int mid=(ThreadPair.first+ThreadPair.second)/2;
    pthread_t leftDivision,rightDivision;
    ///instead of rescursive calls of merge function we make it but with using threads as each thread make a recursive call
    pthread_create(&leftDivision, NULL, mergeSortUsingThreads, (void *)new pair<int,int>(ThreadPair.first,mid));
    pthread_create(&rightDivision, NULL, mergeSortUsingThreads, (void *)new pair<int,int>(mid+1,ThreadPair.second));
    pthread_join(leftDivision,NULL);
    pthread_join(rightDivision,NULL);
    ///let do the merging (conquer)
    mergeit(ThreadPair.first,mid,ThreadPair.second);
    pthread_exit(&leftDivision);
    pthread_exit(&rightDivision);
}
int main()
{
freopen("input.in" , "r",stdin);
freopen("output.out" , "w",stdout);
inputFromFile();
  clock_t start, end;
     double cpu_time_used;

     start = clock();
pthread_t FirstThread;
 pthread_create(&FirstThread, NULL , mergeSortUsingThreads, (void *)new pair<int,int>(0,MAX-1));
 pthread_join(FirstThread,NULL);
  end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
 for(int i=0;i<10;i++){
 printf("%d ",arr[i]);}
printf("\n %lf sec",cpu_time_used);
    return 0;
}
