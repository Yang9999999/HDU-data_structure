#include <stdio.h>
#include <stdlib.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

#define LIST_INIT_SIZE 10
#define LISTINCREMENT  5

typedef int Status;   //定义函数类型名

typedef int ElemType;//定义ElemType类型

typedef struct LNode {  //结点类型定义 

        ElemType data;  

        struct LNode  *next;

}LNode, *LinkList;  

Status InitList(LinkList &L){
	L=(LinkList)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	L->next=NULL;
}

Status ClearList(LinkList &L){
	L->next=NULL;
	//L->data=NULL;
}

Status ListLength(LinkList L){
	int i=0;
	while(L->next!=NULL)
	{
		L=L->next;
		i++;
	}
	return i;
}

Status GetElem(LinkList L,int i,ElemType &e){
	while(i--){
		L=L->next;
	}
	e=L->data;
}

Status LocateList(LinkList L,ElemType e){
	int i=0;
	
	
	while(L->data!=e&&L->next!=NULL){
		i++;
		L=L->next;
	}
	if(L->next!=NULL)return i;
	else{
		return 0;
	}
}

Status ListInsert(LinkList &L,int i,ElemType e){
	int j=0;
	LinkList s,p=L;
	while(p && j<i-1){
		p=p->next;++j;
	}
	if(!p||j>i-1)return ERROR;
	s=(LinkList)malloc(sizeof(LNode));
	s->data=e;
	s->next=p->next;
	p->next=s;
	
}
Status ListDelete(LinkList &L,int i,ElemType &e){
	LinkList q,p=L;
	int j=0;
	while(p&&j<i-1){
		p=p->next;j++;
	}
	q=p->next;
	p->next=p->next->next;
	free(q);
	
}
Status ListTraverse(LinkList L){
	while(L->next!=NULL){
		L=L->next;
		printf("%d ",L->data);
	}
	printf("\n");
}
Status Union(LinkList &La,LinkList Lb){
	int i,len_La,len_Lb;
	ElemType e;
	len_La=ListLength(La);
	len_Lb=ListLength(Lb);
	for(i=1;i<=len_Lb;i++){
		GetElem(Lb,i,e);
		if(!LocateList(La,e))ListInsert(La,++len_La,e);
	}
}
Status Intersection(LinkList &La,LinkList Lb){
	int i,len_La,len_Lb;
	ElemType e;
	len_La=ListLength(La);
	len_Lb=ListLength(Lb);
	for(i=1;i<len_La;i++){
		GetElem(La,i,e);
		if(!LocateList(Lb,e))ListDelete(La,i,e);
		else ++i;
	}
}
Status Difference(LinkList &La,LinkList Lb){
	int i;
	ElemType e;
	i=1;
	while(i<=ListLength(La)){
		GetElem(La,i,e);
		if(LocateList(Lb,e))ListDelete(La,i,e);
		else ++i;
	}
}
Status MergeList(LinkList La,LinkList Lb,LinkList &Lc){
	LinkList pa=La->next;
	LinkList pb=Lb->next;
	LinkList pc;
	Lc=pc=La;
	while(pa&&pb){
		if(pa->data<=pb->data)
		{
			pc->next=pa;pc=pa;pa=pa->next;
		}
		else{
			pc->next=pb;pc=pb;pb=pb->next;
		}
		
	}
	pc->next=pa?pa:pb;
	free(Lb);
}
Status Purge(LinkList &Lc){
	int i,j;
	ElemType a,b;
	i=1;
	while(i<=ListLength(Lc)){
		GetElem(Lc,i,a);
		j=++i;
		while(j<=ListLength(Lc)){
			GetElem(Lc,j,b);
			if(a==b)ListDelete(Lc,j,b);
			else ++j;
		}
	}
}
int main()
{
	ElemType Array1[]={2,8,27,39,66,77,89};
	ElemType Array2[]={6,18,27,59,65,77,89,120,140};
		
	LinkList LA;
	LinkList LB;
	LinkList LC;
	InitList(LA);
	InitList(LB);
	ClearList(LA);
	for(int k=1;k<=7;k++)ListInsert(LA,k,Array1[k-1]);
	for(int k=1;k<=9;k++)ListInsert(LB,k,Array2[k-1]);
	
	
	Union(LA,LB);
	printf("LA∪LB=");
	ListTraverse(LA);
	ClearList(LA);
	for(int k=1;k<=7;k++)ListInsert(LA,k,Array1[k-1]);
	
	
	Intersection(LA,LB);
	printf("LA∩LB=");
	ListTraverse(LA);
	ClearList(LA);
	for(int k=1;k<=7;k++)ListInsert(LA,k,Array1[k-1]);
	
	
	Difference(LA,LB);
	printf("LA-LB=");
	ListTraverse(LA);
	ClearList(LA);
	for(int k=1;k<=7;k++)ListInsert(LA,k,Array1[k-1]);
	
	
	MergeList(LA,LB,LC);
	printf("LA+LB=");
	ListTraverse(LC);
	Purge(LC);
	printf("PurgeLC=");
	ListTraverse(LC);
	
	
	return 0;
}
