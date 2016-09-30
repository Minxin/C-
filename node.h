#ifndef _NODE_H_
#define _NODE_H_

class Node
{
public:
	Node(int data):data_(data) 
	{
		next_ = nullptr;
	}
	bool New();
	void Show() const;
	bool Edit();
	bool Del();

private:
	int No_;
	int data_;
	Node* next_;
	static int Number;
};

#endif // _NODE_H_

