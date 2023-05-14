#include <iostream>
#include <vector>

using namespace std;

class Detail {
protected:
    Detail() {}
public:
    virtual ~Detail() {}
    virtual void show() const = 0;
};

class Assembly : public Detail {
protected:
    Assembly() {}
public:
    virtual ~Assembly() {}
    virtual void add(Detail* d) = 0;
};

class Screw : public Detail {
public:
    Screw() {}
    virtual ~Screw() {}
    void show() const override {
        cout << "Screw\n";
    }
};

class Board : public Assembly {
private:
    vector<Detail*> details_;
public:
    Board() {}
    ~Board() {
        for (Detail* d : details_) {
            delete d;
        }
    }
    void show() const override {
        cout << "Board\n";
        for (Detail* d : details_) {
            d->show();
        }
    }
    void add(Detail* d) override {
        details_.push_back(d);
    }
};

template<typename T>
void add_part(Assembly* a, T t) {
    a->add(new T(t));
}

int main() {
    vector<Detail*> parts;
    Assembly* assembly = new Board();
    add_part(assembly, Screw());
    add_part(assembly, Screw());
    add_part(assembly, Board());
    add_part(assembly, Screw());
    add_part(assembly, Board());
    parts.push_back(assembly);
    for (Detail* d : parts) {
        d->show();
    }
    for (Detail* d : parts) {
        delete d;
    }
    return 0;
}
