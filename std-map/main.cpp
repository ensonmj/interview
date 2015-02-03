#include <iostream>
#include <map>
#include <vector>

using namespace std;

int main(int argc, char const* argv[]) {
    map<int, vector<int>> var;
    auto item = var.find(100); //should be equal to map::end;
    if(item == end(var)) {
        cout << "item is null ";
    }
    cout << item->second.size(); //not crash, just an random number
    return 0;
}
