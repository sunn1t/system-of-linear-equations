#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double c_i = 10; // Значения элементов матрицы на главной диагонали
const double d_i = 1; // Значения элементов матрицы на соседних диагоналях
const size_t N = 20; // Размер матрицы

const double epsilon = 1e-5;

using namespace std;

double get_lambda_abs_max(vector<vector<double> > A) {
    vector<double> X_1(N, 0), X_2(N, 1);
    double lambda1 = 0, lambda2 = 1;

    do {
        X_1 = X_2;
        for (size_t i = 0; i < N; i++) {
            X_2[i] = 0;
            for (size_t j = 0; j < N; j++) {
                X_2[i] += A[i][j]*X_1[j];
            }
        }

        double X_1_X_2 = 0, X_1_X_1 = 0;
        for (size_t i = 0; i < N; i++) {
            X_1_X_2 += X_1[i]*X_2[i];
            X_1_X_1 += X_1[i]*X_1[i];
        }

        lambda1 = lambda2;
        lambda2 = X_1_X_2/X_1_X_1;

    } while (fabs(lambda1 - lambda2) > epsilon);
    return lambda2;
}

int main() {
    vector<vector<double> > A(N);

    // Задаём значения элементов матрицы
    for (size_t i = 0; i < N; i++) {
        A[i].resize(N + 1);
        A[i][i] = c_i;
        if (i < N - 1)
            A[i][i + 1] = d_i;
        if (i > 0)
            A[i][i - 1] = d_i;
        A[i][N] = i + 1;
    }

    // Наибольшее по модулю СЗ матрицы А
    double lambda_max = get_lambda_abs_max(A);

    for (size_t i = 0; i < N; i++)
        A[i][i] -= lambda_max;

    // Наименьшее по модулю СЗ матрицы А
    double lambda_min = get_lambda_abs_max(A) + lambda_max;

    cout << fixed << setprecision(5)
         << "lambda_max = " << lambda_max << endl
         << "lambda_min = " << lambda_min << endl
         << "Answer = " << fabs(lambda_max/lambda_min) << endl;

    return 0;
}
