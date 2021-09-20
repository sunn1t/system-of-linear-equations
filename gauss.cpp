#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

const double c_i = 10; // Значения элементов матрицы на главной диагонали
const double d_i = 1; // Значения элементов матрицы на соседних диагоналях
const size_t N = 20; // Размер матрицы
const double epsilon = 1e-10;

using namespace std;

inline bool equals0(double x) {
    return(fabs(x) < epsilon);
}

int main() {
    vector<vector<double> > A_0(N), A(N);

    // Задаём значения элементов матрицы
    for (size_t i = 0; i < N; i++) {
        A_0[i].resize(N + 1);
        A[i].resize(N + 1);
        A_0[i][i] = c_i;
        if (i < N - 1)
            A_0[i][i + 1] = d_i;
        if (i > 0)
            A_0[i][i - 1] = d_i;
        A_0[i][N] = i + 1;
    }

    A = A_0;

    //Прямой ход метода Гаусса
    for (size_t i = 0; i < N; i++) {

        //Если диагональный элемент равен нулю с точностью 1e-10,
        //пытаемся переставить строки
        if (equals0(A[i][i])) {
            vector<double> tmp(N + 1);
            tmp = A[i];
            for (size_t j = i + 1; j < N; j++) {
                if (!equals0(A[j][i])) {
                    A[i] = A[j];
                    A[j] = tmp;
                }
            }
        }

        if (equals0(A[i][i])) {
            return 0;
        } else { //Если диагональный элемент не равен нулю
            //Делим элементы строки на диагональный элемент
            for (size_t j = N; j >= i && j <= N; j--) {
                A[i][j] /= A[i][i];
            }

            // Вычитаем эту строку из нижних с коэффициентами A[i][j]
            for (size_t j = i + 1; j < N; j++) {
                for (size_t k = N; k >= i && k + 1 != 0; k--) {
                    A[j][k] -= A[i][k]*A[j][i];
                }
            }
        }
    }

    //Обратный ход метода Гаусса
    for (size_t j = N - 1; j + 1 != 0; j--) {
        for (size_t i = j - 1; i + 1 != 0; i--) {
            A[i][N] -= A[j][N]*A[i][j];
            //A[i][j] = 0;
        }
    }

    //Выводим решение
    vector<double> X(N);
    for (size_t i = 0; i < N; i++) {
        X[i] = A[i][N];
        cout << fixed << setprecision(8)
                  << "x_" << i + 1 << " = " << X[i] << endl;
    }

    //Выводим невязки
    vector<double> r(N);
    for (size_t i = 0; i < N; i++) {
        r[i] = A_0[i][N];
        for (size_t j = 0; j < N; j++) {
            r[i] -= A_0[i][j]*X[j];
        }
        cout << "r_" << i + 1 << " = " << scientific
                  << r[i] << endl;
    }
    cout << endl;

    //Считаем квадраты норм
    double NX = 0, Nr = 0;
    for (size_t i = 0; i < N; i++) {
        NX += X[i]*X[i];
        Nr += r[i]*r[i];
    }

    cout << "Отношение нормы невязки к норме решения " << sqrt(Nr/NX) << endl;
    return 0;
}
