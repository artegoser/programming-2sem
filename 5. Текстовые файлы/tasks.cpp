#include <iostream>
#include <fstream>
#include <cctype>
#include <string>

// ============================================================
// Проверяет, является ли символ гласной буквой (a,e,i,o,u)
// ============================================================
bool isVowel(char c) {
    c = static_cast<char>(std::tolower(c));
    return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

// ============================================================
// Обрабатывает один символ в контексте потока:
//   если это первая буква слова и она гласная — делаем заглавной
//
//   inWord  — флаг «мы сейчас внутри слова»
// ============================================================
char processChar(char c, bool& inWord) {
    if (std::isalpha(static_cast<unsigned char>(c))) {
        if (!inWord) {
            // Первая буква нового слова
            inWord = true;
            if (isVowel(c)) {
                return static_cast<char>(std::toupper(c));
            }
        }
    } else {
        inWord = false;   // пробел, пунктуация — слово закончилось
    }
    return c;
}

int main() {
    const std::string inputFile  = "input.txt";
    const std::string outputFile = "output.txt";

    // Открываем файлы
    std::ifstream fin(inputFile);
    if (!fin.is_open()) {
        std::cerr << "Ошибка: не удалось открыть файл \"" << inputFile << "\"\n";
        return 1;
    }

    std::ofstream fout(outputFile);
    if (!fout.is_open()) {
        std::cerr << "Ошибка: не удалось создать файл \"" << outputFile << "\"\n";
        return 1;
    }

    std::cout << "Обработка файла \"" << inputFile << "\"...\n\n";

    bool inWord = false;
    int  wordsFixed = 0;   // счётчик заменённых слов
    char c;

    while (fin.get(c)) {
        char processed = processChar(c, inWord);

        // Если символ изменился — была замена (первая буква слова → uppercase)
        if (processed != c) {
            wordsFixed++;
        }

        fout.put(processed);
    }

    fin.close();
    fout.close();

    // Читаем и выводим оба файла для наглядного сравнения
    auto printFile = [](const std::string& name) {
        std::ifstream f(name);
        std::cout << "--- " << name << " ---\n";
        std::string line;
        while (std::getline(f, line))
            std::cout << line << "\n";
        std::cout << "\n";
    };

    printFile(inputFile);
    printFile(outputFile);

    std::cout << "Готово. Слов с заглавной гласной в начале: "
              << wordsFixed << "\n";
    std::cout << "Результат записан в \"" << outputFile << "\"\n";

    return 0;
}