#include <iostream>
#include <initializer_list>

using namespace std;

class MaxResult {
    public:
        MaxResult(initializer_list<int> il) {
            len = il.size();
            result = new int[len+1](); //用数组下标的1到n
            path = new int[len+1](); //记录路径也只用1到n
            arr = new int[len+1](); //用1到n存放数字
            copy(il.begin(), il.end(), arr+1);
        }

        //动态规划求解
        //result[i] = max{ (result[k-1] + x[k]*x[k+1]*...*x[i]) } 1<=k<=i
        int calcMaxResult() {
            result[0] = 0; //0个数据的最大值为0
            result[1] = arr[1]; //前1个数据的最大值为其本身
            path[1] = 1;

            //递推求解，最终result[i]表示前i个数的最大值
            for(int i=2; i<=len; ++i) {
                result[i] = -1;
                int res;
                for(int j=i; j>=1; --j) {
                    res = 1;
                    int k=j;
                    //arr[j]*arr[j+1]*...*arr[i]
                    while(k<=i) {
                        res *= arr[k++];
                    }
                    //arr[j]*arr[j+1]*...*arr[i] + result[j-1]
                    res += result[j-1];

                    //记录j取不同值时所能达到的最大值，并记录断点path[i]
                    if(res > result[i]) {
                        result[i] = res;
                        path[i] = j;
                    }
                }
            }

            return result[len];
        }

        void printPath() {
            printPath(len);
            cout << " = " << result[len] << endl;
        }

    private:
        //递归打印整个公式
        void printPath(int n) {
            if(path[n] == 1) {
                int i = 1;
                while(i<=n) {
                    cout << arr[i];
                    if(i<n) {
                        cout << "*";
                    }
                    ++i;
                }

                return;
            }

            printPath(path[n]-1);
            cout << "+";
            int i = path[n];
            while(i<=n) {
                cout << arr[i];
                if(i<n) {
                    cout << "*";
                }
                ++i;
            }
        }

    private:
        //动态规划表格，result[n]表示1->n做加乘综合运算后的最大值
        int *result;
        //在动态规划递归过程中记录加号出现的位置
        int *path;
        //存放len个数字, arr[0]空置
        int *arr;
        //数字序列的真实长度
        int len;
};

int main(int argc, char const* argv[]) {
    MaxResult mr({2, 1, 1, 1, 1, 2});
    mr.calcMaxResult();
    mr.printPath();

    MaxResult mr1({2, 1, 1, 3, 1, 2});
    mr1.calcMaxResult();
    mr1.printPath();

    MaxResult mr2({2, 1, 1, 3, 5, 2});
    mr2.calcMaxResult();
    mr2.printPath();

    return 0;
}
