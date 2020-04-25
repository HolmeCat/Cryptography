#include <iostream>
#include <string>
using namespace std;

const int n = 26;
int key = 0; //��Կ
string text; //��Ҫ����ļ���/�������ֶ�
int E(int m){ //���ܺ���
    return (m + key) % n;
}
int D(int L){ //���ܺ���
    return (L - key + n) % n;
}
void ESubstitution(){ //�滻�������
    int i;
    cout << "ģ��1���滻����" <<endl;
    cout << "�����������Կ" << endl;
    cin >> key;
    cout << "������Ҫ���ܵ�Ӣ����ĸ����" << endl;
    getline(cin,text);//��һ������������������س�
    getline(cin,text);
    //�������
    for(i=0;i<text.length();i++){
        if(text[i] >='a'&&text[i] <='z')
            text[i] = E(text[i]-'a'+1)+'a'-1;
        else if(text[i] >='A'&&text[i] <='Z')
            text[i] = E(text[i]-'A'+1)+'A'-1;
    }
    cout << "���ģ�" << text << endl;
    return;
}
void DSubstitution(){ //�滻�������
    int i;
    cout << "ģ��2���滻����" <<endl;
    cout << "�����������Կ" << endl;
    cin >> key;
    cout << "������Ҫ���ܵ�Ӣ����ĸ����" << endl;
    getline(cin,text);//��һ������������������س�
    getline(cin,text);
    //�������
    for(i=0;i<text.length();i++){
        if(text[i] >='a'&&text[i] <='z')
            text[i] = D(text[i]-'a'+1)+'a'-1;
        else if(text[i] >='A'&&text[i] <='Z')
            text[i] = D(text[i]-'A'+1)+'A'-1;
    }
    cout << "���ģ�" << text << endl;
    return;
}
int main(){
    ESubstitution();
    DSubstitution();
    return 0;
}
