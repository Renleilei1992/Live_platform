#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node
{
	int data;
	struct Node *next;
}SLIST;

SLIST *SList_Create(); //创建链表
int SList_Print(SLIST *pHead); //遍历链表
int SList_NodeInsert(SLIST *pHead, int x, int y); //插入值  在x值之前 删除y
int SList_NodeDel(SLIST *pHead, int y);
int SList_Destory(SLIST *pHead);


SLIST *SList_Create()
{

	SLIST *pHead, *pM, *pCur;
	int		data;
	//创建头节点 并初始化
	pHead = (SLIST *)malloc(sizeof(SLIST));
	if (pHead == NULL)
	{
		return NULL;
	}
	pHead->data = 0;
	pHead->next = NULL;

	printf("\nplease enter you data: ");
	scanf("%d", &data);

	pCur = pHead;

	while (data != -1)
	{
		//创建业务节点 并初始化 不断接受输入 malloc新结点
		pM = (SLIST *)malloc(sizeof(SLIST));
		if (pM == NULL)
		{
			return NULL;
		}
		pM->data = data;
		pM->next = NULL;

		//2 新结点 入链表 
		pCur->next = pM;

		//3 新结点变成当前节点
		pCur = pM;  //链表结点的尾部追加 

		printf("\nplease enter you data: ");
		scanf("%d", &data);
	}

	return pHead;
}
int SList_Print(SLIST *pHead)
{
	SLIST *tmp = NULL;
	if (pHead == NULL)
	{
		return -1;
	}
	tmp = pHead->next;

	printf("\nBegin\t");
	while (tmp)
	{
		printf("%d ", tmp->data);
		tmp = tmp->next;
	}
	printf("\tEnd");
	return 0;
}

int SList_NodeInsert(SLIST *pHead, int x, int y)
{
	SLIST *pM, *pCur, *pPre;

	//创建新的业务节点pM
	pM = (SLIST *)malloc(sizeof(SLIST));
	if (pM == NULL)
	{
		return -1;
	}
	pM->next = NULL;
	pM->data = y;

	//遍历链表
	pPre = pHead;
	pCur = pHead->next;

	while (pCur)
	{
		if (pCur->data == x)
		{
			break;
		}
		pPre = pCur;
		pCur = pCur->next;
	}

	//让新结点 连接 后续链表
	pM->next = pPre->next;
	//让前驱节点 连接 新结点
	pPre->next = pM;

	return 0;
}

int SList_NodeDel(SLIST *pHead, int y)
{
	SLIST  *pCur, *pPre;

	//初始化状态

	pPre = pHead;
	pCur = pHead->next;

	while(pCur != NULL)
	{
		if (pCur->data == y)
		{
			break;
		}
		pPre = pCur;
		pCur = pCur->next;
	}

	//删除操作
	if (pCur == NULL)
	{
		printf("没有找到结点值为:%d 的结点\n", y);
		return -1;
	}
	pPre->next = pCur->next;
	if (pCur != NULL)
	{
		free(pCur);
	}
	return 0;
}

int SList_Destory(SLIST *pHead)
{
	SLIST *tmp = NULL;
	if (pHead == NULL)
	{
		return -1;
	}
	
	while (pHead != NULL)
	{
		tmp = pHead->next;
		free(pHead);
		pHead = tmp;
	}
	return 0;
}

int SList_Reverse(SLIST *pHead)
{
	SLIST	*p = NULL; //前驱指针
	SLIST	*q = NULL; //当前指针
	SLIST	*t = NULL; //缓存的一个结点

	if (pHead==NULL || pHead->next == NULL ||pHead->next->next ==NULL )
	{
		return 0;
	}
	
	//初始化 	//前驱结点
	p = pHead->next;
	q = pHead->next->next;

	//p = pHead;  //代码能兼容
	//q = pHead->next;
	
	//一个结点 一个结点的逆置
	while(q)
	{
		t = q->next; //缓冲后面的链表

		q->next = p;	//逆置

		p = q; //让p下移一个结点

		q = t;
	}

	//头节点 变成 尾部结点 后  置null
	pHead->next->next = NULL;
	pHead->next = p;  //

	return 0;
}
void main()
{
	int  ret = 0;

	SLIST *pHead = NULL;
	pHead = SList_Create();
	ret = SList_Print(pHead);

	ret = SList_NodeInsert(pHead, 20, 19);
	ret = SList_Print(pHead);

	ret = SList_NodeDel(pHead, 19);
	ret = SList_Print(pHead);

	ret =  SList_Reverse(pHead);
	ret = SList_Print(pHead);

	SList_Destory(pHead);

	printf("hello...\n");
	system("pause");
	return ;
}
