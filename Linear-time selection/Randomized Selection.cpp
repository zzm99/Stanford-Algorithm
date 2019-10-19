#include <iostream>
#include <cstdlib>
 
using namespace std;
 
int random_partition(int* arr, int start, int end)
{
    int pivotIdx = start + rand() % (end-start+1);
    int pivot = arr[pivotIdx];
    swap(arr[pivotIdx], arr[end]); // move pivot element to the end
    pivotIdx = end;
    int i = start -1;
 
    for(int j=start; j<=end-1; j++)
    {
        if(arr[j] <= pivot)
        {
            i = i+1;
            swap(arr[i], arr[j]);
        }
    }
 
    swap(arr[i+1], arr[pivotIdx]);
    return i+1;
}
 
int random_selection(int* arr, int start, int end, int k)
{
    if(start == end)
        return arr[start];
 
    if(k ==0) return -1;
 
    if(start < end)
    {
 
        int mid = random_partition(arr, start, end);
        int i = mid - start + 1;
        if(i == k)
            return arr[mid];
        else if(k < i)
            return random_selection(arr, start, mid-1, k);
        else
            return random_selection(arr, mid+1, end, k-i);
    }
 
}
int main()
{
    int A[] = {9,5,7,1,10,2,3};
    int loc = random_selection(A, 0,6,5);
    cout << "the 5th smallest is  " << loc << endl;
    return 0;
}