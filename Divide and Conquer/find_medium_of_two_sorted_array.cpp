#include<iostream>
using  namespace std;
// O(log(N))

int MidSerch(int a[], int b[], int la, int ra, int lb, int rb) {
	int ma = (la + ra) / 2;
	int mb = (lb + rb+1) / 2;
	if (la == ra&&lb != rb) {
		if (a[la] > b[rb])return b[rb];
		else return a[la];
	}
	if (lb == rb&&la != ra) {
		if (b[lb] > a[ra])return a[ra];
		else return b[lb];
	}

	if (la == ra&&lb == rb) {
		if (a[la] > b[lb])return b[lb];
		else return a[la];
	}
	else
		{    
			if (la == ra - 1 && lb == rb - 1) 
			{
				ma = (la + ra) / 2;//第一个序列求中位数方法不变
				mb = (lb + rb) / 2;//第二个序列变为与第一序列相同的方法求得中位数
				//但由于元素个数只有两个，所以括号内可写为：mb = mb - 1；
			}
			if (a[ma]==b[mb])
			{
				return a[ma];
			}
			else if (a[ma] > b[mb]) {
				MidSerch(a, b, la, ma ,mb, rb);
			}
			else{
				MidSerch(a, b, ma, ra, lb, mb);
			}

		}
} 


int main() {
	int n;
	cin >> n;
	int *a = new int[n];
	int *b = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> a[i];
	}
	for (int i = 0; i < n; i++)
	{
		cin >> b[i];
	}

	cout<<MidSerch(a, b, 0, n - 1, 0, n - 1);

}