#include "node.h"
#include "windows.h"
#include<iostream>

int Node::Number = 0;

bool Node::New ()
{
	Number++;
	Node* p;
	if (!(p = (Node*)malloc(sizeof(Node))))
	{
		std::cout << "malloc fail£¡"<< std::endl;
		Sleep(1000);
		return false;
	}
	std::cout << "new success!" << std::endl;
	Sleep(1000);
	p->No_ = Number;
	p->data_ = 0;
	p->next_ = Node::next_;
	Node::next_ = p;
	return true;
}

void Node::Show() const
{
	Node* p;
	p = Node::next_;
	std::cout << "The list is:" << std::endl;
	while (p != nullptr)
	{
		std::cout << p->No_ <<".  " ;
		std::cout <<p->data_<< std::endl;
		p = p->next_;
	}
	Sleep(5000);
}

bool Node::Edit()
{
	int num,data;
	Node* p;
	p = Node::next_;
	std::cout << "which node you want to edit?" << std::endl;
	std::cin>>num;
	std::cout << "input the data:" << std::endl;
	std::cin >> data;
	while (p != nullptr)
	{
		if (p->No_ == num)
		{
			p->data_ = data;
			std::cout << "edit success!" << std::endl;
			Sleep(1000);
			return true;
		}
		p = p->next_;
	}
	std::cout << "edit fail!" << std::endl;
	Sleep(1000);
	return false;
}

bool Node::Del()
{
	int num;
	Node* p;
	p = Node::next_;
	std::cout << "which node you want to delete?" << std::endl;
	std::cin >> num;
	if (p->No_ == num)
	{
		Node::next_ = nullptr;
		std::cout << "delete success!" << std::endl;
		return true;
	}
	else
	{
		while (p != nullptr)
		{
			if (p->No_ == num)
			{
				Node* _de_ = Node::next_;
				while (_de_->next_ != nullptr)
				{
					if (_de_->next_ == p)
					{
						_de_->next_ = p->next_;
						std::cout << "delete success!" << std::endl;
						Sleep(1000);
						return true;
					}
					_de_ = _de_->next_;
				}
			}
			p = p->next_;
		}
	}
	std::cout << "delete fail!" << std::endl;
	Sleep(1000);
	return false;
}



