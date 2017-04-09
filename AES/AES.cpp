#include "AES.h"
#include  <iostream>


AES::AES()
{
}

unsigned char AES::ByteMultiply(unsigned char c)
{
	unsigned char temp;
	temp = c << 1;
	if (c & 0x80)
	{
		temp ^= 0x1b;
	}
	return temp;
}

void AES::SubBytes(unsigned char status[N][N],unsigned char bit[])
{
	int i, j;
	char high;
	char low;
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			low = status[i][j] & 0x0F;  //取低4位
			high = (status[i][j] >> 4) & 0x0f;  //取高4位
			status[i][j] = S_BOX[high][low];
		}
	}

}

void AES::ShiftRows(unsigned char State[N][N])
{
	int i = 0, j = 0;
	int shiftnum = 1;
	char tmp;

	for (j = 1; j < N; ++j)
	{
		for (int count = 1; count <= j; ++count)
		{
			tmp = State[0][j];
			for (i = 0; i < N - 1; ++i)
			{
				State[i][j] = State[i+1][j];
			}
			State[i][j] = tmp;
		}
	}
}

void AES::MixColumns(unsigned char status[N][N])
{
	unsigned char temp[4][4];
	for (int j = 0; j < 4; j++)
		for (int i = 0; i < 4; i++)
		{
			temp[i][j] = ByteMultiply(status[j][(i) % 4]) //0x02乘法
				^ (status[j][(i + 1)%4] ^ ByteMultiply(status[j][(i+1)%4])) //0x03乘法
				^ status[j][(i + 2) % 4]  //0x01乘法
				^ status[j][(i + 3) % 4]; //0x01乘法
		}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			status[i][j] = temp[j][i];

}


void AES::KeyExpansion(unsigned char bit[])
{
	unsigned char temp[4];
	unsigned char temp2[4];
	int n = 4,r=0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			key[i][j] = *(defualt_key + 4 * i + j);
		}
	}
	while (n < (4 * 11))
	{
		if ((n % 4) == 0)
		{
			temp[0] = key[n-1][1];
			temp[1] = key[n-1][2];
			temp[2] = key[n-1][3];
			temp[3] = key[n-1][0]; // 列移位
			for (int i = 0; i<4; i++)  //s盒替换
			{
				temp2[i] = S_BOX[temp[i] / 16][temp[i] % 16];
			}
			temp2[0] = temp2[0] ^ Ri[r];
			for (int i = 0; i<4; i++)
			{
				key[n][i] = key[n-4][i] ^ temp2[i];
			}
			r++;
		}
		else
		{
			for (int i = 0; i<4; i++)
			{
				key[n][i] = key[n - 1][i] ^ key[n-4][i];
			}
		}
		n++;
	}
}


void AES::RotWord(unsigned char c[], unsigned char temp[])
{
	for (int i = 1; i < 4; i++)
		temp[i - 1] = c[i];
	temp[3] = c[0];
}

void AES::SubWord(unsigned char temp[], unsigned char bit[])
{
	 for (int i = 0; i < 4; i++)
	 {
		 ByteToBits(temp[i], bit);
		 temp[i] = S_BOX[(bit[7] * 8 + bit[6] * 4 + bit[5] * 2 + bit[4])][(bit[3] * 8 + bit[2] * 4 + bit[1] * 2 + bit[0])];
	}
}

void AES::RoundKeyChoice(unsigned char RoundKey[][4], int cnt)
{
	int cnt1 = (4 * cnt);
	for (int i = 0; i < 4; i++) 
	{
		for (int j = 0; j < 4; j++) 
		{
			RoundKey[i][j] = key[cnt1+i][j];
		}
	}
}

void AES::AddRoundKey(unsigned char RoundKey[][4], unsigned char status[][4])
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			status[i][j] = status[i][j] ^ RoundKey[i][j];
}

void AES::ByteToBits(unsigned char ch, unsigned char bit[])
{
	for (int i = 0; i < 8; i++)
		bit[i] = (ch >> i) & 1;
}

void AES::Encrypte(unsigned char status[N][N], unsigned char bit[], unsigned char RoundKey[][4],int RUN)
{
	printf("Before encryte:\n");
	Output(status);
	KeyExpansion(bit);
	RoundKeyChoice(RoundKey, 0);
	AddRoundKey(RoundKey, status);
	///Output(RoundKey);
	//Output(status);
	for (int nr = 1; nr < RUN; nr++) {
		SubBytes(status, bit);
		//Output(status);
		ShiftRows(status);
		//Output(status);
		MixColumns(status);
		//Output(status);
		RoundKeyChoice(RoundKey, nr);
		AddRoundKey(RoundKey, status);
		//Output(RoundKey);
		//Output(status);
	}
	SubBytes(status, bit);
	//Output(status);
	ShiftRows(status);
	//Output(status);
	RoundKeyChoice(RoundKey, 10);
	//Output(RoundKey);
	AddRoundKey(RoundKey, status);
	printf("After encryted:\n");
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<44; j++)
		{
			printf("%2x ", key[j][i]);
		}
		printf("\n");
	}
	printf("\n");
	Output(status);
}

void AES::Output(unsigned char status[N][N])
{
	for (int i = 0; i<4; i++)
	{
		for (int j = 0; j<4; j++)
		{
			printf("%2x ", status[j][i]);
		}
		printf("\n");
	}
	printf("\n");
}

AES::~AES()
{
}
