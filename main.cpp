#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace {
    const std::string engineer_ = "инженер";
    const std::string chairman_ = "председатель";
}

class Person {
private:
    std::string Name;
    int Year;
    std::string Position;
    std::string Group;
public:
    Person(const std::string& name, int year, const std::string& position, const std::string& group) :
        Name(name), Year(year), Position(position), Group(group) {}

    std::string GetName() const { return Name; }
    int GetYear() const { return Year; }
    std::string GetPosition() const  { return Position; }
    std::string GetGroup() const { return Group; }
    void print() const {
        std::cout << Name << ", " << Year << ", " << Position << ", " << Group << std::endl;
    }
};

class DB {
private:
    std::vector<Person> Employees;
public:
    void AddPerson(const std::string& name, int year, const std::string& position, const std::string& group) {
        Employees.emplace_back(Person(name, year, position, group));
    }
    void PrintEngineer() const {
        for (const auto& p : Employees) {
            if (p.GetPosition() == engineer_) {
                p.print();
            }
        }
    }

    void PrintNoPredsedatel() {
        std::sort(Employees.begin(), Employees.end(), [](const Person& p1, const Person& p2) {
            return p1.GetYear() < p2.GetYear();
        });
        for (const auto& p : Employees) {
            if (p.GetPosition() != chairman_) {
                p.print();
            }
        }
    }

    ~DB() {
        Employees.clear();
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
    DB db;
    std::ifstream fl("Info.txt");
    if (!fl.is_open()) {
        std::cout << "Error opening file!" << std::endl;
    }
    else {
        std::string line;
        std::string name, position, group;
        int year;
        while (std::getline(fl, line)) {
            std::stringstream ss(line);
            std::getline(ss, name, ',');
            ss >> year >> std::ws;
            std::getline(ss, position, ',');
            std::getline(ss >> std::ws, group);
            db.AddPerson(name, year, position, group);
        }
    }

    db.PrintEnergineer();
    std::cout << "------------------------------------" << std::endl;
    db.PrintNoPredsedatel();
    fl.close();
    return 0;
}
