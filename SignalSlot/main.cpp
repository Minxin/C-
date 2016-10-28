#include<iostream>
#include<string>
#include"SignalSlot.h"
using namespace std;

class Machine1:public MySlot
{
public:
	void encrypt(string& str)
	{
		int len = str.length();
		char temp;
		for (int i = 0; i < (len)/2; ++i)
		{
			temp = str[i];
			str[i] = str[len - 1 - i];
			str[len - 1 - i] = temp;
		}
	}
};

class Encryption
{
public:
	MySignal<string&> start;
	void nowStart(string& str)
	{
		start(str);
	}
};
int main()
{
	Encryption enc;
	string str = "Hello World!";
	Machine1* mac1=new Machine1;
	enc.start.connect(mac1, &Machine1::encrypt);
	enc.nowStart(str);
	cout<< str << endl;
	getchar();
	return 0;
}

