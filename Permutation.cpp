#include <iostream>
using namespace std;
const int n = 20;
string text; //需要处理的加密/解密文字段
string result; //存储经过置换的文字段
char Matrix[n][n];//置换矩阵
int length,height; //置换矩阵大小,列数为length，行数为height
int key[n]; //置换密钥
int iKey[n]; //逆置换密钥
void InitMatrix(){ //初始化置换矩阵
    int i,j;
    for(i = 0; i < n; i++)
        for(j = 0; j < n; j++)
            Matrix[i][j] = ' ';
    return;
}
void GetKey(){ //生成置换
    int i;
    cin >> length;
    for(i = 0; i < length; i++){
        cin >> key[i];
        key[i]--; //修正
    }
    return;
}
void GetInverseKey(){ //生成逆置换
    int i;
    for(i = 0; i < length; i++)
        iKey[key[i]] = i;
    return;
}
int CountHeight(int text, int length){ //计算列数
    if(text % length == 0) //正好是一个矩阵
        return text / length;
    else //否则按照往大了算
        return text / length + 1;
}
void EPermutation(){ //置换密码加密
    InitMatrix();
    cout << "模块1：置换加密" <<endl;
    cout << "请在一行内输入置换密钥长度（length<=20）和内容(长度<=length * 20)，中间用空格隔开" << endl;
    GetKey();
    cout << "请输入要加密的英文字母内容" << endl;
    getline(cin, text);//这一行用于清除掉缓冲区回车
    getline(cin, text);
    //输出密文
    result = "";
    int i, j, k;
    height = CountHeight(text.length(), length);
    for(i = 0, k = 0;i < n && k < text.length(); i++) //按行写下置换矩阵
        for(j = 0; j < length && k < text.length(); j++)
            Matrix[i][j] = text[k++];
    for(i = 0; i < length; i++) //按列置换生成密文
        for(j = 0; j < height; j++)
            result = result + Matrix[j][key[i]]; //置换为列
    cout << "密文：" << result << ";"<< endl;
    return;
}
void DPermutation(){ //置换密码解密
    InitMatrix();
    cout << "模块2：置换解密" <<endl;
    cout << "请在一行内输入置换密钥长度（length<=20）和内容(长度<=length * 20)，中间用空格隔开" << endl;
    GetKey();
    GetInverseKey();
    cout << "请输入要解密的英文字母内容" << endl;
    getline(cin, text);//这一行用于清除掉缓冲区回车
    getline(cin, text);
    //输出明文
    result = "";
    int i, j, k;
    height = CountHeight(text.length(), length);
    for(i = 0, k = 0; i < length; i++) //按列写下置换矩阵
        for(j = 0; j < height; j++)
            Matrix[j][i] = text[k++];
    for(i = 0; i < height; i++) //按列逆置换生成明文
        for(j = 0; j < length; j++)
            result = result + Matrix[i][iKey[j]]; //置换为行
    cout << "明文：" << result << ";" << endl;
    return;
}
int main(){
    EPermutation();
    DPermutation();
    return 0;
}
