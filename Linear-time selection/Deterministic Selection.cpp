#include <iostream>

using namespace std;

int Quick_Sort(int A[],int l,int r, int target);

void swap(int &a, int &b)
{
    int c = a;
    a = b;
    b = c;
}

void insersion_sort(int A[] , int len)
{
	for(int j = 1; j<len; j++){
		int i = j -1;
		int key = A[j];
		while(i>0 && A[i] > key){
			A[i+1] = A[i];
			i--;
		}
		A[i+1] = key;
	}
}

int ChoosePivot(int A[], int l, int r)
{
	int size = r-l+1;
	int sub_num = size/5 ;
	int i, j, k=0;
	int tmp[sub_num][5];
	int Sub[sub_num];

	for(i=0; i<sub_num; i++){
		for(j=0; i<5; j++)
			tmp[i][j] = A[k++];
		Sub[i] = Quick_Sort(tmp[i], 0, 4, 2);
	}

	return Quick_Sort(Sub , 0, sub_num-1, sub_num/2);
}

int partition(int A[],int l,int r,int M)
{
	int x = A[M];
	int i = l;
	int j = l+1;

	swap(A[M],A[l]);

	for(;j<=r;j++){
		if(A[j]<=x){
			++i;
			swap(A[i],A[j]);
		}
	}

	swap(A[i],A[l]);
	return i;
}

int Quick_Sort(int A[],int l,int r, int target)
{
    if(target > r)
        return -1;
    if(l<r){
    	if( r-l+1 <10){
			int tmp[r-l+1];
			for(int i=l;i<r-l+1;i++)
				tmp[i] = A[i];
			insersion_sort( tmp , r-l+1 );
			return tmp[target];
		}

		int M = ChoosePivot(A,l,r);

        int q = partition(A,l,r,M);

        if(q==target)
        	return A[q];
        else if(q>target)
        	return Quick_Sort(A,l,q-1,target);
        else
        	return Quick_Sort(A,q+1,r,target);
    }
    else return A[l];
}

int main()
{
    int A[] = {3,4,6,1,5,9,2,8,7};
    int n;
    for(int i=0;i<9;i++)
        cout<<A[i]<<' ';
    cout<<endl;
    cin>>n;

    cout<<"The "<<n<<"th largest number in the array is: "<<Quick_Sort(A,0,8,n-1);
    return 0;
}
/**
 *  select(L,k)
    {
    if (L has 10 or fewer elements)
    {
        sort L
        return the element in the kth position
    }

    partition L into subsets S[i] of five elements each
        (there will be n/5 subsets total).

    for (i = 1 to n/5) do
        x[i] = select(S[i],3)

    M = select({x[i]}, n/10)

    partition L into L1<M, L2=M, L3>M
    if (k <= length(L1))
        return select(L1,k)
    else if (k > length(L1)+length(L2))
        return select(L3,k-length(L1)-length(L2))
    else return M
    }
 */