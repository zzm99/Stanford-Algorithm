// Karatsuba Multiplication
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

string multiply(string x, string y);
string simplyMultiply(string x, string y);
int string2int(string x);
string int2string(int x);
string add(string x, string y);
string Minus(string x, string y);
string addZero(string x, int zeroNum);
string addPreZero(string x, int zeroNum);
string reverseString(string s);
int Max(int x, int y);

int Max(int x, int y){
    /*
     * Description: find max number
     * Input: Two integers
     * Output: Return max between x and y
     */
    return x > y ? x : y;
}

int string2int(string x){
    /*
     * Description: Change string to int
     * Input: A string
     * Output: Return a integer represents origin string
     */
    int n = x.length();
    int s = 0;
    for(int i = 0; i < n; ++i){
        s = 10 * s + x[i] - '0';
    }
    return s;
}

string int2string(int x){
    /*
     * Description: Change int to string
     * Input: An integers
     * Output: Return a string represents origin integers
     */
    string result;
    stringstream stream;
    stream << x;
    stream >> result;
    return result;
}

string simplyMultiply(string x, string y){
    /*
     * Description: multiply two string, whose length = 1
     * Input: Two string
     * Output: Return product
     */
    if(x.empty() | y.empty()){
        return int2string(0);
    }else{
        int result = string2int(x) * string2int(y);
        return int2string(result);
    }
}

string reverseString(string s){
    /*
     * Description: Reverse the string
     * Input: A string
     * Output: Return a reversed string
     */
    string result;
    for(auto temp = s.end() - 1; temp >= s.begin(); --temp){
        result.push_back(*temp);
    }
    return result;
}

string addZero(string x, int zeroNum){
    /*
     * Description: Add zero between a string, simulate x * 10^n
     * Input: A string, a integer represents zero's number after it
     * Output: Return a string, which is added n's 0
     */
    string temp(zeroNum, '0');
    x.append(temp);
    return x;
}

string addPreZero(string x, int zeroNum){
    /*
     * Description: Add zero before a string to fill in empty place
     * Input: A string, a integer represents zero's number
     * Output: Return a string, which is added n's 0 before it
     */
    string temp(zeroNum, '0');
    temp.append(x);
    return temp;
}

string add(string x, string y){
    /*
     * Description: Add two string
     * Input: Two strings
     * Output: Return their sum
     */
    int i, more = 0, tempSum = 0;
    x = reverseString(x);
    y = reverseString(y);
    int maxSize = Max(x.size(), y.size());
    string s(maxSize + 1, '0');
    for(i = 0; i < x.size() && i < y.size(); ++i){
        tempSum = x[i] - '0' + y[i] - '0' + more;
        s[i] = tempSum % 10 + '0';
        more = tempSum / 10;
    }
    if(i != y.size()){
        for(; i < y.size(); ++i){
            tempSum = y[i] - '0' + more;
            s[i] = tempSum % 10 + '0';
            more = tempSum / 10;
        }
    }else if(i != x.size()){
        for(; i < x.size(); ++i){
            tempSum = x[i] - '0' + more;
            s[i] = tempSum % 10 + '0';
            more = tempSum / 10;
        }
    }
    if(more != 0){
        s[i] += more;
    }else{
        s.pop_back();
    }
    s = reverseString(s);
    return s;
}

string Minus(string x, string y){
    /*
     * Description: Minus between strings
     * Input: Two strings
     * Output: Return their difference
     */
    int i;
    x = reverseString(x);
    y = reverseString(y);
    string s(x.size(), '0');
    for(i = 0; i < y.size(); ++i){
        if(x[i] < y[i]){
            x[i] += 10;
            x[i + 1] -= 1;
        }
        s[i] = x[i] - y[i] + '0';
    }
    for(; i < x.size(); ++i){
        s[i] = x[i];
    }
    for(i = x.size() - 1; i > 0; --i){
        if(s[i] == '0'){
            s.pop_back();
        }else{
            break;
        }
    }
    s = reverseString(s);
    return s;
}

string multiply(string x, string y){
    /*Description: Multiply between two strings
     *Input: Two strings, represents two positive integers
     *Output: Return product of x and y
    */

    int xSize = x.length();
    int ySize = y.length();
    int n = Max(xSize, ySize);
    if(n == xSize){
        y = addPreZero(y, n - ySize);
    }else{
        x = addPreZero(x, n - xSize);
    }
    if(n == 1){
        return simplyMultiply(x, y);
    }

    string xLeft = x.substr(0, n / 2);
    string xRight = x.substr(n / 2);
    string yLeft = y.substr(0, n / 2);
    string yRight = y.substr(n / 2);

    string p1 = multiply(xLeft, yLeft);
    string p2 = multiply(xRight, yRight);
    string p3 = multiply(add(xLeft, xRight), add(yLeft, yRight));
    string p4 = Minus(Minus(p3, p1), p2);

    string result = add(add(addZero(p1, 2 * (n - n / 2)),
                            addZero(p4, n - n / 2)), p2);
    return result;
}



int main()
{
    string s1("3141592653589793238462643383279502884197169399375105820974944592");
    string s2("2718281828459045235360287471352662497757247093699959574966967627");
    cout << multiply(s1, s2) << endl;
    return 0;
}


