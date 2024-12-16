#include "Matrices-5.h"

namespace Matrices
{
    /// Constructor: Initialize all elements to zero
    Matrix::Matrix(int _rows, int _cols) : rows(_rows), cols(_cols), a(_rows, vector<double>(_cols, 0)) {}

    /// Add two matrices
    Matrix operator+(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
            throw invalid_argument("Matrix dimensions must match for addition.");

        Matrix result(a.getRows(), a.getCols());
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                result(i, j) = a(i, j) + b(i, j);
            }
        }
        return result;
    }

    /// Multiply two matrices
    Matrix operator*(const Matrix& a, const Matrix& b)
    {
        if (a.getCols() != b.getRows())
            throw invalid_argument("Matrix dimensions must allow multiplication.");

        Matrix result(a.getRows(), b.getCols());
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < b.getCols(); j++)
            {
                for (int k = 0; k < a.getCols(); k++)
                {
                    result(i, j) += a(i, k) * b(k, j);
                }
            }
        }
        return result;
    }

    /// Compare two matrices for equality
    bool operator==(const Matrix& a, const Matrix& b)
    {
        if (a.getRows() != b.getRows() || a.getCols() != b.getCols())
            return false;

        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                if (a(i, j) != b(i, j))
                    return false;
            }
        }
        return true;
    }

    /// Compare two matrices for inequality
    bool operator!=(const Matrix& a, const Matrix& b)
    {
        return !(a == b);
    }

    /// Output matrix
    ostream& operator<<(ostream& os, const Matrix& a)
    {
        for (int i = 0; i < a.getRows(); i++)
        {
            for (int j = 0; j < a.getCols(); j++)
            {
                os << setw(8) << a(i, j) << " ";
            }
            os << endl;
        }
        return os;
    }

    /// RotationMatrix constructor
    RotationMatrix::RotationMatrix(double theta) : Matrix(2, 2)
    {
        (*this)(0, 0) = cos(theta);
        (*this)(0, 1) = -sin(theta);
        (*this)(1, 0) = sin(theta);
        (*this)(1, 1) = cos(theta);
    }

    /// ScalingMatrix constructor
    ScalingMatrix::ScalingMatrix(double scale) : Matrix(2, 2)
    {
        (*this)(0, 0) = scale;
        (*this)(1, 1) = scale;
    }

    /// TranslationMatrix constructor
    TranslationMatrix::TranslationMatrix(double xShift, double yShift, int nCols) : Matrix(2, nCols)
    {
        for (int j = 0; j < nCols; j++)
        {
            (*this)(0, j) = xShift;
            (*this)(1, j) = yShift;
        }
    }
}
