#include <iostream>
#include <string>
using namespace std;
class Fill{ //������������
private:
    char L[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
public:
    int* filling(string input,long length){ //����������ʵ��
        int i,j;
        int* result = new int[16]; //16��32λ
        for(i=0;i<input.length();i++){ //��������Ϣ��Ϣ
            result[i/4] <<= 8; //���Ƴ�8λ�ռ�
            result[i/4] += input[i];
        }
        if(length != -1){ //��������length != -1���������һ��
            //��ʱi%4����Ӧ������1�Ͷ��0��λ��
            result[i/4] <<= 8; //���Ƴ�8λ�ռ�
            result[i/4] += 0x80;//����10000000,��16���Ƶ�80
            for(i++;i<56;i++){ //�������ó��ȱ��i����ô8λһ�ε����,��56ֹͣ
                result[i/4] <<= 8; //���Ƴ�8λ�ռ�
                result[i/4] += 0;
            }
            //���64λ������Ϣ����
            result[14] = result[15] = 0;
            length *= 8;//��������ô��λ
            while((length >> 60)== 0) length <<= 4; //��length��0�������λ
            result[14] = (length >> 32); //��32
            result[15] = length & 0xFFFF; //��32
        }
        return result; //������֮�󷵻�32λint�����γɵķ���
    }
    string intToChar(int input){ //32λ����ת��Ϊ�ַ�����ע���Ǹߵ�λ��ȡ��
        int i;
        string result = ""; //����ַ���
        for(i=0;i<4;i++){
            int temp = (input & 0xF0) >> 4;
            result += L[temp]; //��ȡ��16�����ַ�
            temp = input & 0x0F;
            result += L[temp]; //��ȡ��16�����ַ�
            input >>= 8; //������λ
        }
        return result;
    }
};
class CMD5{ //MD5�㷨ʵ����
private:
    Fill fill; //������
    int A,B,C,D;//���ӱ���
    int* M; //������м��ܵ�����
    int Mi[4][16] = { //4��ѭ��ÿһ���õ�16��Mi
        { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9,10,11,12,13,14,15},
        { 1, 6,11, 0, 5,10,15, 4, 9,14, 3, 8,13, 2, 7,12},
        { 5, 8,11,14, 1, 4, 7,10,13, 0, 3, 6, 9,12,15, 2},
        { 0, 7,14, 5,12, 3,10, 1, 8,15, 6,13, 4,11, 2, 9}};
    int T[64] = { //������Ti
        0xd76aa478,0xe8c7b756,0x242070db,0xc1bdceee,0xf57c0faf,0x4787c62a,0xa8304613,0xfd469501,
        0x698098d8,0x8b44f7af,0xffff5bb1,0x895cd7be,0x6b901122,0xfd987193,0xa679438e,0x49b40821,
        0xf61e2562,0xc040b340,0x265e5a51,0xe9b6c7aa,0xd62f105d,0x02441453,0xd8a1e681,0xe7d3fbc8,
        0x21e1cde6,0xc33707d6,0xf4d50d87,0x455a14ed,0xa9e3e905,0xfcefa3f8,0x676f02d9,0x8d2a4c8a,
        0xfffa3942,0x8771f681,0x6d9d6122,0xfde5380c,0xa4beea44,0x4bdecfa9,0xf6bb4b60,0xbebfbc70,
        0x289b7ec6,0xeaa127fa,0xd4ef3085,0x04881d05,0xd9d4d039,0xe6db99e5,0x1fa27cf8,0xc4ac5665,
        0xf4292244,0x432aff97,0xab9423a7,0xfc93a039,0x655b59c3,0x8f0ccc92,0xffeff47d,0x85845dd1,
        0x6fa87e4f,0xfe2ce6e0,0xa3014314,0x4e0811a1,0xf7537e82,0xbd3af235,0x2ad7d2bb,0xeb86d391}; 
    int Left[4][16] = { //4��ѭ�����Ʋ���
        { 7,12,17,22, 7,12,17,22, 7,12,17,22, 7,12,17,22},
        { 5, 9,14,20, 5, 9,14,20, 5, 9,14,20, 5, 9,14,20},
        { 4,11,16,23, 4,11,16,23, 4,11,16,23, 4,11,16,23},
        { 6,10,15,21, 6,10,15,21, 6,10,15,21, 6,10,15,21}};
    int F(int b,int c,int d) { //F����
        return (b & c) | ((~b) & d);
    }
    int G(int b,int c,int d) { //G����
        return (b & d) | (c & (~d));
    }
    int H(int b,int c,int d) { //H����
        return b ^ c ^ d;
    }
    int I(int b,int c,int d) { //I����
        return c ^ (b | (~d));
    }
public:
    string Hash(string input){ //MD5ɢ���㷨ʵ��
        int i,j,k;
        //��ʼ�����ӱ���
        A = 0x67452301;B = 0xefcdab89;C = 0x98badcfe;D = 0x10325476;
        //����ɢ��ʵ��
        for(i=0;i<input.length();i+=64){ //ÿ64���ַ�*8=512λΪһ������
            int a = A,b = B,c = C,d = D;//׼��abcd����Ԥ��
            if(i + 63 < input.length())//��ͨ����
                M = fill.filling(input.substr(i,i+63),-1);
            else //���һ��
                M = fill.filling(input.substr(i,input.length()),input.length());
            //��ʱ�����˱���ʹ�õ�M���飬��ʼɢ��
            for(j=0;j<4;j++) //4���غϵ�����
                for(k=0;k<16;k++){ //16�ε�Ԫ����
                    //�����Ժ���
                    if(j==0) a += F(b,c,d);
                    else if(j==1) a += G(b,c,d);
                    else if(j==2) a += H(b,c,d);
                    else if(j==3) a += I(b,c,d);
                    a += M[Mi[j][k]]; //��Mi
                    a += T[j * 16 + k]; //��Ti
                    //aѭ������Leftλ�ټ�b
                    a = (a >> (32 - Left[j][k]) | a << Left[j][k]) + b;
                    //�ĸ���λ
                    int temp = d;b = a;c = b;d = c;a = temp;
                }
            //���ӷ�
            A += a;B += b;C += c;D += d;
            //ɢ�н������õ��˱��ε�ABCD�����Ҳ���Ǳ������
        }
        string result = fill.intToChar(A) + fill.intToChar(B) + fill.intToChar(C) + fill.intToChar(D);
        return result;
    }
};
int main(){ //����������
    Fill fill;
    cout << fill.intToChar(0x67452301) << endl;
    CMD5 md5;
    string input;
    cout << "����ɢ���ַ�����";
    cin >> input;
    cout << "MD5�룺" << md5.Hash(input) << endl;
    return 0;
}