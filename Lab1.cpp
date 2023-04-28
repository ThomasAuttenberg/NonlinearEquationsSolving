#include <iostream>
#include <math.h>
#include <fstream>

const double ERROR = DBL_MAX;

double F(double x) {
    return (double)x * x - 20 * sin(x);
}

double d(double func(double), double x) {
    double h = 0.00001;
    return (func(x + h) - func(x)) / h;
}

double dd(double func(double), double x) {
    double h = 0.00001;
    return (d(func, x + h) - d(func, x)) / h;
}

double* chord_method(double a, double b, double func(double), double accuracy) {
    
    double x_i;
    double x_ii;
    int iterations = 0;
    if (func(b) * dd(func, b) > 0) {
        x_i = a;
        while (1) {
            iterations++;
            x_ii = b - func(b) / (func(b) - func(x_i)) * (b - x_i);
            if (abs(x_ii - x_i) <= accuracy) {
                return new double[3] {x_ii, abs(x_ii - x_i), (double)iterations};
            }
            x_i = x_ii;
        }
    }

    if (func(a) * dd(func, a) > 0) {
        x_i = b;
        while (1) {
            iterations++;
            x_ii = a - func(a) / (func(x_i) - func(a)) * (x_i - a);
            if (abs(x_ii - x_i) <= accuracy) {
                return new double[3] {x_ii, abs(x_ii - x_i), (double)iterations};
            }
            x_i = x_ii;
        }
    }

    return new double{ ERROR };

}

double* half_division(double a, double b, double func(double x), double accuracy, int iterations = 0) {
    double b_i = b - (b - a) / 2;
    if (func(a) * func(b_i) <= 0) {
        if (abs(b_i-a) <= accuracy) {
            return new double[3] { (b_i + a) / 2, (b_i - a) / 2, (double)iterations+1 };
        }
        else {
            return half_division(a, b_i, func, accuracy, iterations+1);
        }
    }
    else {
        double a_i = b_i;
        if (func(a_i) * func(b) > 0) return new double { ERROR };
        if (abs(b-a_i) <= accuracy) {
            return new double[3] { (b_i + a) / 2, (b_i - a) / 2, (double)iterations+1 };
        }
        else {
            return half_division(a_i, b, func, accuracy, iterations+1);
        }
    }
}

double* newton_method(double a, double b, double func(double x), double accuracy) {
    double x0;
    if ((F(b) * dd(F, b)) > 0) 
        x0 = b;
    else
        if ((F(a) * dd(F, a)) > 0) 
            x0 = a;
        else 
            return new double{ ERROR };

    double x_i = x0;
    double x_ii = x0;
    int iterations = 0;
    do {
        iterations++;
        x_i = x_ii;
        x_ii = x_i - F(x_i) / d(F, x_i);
    } while (abs(x_ii - x_i) >= accuracy);

    return new double[3]{ x_ii, abs(x_ii - x_i), (double)iterations };
}

int main()
{
    system("chcp 1251");
    system("cls");

    double* result_hd = half_division(2.5, 3, F, 0.0001);
    double* result_chm = chord_method(2.5, 3, F, 0.0001);
    double* result_newton = newton_method(2.5, 3, F, 0.0001);

    //std::cout << F(-0.4) * dd(F, -0.4) <<"\n";
    if (*result_hd == ERROR) std::cout << "ERROR"; else std::cout << "Ответ: " << *result_hd << " | Погрешность: " << result_hd[1]<<" | Итерации: "<<result_hd[2];
    std::cout << "\n\n\n";
    if (*result_chm == ERROR) std::cout << "ERROR"; else std::cout << "Ответ: " << *result_chm << " | Погрешность: " << result_chm[1] << " | Итерации: " << result_chm[2];
    std::cout << "\n\n\n";
    if (*result_newton == ERROR) std::cout << "ERROR"; else std::cout << "Ответ: " << *result_newton << " | Погрешность: " << result_newton[1] << " | Итерации: " << result_newton[2];
    std::cout << "\n\n\n";

    delete[] result_hd;
    delete[] result_chm;
    delete[] result_newton;

    std::ofstream m("File.txt");
    for (double degree = 0; degree >= -15; degree--) {
        result_hd = half_division(2.5, 3, F, pow(10, degree));
        result_chm = chord_method(2.5, 3, F, pow(10, degree));
        result_newton = newton_method(2.5, 3, F, pow(10, degree));
        m << degree << " "<< result_hd[2]<<" " << result_chm[2]<<" " << result_newton[2]<<"\n";
        delete[] result_hd;
        delete[] result_chm;
        delete[] result_newton;
    }

}