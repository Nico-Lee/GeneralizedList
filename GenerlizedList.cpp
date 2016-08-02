#define _CRT_SECURE_NO_WARNINGS 1
#include"Generalized list .h"
GeneralizedList::GeneralizedList(const char* str)
{
	_head = _CreatList(str);
}
GeneralizedList::GeneralizedList()
	:_head(NULL)
{
}
GeneralizedList::~GeneralizedList()
{
	_Release(_head);
}
GeneralizedList::GeneralizedList(const GeneralizedList& g)
{
	_head = _Copy(g._head);
}
GeneralizedList GeneralizedList::operator = (GeneralizedList g)//不能加const和&
{

	//if (this != &g)
	//{
	//	GeneralizedNode* tmp = _Copy(g._head);
	//	_Release(_head);
	//	_head = tmp;
	//}
	//return *this

	swap(_head, g._head);//现代写法
	return *this;
}
void GeneralizedList::Print()
{
	_Print(_head);
}
size_t GeneralizedList::Size()
{
	return _Size(_head);
}
size_t GeneralizedList::Deepth()
{
	return _Deepth(_head);
}
void GeneralizedList::_Release(GeneralizedNode* head)
{
	GeneralizedNode* cur = head;
	while (cur)
	{
		GeneralizedNode* del = cur;
		cur = cur->_next;
		if (del->_type == SUB)
		{
			_Release(del->_SubLink);
		}
		delete del;
	}
}
bool GeneralizedList::_IsValue(const char& c)
{
	if (c >= '1'&&c <= '9'
		|| c >= 'a'&&c <= 'z'
		|| c >= 'A'&& c <= 'Z')
	{
		return true;
	}
	return false;
}
GeneralizedNode* GeneralizedList::_CreatList(const char*& str)
{
	assert(*str == '(');
	++str;
	GeneralizedNode* newhead = new GeneralizedNode(HEAD);
	//每次创建表或者子表都要先new出头结点
	GeneralizedNode* cur = newhead;
	while (*str)
	{
		if (_IsValue(*str))
		{
			GeneralizedNode* tmp = new GeneralizedNode(VALUE);
			tmp->_value = *str;
			cur->_next = tmp;
			cur = cur->_next;
			str++;
		}
		else if (*str == '(')
		{
			GeneralizedNode * subNode = new GeneralizedNode(SUB);
			cur->_next = subNode;
			cur = cur->_next;
			subNode->_SubLink = _CreatList(str);//递归创建子表
		}
		else if (*str == ')')
		{
			str++;
			return newhead;
		}
		else
		{
			++str;
		}

	}
	assert(false);
	return _head;
}
void GeneralizedList::_Print(GeneralizedNode* head)
{
	GeneralizedNode* cur = head;
	while (cur)
	{
		if (cur->_type == HEAD)
		{
			cout << '(';
		}
		else if (cur->_type == VALUE)
		{
			cout << cur->_value;
			if (cur->_next)//不为NULL打印',',防止在表的最后一个值后面打印一个','
			{
				cout << ',';
			}
		}
		else
		{
			_Print(cur->_SubLink);
			if (cur->_next)//(1,2,(3,4))cur为空,不打印','
			{
				cout << ',';
			}
		}
		cur = cur->_next;
	}
	cout << ')';
}
size_t GeneralizedList::_Size(GeneralizedNode* head)
{
	GeneralizedNode* cur = head;
	size_t size = 0;
	while (cur)
	{
		if (cur->_type == VALUE)
		{
			size++;
		}
		else if (cur->_type==SUB)
		{
			size +=_Size(cur->_SubLink);
		}
		cur = cur->_next;
	}
	return size;
}

size_t GeneralizedList::_Deepth(GeneralizedNode* head)
{
	GeneralizedNode* cur = head;
	size_t maxDeep = 1;
	while (cur)
	{
		if (cur->_type == SUB)
		{
			size_t deep = _Deepth(cur->_SubLink);//最深的一层子表返回1，
			if (deep + 1 > maxDeep)
				//	每返回一层deep就会+1；
			{
				maxDeep = deep + 1;
			}
		}
		cur = cur->_next;
	}
	return maxDeep;
}
GeneralizedNode* GeneralizedList::_Copy(GeneralizedNode* head)
{
	GeneralizedNode* cur = head->_next;
	GeneralizedNode* newHead = new GeneralizedNode(HEAD);
	GeneralizedNode* newCur = newHead;
	while (cur)
	{
		if (cur->_type == VALUE)
		{
			newCur->_next = new GeneralizedNode(VALUE);
			newCur = newCur->_next;
			newCur->_value = cur->_value;
		}
		else if (cur->_type == SUB)
		{
			newCur->_next = new GeneralizedNode(SUB);
			newCur = newCur->_next;
			newCur->_SubLink = _Copy(cur->_SubLink);//如果是子表节点，
		//	就递归拷贝字表，将子表的头节点返回链接到SUB节点上，
		//通过SubLink可以找到子表
		}
		cur = cur->_next;
	}
	newCur = NULL;
	return newHead;
}
