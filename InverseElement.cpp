#include <iostream>
using namespace std;
const int MAX = 100; //因为没设计递归，所以需要辅助空间
int GED(int a, int b){//广义欧几里得除法解决逆元
    int i;
    int q[MAX], r[MAX];//商，余数

    r[0] = a; r[1] = b;//和数学基础书上有一些区别，不是从-2开始，是从0开始
    for(i = 0; r[i + 1] != 0; i++){//辗转相除
        q[i] = r[i] / r[i + 1];
        r[i + 2] = r[i] % r[i + 1];
    }//此刻的r[i]就是他们的最大公因数

    int s = 1,t = -1 * q[i - 2];//贝祖等式 sa + tb
    if(i - 2 == 0) return s;
    for(i--; i - 1 > 0; i--){//贝祖等式倒推过程,q[]累加
        int temp = s;
        s = t;
        t = temp - q[i - 2] * t;
    }
    while(s < 0)
        s += b;
    return s;//返回的是s
}
int main(){
    int a,b;
    cout << "请输入a和b，求a mod b 的逆元" << endl;
    cin >> a >> b;
    cout << "逆元为：" << GED(a, b) << endl;
    return 0;
}
