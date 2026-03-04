#include <iostream>
#include <cmath>
#include <cstdlib>
#include <ctime>

// ============================================================
// Задание 1: y = cos|x^3 - x^2|  — через переменную
// ============================================================

void task1() {
    std::cout << "=== Задание 1: y = cos|x^3 - x^2| (переменная) ===\n";

    double x;
    std::cout << "Введите x: ";
    std::cin >> x;

    double inner = x * x * x - x * x;   // x^3 - x^2
    double y = std::cos(std::abs(inner));

    std::cout << "x       = " << x      << "\n";
    std::cout << "x^3-x^2 = " << inner  << "\n";
    std::cout << "y       = " << y      << "\n\n";
}

// ============================================================
// Задание 2: то же самое, но через ссылку на переменную
// ============================================================

void computeY(const double& x, double& y) {
    double inner = x * x * x - x * x;
    y = std::cos(std::abs(inner));
}

void task2() {
    std::cout << "=== Задание 2: y = cos|x^3 - x^2| (через ссылку) ===\n";

    double x;
    std::cout << "Введите x: ";
    std::cin >> x;

    double y;
    const double& refX = x;   // ссылка на x
    double& refY = y;          // ссылка на y

    computeY(refX, refY);

    std::cout << "x (через ссылку) = " << refX << "\n";
    std::cout << "y (через ссылку) = " << refY << "\n\n";
}

// ============================================================
// Задание 3: динамический массив + адресная арифметика
//
// 12.1 — заполнить случайными числами (диапазон: -50..49)
// 12.2 — найти минимальный элемент
// 12.3 — вычислить сумму элементов
// 12.4 — вывести положительные элементы
// ============================================================

void task3() {
    std::cout << "=== Задание 3: Динамический массив ===\n";

    int n;
    std::cout << "Введите размер массива N: ";
    std::cin >> n;

    // Выделение памяти
    int* arr = new int[n];

    std::srand(static_cast<unsigned>(std::time(nullptr)));

    // 12.1 — заполнение случайными числами [-50, 49]
    std::cout << "\n12.1 Массив (случайные числа):\n";
    for (int i = 0; i < n; i++) {
        *(arr + i) = (std::rand() % 100) - 50;   // адресная арифметика
        std::cout << *(arr + i) << " ";
    }
    std::cout << "\n";

    // 12.2 — минимальный элемент
    int minVal = *arr;                            // arr == &arr[0]
    for (int i = 1; i < n; i++)
        if (*(arr + i) < minVal)
            minVal = *(arr + i);
    std::cout << "\n12.2 Минимальный элемент: " << minVal << "\n";

    // 12.3 — сумма элементов
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += *(arr + i);
    std::cout << "\n12.3 Сумма элементов: " << sum << "\n";

    // 12.4 — положительные элементы
    std::cout << "\n12.4 Положительные элементы: ";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (*(arr + i) > 0) {
            std::cout << *(arr + i) << " ";
            found = true;
        }
    }
    if (!found) std::cout << "(нет положительных)";
    std::cout << "\n";

    // Освобождение памяти
    delete[] arr;
}

// ============================================================
int main() {
    task1();
    task2();
    task3();
    return 0;
}