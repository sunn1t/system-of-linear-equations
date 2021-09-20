#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

const double c_i = 10; // Значения элементов матрицы на главной диагонали
const double d_i = 1; // Значения элементов матрицы на соседних диагоналях
const size_t N = 20; // Размер матрицы
const double epsilon = 1e-4;

//Cчитает отношение нормы невязки к норме решения
double error(vector<vector<double> > A, vector<double> X) {
    vector<double> Err(N);
    for (size_t i = 0; i < N; i++) {
        for (size_t j = 0; j < N; j++) {
            Err[i] += A[i][j]*X[j];
        }
        Err[i] -= A[i][N];
    }
    double NX = 0;
    double err = 0;
    for (size_t i = 0; i < N; i++) {
        err += Err[i]*Err[i];
        NX += X[i]*X[i];
    }
    return sqrt(err/NX);
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

    vector<double> X(N, 0), h(N, 1);

    double d;
    do {
        d = 0;
        for (size_t i = 0; i < N; i++) {
            X[i] = A[i][N]/A[i][i];
            for (size_t j = 0; j < i; j++) {
                X[i] -= X[j]*A[i][j]/A[i][i];
            }
            for (size_t j = i + 1; j < N; j++) {
                X[i] -= h[j]*A[i][j]/A[i][i];
            }
        }
        for (size_t i = 0; i < N; i++) {
            d += (X[i] - h[i])*(X[i] - h[i]);
        }
        h = X;
    } while (sqrt(d) > epsilon);

    for (size_t j = 0; j < N; j++) {
        cout << fixed << setprecision(8)
             << "x_" << j << " = " << X[j] << endl;
    }
    cout << scientific << "Отношение нормы невязки к норме решения " << error(A, X) << endl;

    return 0;
}
