#include <iostream>
#include <fstream>
#include <cstring>

// ============================================================
// Структура записи о студенте
// Фиксированная длина строк — для корректной работы с бинарным файлом
// ============================================================
struct Student {
    char name[64];     // ФИО студента
    int  grade[3];     // Оценки по трём дисциплинам (2–5, 0 = не сдан)
};

// Вспомогательный ввод оценки с проверкой диапазона
int inputGrade(const char* discipline) {
    int g;
    while (true) {
        std::cout << "    " << discipline << " (2-5, 0=не сдан): ";
        std::cin >> g;
        if (g == 0 || (g >= 2 && g <= 5)) return g;
        std::cout << "    [!] Введите 0 или число от 2 до 5.\n";
    }
}

int main() {
    const char* filename = "STUDENT.dat";

    std::ofstream fout(filename, std::ios::binary | std::ios::trunc);
    if (!fout.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл \"" << filename << "\"\n";
        return 1;
    }

    int n;
    std::cout << "=== Создание файла " << filename << " ===\n";
    std::cout << "Введите количество студентов: ";
    std::cin >> n;
    std::cin.ignore();

    const char* disciplines[3] = {
        "Математика    ",
        "Физика        ",
        "Программирование"
    };

    for (int i = 0; i < n; i++) {
        Student s{};
        std::cout << "\n--- Студент #" << (i + 1) << " ---\n";
        std::cout << "  ФИО: ";
        std::cin.getline(s.name, sizeof(s.name));

        std::cout << "  Оценки:\n";
        for (int j = 0; j < 3; j++)
            s.grade[j] = inputGrade(disciplines[j]);

        fout.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }

    fout.close();
    std::cout << "\nФайл \"" << filename << "\" успешно создан. "
              << "Записей: " << n << "\n";
    return 0;
}