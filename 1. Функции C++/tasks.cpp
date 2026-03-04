#include <iostream>
#include <cmath>
#include <functional>

// ============================================================
// Задание 1: IsPrime — проверка числа на простоту
// ============================================================

bool IsPrime(int N) {
    if (N < 2) return false;
    if (N == 2) return true;
    if (N % 2 == 0) return false;
    for (int i = 3; i <= static_cast<int>(std::sqrt(N)); i += 2)
        if (N % i == 0) return false;
    return true;
}

void task1() {
    std::cout << "=== Задание 1: Простые числа ===\n";
    int numbers[10] = {2, 4, 7, 9, 13, 15, 17, 20, 23, 25};
    int count = 0;

    std::cout << "Набор: ";
    for (int n : numbers) std::cout << n << " ";
    std::cout << "\nПростые: ";
    for (int n : numbers) {
        if (IsPrime(n)) {
            std::cout << n << " ";
            count++;
        }
    }
    std::cout << "\nКоличество простых чисел: " << count << "\n\n";
}

// ============================================================
// Задание 2: Перегруженные функции Min()
// ============================================================

// Минимум в массиве целых чисел
int Min(const int arr[], int size) {
    int m = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] < m) m = arr[i];
    return m;
}

// Минимум в массиве вещественных чисел
double Min(const double arr[], int size) {
    double m = arr[0];
    for (int i = 1; i < size; i++)
        if (arr[i] < m) m = arr[i];
    return m;
}

// Минимум из двух целых чисел
int Min(int a, int b) {
    return (a < b) ? a : b;
}

// Минимум из трёх целых чисел
int Min(int a, int b, int c) {
    return Min(Min(a, b), c);
}

void task2() {
    std::cout << "=== Задание 2: Перегруженные Min() ===\n";

    int iArr[] = {5, 2, 8, 1, 9};
    double dArr[] = {3.14, 2.71, 1.41, 0.57};

    std::cout << "Min в int-массиве {5,2,8,1,9}: "
              << Min(iArr, 5) << "\n";
    std::cout << "Min в double-массиве {3.14,2.71,1.41,0.57}: "
              << Min(dArr, 4) << "\n";
    std::cout << "Min(7, 3): "    << Min(7, 3)    << "\n";
    std::cout << "Min(7, 3, 5): " << Min(7, 3, 5) << "\n\n";
}

// ============================================================
// Задание 3: Шаблон для функции IsPrime (задание 1)
// ============================================================

template <typename T>
bool IsPrimeTemplate(T N) {
    if (N < static_cast<T>(2)) return false;
    if (N == static_cast<T>(2)) return true;
    if (N % static_cast<T>(2) == static_cast<T>(0)) return false;
    for (T i = 3; i * i <= N; i += static_cast<T>(2))
        if (N % i == static_cast<T>(0)) return false;
    return true;
}

void task3() {
    std::cout << "=== Задание 3: Шаблон IsPrimeTemplate<T> ===\n";

    int  a = 17;
    long b = 97L;
    std::cout << "IsPrimeTemplate<int>("  << a << ")  = "
              << (IsPrimeTemplate(a) ? "true" : "false") << "\n";
    std::cout << "IsPrimeTemplate<long>(" << b << ")  = "
              << (IsPrimeTemplate(b) ? "true" : "false") << "\n";
    std::cout << "IsPrimeTemplate<int>(15) = "
              << (IsPrimeTemplate(15) ? "true" : "false") << "\n\n";
}

// ============================================================
// Задание 4: Рекурсивная функция Root (метод бисекции)
//
//   f(a) * f(b) < 0  — условие существования корня
//   Root рекурсивно делит [a,b] пополам до |b-a| < ε
// ============================================================

double Root(double a, double b, double eps,
            const std::function<double(double)>& f) {
    double mid = (a + b) / 2.0;
    if ((b - a) < eps) return mid;           // точность достигнута

    if (f(a) * f(mid) < 0)                  // корень в левой половине
        return Root(a, mid, eps, f);
    else                                     // корень в правой половине
        return Root(mid, b, eps, f);
}

void task4() {
    std::cout << "=== Задание 4: Рекурсивная Root (бисекция) ===\n";

    // f(x) = x^3 - x - 2,  корень ≈ 1.5214 на [1, 2]
    auto f1 = [](double x) { return x*x*x - x - 2; };
    double root1 = Root(1.0, 2.0, 1e-6, f1);
    std::cout << "f(x)=x^3-x-2 на [1,2], eps=1e-6:\n"
              << "  корень ≈ " << root1
              << "  (проверка: f(" << root1 << ")="
              << f1(root1) << ")\n";

    // f(x) = cos(x) - x,  корень ≈ 0.7391 на [0, π/2]
    auto f2 = [](double x) { return std::cos(x) - x; };
    double root2 = Root(0.0, M_PI / 2, 1e-9, f2);
    std::cout << "f(x)=cos(x)-x на [0, π/2], eps=1e-9:\n"
              << "  корень ≈ " << root2
              << "  (проверка: f(" << root2 << ")="
              << f2(root2) << ")\n";
}

// ============================================================
int main() {
    task1();
    task2();
    task3();
    task4();
    return 0;
}