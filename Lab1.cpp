#include <iostream>
#include <math.h>

const double ERROR = DBL_MIN;

double F(double x) {
    return x * x - 20 * sin(x);
}

double derivative_2nd(double func(double), double x) {
    double h = 0.000000000000001;
    return (func(x + h) - 2 * func(x) + func(x - h)) / 2;
}

double* hord_method(double a, double b, double func(double), double accuracy) {
    if (func(b) * derivative_2nd(func, a) > 0)
}

double* half_division(double a, double b, double func(double x), double accuracy) {
    double b_i = b - (b - a) / 2;
    if (func(a) * func(b_i) < 0) {
        if (b_i - a <= accuracy) {
            return new double[2] { (b_i + a) / 2, (b_i - a) / 2 };
        }
        else {
            return half_division(a, b_i, func, accuracy);
        }
    }
    else {
        double a_i = b_i;
        if (func(a_i) * func(b) > 0) return new double[2] { ERROR, 0 };
        if (b - a_i <= accuracy) {
            return new double[2] { (b_i + a) / 2, (b_i - a) / 2 };
        }
        else {
            return half_division(a_i, b, func, accuracy);
        }
    }
}

int main()
{
    system("chcp 1251");
    system("cls");

    /*
    # решение = (An+Bn)/2
    # погрешность = (Bn-An)/2
    # количество разбиений >= log2((b-a)/точность);
    # формулы какие-то: Bn-An = (Bn-1 - An-1)/2 = (B-A)/2^n
    # Условие ответа: F(An) * F(Bn) < 0, (Bn - An) <= точность

    */
    double* result = half_division(-0.0001, 0.0001, F, pow(10, -3));


    if (*result == ERROR) std::cout << "ERROR"; else std::cout << "Ответ: " << *result << " | Погрешность: " << result[1];
    std::cout << "\n\n\n";

}