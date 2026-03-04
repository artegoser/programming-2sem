#include <iostream>
#include <cstdlib>
#include <ctime>

// ============================================================
// Задание 1: Одномерный массив — функции ввода/вывода,
//            поиск минимума и сумма элементов
// ============================================================

// Ввод массива с клавиатуры
void inputArray(int* arr, int n) {
    std::cout << "Введите " << n << " элементов массива:\n";
    for (int i = 0; i < n; i++) {
        std::cout << "  arr[" << i << "] = ";
        std::cin >> *(arr + i);
    }
}

// Вывод массива на экран
void printArray(const int* arr, int n) {
    std::cout << "[ ";
    for (int i = 0; i < n; i++)
        std::cout << *(arr + i) << " ";
    std::cout << "]\n";
}

// 12.1 — минимальный элемент; возвращает значение, индекс через ссылку
int findMin(const int* arr, int n, int& minIndex) {
    int minVal = *arr;
    minIndex = 0;
    for (int i = 1; i < n; i++) {
        if (*(arr + i) < minVal) {
            minVal = *(arr + i);
            minIndex = i;
        }
    }
    return minVal;
}

// 12.2 — сумма элементов
long long calcSum(const int* arr, int n) {
    long long sum = 0;
    for (int i = 0; i < n; i++)
        sum += *(arr + i);
    return sum;
}

void task1() {
    std::cout << "========================================\n";
    std::cout << "  Задание 1: Одномерный массив\n";
    std::cout << "========================================\n";

    int n;
    std::cout << "Введите размер массива N: ";
    std::cin >> n;

    int* arr = new int[n];

    inputArray(arr, n);

    std::cout << "\nМассив: ";
    printArray(arr, n);

    int minIdx;
    int minVal = findMin(arr, n, minIdx);
    std::cout << "12.1 Минимальный элемент: " << minVal
              << " (индекс " << minIdx << ")\n";

    std::cout << "12.2 Сумма элементов:     " << calcSum(arr, n) << "\n";

    delete[] arr;
    std::cout << "\n";
}

// ============================================================
// Задание 2: Матрица A(n,m) → одномерный массив B
//
//   B[i] = (сумма элементов i-й строки) * i
//   (строки нумеруются с 1, индексы с 0 → множитель = i+1)
// ============================================================

// Ввод матрицы (массив указателей на строки)
void inputMatrix(int** A, int n, int m) {
    std::cout << "Введите элементы матрицы " << n << "x" << m << ":\n";
    for (int i = 0; i < n; i++) {
        std::cout << "  Строка " << (i + 1) << ": ";
        for (int j = 0; j < m; j++)
            std::cin >> A[i][j];
    }
}

// Вывод матрицы
void printMatrix(int** A, int n, int m) {
    for (int i = 0; i < n; i++) {
        std::cout << "  ";
        for (int j = 0; j < m; j++)
            std::cout << A[i][j] << "\t";
        std::cout << "\n";
    }
}

// Вывод вещественного массива B
void printArrayB(const long long* B, int n) {
    std::cout << "B = [ ";
    for (int i = 0; i < n; i++)
        std::cout << B[i] << " ";
    std::cout << "]\n";
}

// Формирование массива B:
//   B[i] = (sum of A[i][0..m-1]) * (i+1)
void buildB(int** A, int n, int m, long long* B) {
    for (int i = 0; i < n; i++) {
        long long rowSum = 0;
        for (int j = 0; j < m; j++)
            rowSum += A[i][j];
        B[i] = rowSum * (i + 1);   // номер строки = i+1
    }
}

void task2() {
    std::cout << "========================================\n";
    std::cout << "  Задание 2: Матрица → массив B\n";
    std::cout << "========================================\n";

    int n, m;
    std::cout << "Введите число строк n:    ";
    std::cin >> n;
    std::cout << "Введите число столбцов m: ";
    std::cin >> m;

    // Динамическое выделение матрицы
    int** A = new int*[n];
    for (int i = 0; i < n; i++)
        A[i] = new int[m];

    // Динамический массив B
    long long* B = new long long[n];

    inputMatrix(A, n, m);

    std::cout << "\nМатрица A:\n";
    printMatrix(A, n, m);

    buildB(A, n, m, B);

    std::cout << "\nМассив B (B[i] = сумма строки i * номер строки):\n";
    printArrayB(B, n);

    std::cout << "\nДетализация:\n";
    for (int i = 0; i < n; i++) {
        long long rowSum = B[i] / (i + 1);
        std::cout << "  Строка " << (i + 1)
                  << ": сумма = " << rowSum
                  << ",  * " << (i + 1)
                  << " = " << B[i] << "\n";
    }

    // Освобождение памяти
    for (int i = 0; i < n; i++)
        delete[] A[i];
    delete[] A;
    delete[] B;
}

// ============================================================
int main() {
    task1();
    task2();
    return 0;
}