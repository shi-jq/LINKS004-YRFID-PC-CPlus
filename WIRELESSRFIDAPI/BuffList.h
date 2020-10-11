
#pragma once

//*******************
//template < class Type> class List;  //ǰ�ӵ��ඨ��
template < class Type> class CBuffList;  //ǰ�ӵ��ඨ��

template < class Type > class ListNode //����ڵ���Ķ���
{
	//	friend class List<Type>;   //List����Ϊ��Ԫ�ඨ��
	friend class CBuffList<Type>;
public:
	ListNode();      //�������ݵĹ��캯��
	ListNode(const Type &item);  //�����ݵĹ��캯��
	ListNode<Type>* NextNode()  //������ǰ�ڵ����һ���ڵ��ַ
	{
		return link;
	}
	void InsertAfter( ListNode<Type> * p); //��ǰ�ڵ����
	ListNode<Type>* GetNode(const Type &item,ListNode<Type> *next);//����һ���½ڵ�
	ListNode<Type>* RemoveAfter();   //ɾ����ǰ�ڵ����һ���ڵ�
private:
	Type data;     //������
	ListNode<Type> *link;  //��ָ����
};



template <class Type> 

class CBuffList //�������ඨ��
{
public:
	CBuffList(); //���캯��
	CBuffList(int nCount); //���캯��
	bool Init(int nCount); //���캯��
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
	ListNode<Type>* pFirst;    //����ı�ͷָ��,��βָ��
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
CBuffList<Type>::CBuffList() //���캯��
{
}

template <class Type> 
CBuffList<Type>::CBuffList(int nCount) //���캯��
{
	pFirst = NULL;    //����ı�ͷָ��,��βָ��
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

		if( 0 == i ) //����ͷָ��
		{
			pFirst = pNow;
		}
		//if( nCount-1 == i ) //����βָ��
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
bool CBuffList<Type>::Init(int nCount) //���캯��
{

	pFirst = NULL;    //����ı�ͷָ��,��βָ��
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

		if( 0 == i ) //����ͷָ��
		{
			pFirst = pNow;
		}
		//if( nCount-1 == i ) //����βָ��
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
	//	//���m_nIncCount�Ƿ��Ѿ������ֵ
	//	if( m_nCurCount >= m_nInitCount ) //�Ƿ��Ѿ�����
	//	{
	//		//�ж�Dec�Ƿ����0
	//		return false;
	//	}

	//	if( NULL != pToAdd )
	//	{
	//		memcpy((void*)&pToAdd->data,(void*)&data,sizeof(data));
	//	}

	//	pToAdd = pToAdd->link;//���µ�����һ��ָ��


	//	m_nCurCount++;//��ǰ��ʹ��++

	//	if( 1 == m_nCurCount ) //���Ϊ1,��setevent
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
		m_nCurCount = 0 ;//ʹΪ0
		pToAdd = pFirst;//ָ��ͷָ��
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
			//���m_nIncCount�Ƿ��Ѿ������ֵ
			if( m_nCurCount >= m_nInitCount ) //�Ƿ��Ѿ�����
			{
				//�ж�Dec�Ƿ����0
				bRet = false;
				break;
			}

			//if( NULL == pToAdd )//BUFFER����ʱ,pToAdd = NULL,������������жϲ�Ӧ�û���������
			//{
			//	bRet = false;
			//	break;
			//}

			memcpy((void*)&pToAdd->data,pData,sizeof(Type));
			pToAdd = pToAdd->link;//���µ�����һ��ָ��
			if( NULL == pToAdd ) //֤����βָ����
			{
				pToAdd = pFirst;
				/*��ͷ��ʼ������,����᲻��������?
				����,��Ϊǰ����
				m_nCurCount >= m_nInitCount�ж�*/
			}

			m_nCurCount++;//��ǰ��ʹ��++

			if( 1 == m_nCurCount ) //���Ϊ1,��setevent
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
			if( 0 == m_nCurCount ) //�����ݿ�ȡ
			{
				bRet = false;
				break;
			}
			memcpy((void*)&data,(void*)&pFirst->data,sizeof(data));
			ListNode<Type> *pOrgFirst = pFirst;//����ԭ��ͷָ��
			pFirst = pFirst->link;//ͷָ�������ƶ�
			pLast->link = pOrgFirst;//����βָ�룬ָ��ԭ����ͷ

			pLast = pOrgFirst ;//ԭ����ͷ�����β 
			pLast->link = NULL;//βָ�������NULL
			m_nCurCount--;//��ʹ���� 

			if( 0 == m_nCurCount ) //���Ϊ0,��setevent
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

�и��ϳ��������ǣ�д�� .inc�ļ���
���漰��ģ��ķ������ģʽ�����ǰѶ����ʵ�ַ��ڲ�ͬ���ļ���ڡ�c++primer�� 3rd���н������������ƺܼ򵥵�һ�����⣬ʵ����Ҫ�����������Ļ����ǱȽ����ѵģ��������ⷽ������ϡ�
ģ����Դ���뼶�����ã�����Ҫ���ػ�����ܲ��������Ŀ�ִ�д���ͷ��ţ����������ӡ�#����� ������2006-02-24 10:12:00  IP: 207.46.89.*
C++��׼��涨��export�ؼ�������ʵ��ģ�涨����ʵ�ֵķ��룬������ĿǰΪֹ����û�б�һ��֧������ؼ���#�� ������2006-02-24 17:49:00  IP: 210.82.77.*
Ŀǰ����û�б�����֧��ģ�������� 



���԰�ģ�濴�ɺ�ĸ����ӣ���ʵ�õ���ʽ�����ߺ����ƣ���������Ԥ�����ڼ�ʵ�������ܱ���ͨ��������ʵ��һ�㶼�Ƿ���h�У������ʵ�ִ������cpp�У��ͱ�����ʹ�ø�ģ���cpp��include��ʵ��cpp��������޷�ʵ������
ģ�庯�����ػ��汾�ǿ��Է���cpp�С� 

Ԥ����ͱ����ڿ��²���һ����Ŷ�� 

���Ǽ򵥵������滻��ͨ��Ԥ���봦����ɼ򵥵������滻���������ڼ�û��Ŀ���ļ������� 

�����ڿɾ�û��ô���ˡ� 

CPP��ͬʱ���ģ���ʵ�ֻ���ѽ��������Ƶ�˫����Ƕ�������� 
"ABC"DCE"PROC"MFFC"TTX"������N�ֲ�ͬ�Ľ��͡� 

���磬CPP��������ػ�ģ�庯�����ڣ����������Ҫʵ����ĳ��������ʱ�򣬸ú�����ģ��Ԫ����ȴ��û�С��� 

ʵ�ַ��������Ҫ��CPP����Hͷ�ļ�һ���Ĵ������ģ�������ġ��� 
��������֪����ЩCPPֻ����ģ����ػ�ʵ�֣��������CPP�ǻ�ϵģ�����30%������70%�� 
���̫�����ˣ���������������������ţ�ı����ٶȡ��� 




*/