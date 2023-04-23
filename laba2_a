#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include <iostream>
#include <vector>
#include <typeinfo>
using namespace std;

struct Leaks {
    ~Leaks() { _CrtDumpMemoryLeaks(); }
}_l;

class Class1 {
public:
    Class1() { }

    Class1(const Class1& other) { }

    virtual ~Class1() { }
};

class Class2 :public Class1 {
public:
    Class2() { }

    Class2(const Class2& other) :Class1(other) { }

    virtual ~Class2() { }
};

void my_copy(vector<Class1*>& Obj, vector<Class1*>& BD) {

    for (auto obj : Obj) {
        Class2* copy_obj = dynamic_cast<Class2*>(obj);
        if (copy_obj)
            BD.push_back(new Class2(*copy_obj));
        else
            BD.push_back(new Class1(*copy_obj));
    }
}

int main() {

    vector<Class1*> Obj;
    vector<Class1*> BD;

    Class1 obj1;
    Class1 obj2;
    Class2 obj3;
    Class2 obj4;

    Obj.push_back(&obj1);
    Obj.push_back(&obj2);
    Obj.push_back(&obj3);
    Obj.push_back(&obj4);

    my_copy(Obj, BD);

    cout << "Type objects: " << '\n' << endl;

    for (auto obj : BD) {
        cout << typeid(*obj).name() << endl;
        delete obj;
    }
    return 0;
}
