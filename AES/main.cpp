#include <iostream>
#include "AES.h"
using namespace std;

int main()
{
	AES aes = AES();
	int RUN;
	unsigned char status[4][4]= { 0x32, 0x43 ,0xf6 ,0xa8 ,0x88 ,0x5a ,0x30 ,0x8d ,0x31 ,0x31 ,0x98 ,0xa2 ,0xe0 ,0x37 ,0x07 ,0x34 };
	unsigned char RoundKey[4][4] = { 0x00 };
	unsigned char bit[8] = { 0x00 };
	cout << "AES encrypt start:" << endl;
	cout << "请输入加密轮数： " << endl;
	cin >> RUN;
	aes.Encrypte(status, bit,RoundKey,RUN);
	getchar();
	return 0;
}
