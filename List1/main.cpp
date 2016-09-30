#include<iostream>
#include"node.h"
using namespace std;

int main()
{
	int chosen;
	Node List(0);
	while (1)
	{
		system("cls");
		cout << "what you want to do?"<<endl<<"1.new a node"<<endl << "2.show nodes" << endl << "3.edit a node" << endl<<"4.delete a node"<<endl;
		cin >> chosen;
		switch (chosen)
		{
		case 1:List.New(); break;
		case 2:List.Show(); break;
		case 3:List.Edit(); break;
		case 4:List.Del(); break;
		default:
			break;
		}
	}
	return 0;
}
