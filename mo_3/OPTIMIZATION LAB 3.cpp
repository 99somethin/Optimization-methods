#include <iostream>
#include <locale.h>
#include <cmath>
#include <MLang.h>
using namespace std;
void main()
{
    setlocale(LC_ALL, "Rus");
    double x1[20], x2[20], e1 = 0.15, e2 = 0.2, M = 10;
    double f[20], fx1[20], fx2[20], mod_f[20];
    double d = 6, e = 0.6, g = 3;
    double t_k = 1;
    bool inverse = false;
    int k;
    cout << "Дана функция f(x1, x2) = " << d << " * x1^2 + " << e << " * x1 * x2 + " << g << " * x2^2.";
    cout << "\n\nШаг 1: x0 = (" << (x1[0] = 1.5) << ", " << (x2[0] = 0.5) << "), e1 = " << e1 << ", e2 = " << e2 << ", M = " << M << ". Градиент в произвольной точке f(x) = (" << 2 * d << " * x1 + " << e << " * x2; " << e << " * x1 + " << 2 * g << " * x2)";
    cout << "\nМатрица Гессе: \n\t" << 2 * d << "\t" << e << "\n\t" << e << "\t" << g << "\n\nШаг 2: k = 0.";
    k = 0; // ШАГ 2
    for (;;) {
        cout << "\n\nГруппа шагов " << k << ":";
        f[k] = d * x1[k] * x1[k] + e * x1[k] * x2[k] + g * x2[k] * x2[k]; // ШАГ 3
        fx1[k] = 2 * d * x1[k] + e * x2[k];
        fx2[k] = e * x1[k] + 2 * g * x2[k];
        cout << "\nШаг 3: Вычисляем градиент x[" << k << "] = (" << fx1[k] << ", " << fx2[k] << ")";
        mod_f[k] = sqrt(fx1[k] * fx1[k] + fx2[k] * fx2[k]);
        cout << "\n\nШаг 4: Вычисление нормы град. f(x[" << k << "]) = " << mod_f[k] << ". Сравнение с e1";
        if (mod_f[k] > e1) { // ШАГ 4
            cout << "\n\nШаг 5: Проверим условие k >= M. ";
            if (k < M) { // ШАГ 5
                cout << k << " < " << M;
                double HesseMatrix[2][2];
                HesseMatrix[0][0] = 2 * d;
                HesseMatrix[0][1] = e;
                HesseMatrix[1][0] = e;
                HesseMatrix[1][1] = 2 * g;
                double Det = HesseMatrix[0][0] * HesseMatrix[1][1] - HesseMatrix[1][0] * HesseMatrix[0][1];
                cout << "\n\nШаг 6: Вычисляем матрицу Гессе с х[" << k << "]:\n\t" << HesseMatrix[0][0] << "\t" << HesseMatrix[0][1] << "\n\t" << HesseMatrix[1][0] << "\t" << HesseMatrix[1][1];
                double RevHesseMatrix[2][2];
                RevHesseMatrix[0][0] = (1 / Det) * HesseMatrix[1][1];
                RevHesseMatrix[0][1] = (-1 / Det) * HesseMatrix[1][0];
                RevHesseMatrix[1][0] = (-1 / Det) * HesseMatrix[0][1];
                RevHesseMatrix[1][1] = (1 / Det) * HesseMatrix[0][0];
                double RevDet = RevHesseMatrix[0][0] * RevHesseMatrix[1][1] - RevHesseMatrix[1][0] * RevHesseMatrix[0][1];
                cout << "\n\nШаг 7: Вычисляем обратную матрицу Гессе с х[" << k << "]:\n\t" << RevHesseMatrix[0][0] << "\t" << RevHesseMatrix[0][1] << "\n\t" << RevHesseMatrix[1][0] << "\t" << RevHesseMatrix[1][1] << "\nH^(-1)(x[k]) = " << RevDet;
                cout << "\n\nШаг 8: Проверка условия H^(-1)(x[" << k << "]) > 0. ";
                cout << "Условие выполнено.\n\nШаг 9: Определение d_k = -H^(-1)(x[k]) * град. f(x[k])";
                double d_k1 = -((RevHesseMatrix[0][0] * fx1[k]) + (RevHesseMatrix[0][1] * fx2[k]));
                double d_k2 = -((RevHesseMatrix[1][0] * fx1[k]) + (RevHesseMatrix[1][1] * fx2[k]));
                cout << "\nd_k = (" << d_k1 << "; " << d_k2 << ")";


                cout << "\n\nШаг 10: Вычисление x[" << k + 1 << "] = x[" << k << "] + t_k * d_k(t_k принимается за 1): ";
                while (true)
                    if (f[k + 1] < f[k])
                    {
                        break;
                    }
                    else
                    {
                        if (inverse)
                        {
                            t_k *= 2;
                            f[k] = d * x1[k] * x1[k] + e * x1[k] * x2[k] + g * x2[k] * x2[k];
                            if (f[k + 1] < f[k])
                            {
                                break;
                            }
                            else
                            {
                                t_k /= 4;
                                f[k] = d * x1[k] * x1[k] + e * x1[k] * x2[k] + g * x2[k] * x2[k];
                                inverse = !inverse;
                            }
                        }
                    }
                x1[k + 1] = x1[k] + t_k * d_k1;
                x2[k + 1] = x2[k] + t_k * d_k2;


                cout << "x1[" << k + 1 << "] = " << x1[k] << " + " << d_k1 << " = " << x1[k + 1] << "\n";
                cout << "x2[" << k + 1 << "] = " << x2[k] << " + " << d_k2 << " = " << x2[k + 1] << "\n";
                // ШАГ 11
                cout << "\n\nШаг 11: Проверка выполнения условий x[k + 1] - x[k]  < e2 и | f(x[k + 1]) - f(x[k]) | < e2 для k = " << k << " и k = k - 1 = " << k - 1;
                if ((sqrt(pow(x1[k + 1] - x1[k], 2) + pow(x2[k + 1] - x2[k], 2)) < e2) && (abs(f[k + 1] - f[k]) < e2) && ((sqrt(pow(x1[k] - x1[k - 1], 2) + pow(x2[k] - x2[k - 1], 2)) < e2) && abs(f[k] - f[k - 1]) < e2)) {
                    f[k + 1] = d * x1[k + 1] * x1[k + 1] + e * x1[k + 1] * x2[k + 1] + g * x2[k + 1] * x2[k + 1];
                    cout << "\nУсловие выполнено. x* = x[k + 1]";
                    cout << "\n\nf = f(" << x1[k + 1] << "; " << x2[k + 1] << ") = " << f[k] << "\n";
                    break;
                }
                else {
                    k++;
                    cout << "\nУсловие не выполнено. k = k + 1";
                }
                f[k] = d * x1[k] * x1[k] + e * x1[k] * x2[k] + g * x2[k] * x2[k];
                cout << "\n\nf = f(" << x1[k] << "; " << x2[k] << ") = " << f[k] << "\n";
            }
            else {
                cout << k << " >= " << M << ". x* = x[k]";
                f[k] = d * x1[k] * x1[k] + e * x1[k] * x2[k] + g * x2[k] * x2[k];
                cout << "\n\nf_min = f(" << x1[k] << "; " << x2[k] << ") = " << -f[k] << "\n";
                return;
            }
        }
        else {
            cout << "Условие выполнено. x* = x[k]";
            f[k] = d * x1[k] * x1[k] + e * x1[k] * x2[k] + g * x2[k] * x2[k];
            cout << "\n\nf_min = f(" << x1[k] << "; " << x2[k] << ") = " << -f[k] << "\n";
            return;
        }
    }
}