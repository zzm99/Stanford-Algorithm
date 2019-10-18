/*
For some fixed N, an array A is beautiful if it is a permutation of the integers 1, 2, ..., N, such that:

For every i < j, there is no k with i < k < j such that A[k] * 2 = A[i] + A[j].

Given N, return any beautiful array A.  (It is guaranteed that one exists.)

 

Example 1:

Input: 4
Output: [2,1,4,3]
Example 2:

Input: 5
Output: [3,1,2,5,4]
*/

class Solution {
public:
    int getmid(vector<int>& v, int start, int end, int mask){
        int j=start;
        for(int i=start; i<=end; i++){
            if((v[i] & mask) != 0){
                swap(v[i], v[j]);
                j++;
            }
        }
        return j;
    }
    
    void sort(vector<int>& res, int start, int end, int mask){
        if(start >= end) return;
        int mid = getmid(res, start, end, mask);
        sort(res, start, mid-1, mask << 1);
        sort(res, mid, end, mask << 1);
    }
    
    vector<int> beautifulArray(int N) {
        vector<int> ret;
        for(int i=0; i<N; i++) ret.push_back(i+1);
        sort(ret, 0, N-1, 1);
        return ret;
    }
};