#include "matrix.h"

class matrix{

public:
    matrix(){} //создание
    matrix(int Rows, int Cols){ //конструктор с кол-вом строк и столбцов
        rows = Rows;
        cols = Cols; 
    }
    matrix(const matrix& other)//копирование
    {
        rows = other.rows;
        //cout << "rowCre\n";
        cols = other.cols;
        //cout << "colCre\n";
        arr = other.arr;
        //cout << "arrCre\n";
        //throw("Error copy obj!");
        //cout << "Error in create matrix!\n";
    }
    ~matrix(){
        //delete(this);
    };

    void changeMatrix(vector<vector<int>> arr_, int Rows, int Cols){
        cols = Cols;
        //cout << "colCre\n";
        rows = Rows;
        //cout << "rowCre\n";
        arr = arr_;
        //cout << "arrCre\n";
    }

    int getRows(){
        return rows;
    }
    int getCols(){
        return cols;
    }
    vector<vector<int>> getArr(){
        return arr;
    }
    void printMatrix(){
        cout << "rows: " << rows << "\n";
        cout << "cols: " << cols << "\n";

        for(int a = 0; a < rows; a++){
            for(int b = 0; b < cols; b++){
                cout << arr[a][b] << " ";
            }
            cout << "\n";
        }
    }

    bool EqMatrix(const matrix& other){
        if(rows == other.rows and cols == other.cols and arr == other.arr){
            return true;
        }
        return false;
    }

    void SumMatrix(const matrix& other){
        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot sum it because matrix have different sizes!");
        }

        for(int a = 0; a < cols; a++){
            for(int b = 0; b < rows; b++){
                arr[a][b] += other.arr[a][b];
            }
        }
        
    }

    void SubMatrix(const matrix& other){

        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot sub it because matrix have different sizes!");
        }

        for(int a = 0; a < cols; a++){
            for(int b = 0; b < rows; b++){
                arr[a][b] -= other.arr[a][b];
            }
        }
    }

    void MulNumber(const double num){
        for(int a = 0; a < cols; a++){
            for(int b = 0; b < rows; b++){
                arr[a][b] *= num;
            }
        }
    }

    void MulMatrix(const matrix& other){
        if(rows != other.rows or cols != other.cols){
            throw("Error: Cannot exp it because matrix have different sizes!");
        }

        for(int a = 0; a < cols; a++){
            for(int b = 0; b < rows; b++){
                arr[a][b] *= other.arr[a][b];
            }
        }
    }

    matrix Transpose(){
        matrix out = *new matrix(cols, rows);

        vector<vector<int>> mat_buff;
        vector<int> mat_buff_buff;

        for(int i = 0; i < rows; i++){
            for(int i = 0; i < cols; i++){
                mat_buff_buff.push_back(0);
            }
            mat_buff.push_back(mat_buff_buff);
            mat_buff_buff.clear();
        }
        out.arr = mat_buff;

        for(int a = 0; a < rows; a++){
            for(int b = 0; b < cols; b++){
                out.arr[b][a] = arr[a][b];
            }
        }
        out.cols = rows;
        out.rows = cols;

        return out;
    }

    /*
        1 2 3
        4 5 6
        7 8 9
        эл 6
        1 2
        7 8
    */
    
    
    matrix CalcComplements(){
        if(cols != rows) throw("Error: Matrix is not square");

        matrix out = *new matrix(rows, cols);
        //cout << "_1\n";
        out.arr = getAlgAppend(arr);
        //cout << "_2\n";


        return out;
        
    }

private:
    int rows; int cols;
    vector<vector<int>> arr;

    vector<vector<int>> getMinor(vector<vector<int>> matrix_, int rows, int cols){
        int n = matrix_.size();
        vector<vector<int>> out_minor(n - 1, vector<int>(n - 1));

        if(n == 1) return matrix_;

        for(int i = 0, p = 0; i < n; i++){
            if(i == rows) continue;
            for(int j = 0, q = 0; j < n; j++){
                if(j == cols) continue;
                out_minor[p][q] = matrix_[i][j];
                q++;
            }
            p++;
        }
        //cout << "minor\n";
        return out_minor;
    }

    double determinant(vector<vector<int>>& matrix_){
        int n = matrix_.size();
        vector<int> test = matrix_[0];
        int b = test.size();
        int det = 0;

        if(n != b){
            cout << "Not square! n = " << n << " b = " << b << "\n";
            return 0;
        } 

        if(n == 0){
            return 0;
        }
        else if(n == 1){
            //cout << "deter\n";
            return matrix_[0][0];
        }
        else if(n == 2){
            //cout << "deter\n";
            return (matrix_[0][0] * matrix_[1][1]) - (matrix_[0][1] * matrix_[1][0]); //косяк тут
        }
        else{
            for(int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    vector<vector<int>> minor = getMinor(matrix_, i, j);
                    int sign = j % 2 ? 1 : -1;
                    det += sign * matrix_[i][j] * determinant(minor);
                //cout << sign << ":s " << matrix_[i][j] << ":m " << determinant(minor) << ":d" << det << ":det\n";
                }
            }
            
            //cout << "deter\n";
            //cout << det << ":det" << "\n";
            return det;
        }
    }

    vector<vector<int>> getAlgAppend(vector<vector<int>> mat_){
        int n = mat_.size();
        vector<vector<int>> cofactors(n, vector<int>(n));

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                vector<vector<int>> minors = getMinor(mat_, i, j);
                int sign = (i + j) % 2 == 0 ? 1: -1;
                cofactors[j][i] = int(sign * determinant(minors));
            }
        }
        //cout << "alg\n";
        return cofactors;
    }


};


int main(){
    matrix matTest = *new matrix();
    vector<vector<int>> mat_buff;
    vector<int> mat_buff_buff;

    int counter = 1;
    for(int i = 0; i < 3; i++){
        for(int i = 0; i < 2; i++){
            mat_buff_buff.push_back(counter);
            counter+=1;
        }
        counter-=0;
        mat_buff.push_back(mat_buff_buff);
        mat_buff_buff.clear();
    }

}
