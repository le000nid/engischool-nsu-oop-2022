#include "Matrix.h"

using namespace std;

int main()
{
    Mat matrix(10, 10, 5);
    Mat matrix2(matrix);

    Mat zeroMat = Mat::zeros(5, 5);
    Mat eyeMat = Mat::eye(5).t();
    Mat matrix1234(2, 2, 1);

    matrix1234(0, 1) = 2;
    matrix1234(1, 0) = 3;
    matrix1234(1, 1) = 4;

    matrix = matrix1234.t();

    std::cin >> matrix;

    std::cout << matrix;

    printf("%lf\n", matrix.det());

    return 0;
}