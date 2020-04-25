#include <iostream>
#include <string>
using namespace std;

const int n = 26;
int key = 0; //密钥
string text; //需要处理的加密/解密文字段
int E(int m){ //加密函数
    return (m + key) % n;
}
int D(int L){ //解密函数
    return (L - key + n) % n;
}
void ESubstitution(){ //替换密码加密
    int i;
    cout << "模块1：替换加密" <<endl;
    cout << "请输入加密密钥" << endl;
    cin >> key;
    cout << "请输入要加密的英文字母内容" << endl;
    getline(cin,text);//这一行用于清除掉缓冲区回车
    getline(cin,text);
    //输出密文
    for(i=0;i<text.length();i++){
        if(text[i] >='a'&&text[i] <='z')
            text[i] = E(text[i]-'a'+1)+'a'-1;
        else if(text[i] >='A'&&text[i] <='Z')
            text[i] = E(text[i]-'A'+1)+'A'-1;
    }
    cout << "密文：" << text << endl;
    return;
}
void DSubstitution(){ //替换密码解密
    int i;
    cout << "模块2：替换解密" <<endl;
    cout << "请输入解密密钥" << endl;
    cin >> key;
    cout << "请输入要解密的英文字母内容" << endl;
    getline(cin,text);//这一行用于清除掉缓冲区回车
    getline(cin,text);
    //输出明文
    for(i=0;i<text.length();i++){
        if(text[i] >='a'&&text[i] <='z')
            text[i] = D(text[i]-'a'+1)+'a'-1;
        else if(text[i] >='A'&&text[i] <='Z')
            text[i] = D(text[i]-'A'+1)+'A'-1;
    }
    cout << "明文：" << text << endl;
    return;
}
int main(){
    ESubstitution();
    DSubstitution();
    return 0;
}
