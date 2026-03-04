#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>

// ============================================================
// Структура должна совпадать с той, что использовалась при создании файла
// ============================================================
struct Student {
    char name[64];
    int  grade[3];
};

const char* DISCIPLINES[3] = {
    "Математика",
    "Физика",
    "Программирование"
};

// Возвращает количество задолженностей студента (оценка < 3 или 0)
int countDebts(const Student& s) {
    int debts = 0;
    for (int i = 0; i < 3; i++)
        if (s.grade[i] < 3)   // 0 (не сдан) и 2 (неуд) — задолженность
            debts++;
    return debts;
}

// Печатает строку-разделитель
void printLine() {
    std::cout << "+--" << std::string(64, '-')
              << "+--------+--------+--------+----------+\n";
}

// Заголовок таблицы
void printHeader() {
    printLine();
    std::cout << "| " << std::left << std::setw(64) << "ФИО студента"
              << "| Матем. | Физика | Прогр. | Задолж.  |\n";
    printLine();
}

int main() {
    const char* filename = "STUDENT.dat";

    std::ifstream fin(filename, std::ios::binary);
    if (!fin.is_open()) {
        std::cerr << "Ошибка: файл \"" << filename
                  << "\" не найден. Сначала запустите create_students.\n";
        return 1;
    }

    std::cout << "=== Обработка файла " << filename << " ===\n";
    std::cout << "Студенты, имеющие хотя бы одну задолженность:\n\n";

    printHeader();

    int totalStudents = 0;
    int debtorCount   = 0;
    Student s;

    while (fin.read(reinterpret_cast<char*>(&s), sizeof(Student))) {
        totalStudents++;
        int debts = countDebts(s);

        if (debts > 0) {
            debtorCount++;

            // Оценку отображаем: 0 → "н/с" (не сдан), 2 → "2", иначе цифра
            auto gradeStr = [](int g) -> std::string {
                if (g == 0) return " н/с";
                return "   " + std::to_string(g);
            };

            std::cout << "| " << std::left  << std::setw(64) << s.name
                      << "|" << gradeStr(s.grade[0])
                      << "    |" << gradeStr(s.grade[1])
                      << "    |" << gradeStr(s.grade[2])
                      << "    |    "
                      << debts << " шт.  |\n";
        }
    }

    printLine();
    fin.close();

    if (debtorCount == 0) {
        std::cout << "\nСтудентов с задолженностями не найдено.\n";
    } else {
        std::cout << "\nИтого студентов в файле:    " << totalStudents << "\n";
        std::cout << "Из них с задолженностями:   " << debtorCount    << "\n";
    }

    return 0;
}