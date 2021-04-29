#include <iostream>
#include <string>
using namespace std;
class CAES{ //����AES��
private:
	int round;//����
	int m[16]; //����
	int key[16]; //��Կ;
	int iv[16];  //cbc�����iv����
	int rect_key[44][4]; //��չ��Կ
	int rect_m[4][4]; //State���󣬼ӽ��ܴ���ռ�
	const int S[16][16] = {
		{0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
		{0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
		{0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
		{0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
		{0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
		{0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
		{0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
		{0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
		{0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
		{0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
		{0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
		{0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
		{0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
		{0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
		{0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
		{0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16}};
	const int S2[16][16] = {
		{0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
		{0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
		{0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
		{0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
		{0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
		{0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
		{0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
		{0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
		{0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
		{0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
		{0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
		{0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
		{0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
		{0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
		{0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
		{0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}};
	const int colm[4][4] = {
		{2, 3, 1, 1},
		{1, 2, 3, 1},
		{1, 1, 2, 3},
		{3, 1, 1, 2}};
	const int deColM[4][4] = {
		{0xe, 0xb, 0xd, 0x9},
		{0x9, 0xe, 0xb, 0xd},
		{0xd, 0x9, 0xe, 0xb},
		{0xb, 0xd, 0x9, 0xe}};
	const int Rcon[11] = {1, 2, 4, 8, 10, 20, 40, 80, 0x1b, 36, 0x6c};
	//��������
	int getIntFromChar(char c){//��һ���ַ����16λ������
		int result = (int)c;
		return result & 0x000000ff;
	}
	int getLeft4Bit(int a){ //һ��16����������4λ
		int left = a & 0x000000f0;
		return left >> 4;
	}
	int getRight4Bit(int a){ //һ��16����������4λ
		return a & 0x0000000f;
	}
	int getNumFromSBox(int a, const int s[][16]){ //��s������ȡ����
		int row = getLeft4Bit(a);
		int col = getRight4Bit(a);
		return s[row][col];
	}
	int aesMultiple(int a, int le){ //AES�˷�,GF(2^8)�ϳ˷�
		int thr = le & 0x8;
		int sec = le & 0x4;
		int fir = le & 0x2;
		int fir_mod = le % 2;
		int result = 0;
		if (thr){ //����λ
			int b = a;
			for (int i = 1; i <= 3; ++i) {
				b = b << 1;
				if (b >= 256)
					b = b ^ 0x11b;
			}
			b = b % 256;
			result = result ^ b;
		}
		if(sec){
			int b = a;
			for (int i = 1;i <= 2; ++i) {
				b = b << 1;
				if (b >= 256)
					b = b ^ 0x11b;
			}
			b = b % 256;
			result = result ^ b;
		}
		if(fir){
			int b = a << 1;
			if (b >= 256)
				b = b ^ 0x11b;
			b = b % 256;
			result = result ^ b;
		}
		if(fir_mod)
			result = result ^ a;
		return  result;
	}
	//AES
	void SubBytes(const int s[][16]){ //S���û�
		int j;
		for(j = 0; j < 16; j++){ //S���滻
			rect_m[j / 4][j % 4] = getNumFromSBox(rect_m[j / 4][j % 4], s);
		}
		return;
	}
	void ShiftRows(){ //����λ
		int i, j;
		int temp[4];
		for(i = 0; i < 4; i++){
			for(j = 0; j < 4; j++) //���󣬷���Ϊ-�ţ�+��4��ֹ����
				temp[(j - i + 4) % 4] = rect_m[i][j];
			for(j = 0; j < 4; j++)
				rect_m[i][j] = temp[j];
		}
		return;
	}
	void InverseShiftRows(){ //��������λ
		int i, j;
		int temp[4];
		for(i = 0; i < 4; i++){
			for(j = 0; j < 4; j++) //�����෴��Ϊ+��
				temp[(j + i) % 4] = rect_m[i][j];
			for(j = 0; j < 4; j++)
				rect_m[i][j] = temp[j];
		}
		return;
	}
	void MixColumns(const int c[][4]){ //�л���
		int i, j, k;
		//�л�������˷�
		int temp[4][4] = {0}; //�ݴ���
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++)
				for(k = 0; k < 4; k++){ //�˴���GF(2^8)�ϳ˷����л�������
					if(k == 0) temp[i][j] = aesMultiple(rect_m[k][j], c[i][k]);
					else temp[i][j] ^= aesMultiple(rect_m[k][j], c[i][k]);
				}
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++)
				rect_m[i][j] = temp[i][j];
		return;
	}
	void AddRoundKey(int k){ //k����Կ��
		int i, j;
		for(i = 0; i < 4; i++)
			for(j = 0; j < 4; j++) //��Ӧλ����������㣬ע����Կ�� k*4 + i�ľ�����
				rect_m[i][j] ^= rect_key[k * 4 + i][j];
		return;
	}
public:
	CAES(string KEY, string IV = "0123456789ABCDEF", int r = 10):round(r){ //���캯����r������Ĭ��10�֣�KEY����Կ��IV��CBC����ģʽ����
		for (int i = 0;i < 16;i++){ //����string����
			key[i] = getIntFromChar(KEY[i]);
			iv[i] = getIntFromChar(IV[i]);
		}
	} 
	void createKey(){ //������չ��Կ
		int n, i, j;
		int SubWord[4]; //�洢��0������ʱ��Ҫ��ǰһ����������
		//��0����Կ����������Կ
		for(i = 0; i < 16; i++)
			rect_key[i / 4][i % 4] = key[i];
		//��i�������չ�������⴦��
		for(n = 1; n < 11; n++){ //��1�鵽��10������
			//��0���������ɴ���
			for(j = 0; j < 4; j++) //��ǰһ�м���n-1���3�У�i=3����4���ֽ�ѭ������1���ֽ�
				SubWord[j] = rect_key[(n - 1) * 4 + ((j + 1) % 4)][3];
			for(j = 0; j < 4; j++) //����ÿ���ֽڽ����ֽ�����任SubBytes
				SubWord[j] = getNumFromSBox(SubWord[j], S);
			//����һ�У�����һ���ֽڣ���1�ֳ���rc[n]�����
			SubWord[0] ^= Rcon[n];
			for(j = 0; j < 4; j++) //����ǰһ����������
				rect_key[n * 4 + j][0] = SubWord[j] ^ rect_key[(n - 1) * 4 + j][0];
			for(i = 1; i < 4; i++) //��n���1�е���3������
				for(j = 0; j < 4; j++) //��i�е�j�����������
					rect_key[n * 4 + j][i] = rect_key[(n - 1) * 4 + j][i] ^ rect_key[n * 4 + j][i - 1];
			//��n���i��Ϊ��n-1���i�����n���i-1��֮���
		}
		return;
	}
	void Encryption(){ //AES����
		int i, j;
		for(i = 0; i < 16; i++) //State����rect_m׼��
			rect_m[i / 4][i % 4] = m[i];
		AddRoundKey(0);
		for(int i = 1; i <= round; i++){ //ʮ�ֵ���
			SubBytes(S); //S���û�
			ShiftRows(); //����λ
			if(i < round) //�������һ�ֵĻ����л���
				MixColumns(colm);
			AddRoundKey(i); //i����Կ��
		}
		for(i = 0; i < 16; i++) //State����rect_m����
			m[i] = rect_m[i / 4][i % 4];
		return;
	}
	void Decryption(){ //AES����
		int i;
		for(i = 0; i < 16; i++) //State����rect_m׼��
			rect_m[i / 4][i % 4] = m[i];
		AddRoundKey(round);
		for(int i = round - 1;i >= 0; i--){ //ʮ�ֵ���������i�ǰ��ռ���˳��������
			InverseShiftRows();//��������λ
			SubBytes(S2);//����S���滻
			AddRoundKey(i);//i����Կ��
			if(i > 0) //�������һ�ֵĻ��������л���
				MixColumns(deColM);//�����л���
		}
		for(i = 0;i < 16; i++) //State����rect_m����
			m[i] = rect_m[i / 4][i % 4];
		return;
	}
	void showContext(int mode){ //�����ǰ���ݣ�0��ʾint��1��ʾchar
		int i;
		for(i = 0; i < 16; i++){
			if(mode == 1)
				cout << (char)m[i] << " ";
			else if (mode == 0)
				cout << m[i] << " ";
		}
		cout << endl;
		return;
	}
	void changeContext(string M){ //��������
		for (int i = 0;i < 16;i++){
			m[i] = getIntFromChar(M[i]);
		}
		return;
	}
	void CBCEncryption(int number, string M[]){ //CBC����,����������������������string����
		int i, j;
		for(i = 1;i <= number; i++){
			changeContext(M[i]);
			if(i == 1){
				for(j = 0; j < 16; j++) //���IV
					m[j] ^= iv[j];
			}
			else{
				for(j = 0; j < 16; j++) //�����һ�ֽ��State
					m[j] ^= rect_m[j / 4][j % 4];
			}
			Encryption();
			showContext(0);
			showContext(1);
			cout << endl;
		}
		return;
	}
	void CBCDecryption(int number, string M[]){ //CBC����,����������������������string����
		int i, j;
		for(i = 1; i <= number; i++){
			changeContext(M[i]);
			//��¼������һ�����ķ���Ľ��
			int temp[16];
			for(j = 0; j < 16; j++)
				temp[j] = m[j];
			Decryption();
			if(i == 1){
				for(j = 0; j < 16; j++) //���IV
					m[j] ^= iv[j];
			}
			else{
				for(j = 0; j < 16; j++) //�����һ�����ķ���
					m[j] ^= temp[j];
			}
			showContext(0);
			showContext(1);
			cout << endl;
		}
		return;
	}
};
//������CAES���÷�ʵ��
void AESDemo(){ //����AES�ӽ�������
	int i;
	//������Կ
	string KEY, M;
	cout << "������Կ";
	cin >> KEY;
	while (KEY.length() != 16){
		cout << "��Կ�ĳ���Ӧ����16" << endl << "������Կ";
		cin >> KEY;
	}
	//��ʼ��AES�㷨API��
	CAES AES(KEY);
	AES.createKey();
	cout << "��������";
	cin >> M;
	while (M.length() != 16){
		cout << "���ĵĳ���Ӧ����16" << endl << "��������";
		cin >> M;
	}
	AES.changeContext(M);
	AES.showContext(0); //��ʾԭʼ��������
	AES.Encryption();
	AES.showContext(0); //��ʾ���ܽ������
	AES.Decryption();
	AES.showContext(0); //��ʾ���ܽ������
	return;
}
void CBCDemo(){ //CBCģʽ�ӽ�������
	int i, k = 3;
	//������Կ��IV����
	string KEY, IV, M[3];
	cout << "������Կ";
	cin >> KEY;
	while (KEY.length() != 16){
		cout << "��Կ�ĳ���Ӧ����16" << endl << "������Կ";
		cin >> KEY;
	}
	cout << "����IV����";
	cin >> IV;
	while (IV.length() != 16){
		cout << "IV�ĳ���Ӧ����16" << endl << "����IV";
		cin >> IV;
	}
	//��ʼ��AES�㷨API��
	CAES AES(KEY, IV);
	AES.createKey();
	//����k������
	for(i = 1; i <= k; i++){
		cout << "�����" << i << "������";
		cin >> M[i];
		while (M[i].length() != 16){
			cout << "���ĵĳ���Ӧ����16" << endl << "��������";
			cin >> M[i];
		}
	}
	//������ʾ
	cout << "������ʾ" << endl;
	AES.CBCEncryption(k, M);
	//����k������
	for(i = 1;i <= k; i++){
		cout << "�����" << k << "������";
		cin >> M[i];
		while (M[i].length() != 16){
			cout << "���ĵĳ���Ӧ����16" << endl << "��������";
			cin >> M[i];
		}
	}
	//������ʾ
	cout << "������ʾ" << endl;
	AES.CBCDecryption(k, M);
	return;
}
int main(){ //����������
	//AESDemo();
	//CBCDemo();
    return 0;
}