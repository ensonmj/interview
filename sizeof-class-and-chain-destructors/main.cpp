#include <iostream>
#include <climits>

using namespace std;

//g++ -fdump-class-hierarchy 可以dump内存结构
//x86-64 int 4字节，long 8字节，指针8字节
//类对齐到最大成员（此处是指针)大小，即8字节对齐
//
//虚函数表中最后两项都是析构函数，虚继承的情况下可能会有三个
//http://stackoverflow.com/questions/6613870/gnu-gcc-g-why-does-it-generate-multiple-dtors
class A {
    const int a=1;
    const int c = 3;

    public:
    const int d = 4;
    virtual void f() { cout << "A::f" << endl; }
    void g() { cout << "A::g" << endl; }
    virtual ~A() {
        cout << "A::~A" << endl;
    }
};

class B : public A {
    const int b=2;

    public:
    void test() { cout << "B::test" << b << d << endl; }

    virtual void f() { cout << "B::f" << endl; }
    void g() { cout << "B::g" << endl; }
    void h() { cout << "B::h" << endl; }
    //反汇编后可以看出，子类虚析构函数直接嵌入调用父类虚析构函数
    virtual ~B() {
        cout << "B::~B" << endl;
    }
};

int main() {
    cout << "sizeof(int): " << sizeof(int) << " sizeof(long): " << sizeof(long) << " sizeof(void *): " << sizeof(void *) << endl;
    cout << "INT_MAX: " << INT_MAX << "INT_MIN: " << INT_MIN << endl;

    cout << "sizeof(A): " << sizeof(A) << " sizeof(B): " << sizeof(B) << endl;

    A *pa = new A[2];
    pa->f();
    pa->g();
    delete [] pa;

    B *pb = new B[2];
    pa = pb;

    pb->test();
    pb->f();
    pb->g();
    pb->h();

    pa->f();
    pa->g();

    delete [] pa;
}
