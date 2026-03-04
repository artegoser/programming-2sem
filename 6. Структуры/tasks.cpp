#include <iostream>
#include <string>

// ============================================================
// Задание 2: Структура Date и функция проверки корректности
// (описана раньше, т.к. используется в Задании 1)
// ============================================================

struct Date {
    int day;
    int month;
    int year;
};

// Проверяет, является ли год високосным
bool isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

// Возвращает количество дней в месяце
int daysInMonth(int month, int year) {
    const int days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && isLeapYear(year))
        return 29;
    if (month < 1 || month > 12)
        return 0;
    return days[month];
}

// Функция «верна ли дата»
bool isValidDate(const Date& d) {
    if (d.year < 1 || d.year > 9999)    return false;
    if (d.month < 1 || d.month > 12)    return false;
    if (d.day < 1 || d.day > daysInMonth(d.month, d.year))
                                         return false;
    return true;
}

// Вспомогательный ввод даты с проверкой
Date inputDate(const std::string& prompt) {
    Date d;
    while (true) {
        std::cout << prompt;
        std::cout << "\n  День   : "; std::cin >> d.day;
        std::cout << "  Месяц  : "; std::cin >> d.month;
        std::cout << "  Год    : "; std::cin >> d.year;
        std::cin.ignore();
        if (isValidDate(d)) break;
        std::cout << "  [!] Некорректная дата. Повторите ввод.\n";
    }
    return d;
}

void task2() {
    std::cout << "========================================\n";
    std::cout << "  Задание 2: Проверка корректности даты\n";
    std::cout << "========================================\n";

    // Демонстрируем несколько тестовых дат
    Date tests[] = {
        {29, 2, 2024},   // Верна (2024 — високосный)
        {29, 2, 2023},   // Неверна
        {31, 4, 2020},   // Неверна (в апреле 30 дней)
        {15, 8, 1999},   // Верна
        { 0, 1, 2000},   // Неверна
    };

    for (const auto& d : tests) {
        std::cout << "  " << d.day << "." << d.month << "." << d.year
                  << " -> "
                  << (isValidDate(d) ? "Верная дата" : "НЕВЕРНАЯ дата")
                  << "\n";
    }

    std::cout << "\nВведите дату для проверки:\n";
    Date d = inputDate("");
    std::cout << "  Итог: дата "
              << d.day << "." << d.month << "." << d.year
              << " — " << (isValidDate(d) ? "верная." : "неверная.")
              << "\n\n";
}

// ============================================================
// Задание 1: Структура NOTE, массив из 9 записей,
//            поиск по году рождения
// ============================================================

struct NOTE {
    std::string fullName;     // фамилия и имя
    std::string phone;        // номер телефона
    int birthDate[3];         // [0]=день, [1]=месяц, [2]=год
};

const int SIZE = 9;

// Ввод одной записи
NOTE inputNote(int index) {
    NOTE n;
    std::cout << "\n--- Запись #" << (index + 1) << " ---\n";
    std::cout << "  Фамилия и имя : ";
    std::getline(std::cin, n.fullName);
    std::cout << "  Номер телефона: ";
    std::getline(std::cin, n.phone);

    // Ввод даты рождения с проверкой
    Date bd;
    while (true) {
        std::cout << "  Дата рождения:\n";
        std::cout << "    День  : "; std::cin >> n.birthDate[0];
        std::cout << "    Месяц : "; std::cin >> n.birthDate[1];
        std::cout << "    Год   : "; std::cin >> n.birthDate[2];
        std::cin.ignore();

        bd = {n.birthDate[0], n.birthDate[1], n.birthDate[2]};
        if (isValidDate(bd)) break;
        std::cout << "  [!] Некорректная дата рождения. Повторите.\n";
    }
    return n;
}

// Вывод одной записи
void printNote(const NOTE& n) {
    std::cout << "  Имя   : " << n.fullName << "\n";
    std::cout << "  Тел.  : " << n.phone    << "\n";
    std::cout << "  Д.р.  : "
              << n.birthDate[0] << "."
              << n.birthDate[1] << "."
              << n.birthDate[2] << "\n";
}

void task1() {
    std::cout << "========================================\n";
    std::cout << "  Задание 1: Телефонная книга (NOTE)\n";
    std::cout << "========================================\n";

    NOTE notebook[SIZE];

    std::cout << "Введите данные для " << SIZE << " записей:\n";
    for (int i = 0; i < SIZE; i++)
        notebook[i] = inputNote(i);

    int searchYear;
    std::cout << "\nВведите год рождения для поиска: ";
    std::cin >> searchYear;
    std::cin.ignore();

    std::cout << "\nЛюди, родившиеся в " << searchYear << " году:\n";
    bool found = false;
    for (int i = 0; i < SIZE; i++) {
        if (notebook[i].birthDate[2] == searchYear) {
            std::cout << "---\n";
            printNote(notebook[i]);
            found = true;
        }
    }
    if (!found)
        std::cout << "  Никто из введённых людей не родился в "
                  << searchYear << " году.\n";
}

// ============================================================
int main() {
    // Сначала демонстрируем Задание 2 (проверку дат),
    // затем запускаем основное Задание 1
    task2();
    task1();
    return 0;
}