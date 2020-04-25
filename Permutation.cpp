#include <iostream>
using namespace std;
const int n = 20;
string text; //��Ҫ����ļ���/�������ֶ�
string result; //�洢�����û������ֶ�
char Matrix[n][n];//�û�����
int length,height; //�û������С,����Ϊlength������Ϊheight
int key[n]; //�û���Կ
int iKey[n]; //���û���Կ
void InitMatrix(){ //��ʼ���û�����
    int i,j;
    for(i=0;i<n;i++)
        for(j=0;j<n;j++)
            Matrix[i][j] = ' ';
    return;
}
void GetKey(){ //�����û�
    int i;
    cin >> length;
    for(i=0;i<length;i++){
        cin >> key[i];
        key[i]--; //����
    }
    return;
}
void GetInverseKey(){ //�������û�
    int i;
    for(i=0;i<length;i++)
        iKey[key[i]] = i;
    return;
}
int CountHeight(int text,int length){ //��������
    if(text%length == 0) //������һ������
        return text/length;
    else //��������������
        return text/length + 1;
}
void EPermutation(){ //�û��������
    InitMatrix();
    cout << "ģ��1���û�����" <<endl;
    cout << "����һ���������û���Կ���ȣ�length<=20��������(����<=length * 20)���м��ÿո����" << endl;
    GetKey();
    cout << "������Ҫ���ܵ�Ӣ����ĸ����" << endl;
    getline(cin,text);//��һ������������������س�
    getline(cin,text);
    //�������
    result = "";
    int i,j,k;
    height = CountHeight(text.length(),length);
    for(i=0,k=0;i<n && k<text.length();i++) //����д���û�����
        for(j=0;j<length && k<text.length();j++)
            Matrix[i][j] = text[k++];
    for(i=0;i<length;i++) //�����û���������
        for(j=0;j<height;j++)
            result = result + Matrix[j][key[i]]; //�û�Ϊ��
    cout << "���ģ�" << result << ";"<< endl;
    return;
}
void DPermutation(){ //�û��������
    InitMatrix();
    cout << "ģ��2���û�����" <<endl;
    cout << "����һ���������û���Կ���ȣ�length<=20��������(����<=length * 20)���м��ÿո����" << endl;
    GetKey();
    GetInverseKey();
    cout << "������Ҫ���ܵ�Ӣ����ĸ����" << endl;
    getline(cin,text);//��һ������������������س�
    getline(cin,text);
    //�������
    result = "";
    int i,j,k;
    height = CountHeight(text.length(),length);
    for(i=0,k=0;i<length;i++) //����д���û�����
        for(j=0;j<height;j++)
            Matrix[j][i] = text[k++];
    for(i=0;i<height;i++) //�������û���������
        for(j=0;j<length;j++)
            result = result + Matrix[i][iKey[j]]; //�û�Ϊ��
    cout << "���ģ�" << result << ";" << endl;
    return;
}
int main(){
    EPermutation();
    DPermutation();
    return 0;
}
