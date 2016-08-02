#pragma once
#include<iostream>
#include<string>
#include<assert.h>
using namespace std;

enum Type
{
	HEAD,
	SUB,
	VALUE
};

struct GeneralizedNode
{
	Type _type;
	union
	{
		int _value;
		GeneralizedNode* _SubLink;
	};
	GeneralizedNode* _next;

	GeneralizedNode(Type type)
	{
		if (type == HEAD)
		{
			_type = HEAD;
			_next = NULL;
		}
		else if (type == VALUE)
		{
			_type = VALUE;
			_value = 0;
			_next = NULL;
		}
		else
		{
			_type = SUB;
			_SubLink = NULL;
			_next = NULL;
		}
	}
};

class GeneralizedList
{
public:
	GeneralizedList(const char* str);
	GeneralizedList();
	~GeneralizedList();
	GeneralizedList(const GeneralizedList& g);
	GeneralizedList operator=(GeneralizedList g);
	size_t Size();
	size_t Deepth();
	void Print();
private:
	size_t _Size(GeneralizedNode* head);
	size_t _Deepth(GeneralizedNode* head);
	bool _IsValue(const char& c);
	GeneralizedNode* _CreatList(const char*& str);
	void _Print(GeneralizedNode* head);
	GeneralizedNode* _Copy(GeneralizedNode* head);
	void _Release(GeneralizedNode* head);
private:
	GeneralizedNode* _head;
};
