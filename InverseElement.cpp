#include <iostream>
using namespace std;
const int MAX = 100; //��Ϊû��Ƶݹ飬������Ҫ�����ռ�
int GED(int a,int b){//����ŷ����ó��������Ԫ
    int i;
    int q[MAX],r[MAX];//�̣�����

    r[0] = a;r[1] = b;//����ѧ����������һЩ���𣬲��Ǵ�-2��ʼ���Ǵ�0��ʼ
    for(i=0;r[i+1] != 0;i++){//շת���
        q[i] = r[i] / r[i+1];
        r[i+2] = r[i] % r[i+1];
    }//�˿̵�r[i]�������ǵ��������

    int s = 1,t = -1 * q[i-2];//�����ʽsa+tb
    if(i - 2 == 0) return s;
    for(i--;i-1>0;i--){//�����ʽ���ƹ���,q[]�ۼ�
        int temp = s;
        s = t;
        t = temp - q[i-2] * t;
    }
    while(s < 0)
        s += b;
    return s;//���ص���s
}
int main(){
    int a,b;
    cout << "������a��b����a mod b ����Ԫ" << endl;
    cin >> a >> b;
    cout << "��ԪΪ��" << GED(a,b) << endl;
    return 0;
}
