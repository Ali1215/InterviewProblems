#ifndef _MATRIX_H_
#define _MATRIX_H_

using namespace std;

class Matrix {

public:

    //constructors
    Matrix(const size_t num_rows, const size_t num_columns, const float init);
    Matrix(const size_t num_rows, const size_t num_columns, const float * arr_ptr);
    
    //copy constructor
    Matrix(const Matrix& rhs);
    //destructor
    ~Matrix();

    //operators
    const Matrix operator+(const Matrix& rhs) const;
    const Matrix operator-(const Matrix& rhs) const;
    const Matrix operator-() const;
    const Matrix operator*(const Matrix& rhs) const;

    //non-const version will allow mat to be updated
    float* operator[](const unsigned int index);
    const float* operator[](const unsigned int index) const;

    //misc functions
    const Matrix transpose() const;
    const Matrix submatrix(const size_t row_start, const size_t row_end, const size_t column_start, const size_t column_end) const;

    //iostrean
    friend istream& operator>>(istream& in, const Matrix& rhs);
    friend ostream& operator<<(ostream& out, const Matrix rhs);

private:
    
    float **mat;
    unsigned int num_rs;
    unsigned int num_cols;
};

#endif // !defined