
//native solution 
void Mul(int** matrixA, int** matrixB, int** matrixC)   
{   
    for(int i = 0; i < 2; ++i)    
    {   
        for(int j = 0; j < 2; ++j)    
        {   
            matrixC[i][j] = 0;   
            for(int k = 0; k < 2; ++k)    
            {   
                matrixC[i][j] += matrixA[i][k] * matrixB[k][j];   
            }   
        }   
    }   
}


// simple conquer solution
template<typename T>
Matrix Square_max_matrix_multiply_recursive(const T &A, const T &B) {
    size_t n = A.rows();
    Matrix C(n, n);
    if (n == 1)
        return C = A.get()*B.get();
    else {
        MatrixRef A_11(A, 0, 0), A_12(A, 0, n / 2), A_21(A, n / 2, 0), A_22(A, n / 2, n / 2);    // 使用一个类MatirxRef
        MatrixRef B_11(B, 0, 0), B_12(B, 0, n / 2), B_21(B, n / 2, 0), B_22(B, n / 2, n / 2);    // 含有三个size_t类型。其中两个实现坐标，一个指明矩阵长度
        MatrixRef C_11(C, 0, 0), C_12(C, 0, n / 2), C_21(C, n / 2, 0), C_22(C, n / 2, n / 2);    // 进行分割
        C_11 = Square_max_matrix_multiply_recursive(A_11, B_11) + Square_max_matrix_multiply_recursive(A_12, B_21);  // Matrix::operator+;
        C_12 = Square_max_matrix_multiply_recursive(A_11, B_12) + Square_max_matrix_multiply_recursive(A_12, B_22);  // MatrixRef::operator=;
        C_21 = Square_max_matrix_multiply_recursive(A_21, B_11) + Square_max_matrix_multiply_recursive(A_22, B_21);  // MatrixRef get the & of Matrix, change MatrixRef changes Matrix too
        C_22 = Square_max_matrix_multiply_recursive(A_21, B_12) + Square_max_matrix_multiply_recursive(A_22, B_22);
    }
    return C;
}



//Strassen's Algorithm

// Matrix1.h
#ifndef MATRIX_H
#define MATRIX_H
#include<iostream>
#include<memory>
#include<vector>
class MatrixRef;
class Matrix {
    friend Matrix operator+(const Matrix &, const Matrix &);
    friend Matrix operator-(const Matrix &, const Matrix &);
    friend std::ostream& operator<<(std::ostream&, const Matrix &);
    friend Matrix operator+(const MatrixRef &, const MatrixRef &);
    friend Matrix operator-(const MatrixRef &, const MatrixRef &);
    friend class MatrixRef;
public:
    Matrix();
    template<unsigned M, unsigned N>
    Matrix(int(&A)[M][N]) : hight(M), width(N), data(make_shared<vector<int>>()) {
        data->reserve(M*N);
        for (size_t i = 0;i != M;++i)
            for (size_t j = 0;j != N;++j)
                data->push_back(A[i][j]);
    }
    Matrix(size_t l, size_t r); // 创建一个行l、列r的零矩阵
    Matrix(const Matrix &rhs); // 深层次拷贝构造
    explicit Matrix(const MatrixRef &);  // 将MatrixRef转换为Matrix 
    int& get(size_t l, size_t r); // 取得行L、列R的值
    const int& get(size_t l, size_t r) const;
    int get() const; // 得到第一个值
    Matrix& operator=(const Matrix &rhs); // 深层次拷贝赋值
    Matrix& operator+=(const Matrix &rhs);
    Matrix& operator=(int i); // 把一个为i的值赋给行为1、列为1的矩阵
    Matrix& operator-(); // 对矩阵取负
    size_t rows() const {
        return width;
    }
    size_t size() const {
        return hight * width;
    }
private:
    void check_situation(size_t l, size_t r) const {
        if (l > hight || r > width)
            throw std::range_error("Invalid range");
    }
    size_t hight = 1;
    size_t width = 1;
    std::shared_ptr<std::vector<int>> data;
};
 
class MatrixRef {
    friend Matrix operator-(const MatrixRef &, const MatrixRef &);
    friend Matrix operator+(const MatrixRef &, const MatrixRef &);
    friend class Matrix;
public:
    MatrixRef(const Matrix &m, size_t line, size_t row);
    MatrixRef(const MatrixRef &mref, size_t line, size_t row);
    MatrixRef& operator=(const Matrix &rhs); // 对C_11、C_12、C_13、C_14进行赋值拼接的函数
    int& get() const; // 得到第一个值
    size_t rows() const {
        return length;
    }
private:
    std::weak_ptr<std::vector<int>> wptr;
    size_t hight_startptr;
    size_t width_startptr;
    size_t length;
};
Matrix operator+(const Matrix &, const Matrix &);
Matrix operator-(const Matrix &, const Matrix &);
Matrix operator+(const MatrixRef &, const MatrixRef &);
Matrix operator-(const MatrixRef &, const MatrixRef &);
std::ostream& operator<<(std::ostream&, const Matrix &);
 
template<typename T>
Matrix Square_max_matrix_multiply_recursive(const T &A, const T &B) {
    size_t n = A.rows();
    Matrix C(n, n);
    if (n == 1)
        return C = A.get()*B.get();
    else {
        MatrixRef A_11(A, 0, 0), A_12(A, 0, n / 2), A_21(A, n / 2, 0), A_22(A, n / 2, n / 2);// 使用一个类MatirxRef
        MatrixRef B_11(B, 0, 0), B_12(B, 0, n / 2), B_21(B, n / 2, 0), B_22(B, n / 2, n / 2);// 含有三个size_t类型。其中两个实现坐标，一个指明矩阵长度
        MatrixRef C_11(C, 0, 0), C_12(C, 0, n / 2), C_21(C, n / 2, 0), C_22(C, n / 2, n / 2);// 进行分割
        C_11 = Square_max_matrix_multiply_recursive(A_11, B_11) + Square_max_matrix_multiply_recursive(A_12, B_21);// Matrix::operator+;
        C_12 = Square_max_matrix_multiply_recursive(A_11, B_12) + Square_max_matrix_multiply_recursive(A_12, B_22);// MatrixRef::operator=;
        C_21 = Square_max_matrix_multiply_recursive(A_21, B_11) + Square_max_matrix_multiply_recursive(A_22, B_21);
        C_22 = Square_max_matrix_multiply_recursive(A_21, B_12) + Square_max_matrix_multiply_recursive(A_22, B_22);
    }
    return C;
}
template<typename T, typename N>
Matrix Strassen_matrix_fit(const T &A, const N &B) { // 为2的幂的情况下
    size_t n = A.rows();
    Matrix C(n, n);
    if (n == 1) {
        return C = A.get()*B.get();
    }
    else {
        MatrixRef A_11(A, 0, 0), A_12(A, 0, n / 2), A_21(A, n / 2, 0), A_22(A, n / 2, n / 2);// 使用一个类MatirxRef
        MatrixRef B_11(B, 0, 0), B_12(B, 0, n / 2), B_21(B, n / 2, 0), B_22(B, n / 2, n / 2);// 含有三个size_t类型。其中两个实现坐标，一个指明矩阵长度
        MatrixRef C_11(C, 0, 0), C_12(C, 0, n / 2), C_21(C, n / 2, 0), C_22(C, n / 2, n / 2);// 进行分割
        Matrix S1 = B_12 - B_22, S2 = A_11 + A_12, S3 = A_21 + A_22, S4 = B_21 - B_11, S5 = A_11 + A_22, //MatrixRef的加、减
            S6 = B_11 + B_22, S7 = A_12 - A_22, S8 = B_21 + B_22, S9 = A_11 - A_21, S10 = B_11 + B_12;
        Matrix P1 = Strassen_matrix_fit(A_11, S1), P2 = Strassen_matrix_fit(S2, B_22),
            P3 = Strassen_matrix_fit(S3, B_11), P4 = Strassen_matrix_fit(A_22, S4),
            P5 = Strassen_matrix_fit(S5, S6), P6 = Strassen_matrix_fit(S7, S8), P7 = Strassen_matrix_fit(S9, S10);
        C_11 = P5 + P4 - P2 + P6;
        C_12 = P1 + P2;
        C_21 = P3 + P4;
        C_22 = P5 + P1 - P3 - P7;
    }
    return C;
}
template<typename T, typename N>
Matrix Strassen_matrix(const T &A, const N &B) {
    size_t n = A.rows();
    double size = log(n) / log(2);
    size_t l_size = static_cast<size_t>(size);
    if (l_size != size) {
        size_t t_size = (l_size + 1)*(l_size + 1);
        Matrix a(t_size, t_size), b(t_size, t_size);
        a = A;
        b = B;
        Matrix C = Strassen_matrix_fit(a, b);
        Matrix c(n, n);
        c = C;
        return c;
    }
    else
        return Strassen_matrix_fit(A, B);
}
 
 
#endif

// Matrix1.cpp
#include"Matrix1.h"
#include<math.h>
using namespace std;
 
Matrix::Matrix() :data(make_shared<vector<int>>()) {
    data->push_back(0);
}
Matrix::Matrix(size_t l, size_t r) : hight(l), width(r), data(make_shared<vector<int>>()) {
    data->resize(l*r);
}
Matrix::Matrix(const Matrix &rhs) : hight(rhs.hight), width(rhs.width), data(make_shared<vector<int>>()) {
        for (size_t i = 0;i != size(); ++i)                        
            data->push_back((*rhs.data)[i]);                                                        
}
Matrix::Matrix(const MatrixRef &rhs) : hight(rhs.length), width(rhs.length), data(make_shared<vector<int>>()) {
    size_t max_size = static_cast<size_t>(sqrt(rhs.wptr.lock()->size())); // 未分解的原式中的矩阵长度
    auto ivec = *rhs.wptr.lock();
    for (size_t i = 0; i != hight; ++i) {
        for (size_t j = 0; j != width; ++j) {
            data->push_back(ivec[(i + rhs.hight_startptr)*max_size + j + rhs.width_startptr]);
        }
    }
}
int& Matrix::get(size_t l, size_t r) {
    check_situation(l, r);
    return (*data)[--l * width + --r];
}
const int& Matrix::get(size_t l, size_t r) const {
    check_situation(l, r);
    return (*data)[--l * width + --r];
}
int Matrix::get() const {
    return (*data)[0];
}
Matrix& Matrix::operator=(const Matrix &rhs) {
    if (hight == rhs.hight) {                                               //  rhs          this
        for (size_t i = 0; i != size(); ++i) {                              //  1 2 3        1 2 3
            (*data)[i] = (*rhs.data)[i];                                    //  2 3 2   ->   2 3 2
        }                                                                   //  3 2 1        3 2 1
    }                                                                        
    else if (hight > rhs.hight) {                                           //  1 2 3        1 2 3 0
        for (size_t i = 0;i != hight; ++i) {                                //  2 3 2   ->   2 3 2 0
            for (size_t j = 0, n = 1;j != width; ++j) {                     //  3 2 1        3 2 1 0
                if (j >= rhs.width || i >= rhs.hight)                       //               0 0 0 0
                    (*data)[i * width + j] = 0;
                else                                                                
                    (*data)[i * width + j] = (*rhs.data)[i * rhs.width + j];    
            }
        }
    }
    else {                                                                   // 1 2 3 4       1 2 3 
            for (size_t i = 0;i != hight; ++i) {                             // 2 3 4 3   ->  2 3 4 
                for (size_t j = 0;j != width; ++j) {                         // 3 4 3 2       3 4 3 
                    (*data)[i * width + j] = (*rhs.data)[i * rhs.width + j]; // 4 3 2 1      
                }
            }
    }
    return *this;
}
Matrix& Matrix::operator+=(const Matrix &rhs) {
    if (hight == rhs.hight && width == rhs.width) {
        for (size_t i = 0;i != size();++i)
            (*data)[i] += (*rhs.data)[i];
    }
    else
        throw std::logic_error("Not Matched");
    return *this;
}
Matrix& Matrix::operator=(int i) {
    if (hight == width && hight == 1)
        (*data)[0] = i;
    return *this;
}
Matrix& Matrix::operator-() {
    for (auto &f : *data)
        f = -f;
    return *this;
}
 
Matrix operator+(const Matrix &lhs, const Matrix &rhs) {
    Matrix m(lhs);
    return m += rhs;
}
Matrix operator-(const Matrix &lhs,const Matrix &rhs) {
    Matrix m(rhs);
    return m = -m + lhs;
}
 
MatrixRef::MatrixRef(const Matrix &m, size_t line, size_t row) : wptr(m.data), hight_startptr(line), width_startptr(row), length(m.rows() / 2) { }
MatrixRef::MatrixRef(const MatrixRef &mref, size_t line, size_t row) : wptr(mref.wptr), hight_startptr(mref.hight_startptr + line),
width_startptr(mref.width_startptr + row), length(mref.rows() / 2) { }
MatrixRef& MatrixRef::operator=(const Matrix &rhs) {   
    for (size_t i = 0;i != length;++i) {
        for (size_t j = 0;j != length;++j) {
            (*wptr.lock())[(i + hight_startptr)*length * 2 + j + width_startptr] = rhs.get(i + 1, j + 1);  //注意：length*2  因为C也被分割了
        }
    }
    return *this;
}
int& MatrixRef::get() const {
    return (*wptr.lock())[static_cast<size_t>(hight_startptr*sqrt(wptr.lock()->size())) + width_startptr];
}
Matrix operator+(const MatrixRef &lhs, const MatrixRef &rhs) {
    Matrix ml(lhs), mr(rhs);
    return ml += mr;
}
Matrix operator-(const MatrixRef &lhs, const MatrixRef &rhs) {
    Matrix ml(lhs), mr(rhs);
    return ml = -mr + ml;
}
ostream& operator<<(ostream &os, const Matrix &m) {
    int i = 0;
    for (auto f : *m.data) {
        cout << f;
        if (++i == m.width) {
            std::cout << '\n';
            i = 0;
        }
        else
            cout << ' ';
    }
    return os;
}