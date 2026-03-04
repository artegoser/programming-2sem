#include <iostream>
#include <stack>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

// ============================================================
// Задание 1: STL stack — клиенты банка
// ============================================================

struct Client {
    std::string name;
    double      balance;
};

// Вывод содержимого стека (не разрушает оригинал — работаем с копией)
void printStack(std::stack<Client> s) {
    std::cout << "\n+---------------------------+---------------+\n";
    std::cout << "| Фамилия клиента           |  Сумма (руб.) |\n";
    std::cout << "+---------------------------+---------------+\n";

    while (!s.empty()) {
        const Client& c = s.top();
        std::cout << "| " << std::left  << std::setw(25) << c.name
                  << " | " << std::right << std::setw(13)
                  << std::fixed << std::setprecision(2) << c.balance
                  << " |\n";
        s.pop();
    }
    std::cout << "+---------------------------+---------------+\n";
}

void task1() {
    std::cout << "========================================\n";
    std::cout << "  Задание 1: STL stack — Клиенты банка\n";
    std::cout << "========================================\n";

    std::stack<Client> bank;

    // Заполнение стека
    std::vector<Client> data = {
        {"Иванов И.И.",    50000.00},
        {"Петрова А.С.",  120000.00},
        {"Сидоров В.В.",   75000.50},
        {"Кузнецова О.П.",210000.00},
        {"Новиков Д.Д.",   99999.99},
        {"Морозов С.Л.",  350000.00},
        {"Лебедева Е.А.",  15000.00},
        {"Волков А.Н.",   105000.00},
    };

    std::cout << "\nДобавляем клиентов в стек (LIFO):\n";
    for (const auto& c : data) {
        bank.push(c);
        std::cout << "  push -> " << c.name
                  << " (" << c.balance << " руб.)\n";
    }

    std::cout << "\nРазмер стека: " << bank.size() << "\n";
    std::cout << "Верхний элемент: " << bank.top().name
              << " — " << bank.top().balance << " руб.\n";

    // Просмотр стека (через копию — оригинал не трогаем)
    std::cout << "\nПросмотр всех записей (от вершины к основанию):";
    printStack(bank);

    // Подсчёт клиентов с балансом > 100 000
    int richCount = 0;
    std::stack<Client> temp = bank;   // копия для подсчёта
    std::cout << "\nКлиенты с суммой на счету > 100 000 руб.:\n";
    std::cout << "+---------------------------+---------------+\n";
    while (!temp.empty()) {
        if (temp.top().balance > 100000.0) {
            std::cout << "  " << std::left << std::setw(25)
                      << temp.top().name
                      << " -> " << temp.top().balance << " руб.\n";
            richCount++;
        }
        temp.pop();
    }
    std::cout << "+---------------------------+---------------+\n";
    std::cout << "Итого таких клиентов: " << richCount << "\n\n";
}

// ============================================================
// Задание 2: STL vector — вставка 25 и удаление отрицательных
// ============================================================

void printVector(const std::vector<int>& v, const std::string& label) {
    std::cout << label << " [";
    for (size_t i = 0; i < v.size(); i++) {
        std::cout << v[i];
        if (i + 1 < v.size()) std::cout << ", ";
    }
    std::cout << "]  (размер: " << v.size() << ")\n";
}

void task2() {
    std::cout << "========================================\n";
    std::cout << "  Задание 2: STL vector\n";
    std::cout << "========================================\n";

    // Исходный вектор
    std::vector<int> v = {-3, 7, 0, -1, 4, 15, -8, 2, -5, 10};
    printVector(v, "Исходный вектор:          ");

    // --- Шаг 1: Вставить 25 перед каждым положительным элементом ---
    // Идём с конца, чтобы вставка не сбивала индексы
    for (int i = static_cast<int>(v.size()) - 1; i >= 0; i--) {
        if (v[i] > 0) {
            v.insert(v.begin() + i, 25);
        }
    }
    printVector(v, "После вставки 25:         ");

    // --- Шаг 2: Удалить все отрицательные числа ---
    // erase + remove_if — идиома «стереть-удалить»
    v.erase(
        std::remove_if(v.begin(), v.end(),
                       [](int x) { return x < 0; }),
        v.end()
    );
    printVector(v, "После удаления < 0:       ");
}

// ============================================================
int main() {
    task1();
    task2();
    return 0;
}