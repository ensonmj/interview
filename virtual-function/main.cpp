#include <iostream>

using namespace std;

class Parent {
    public:
        void Test() {
            Func();
        }
    private:
        virtual void Func() {
            cout << "Parent::" << __func__ << endl;
        }
};

class Derived : public Parent {
    private:
        void Func() {
            cout << "Derived::" << __func__ << endl;
        }
};

int main(int argc, char const* argv[])
{
    Parent *p = new Derived();
    p->Test();

    return 0;
}
