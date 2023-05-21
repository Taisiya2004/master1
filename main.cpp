#include <string>
#include <iostream>
#include <vector>
#include <list>
#include <typeinfo>
#include <algorithm>

using namespace std;

class A {
public:

    string s;
    A() {
        cout << "Конструктор по умолчанию класса A" << endl;
    }

    A(const char* a) {
        s = a;
        cout << "Пользовательский Конструктор класса A" << endl;
        cout << s << endl;
    }

    virtual ~A() {
        cout << "Деструктор класса A" << endl;
        cout << typeid(*this).name() << endl;
    }
};

class B : public A {
public:
    B() {
        cout << "Конструктор  класса B" << endl;
    }
    B(const char* a) : A(a) {
        cout << "Пользовательский Конструктор класса B" << endl;
        cout << a << endl;
    }
    ~B() {
        cout << "Деструктор класса B" << endl;
        cout << typeid(*this).name() << endl;
    }
};

void del(vector<A*>& v) {
    for (int i = 0; i < v.size(); i++)
        delete v[i];
}

int main() {
    setlocale(LC_ALL, "rus");
    list<A*> l;
    l.push_back(new A("first"));
    l.push_back(new B("second"));

    vector<A*> v(l.size());
    std::copy(l.begin(), l.end(), v.begin());

    del(v);
    return 0;
}
