#ifndef L_BARAYSHCHUK_LAB1_2_MATRIX_H
#define L_BARAYSHCHUK_LAB1_2_MATRIX_H


#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>

class Mat {

private:

    int cols;
    int rows;
    double* M;

public:
    Mat();
    Mat(int rows, int cols);
    Mat(int rows, int cols, const double& value);
    Mat(const Mat& m);
    ~Mat();

    friend std::ostream& operator<< (std::ostream&, Mat const&);
    friend std::istream& operator>> (std::istream&, Mat&);

    double& operator() (int row, int col);
    double& operator[] (int id);
    const double& operator() (int row, int col) const;
    const Mat& operator= (const Mat& m);
    const Mat& operator= (const double& s);

    Mat operator+ (const Mat& b);
    Mat operator+ (const double& s);
    Mat operator- (const Mat& b);
    Mat operator- (const double& s);
    Mat operator* (const Mat& b);
    Mat operator* (const double& s);
    bool operator== (const Mat& b);
    bool operator!= (const Mat& b);

    Mat t();
    double det();
    void stup_vid(double* m, int n, int* minus);

    static Mat eye(int cols);
    static Mat zeros(int rows, int cols);
};

Mat::Mat()
{
    rows = 1;
    cols = 1;
    M = new double[1];
    M[0] = 0.0;
}

Mat::Mat(int r, int c) : Mat(r, c, 0) {}

Mat::Mat(int r, int c, const double& v) : cols(c), rows(r)
{
    M = (double*) new double[rows * cols];
    for (int i = 0; i < cols * rows; ++i)
    {
        M[i] = v;
    }
}

Mat::Mat(const Mat& m) : cols(m.cols), rows(m.rows)
{
    M = (double*) new double[rows * cols];
    for (int i = 0; i < cols * rows; ++i)
    {
        M[i] = m.M[i];
    }
}

Mat::~Mat()
{
    delete[] M;
}

std::ostream& operator <<(std::ostream& ost, Mat const& mat)
{
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            ost << mat(i, j) << " ";
        }
        ost << "\n";
    }

    return ost << "";
}

std::istream& operator>>(std::istream& ist, Mat& mat)
{
    for (int i = 0; i < mat.rows; ++i) {
        for (int j = 0; j < mat.cols; ++j) {
            std::cout << "number in " << i << " " << j << ": ";
            ist >> mat(i, j);
        }
    }
    return ist;
}

double& Mat::operator()(int row, int col)
{
    return M[row * cols + col];
}

double& Mat::operator[](int id)
{
    return M[id];
}

const double& Mat::operator()(int row, int col) const
{
    return M[row * cols + col];
}

Mat Mat::zeros(int rows, int cols)
{
    return Mat(rows, cols);
}

Mat Mat::eye(int cols)
{
    Mat Eye(cols, cols);
    for (int i = 0; i < cols; ++i)
    {
        Eye(i, i) = 1;
    }
    return Eye;
}

const Mat& Mat::operator=(const Mat& m)
{
    rows = m.rows;
    cols = m.cols;
    M = new double[rows * cols];
    for (int i = 0; i < rows * cols; ++i)
    {
        M[i] = m.M[i];
    }
    return *this;
}

const Mat& Mat::operator=(const double& s)
{
    for (int i = 0; i < rows * cols; ++i)
    {
        M[i] = s;
    }
    return *this;
}

Mat Mat::operator+(const Mat& b)
{
    Mat matrix(b);
    for (int i = 0; i < cols * rows; ++i) {
        matrix.M[i] += M[i];
    }

    return matrix;
}

Mat Mat::operator+(const double& s)
{
    Mat matrix(rows, cols, s);
    for (int i = 0; i < cols * rows; ++i) {
        matrix.M[i] += M[i];
    }

    return matrix;
}

Mat Mat::operator-(const Mat& b)
{
    Mat matrix(b);
    for (int i = 0; i < cols * rows; ++i) {
        matrix.M[i] = M[i] - matrix.M[i];
    }

    return matrix;
}

Mat Mat::operator-(const double& s)
{
    Mat matrix(rows, cols, s);
    for (int i = 0; i < cols * rows; ++i) {
        matrix.M[i] = M[i] - matrix.M[i];
    }

    return matrix;
}

Mat Mat::operator*(const Mat& b)
{
    Mat thisM(*this);
    Mat matrix(rows, b.cols, 0);
    int sum;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < b.cols; ++j) {
            sum = 0;
            for (int k = 0; k < cols; k++)
                matrix(i, j) += (thisM(i, k) * b(k, j));
        }
    }

    return matrix;
}

Mat Mat::operator*(const double& s)
{
    Mat thisM(*this);
    Mat matrix(cols, cols, 0);
    Mat b = Mat::eye(cols);

    for (int i = 0; i < cols; ++i) {
        b(i, i) = s;
    }

    matrix = thisM * b;

    return matrix;
}

bool Mat::operator==(const Mat& b)
{
    if (cols != b.cols || rows != b.rows) return false;
    for (int i = 0; i < rows * cols; ++i) {
        if (M[i] != b.M[i]) return false;
    }
    return true;
}

bool Mat::operator!=(const Mat& b)
{
    if (cols != b.cols || rows != b.rows) return true;
    for (int i = 0; i < rows * cols; ++i) {
        if (M[i] == b.M[i]) return false;
    }
    return true;
}

Mat Mat::t()
{
    Mat m = Mat(rows, cols);
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            m.M[i * rows + j] = M[j * cols + i];
        }
    }
    return m;
}

double Mat::det()
{
    int minus = 1;
    double det = 1;
    auto m = Mat(*this);
    stup_vid(m.M, cols, &minus);
    for (int i = 0; i < cols; ++i) {
        det *= m.M[i * cols + i];
    }
    if (det == 0) {
        return 0;
    }
    return det * minus;
}

void Mat::stup_vid(double* m, int n, int* minus)
{
    int j, k, nul = 1;
    double c;
    auto newM = new double[(n - 1) * (n - 1)];
    if (n == 1) {
        return;
    }
    else {
        nul = 1;
        for (j = 0; j < n; ++j) {
            if (m[j] != 0) {
                nul = 0;
                break;
            }
        }
        if (nul == 0) {
            if (m[0] == 0) {
                k = 1;
                while (m[0] == 0) {
                    if (m[k] != 0) {
                        for (j = 0; j < n; ++j) {
                            using std::swap;
                            swap(m[j * n], m[j * n + k]);
                        }
                        *minus *= -1;
                    }
                    ++k;
                }
            }
            for (j = 1; j < n; ++j) {
                c = m[j] / m[0];
                for (k = 0; k < n; ++k) {
                    m[k * n + j] += (m[k * n] * (-c));
                }
            }
            for (j = 0; j < (n - 1); ++j) {
                for (k = 0; k < (n - 1); ++k) {
                    newM[k * (n - 1) + j] = m[(k + 1) * n + (j + 1)];
                }
            }
            stup_vid(newM, n - 1, minus);
            for (j = 0; j < (n - 1); ++j) {
                for (k = 0; k < (n - 1); ++k) {
                    m[(k + 1) * n + (j + 1)] = newM[k * (n - 1) + j];
                }
            }
        }
        else {
            for (j = 0; j < (n - 1); ++j) {
                for (k = 0; k < (n - 1); ++k) {
                    newM[k * (n - 1) + j] = m[(k + 1) * n + (j + 1)];
                }
            }
            stup_vid(newM, n - 1, minus);
            for (j = 0; j < (n - 1); ++j) {
                for (k = 0; k < (n - 1); ++k) {
                    m[(k + 1) * n + (j + 1)] = newM[k * (n - 1) + j];
                }
            }
        }
    }
}

#endif //L_BARAYSHCHUK_LAB1_2_RATIONAL_H