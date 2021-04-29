#include <iostream>
#include <string>
using namespace std;
class Fill{ //填充操作工具类
private:
    char L[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
public:
    int* filling(string input,long length){ //分组填充具体实现
        int i,j;
        int* result = new int[16]; //16组32位
        for(i=0;i<input.length();i++){ //先填入消息信息
            result[i/4] <<= 8; //左移出8位空间
            result[i/4] += input[i];
        }
        if(length != -1){ //如果输入的length != -1，代表最后一组
            //此时i%4就在应该填入1和多个0的位置
            result[i/4] <<= 8; //左移出8位空间
            result[i/4] += 0x80;//填入10000000,即16进制的80
            for(i++;i<56;i++){ //继续利用长度标记i，那么8位一次地填充,到56停止
                result[i/4] <<= 8; //右移出8位空间
                result[i/4] += 0;
            }
            //最后64位放入消息长度
            result[14] = result[15] = 0;
            length *= 8;//代表有这么多位
            while((length >> 60)== 0) length <<= 4; //把length非0顶到最高位
            result[14] = (length >> 32); //高32
            result[15] = length & 0xFFFF; //低32
        }
        return result; //填充完毕之后返回32位int数组形成的分组
    }
    string intToChar(int input){ //32位整数转化为字符串，注意是高低位倒取法
        int i;
        string result = ""; //结果字符串
        for(i=0;i<4;i++){
            int temp = (input & 0xF0) >> 4;
            result += L[temp]; //获取到16进制字符
            temp = input & 0x0F;
            result += L[temp]; //获取到16进制字符
            input >>= 8; //右移四位
        }
        return result;
    }
};
class CMD5{ //MD5算法实现类
private:
    Fill fill; //填充操作
    int A,B,C,D;//链接变量
    int* M; //填充后进行加密的数组
    int Mi[4][16] = { //4轮循环每一轮用的16个Mi
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15},
        { 1, 6,11, 0, 5,10,15, 4, 9,14, 3, 8,13, 2, 7,12},
        { 5, 8,11,14, 1, 4, 7,10,13, 0, 3, 6, 9,12,15, 2},
        { 0, 7,14, 5,12, 3,10, 1, 8,15, 6,13, 4,11, 2, 9}};
    int T[64] = { //常数表Ti
        0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
        0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
        0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
        0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
        0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
        0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
        0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
        0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391}; 
    int Left[4][16] = { //4轮循环左移步数
        { 7,12,17,22, 7,12,17,22, 7,12,17,22, 7,12,17,22},
        { 5, 9,14,20, 5, 9,14,20, 5, 9,14,20, 5, 9,14,20},
        { 4,11,16,23, 4,11,16,23, 4,11,16,23, 4,11,16,23},
        { 6,10,15,21, 6,10,15,21, 6,10,15,21, 6,10,15,21}};
    int F(int b,int c,int d) { //F函数
        return (b & c) | ((~b) & d);
    }
    int G(int b,int c,int d) { //G函数
        return (b & d) | (c & (~d));
    }
    int H(int b,int c,int d) { //H函数
        return b ^ c ^ d;
    }
    int I(int b,int c,int d) { //I函数
        return c ^ (b | (~d));
    }
public:
    string Hash(string input){ //MD5散列算法实现
        int i, j, k;
        //初始化链接变量
        A = 0x67452301; B = 0xefcdab89; C = 0x98badcfe; D = 0x10325476;
        //分组散列实现
        for(i = 0;i < input.length();i += 64){ //每64个字符*8=512位为一个分组
            int a = A, b = B, c = C, d = D;//准备abcd，即预设
            if(i + 63 < input.length())//普通分组
                M = fill.filling(input.substr(i, i + 63), -1);
            else //最后一个
                M = fill.filling(input.substr(i, input.length()), input.length());
            //此时生成了本次使用的M数组，开始散列
            for(j = 0; j < 4; j++) //4个回合的运算
                for(k = 0; k < 16; k++){ //16次单元运算
                    //非线性函数
                    if(j == 0) a += F(b, c, d);
                    else if(j == 1) a += G(b, c, d);
                    else if(j == 2) a += H(b, c, d);
                    else if(j == 3) a += I(b, c, d);
                    a += M[Mi[j][k]]; //加Mi
                    a += T[j * 16 + k]; //加Ti
                    //a循环左移Left位再加b
                    a = (a >> (32 - Left[j][k]) | a << Left[j][k]) + b;
                    //四个换位
                    int temp = d; b = a; c = b; d = c; a = temp;
                }
            //最后加法
            A += a;B += b;C += c;D += d;
            //散列结束，得到了本次的ABCD结果，也就是本轮输出
        }
        string result = fill.intToChar(A) + fill.intToChar(B) + fill.intToChar(C) + fill.intToChar(D);
        return result;
    }
};
int main(){ //测试主函数
    Fill fill;
    cout << fill.intToChar(0x67452301) << endl;
    CMD5 md5;
    string input;
    cout << "输入散列字符串：";
    cin >> input;
    cout << "MD5码：" << md5.Hash(input) << endl;
    return 0;
}