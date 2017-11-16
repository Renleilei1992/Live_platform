#define  _CRT_SECURE_NO_WARNINGS 
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct Node
{
	int data;
	struct Node *next;
}SLIST;

SLIST *SList_Create(); //��������
int SList_Print(SLIST *pHead); //��������
int SList_NodeInsert(SLIST *pHead, int x, int y); //����ֵ  ��xֵ֮ǰ ɾ��y
int SList_NodeDel(SLIST *pHead, int y);
int SList_Destory(SLIST *pHead);


SLIST *SList_Create()
{

	SLIST *pHead, *pM, *pCur;
	int		data;
	//����ͷ�ڵ� ����ʼ��
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
		//����ҵ��ڵ� ����ʼ�� ���Ͻ������� malloc�½��
		pM = (SLIST *)malloc(sizeof(SLIST));
		if (pM == NULL)
		{
			return NULL;
		}
		pM->data = data;
		pM->next = NULL;

		//2 �½�� ������ 
		pCur->next = pM;

		//3 �½���ɵ�ǰ�ڵ�
		pCur = pM;  //�������β��׷�� 

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

	//�����µ�ҵ��ڵ�pM
	pM = (SLIST *)malloc(sizeof(SLIST));
	if (pM == NULL)
	{
		return -1;
	}
	pM->next = NULL;
	pM->data = y;

	//��������
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

	//���½�� ���� ��������
	pM->next = pPre->next;
	//��ǰ���ڵ� ���� �½��
	pPre->next = pM;

	return 0;
}

int SList_NodeDel(SLIST *pHead, int y)
{
	SLIST  *pCur, *pPre;

	//��ʼ��״̬

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

	//ɾ������
	if (pCur == NULL)
	{
		printf("û���ҵ����ֵΪ:%d �Ľ��\n", y);
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
	SLIST	*p = NULL; //ǰ��ָ��
	SLIST	*q = NULL; //��ǰָ��
	SLIST	*t = NULL; //�����һ�����

	if (pHead==NULL || pHead->next == NULL ||pHead->next->next ==NULL )
	{
		return 0;
	}
	
	//��ʼ�� 	//ǰ�����
	p = pHead->next;
	q = pHead->next->next;

	//p = pHead;  //�����ܼ���
	//q = pHead->next;
	
	//һ����� һ����������
	while(q)
	{
		t = q->next; //������������

		q->next = p;	//����

		p = q; //��p����һ�����

		q = t;
	}

	//ͷ�ڵ� ��� β����� ��  ��null
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