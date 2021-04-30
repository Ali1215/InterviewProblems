#include <iostream>
#include "matrix.h"
//justification of const variables/methods in README

using namespace std;

Matrix::Matrix(const size_t num_rows, const size_t num_columns, const float init){
    /*
    Description:  Creates a new matrix class of indicated number of rows and columns with
                    the indicated initial value

    args: num_rows  = number of rows of new matrix
          num_columns = number of columns of new matrix
          init      = initial value to set all matrix elements to
    
    returns: none
  */
    
    //set class attributes to inputted values
    num_rs = num_rows;
    num_cols = num_columns;
    
    //an array of pointers will function as a matrix
    mat = new float*[num_rows];
    for (int i = 0; i < num_rows; i++){
        //intialize a new column for every row
        mat[i] = new float[num_columns];
        for (int j = 0; j < num_columns; j ++){
            //set each matrix element in every column to the initial value
            mat[i][j] = init;
        }
    }
}

Matrix::Matrix(const size_t num_rows, const size_t num_columns, const float * arr_ptr){
    /*
    Description:  Creates a new matrix class of indicated number of rows and columns
                    according to an array of values

    args: num_rows  = number of rows of new matrix
          num_columns = number of columns of new matrix
          arr_ptr   = float array with initial values for matrix
    
    returns: none
  */
    
    // set class attributes to inputted values
    num_rs = num_rows;
    num_cols = num_columns;
    
    //an array of pointers will function as a matrix
    mat = new float*[num_rows];

    //index for initial values array
    int index = 0;

    for (int i = 0; i < num_rows; i++){
        //intialize a new column for every row
        mat[i] = new float[num_columns];
        for (int j = 0; j < num_columns; j ++){
            //read initial values from initial value array and increment index
            mat[i][j] = arr_ptr[index];
            index++;
        }
    }
}

Matrix::~Matrix(){
    /*

    Description: this function will free every column from memory
                    and then all the rows
    args = none
    returns = none
  */
    for (int i = 0; i < num_rs; i++){
        //delete column
        delete[] mat[i];
    }
    //delete rows
    delete[] mat;
}

const Matrix Matrix::operator+(const Matrix& rhs) const{
    /*
    Description:  Overloads the + operator to allow for element by element addition
                    for compatible arrays of the same dimensions

    args: rhs  = Matrix class that will be added to this matrix class

    
    returns: new Matrix class that is the arithmetic sum
    */
    //initialize new matrix to store new sum into
    Matrix mat_sum(num_rs, num_cols, 0.0);

    for (int i = 0; i < num_rs; i++){
        for (int j = 0; j < num_cols; j++){
            //store the sum of each matching element into new matrix
            mat_sum.mat[i][j] = mat[i][j] + rhs.mat[i][j];
        }  

    }

    return mat_sum;
}


const Matrix Matrix::operator-(const Matrix& rhs) const{
    /*
    Description:  Overloads the - operator to allow for element by element subtraction
                    for compatible arrays of the same dimensions

    args: rhs  = Matrix class that will be subtracted from this matrix class

    
    returns: new Matrix class that is the arithmetic difference
    */
    //initialize new matrix to store new difference into
    Matrix mat_diff(num_rs, num_cols, 0.0);

    for (int i = 0; i < num_rs; i++){
        for (int j = 0; j < num_cols; j++){
            //store the difference of each matching element into new matrix
            mat_diff.mat[i][j] = mat[i][j] - rhs.mat[i][j];
        }  

    }

    return mat_diff;
}

const Matrix Matrix::operator-() const {
    /*
    Description:  Overloads the - operator to allow for unary negation by multipying
                    each element by -1

    args: rhs  = Matrix class that will be subtracted from this matrix class

    
    returns: new Matrix class that is the arithmetic difference
    */
   //initialize new matrix to store unary negation into
    Matrix mat_neg(num_rs, num_cols, 0.0);

    for (int i = 0; i < num_rs; i++){
        for (int j = 0; j < num_cols; j++){
            //store each matching element into new matrix with sign flipped
            mat_neg.mat[i][j] = mat[i][j]*-1;
        }  

    }
    
    return mat_neg;
}

const Matrix Matrix::operator*(const Matrix& rhs) const{
    /*
    Description:  Overloads the * operator to allow for matrix multiplication
                    of two compatible Matrixes

    args: rhs  = Matrix class that will be multiplied to this matrix class

    
    returns: new Matrix class that is the result of matrix multiplication
    */
    
    //initialize new matrix to store result into

    Matrix mat_prod(num_rs, rhs.num_cols, 0.0);
    
    float temp_sum = 0.0;
    
    for (int i = 0; i < num_rs; i++){
        for (int j = 0; j < rhs.num_cols; j++){
            temp_sum = 0.0;
            for (int k = 0; k < num_cols; k++){
                //do dot product across the row of the first matrix, and column of the second one
                temp_sum += mat[i][k] * rhs.mat[k][j];
            }
            //store result of dot product into matrix
            mat_prod.mat[i][j] = temp_sum;
        }  

    }

    return mat_prod;
}

float* Matrix::operator[](const unsigned int index){
    /*
    Description:  Overloads the [] operator to allow for a specific
                    row of the matrix to be referenced

    args: index  = the row to be extracted

    
    returns: the row of the array indicated by the index, as an array.
    */
    return mat[index];
}
const float* Matrix::operator[](const unsigned int index) const{
    // This is the same function as the previous, yet modified to return a const
    // array if the operator is acting on a const matrix
    return mat[index];
}

Matrix::Matrix(const Matrix& rhs){
    /*
    Description:  Copy constructor that copies the class atributes of another matrix
                    and makes another matrix that is a copy
    args: rhs  = the Matrix to be copied


    */
    //copy matrix attributes
    num_rs = rhs.num_rs;
    num_cols = rhs.num_cols;

    //initialize new matrix
    mat = new float*[num_rs];

    for (int i = 0; i < num_rs; i++){
        mat[i] = new float[num_cols];
        for (int j = 0; j < num_cols; j ++){
            //set each element of the new matrix to the matching element of the old matrix
            mat[i][j] = rhs.mat[i][j];
        }
    }
    
}

const Matrix Matrix::transpose() const {
    /*
    Description:  Returns a new matrix with the rows and columns swapped

    args: none (other than the matrix it is acting on)

    
    returns: a new matrix with the rows and columns swapped
    */

   //create a new matrix with swapped dimensions
    Matrix trans(num_cols, num_rs, 0.0);
    
    for (int i = 0; i < num_cols; i++){
        for (int j = 0; j < num_rs; j++){
            //the coordinates of each element maps to the swapped coordinates
            // in the other matrix
            trans.mat[i][j] = mat[j][i];

        }
    }
    return trans;
}

const Matrix Matrix::submatrix(const size_t row_start, const size_t row_end, const size_t column_start, const size_t column_end) const {
    /*
    Description:  Returns a new matrix that is a portion of the original matrix

    args: row_start = beginning row to include in new matrix
          row_end   = last row (exclusive) to include in new matrix
          column_start = beginning column to include in new matrix
          column_end   = last column (exclusive) to include in new matrix


    
    returns: a new matrix with the indicated portion of the original matrix
    */

    //create a new matrix of appropriate size
    Matrix sub_mat(row_end - row_start, column_end - column_start, 0.0);

    for (int i = row_start; i < row_end; i++){
        for (int j = column_start; j < column_end; j++){
            //iterate over the selected region of the old matrix and map it to values in new matrix
            sub_mat.mat[i - row_start][j - column_start] = mat[i][j];
        }
    }
    return sub_mat;
}

istream& operator>>(istream& in, const Matrix& rhs) {
    /*
    Description:  Overloads the extraction operator to allow for element by element input
                    across rows into a matrix. This assumes a correct amount of values will be
                    inputted by the user.

    args: in = input stream from <iostream>
          rhs   = any matrix already initialized.
          

    
    returns: a reference to the input stream
    */
    for (int i = 0; i < rhs.num_rs; i++){
        for (int j = 0; j < rhs.num_cols; j++){
            in >> rhs.mat[i][j];
        }  
    }
    return in;
}

ostream& operator<<(ostream& out,const Matrix rhs) {
  /*
    Description:  Overloads the insertion operator to allow for row by row output of a Matrix
                    to the terminal. 

    args: out = output stream from <iostream>
          rhs   = any matrix already initialized and filled.
          

    
    returns: a reference to the input stream
    */
    for (int i = 0; i < rhs.num_rs; i++){
        for (int j = 0; j < (rhs.num_cols - 1); j++){
            //print space separated values for every column in row
            out << rhs.mat[i][j] << ' ';
        }
        //print last column of every row without a space and instead a newline char
        out << rhs[i][rhs.num_cols - 1] << endl;

    }
    return out;
}