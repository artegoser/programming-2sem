// ============================================================
//  Вариант 12: Информационно-справочная система
//  Заказы производства + справочник сотрудников
//  Структура данных: двунаправленный список (ручная реализация)
// ============================================================
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <limits>

// ============================================================
//  Структуры данных
// ============================================================

struct Worker {
    std::string code;        // код мастера (W001, ...)
    std::string fullName;    // ФИО
    std::string position;    // должность
    std::string phone;       // телефон
};

struct Order {
    std::string orderCode;   // код заказа (ORD-001, ...)
    std::string product;     // наименование продукции
    int         quantity;    // количество изделий
    std::string workerCode;  // код мастера (FK → workers)
};

// ============================================================
//  Узел двунаправленного списка
// ============================================================

struct Node {
    Order  data;
    Node*  prev;
    Node*  next;

    explicit Node(const Order& o) : data(o), prev(nullptr), next(nullptr) {}
};

// ============================================================
//  Двунаправленный список заказов
// ============================================================

class DoublyList {
public:
    Node* head;
    Node* tail;
    int   size;

    DoublyList() : head(nullptr), tail(nullptr), size(0) {}
    ~DoublyList() { clear(); }

    // Добавить в конец
    void pushBack(const Order& o) {
        Node* node = new Node(o);
        if (!tail) {
            head = tail = node;
        } else {
            node->prev = tail;
            tail->next = node;
            tail = node;
        }
        size++;
    }

    // Удалить узел по коду заказа
    bool removeByCode(const std::string& code) {
        Node* cur = head;
        while (cur) {
            if (cur->data.orderCode == code) {
                if (cur->prev) cur->prev->next = cur->next;
                else           head = cur->next;
                if (cur->next) cur->next->prev = cur->prev;
                else           tail = cur->prev;
                delete cur;
                size--;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    // Поиск по коду заказа
    Node* findByCode(const std::string& code) const {
        Node* cur = head;
        while (cur) {
            if (cur->data.orderCode == code) return cur;
            cur = cur->next;
        }
        return nullptr;
    }

    // Проверка уникальности кода заказа
    bool codeExists(const std::string& code) const {
        return findByCode(code) != nullptr;
    }

    // Сортировка по количеству изделий (пузырёк — без пересоздания узлов)
    void sortByQuantity() {
        if (!head || head == tail) return;
        bool swapped;
        do {
            swapped = false;
            Node* cur = head;
            while (cur->next) {
                if (cur->data.quantity > cur->next->data.quantity) {
                    std::swap(cur->data, cur->next->data);
                    swapped = true;
                }
                cur = cur->next;
            }
        } while (swapped);
    }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        size = 0;
    }
};

// ============================================================
//  Справочник сотрудников
// ============================================================

class WorkerDB {
public:
    std::vector<Worker> workers;

    bool loadFromFile(const std::string& filename) {
        std::ifstream fin(filename);
        if (!fin.is_open()) return false;
        workers.clear();
        std::string line;
        while (std::getline(fin, line)) {
            if (line.empty()) continue;
            Worker w;
            std::istringstream ss(line);
            std::getline(ss, w.code,     '|');
            std::getline(ss, w.fullName, '|');
            std::getline(ss, w.position, '|');
            std::getline(ss, w.phone,    '|');
            workers.push_back(w);
        }
        return true;
    }

    bool saveToFile(const std::string& filename) const {
        std::ofstream fout(filename);
        if (!fout.is_open()) return false;
        for (const auto& w : workers)
            fout << w.code << "|" << w.fullName << "|"
                 << w.position << "|" << w.phone << "\n";
        return true;
    }

    // Проверка: существует ли мастер с данным кодом
    bool workerExists(const std::string& code) const {
        for (const auto& w : workers)
            if (w.code == code) return true;
        return false;
    }

    // Добавить мастера (false — код уже занят)
    bool addWorker(const Worker& w) {
        if (workerExists(w.code)) return false;
        workers.push_back(w);
        return true;
    }

    // Удалить мастера по коду (false — не найден)
    bool removeByCode(const std::string& code) {
        for (auto it = workers.begin(); it != workers.end(); ++it) {
            if (it->code == code) {
                workers.erase(it);
                return true;
            }
        }
        return false;
    }

    // Получить мастера по коду (nullptr если нет)
    const Worker* getWorker(const std::string& code) const {
        for (const auto& w : workers)
            if (w.code == code) return &w;
        return nullptr;
    }

    void printAll() const {
        std::cout << "\n" << std::string(72, '=') << "\n";
        std::cout << " СПРАВОЧНИК СОТРУДНИКОВ\n";
        std::cout << std::string(72, '=') << "\n";
        std::cout << std::left
                  << std::setw(7)  << "Код"
                  << std::setw(28) << "ФИО"
                  << std::setw(22) << "Должность"
                  << "Телефон\n";
        std::cout << std::string(72, '-') << "\n";
        for (const auto& w : workers) {
            std::cout << std::left
                      << std::setw(7)  << w.code
                      << std::setw(28) << w.fullName
                      << std::setw(22) << w.position
                      << w.phone << "\n";
        }
        std::cout << std::string(72, '=') << "\n";
    }
};

// ============================================================
//  Вспомогательные функции вывода
// ============================================================

const char* ORDERS_FILE  = "orders.txt";
const char* WORKERS_FILE = "workers.txt";

void printLine() {
    std::cout << "+" << std::string(10,'-')
              << "+" << std::string(28,'-')
              << "+" << std::string(8,'-')
              << "+" << std::string(7,'-') << "+\n";
}

void printHeader() {
    printLine();
    std::cout << "| " << std::left << std::setw(9)  << "Код заказа"
              << "| " << std::setw(27) << "Наименование продукции"
              << "| " << std::setw(7)  << "Кол-во"
              << "| " << std::setw(6)  << "Мастер" << "|\n";
    printLine();
}

void printOrder(const Order& o) {
    std::cout << "| " << std::left << std::setw(9)  << o.orderCode
              << "| " << std::setw(27) << o.product
              << "| " << std::right << std::setw(6) << o.quantity
              << " | " << std::left << std::setw(5) << o.workerCode << " |\n";
}

void viewList(const DoublyList& list) {
    if (!list.head) {
        std::cout << "  [Список пуст]\n";
        return;
    }
    std::cout << "\n";
    printHeader();
    Node* cur = list.head;
    while (cur) {
        printOrder(cur->data);
        cur = cur->next;
    }
    printLine();
    std::cout << "  Записей: " << list.size << "\n";
}

// ============================================================
//  Загрузка/сохранение заказов
// ============================================================

bool loadOrdersFromFile(DoublyList& list, const std::string& filename) {
    std::ifstream fin(filename);
    if (!fin.is_open()) return false;

    std::string line;
    int loaded = 0;
    while (std::getline(fin, line)) {
        if (line.empty()) continue;
        Order o;
        std::istringstream ss(line);
        std::string qty;
        std::getline(ss, o.orderCode,  '|');
        std::getline(ss, o.product,    '|');
        std::getline(ss, qty,          '|');
        std::getline(ss, o.workerCode, '|');
        o.quantity = std::stoi(qty);
        list.pushBack(o);
        loaded++;
    }
    std::cout << "  Загружено записей: " << loaded << "\n";
    return true;
}

bool saveOrdersToFile(const DoublyList& list, const std::string& filename) {
    std::ofstream fout(filename);
    if (!fout.is_open()) return false;

    Node* cur = list.head;
    while (cur) {
        fout << cur->data.orderCode  << "|"
             << cur->data.product    << "|"
             << cur->data.quantity   << "|"
             << cur->data.workerCode << "\n";
        cur = cur->next;
    }
    return true;
}

// ============================================================
//  Ввод заказа с клавиатуры (с валидацией)
// ============================================================

std::string inputLine(const std::string& prompt) {
    std::cout << prompt;
    std::string s;
    std::getline(std::cin, s);
    return s;
}

Order inputOrder(const DoublyList& list, const WorkerDB& wdb) {
    Order o;
    // Код заказа — уникальность
    while (true) {
        o.orderCode = inputLine("  Код заказа (напр. ORD-009): ");
        if (o.orderCode.empty()) { std::cout << "  Код не может быть пустым.\n"; continue; }
        if (list.codeExists(o.orderCode)) {
            std::cout << "  [!] Заказ с кодом \"" << o.orderCode << "\" уже существует!\n";
            continue;
        }
        break;
    }
    o.product = inputLine("  Наименование продукции:      ");

    while (true) {
        std::string qty = inputLine("  Количество изделий:         ");
        try {
            o.quantity = std::stoi(qty);
            if (o.quantity > 0) break;
        } catch (...) {}
        std::cout << "  [!] Введите целое положительное число.\n";
    }

    // Код мастера — должен быть в справочнике
    while (true) {
        o.workerCode = inputLine("  Код мастера (напр. W001):   ");
        if (wdb.workerExists(o.workerCode)) break;
        std::cout << "  [!] Мастер с кодом \"" << o.workerCode
                  << "\" не найден в справочнике!\n";
        std::cout << "  Доступные коды: ";
        for (const auto& w : wdb.workers)
            std::cout << w.code << " ";
        std::cout << "\n";
    }
    return o;
}

// ============================================================
//  Ввод мастера с клавиатуры (с валидацией)
// ============================================================

Worker inputWorker(const WorkerDB& wdb) {
    Worker w;
    while (true) {
        w.code = inputLine("  Код мастера (напр. W006):   ");
        if (w.code.empty()) { std::cout << "  Код не может быть пустым.\n"; continue; }
        if (wdb.workerExists(w.code)) {
            std::cout << "  [!] Мастер с кодом \"" << w.code << "\" уже существует!\n";
            continue;
        }
        break;
    }
    while (true) {
        w.fullName = inputLine("  ФИО:                        ");
        if (!w.fullName.empty()) break;
        std::cout << "  ФИО не может быть пустым.\n";
    }
    while (true) {
        w.position = inputLine("  Должность:                  ");
        if (!w.position.empty()) break;
        std::cout << "  Должность не может быть пустой.\n";
    }
    while (true) {
        w.phone = inputLine("  Телефон:                    ");
        if (!w.phone.empty()) break;
        std::cout << "  Телефон не может быть пустым.\n";
    }
    return w;
}

// ============================================================
//  Справочная информация о мастере
// ============================================================

void workerInfo(const WorkerDB& wdb) {
    std::string code = inputLine("\n  Введите код мастера: ");
    const Worker* w = wdb.getWorker(code);
    if (!w) {
        std::cout << "  [!] Мастер \"" << code << "\" не найден.\n";
        return;
    }
    std::cout << "\n  ┌─ Справка о сотруднике ────────────────┐\n";
    std::cout << "  │ Код:       " << std::left << std::setw(29) << w->code      << "│\n";
    std::cout << "  │ ФИО:       " << std::setw(29) << w->fullName  << "│\n";
    std::cout << "  │ Должность: " << std::setw(29) << w->position  << "│\n";
    std::cout << "  │ Телефон:   " << std::setw(29) << w->phone     << "│\n";
    std::cout << "  └───────────────────────────────────────┘\n";
}

// ============================================================
//  Главное меню
// ============================================================

void clearInput() {
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void menu(DoublyList& list, WorkerDB& wdb) {
    while (true) {
        std::cout << "\n";
        std::cout << std::string(44, '=') << "\n";
        std::cout << "  СИСТЕМА УПРАВЛЕНИЯ ЗАКАЗАМИ (Вариант 12)\n";
        std::cout << std::string(44, '=') << "\n";
        std::cout << "  --- Заказы ---\n";
        std::cout << "  1. Просмотр всех заказов\n";
        std::cout << "  2. Загрузить заказы из файла (" << ORDERS_FILE << ")\n";
        std::cout << "  3. Ввести заказ с клавиатуры\n";
        std::cout << "  4. Удалить заказ по коду\n";
        std::cout << "  5. Поиск заказа по коду\n";
        std::cout << "  6. Сортировка по количеству изделий\n";
        std::cout << "  7. Сохранить заказы в файл (" << ORDERS_FILE << ")\n";
        std::cout << "  --- Мастера ---\n";
        std::cout << "  8. Просмотр справочника сотрудников\n";
        std::cout << "  9. Справочная информация о мастере\n";
        std::cout << " 10. Добавить мастера\n";
        std::cout << " 11. Удалить мастера по коду\n";
        std::cout << " 12. Сохранить справочник в файл (" << WORKERS_FILE << ")\n";
        std::cout << "  0. Выход\n";
        std::cout << std::string(44, '-') << "\n";
        std::cout << "  Выбор: ";

        int choice;
        std::cin >> choice;
        clearInput();

        switch (choice) {
            // --- Просмотр ---
            case 1:
                std::cout << "\n  === Содержимое базы заказов ===\n";
                viewList(list);
                break;

            // --- Загрузка из файла ---
            case 2:
                list.clear();
                if (loadOrdersFromFile(list, ORDERS_FILE))
                    std::cout << "  Файл \"" << ORDERS_FILE << "\" загружен.\n";
                else
                    std::cout << "  [!] Не удалось открыть файл \"" << ORDERS_FILE << "\".\n";
                break;

            // --- Ввод с клавиатуры ---
            case 3: {
                std::cout << "\n  === Ввод нового заказа ===\n";
                Order o = inputOrder(list, wdb);
                list.pushBack(o);
                const Worker* w = wdb.getWorker(o.workerCode);
                std::cout << "  [OK] Заказ \"" << o.orderCode << "\" добавлен.\n";
                std::cout << "       Мастер: " << (w ? w->fullName : "?") << "\n";
                break;
            }

            // --- Удаление ---
            case 4: {
                std::string code = inputLine("\n  Введите код заказа для удаления: ");
                if (list.removeByCode(code))
                    std::cout << "  [OK] Заказ \"" << code << "\" удалён.\n";
                else
                    std::cout << "  [!] Заказ \"" << code << "\" не найден.\n";
                break;
            }

            // --- Поиск ---
            case 5: {
                std::string code = inputLine("\n  Введите код заказа для поиска: ");
                Node* found = list.findByCode(code);
                if (found) {
                    std::cout << "\n  Найден заказ:\n";
                    printHeader();
                    printOrder(found->data);
                    printLine();
                    // Дополнительно — справка о мастере
                    const Worker* w = wdb.getWorker(found->data.workerCode);
                    if (w)
                        std::cout << "  Мастер: " << w->fullName
                                  << " (" << w->position << "), "
                                  << w->phone << "\n";
                } else {
                    std::cout << "  [!] Заказ \"" << code << "\" не найден.\n";
                }
                break;
            }

            // --- Сортировка ---
            case 6:
                list.sortByQuantity();
                std::cout << "  [OK] Список отсортирован по количеству изделий.\n";
                viewList(list);
                break;

            // --- Сохранение в файл ---
            case 7:
                if (saveOrdersToFile(list, ORDERS_FILE))
                    std::cout << "  [OK] Данные сохранены в \"" << ORDERS_FILE << "\".\n";
                else
                    std::cout << "  [!] Ошибка записи в файл.\n";
                break;

            // --- Справочник сотрудников ---
            case 8:
                wdb.printAll();
                break;

            // --- Справка о мастере ---
            case 9:
                workerInfo(wdb);
                break;

            // --- Добавить мастера ---
            case 10: {
                std::cout << "\n  === Добавление нового мастера ===\n";
                Worker w = inputWorker(wdb);
                wdb.addWorker(w);
                std::cout << "  [OK] Мастер \"" << w.code << "\" (" << w.fullName << ") добавлен.\n";
                break;
            }

            // --- Удалить мастера ---
            case 11: {
                std::string code = inputLine("\n  Введите код мастера для удаления: ");
                // Предупреждение, если на мастера ссылаются заказы
                int refs = 0;
                for (Node* cur = list.head; cur; cur = cur->next)
                    if (cur->data.workerCode == code) refs++;
                if (refs > 0)
                    std::cout << "  [!] Внимание: на этого мастера ссылаются "
                              << refs << " заказ(ов).\n"
                              << "      Мастер будет удалён, но заказы сохранят его код.\n";
                if (wdb.removeByCode(code))
                    std::cout << "  [OK] Мастер \"" << code << "\" удалён из справочника.\n";
                else
                    std::cout << "  [!] Мастер \"" << code << "\" не найден.\n";
                break;
            }

            // --- Сохранить справочник ---
            case 12:
                if (wdb.saveToFile(WORKERS_FILE))
                    std::cout << "  [OK] Справочник сохранён в \"" << WORKERS_FILE << "\".\n";
                else
                    std::cout << "  [!] Ошибка записи в файл.\n";
                break;

            // --- Выход ---
            case 0:
                std::cout << "\n  Выход из программы. До свидания!\n";
                return;

            default:
                std::cout << "  [!] Неверный выбор.\n";
        }
    }
}

// ============================================================
int main() {
    DoublyList list;
    WorkerDB   wdb;

    std::cout << "=== Инициализация системы ===\n";

    // Загрузка справочника сотрудников (обязательно)
    if (!wdb.loadFromFile(WORKERS_FILE)) {
        std::cerr << "[!] Критическая ошибка: файл справочника \""
                  << WORKERS_FILE << "\" не найден!\n";
        return 1;
    }
    std::cout << "  Справочник сотрудников: " << wdb.workers.size() << " записей.\n";

    // Автоматическая загрузка заказов при старте
    std::cout << "  Загрузка заказов из \"" << ORDERS_FILE << "\": ";
    if (!loadOrdersFromFile(list, ORDERS_FILE))
        std::cout << "  [!] Файл не найден, начинаем с пустой базы.\n";

    menu(list, wdb);
    return 0;
}