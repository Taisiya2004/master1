#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Класс для хранения информации о сотруднике
class Employee {
private:
    string name;
    int birthYear;
    string position;
    string unit;

public:
    // Конструктор
    Employee(const string& name,const int& birthYear, const string& position, const string& unit) :
        name(name), birthYear(birthYear), position(position), unit(unit) {}

    // Геттеры
    string getName() const {
        return name;
    }
    int getBirthYear() const {
        return birthYear;
    }
    string getPosition() const {
        return position;
    }
    string getUnit() const {
        return unit;
    }

    // Метод для вывода информации о сотруднике
    void print() const {
        cout << name << " " << birthYear << ", " << position << ", " << unit << endl;
    }
};

// Класс для хранения БД сотрудников
class EmployeeDB {
private:
    vector<Employee*> employees;

public:
    // Конструктор по умолчанию
    EmployeeDB() {}

    // Деструктор
    ~EmployeeDB() {
        for (auto emp : employees) {
            delete emp;
        }
    }

    // Метод для добавления сотрудника в БД
    void addEmployee(Employee* emp) {
        employees.push_back(emp);
    }

    // Метод для вывода информации о всех инженерах
    void printEngineers() const {
        cout << "Engineers:" << endl;
        for (auto emp : employees) {
            if (emp->getPosition() == "инженер") {
                emp->print();
            }
        }
    }

    // Метод для вывода информации о всех сотрудниках, не являющихся председателями, в порядке возрастания года рождения
    void printNonChairmen() const {
        // Создаем вектор для хранения сотрудников, не являющихся председателями
        vector<Employee*> nonChairmen;
        for (auto emp : employees) {
            if (emp->getPosition() != "председатель") {
                nonChairmen.push_back(emp);
            }
        }

        // Сортируем сотрудников, не являющихся председателями, по возрастанию года рождения
        sort(nonChairmen.begin(), nonChairmen.end(), [](Employee* a, Employee* b) {
            return a->getBirthYear() < b->getBirthYear();
            });

        // Выводим информацию о сотрудниках, не являющихся председателями, в порядке возрастания года рождения
        cout << "Non-chairmen:" << endl;
        for (auto emp : nonChairmen) {
            emp->print();
        }
    }
};

int main() {
    setlocale(LC_ALL, "rus");
    // Открываем файл
    ifstream file("Info.txt");
   

    // Создаем объект класса EmployeeDB
    EmployeeDB db;

    // Считываем данные из файла и добавляем сотрудников в БД
    string line;
    if (!file.is_open()) {
        std::cout << "Error opening file!" << std::endl;
    }
    else {
        std::string line;
        std::string name, position, group;
        int year;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::getline(ss, name, ',');
            ss >> year >> std::ws;
            std::getline(ss, position, ',');
            std::getline(ss >> std::ws, group);
            db.addEmployee(new Employee(name, year, position, group));
        }
    }
    // Закрываем файл
    file.close();

    // Выводим информацию о всех инженерах
    db.printEngineers();

    // Выводим информацию о всех сотрудниках, не являющихся председателями, в порядке возрастания года рождения
    db.printNonChairmen();

    return 0;
}
