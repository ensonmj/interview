#include <iostream>
#include <vector>

using namespace std;

class StrVec {
    public:
        StrVec() {cout<<"constructor"<<endl;}
        ~StrVec() {cout<<"destructor"<<endl;}

        StrVec(const StrVec &strvec) {
            cout << "copy constructor" << endl;
        }

        StrVec(StrVec &&strvec) {
            cout << "move constructor" << endl;
        }
};

//http://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers
//If a variable or parameter is declared to have type T&& for some deduced type T, that variable or parameter is a universal reference.
template<typename T>
void testr(T && arg) {
    cout << "testr" << endl;
    std::forward<T>(arg);
}

int main(int argc, char const* argv[])
{
    StrVec s;

    //test universal reference
    testr(s);
    testr(std::move(s));

    vector<string> vec;
    string str;
    // universal reference
    vec.emplace_back(str);
    vec.emplace_back("str");

    std::allocator<StrVec> alloc;
    StrVec *p = alloc.allocate(2*sizeof(StrVec));
    alloc.construct(p, s); //copy
    alloc.construct(p+1, std::move(s)); //move
    alloc.destroy(p);
    alloc.destroy(p+1);

    return 0;
}
