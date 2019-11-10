#include <iostream>
#include <ctime>
using namespace std;

bool ShellSort(int * pUnSortAry, int nSize){
	if(pUnSortAry == nullptr || nSize <= 0){
		return false;
	}
	int nGrp = 0;
	for(nGrp = 1; nGrp <= (nSize-1)/3; nGrp=nGrp*3+1);
	for( ; nGrp > 0; nGrp /= 3){
		for(int iIndex = nGrp; iIndex < nSize; iIndex++){ 
			int nTemp = pUnSortAry[iIndex];
			int jIndex = iIndex - nGrp;
			for( ; jIndex >= 0 && pUnSortAry[jIndex] > nTemp; jIndex -= nGrp){
				pUnSortAry[jIndex+nGrp] = pUnSortAry[jIndex];
			}
			pUnSortAry[jIndex+nGrp] = nTemp;
		}
	}
	return true;
}

void PrintData(int * arr, int n){
	for(int i=0; i<n; i++){
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main(){
	srand(time(NULL));

    int nArry[30] = { 0 };

    for (int jIndex = 0; jIndex < 10; jIndex++)
    {
      for (int iIndex = 0; iIndex < sizeof(nArry) / sizeof(nArry[0]); iIndex++)
      {
        nArry[iIndex] = rand() % 150;
      }
      printf("排序前:");
      PrintData(nArry, sizeof(nArry) / sizeof(nArry[0]));
      ShellSort(nArry, sizeof(nArry) / sizeof(nArry[0]));
      printf("排序后:");
      PrintData(nArry, sizeof(nArry) / sizeof(nArry[0]));
    }
    return 0;
}
