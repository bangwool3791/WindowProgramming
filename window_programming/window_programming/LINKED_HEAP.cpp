#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

typedef int ListElementDataType;

typedef struct _node
{
	ListElementDataType data;
	struct _node* next;
}node;

node* head;
node* tail;

HANDLE hHeap = 0;

void InitListHeap()
{
	SYSTEM_INFO sysInfo;
	GetSystemInfo(&sysInfo);

	UINT pageSize = sysInfo.dwPageSize;

	hHeap = HeapCreate(HEAP_NO_SERIALIZE, pageSize * 10, pageSize * 100);
}

void InitList(void)
{
	InitListHeap();

	head = (node*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(node));
	tail = (node*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(node));

	head->next = tail;
	tail->next = tail;
}

int DeleteNode(int data)
{
	node* nd = head;
	node* ndNext = nd->next;

	while (ndNext->data != data && ndNext != tail)
	{
		nd = nd->next;
		ndNext = nd->next;
	}

	if (ndNext != tail)
	{
		nd->next = ndNext->next;
		HeapFree(hHeap, HEAP_NO_SERIALIZE, ndNext);
		return 1;
	}
	else
		return 0;
}

void OrderdInsert(int data)
{
	node* nd = head;
	node* ndNext = nd->next;
	node* newNode;
	while (ndNext->data <= data && ndNext != tail)
	{
		nd = nd->next;
		ndNext = nd->next;
	}

	newNode = (node*)HeapAlloc(hHeap, HEAP_NO_SERIALIZE, sizeof(node));

	newNode->data = data;
	nd->next = newNode;
	newNode->next = ndNext;
}

void PrintAllList()
{
	node* startNode = head->next;
	while (startNode != tail)
	{
		printf("%-4d", startNode->data);
		startNode = startNode->next;
	}

	printf("\n\n");
}

void DeletaAll(void)
{
	HeapDestroy(hHeap);
	InitList();
}

int main(int argc, char* argv[])
{
	InitList();

	printf("1, 2, 3 입력 ...\n");
	OrderdInsert(1);
	OrderdInsert(2);
	OrderdInsert(3);
	PrintAllList();

	printf("4, 5, 6 입력 ...\n");
	OrderdInsert(4);
	OrderdInsert(5);
	OrderdInsert(6);
	PrintAllList();

	printf("2와 5 삭제...\n");
	DeleteNode(2);
	DeleteNode(5);
	PrintAllList();

	printf("모든리스트삭제... \n");
	DeletaAll();

	printf("6, 5, 4 입력...\n");
	OrderdInsert(6);
	OrderdInsert(5);
	OrderdInsert(4);
	PrintAllList();

	printf("모든 리스트 삭제...\n");
	DeletaAll();

	printf("1, 3, 5 입력...\n");
	OrderdInsert(1);
	OrderdInsert(3);
	OrderdInsert(5);
	PrintAllList();

	printf("2, 4, 5 입력...\n");
	OrderdInsert(2);
	OrderdInsert(4);
	OrderdInsert(6);
	PrintAllList();

	return 0;
}