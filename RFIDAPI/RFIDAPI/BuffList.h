
#pragma once

//*******************
//template < class Type> class List;  //前视的类定义
template < class Type> class CBuffList;  //前视的类定义

template < class Type > class ListNode //链表节点类的定义
{
	//	friend class List<Type>;   //List类作为友元类定义
	friend class CBuffList<Type>;
public:
	ListNode();      //不给数据的构造函数
	ListNode(const Type &item);  //给数据的构造函数
	ListNode<Type>* NextNode()  //给出当前节点的下一个节点地址
	{
		return link;
	}
	void InsertAfter( ListNode<Type> * p); //当前节点插入
	ListNode<Type>* GetNode(const Type &item,ListNode<Type> *next);//建立一个新节点
	ListNode<Type>* RemoveAfter();   //删除当前节点的下一个节点
private:
	Type data;     //数据域
	ListNode<Type> *link;  //链指针域
};



template <class Type> 

class CBuffList //单链表类定义
{
public:
	CBuffList(); //构造函数
	CBuffList(int nCount); //构造函数
	bool Init(int nCount); //构造函数
	bool Add(Type& data);
	bool Add(Type* pData);
	bool Clear();
	bool RemoveHead(Type &data);
	int Length() const;
	void MakeEmpty();
	~CBuffList(); 
	HANDLE GetSingle();
	int GetCurCount();

private:
	ListNode<Type>* pFirst;    //链表的表头指针,表尾指针
	ListNode<Type>* pLast;
	ListNode<Type>* pToAdd;
	int m_nInitCount;
	int m_nCurCount;
	HANDLE m_DataRecvHanle;
	CRITICAL_SECTION CriticalSection; 

};


template <class Type> 
ListNode<Type>::ListNode():link(NULL)
{

}

template <class Type> 
ListNode<Type>::ListNode(const Type&item)//	:data(item),link(NULL)
{
	memcpy(data,item,sizeof(item));
	link = NULL;
}

template <class Type> 
void ListNode<Type>::InsertAfter(ListNode<Type> *p)
{
	p->link=link;
	link=p;
}

template <class Type> 
ListNode<Type>* ListNode<Type>::GetNode(const Type& item,ListNode<Type> *next=NULL)
{
	ListNode<Type> *newnode=new ListNode<Type>(item);
	newnode->link=next;
	return newnode;
}

template <class Type> 
ListNode<Type> * ListNode<Type>::RemoveAfter()
{
	ListNode<Type> * tempptr=link;
	if(link==NULL)return NULL;
	link=tempptr->link;
	return tempptr;
}

template <class Type> 
CBuffList<Type>::CBuffList() //构造函数
{
}

template <class Type> 
CBuffList<Type>::CBuffList(int nCount) //构造函数
{
	pFirst = NULL;    //链表的表头指针,表尾指针
	pLast = NULL;
	pToAdd = NULL;
	m_nCurCount = 0;
	m_DataRecvHanle = NULL;

	m_DataRecvHanle = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_nInitCount = nCount;

	ListNode<Type> *pNow = NULL;
	ListNode<Type> *pOrg = NULL;
	for( int i = 0 ; i < nCount ; i++)
	{
		pNow = new ListNode<Type>;
		if( NULL == pNow )
		{
			break;
		}

		if( 0 == i ) //保存头指针
		{
			pFirst = pNow;
		}
		//if( nCount-1 == i ) //保存尾指针
		//{
		//	pLast = pNow;
		//}
		if( NULL != pOrg)
		{
			pOrg->link = pNow;
		}

		pOrg = pNow;
	}

	pToAdd = pFirst;
	pLast =  pNow;
	pLast-> link = NULL;
	InitializeCriticalSection(&CriticalSection);

}


template <class Type> 
bool CBuffList<Type>::Init(int nCount) //构造函数
{

	pFirst = NULL;    //链表的表头指针,表尾指针
	pLast = NULL;
	pToAdd = NULL;
	m_nCurCount = 0;
	m_DataRecvHanle = NULL;

	m_DataRecvHanle = CreateEvent(NULL,TRUE,FALSE,NULL);
	m_nInitCount = nCount;

	ListNode<Type> *pNow = NULL;
	ListNode<Type> *pOrg = NULL;
	for( int i = 0 ; i < nCount ; i++)
	{
		pNow = new ListNode<Type>;
		if( NULL == pNow )
		{
			break;
		}

		if( 0 == i ) //保存头指针
		{
			pFirst = pNow;
		}
		//if( nCount-1 == i ) //保存尾指针
		//{
		//	pLast = pNow;
		//}
		if( NULL != pOrg)
		{
			pOrg->link = pNow;
		}

		pOrg = pNow;
	}

	pToAdd = pFirst;
	pLast =  pNow;
	pLast-> link = NULL;
	InitializeCriticalSection(&CriticalSection);
	return true;
}

template <class Type> 
bool CBuffList<Type>::Add(Type& data)
{
	//try
	//{
	//	EnterCriticalSection(&CriticalSection);
	//	//检查m_nIncCount是否已经是最大值
	//	if( m_nCurCount >= m_nInitCount ) //是否已经填满
	//	{
	//		//判断Dec是否大于0
	//		return false;
	//	}

	//	if( NULL != pToAdd )
	//	{
	//		memcpy((void*)&pToAdd->data,(void*)&data,sizeof(data));
	//	}

	//	pToAdd = pToAdd->link;//更新到后面一个指针


	//	m_nCurCount++;//当前已使数++

	//	if( 1 == m_nCurCount ) //如果为1,则setevent
	//	{
	//		SetEvent(m_DataRecvHanle);
	//	}
	//}
	//catch (...)
	//{
	//	

	//}
	//LeaveCriticalSection(&CriticalSection);

	return true;

}

template <class Type> 
bool CBuffList<Type>::Clear()
{
	try
	{
		EnterCriticalSection(&CriticalSection);
		m_nCurCount = 0 ;//使为0
		pToAdd = pFirst;//指向头指针
		ResetEvent(m_DataRecvHanle);
	}
	catch (...)
	{

	}

	LeaveCriticalSection(&CriticalSection);
	return true;
}


template <class Type> 
bool CBuffList<Type>::Add(Type* pData)
{
	bool bRet = true;
	try
	{
		do 
		{
			EnterCriticalSection(&CriticalSection);
			//检查m_nIncCount是否已经是最大值
			if( m_nCurCount >= m_nInitCount ) //是否已经填满
			{
				//判断Dec是否大于0
				bRet = false;
				break;
			}

			//if( NULL == pToAdd )//BUFFER已满时,pToAdd = NULL,不过有上面的判断不应该会来到这里
			//{
			//	bRet = false;
			//	break;
			//}

			memcpy((void*)&pToAdd->data,pData,sizeof(Type));
			pToAdd = pToAdd->link;//更新到后面一个指针
			if( NULL == pToAdd ) //证明是尾指针了
			{
				pToAdd = pFirst;
				/*从头开始再增加,这里会不会冲掉数据?
				不会,因为前面有
				m_nCurCount >= m_nInitCount判断*/
			}

			m_nCurCount++;//当前已使数++

			if( 1 == m_nCurCount ) //如果为1,则setevent
			{
				SetEvent(m_DataRecvHanle);
			}

		} while (0);

	}
	catch (...)
	{

	}

	LeaveCriticalSection(&CriticalSection);
	return bRet;
}



template <class Type>
HANDLE CBuffList<Type>::GetSingle()
{
	return m_DataRecvHanle;
}
template <class Type>
bool CBuffList<Type>::RemoveHead(Type &data)
{
	bool bRet = true;
	try
	{
		do 
		{
			EnterCriticalSection(&CriticalSection);
			if( 0 == m_nCurCount ) //无数据可取
			{
				bRet = false;
				break;
			}
			memcpy((void*)&data,(void*)&pFirst->data,sizeof(data));
			ListNode<Type> *pOrgFirst = pFirst;//保存原来头指针
			pFirst = pFirst->link;//头指针往后移动
			pLast->link = pOrgFirst;//更新尾指针，指向原来的头

			pLast = pOrgFirst ;//原来的头变成了尾 
			pLast->link = NULL;//尾指针后来是NULL
			m_nCurCount--;//已使用数 

			if( 0 == m_nCurCount ) //如果为0,则setevent
			{
				ResetEvent(m_DataRecvHanle);
			}


		}while (0);

	} 
	catch (...)
	{

	}	

	LeaveCriticalSection(&CriticalSection);
	return bRet;
}

template <class Type>
int CBuffList<Type>::Length() const
{
	return m_nCurCount;
}

template <class Type> 
CBuffList<Type>::~CBuffList()
{
	MakeEmpty();
	if( m_DataRecvHanle != NULL )
	{
		CloseHandle(m_DataRecvHanle);
		m_DataRecvHanle = NULL;
		DeleteCriticalSection(&CriticalSection);
	}
}

template <class Type> 
int CBuffList<Type>::GetCurCount()
{
	return m_nCurCount;
}


template <class Type> 
void CBuffList<Type>::MakeEmpty()
{
	ListNode<Type> *p = pFirst;
	ListNode<Type> *pTemp;
	while( p != NULL)
	{
		pTemp = p->link;
		delete p;		
		p = pTemp;
	}
}



/*

有个较常的作法是，写到 .inc文件中
这涉及到模板的分离编译模式，就是把定义和实现放在不同的文件里，在《c++primer》 3rd里有讲到。本来看似很简单的一个问题，实际上要编译器来做的话还是比较困难的，网上有这方面的资料。
模板是源代码级的重用，必须要能特化后才能产生真正的可执行代码和符号，才能做连接。#拎壶冲 发表于2006-02-24 10:12:00  IP: 207.46.89.*
C++标准里规定了export关键字用于实现模版定义与实现的分离，不过到目前为止几乎没有便一起支持这个关键字#乱 发表于2006-02-24 17:49:00  IP: 210.82.77.*
目前好像还没有编译器支持模版分离编译 



可以把模版看成宏的更复杂，更实用的形式，两者很类似，都必须在预编译期间实例化才能编译通过，所以实现一般都是放在h中，如果把实现代码放在cpp中，就必须在使用该模版的cpp中include该实现cpp，否则就无法实例化。
模板函数的特化版本是可以放在cpp中。 

预编译和编译期恐怕不是一回事哦。 

宏是简单的文字替换，通过预编译处理完成简单的文字替换工作，这期间没有目标文件产生。 

编译期可就没那么简单了。 

CPP中同时存放模板和实现会很难解析。类似的双引号嵌套那样： 
"ABC"DCE"PROC"MFFC"TTX"，产生N种不同的解释。 

假如，CPP中允许非特化模板函数存在，会出现在需要实例化某个函数的时候，该函数的模板元数据却还没有…… 

实现分离编译需要对CPP做和H头文件一样的处理，天哪，会崩溃的…… 
编译器不知道那些CPP只含有模板非特化实现，而另外的CPP是混合的，或者30%，或者70%。 
真得太困难了，除非你能忍受慢的像蜗牛的编译速度…… 




*/