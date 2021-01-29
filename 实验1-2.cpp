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

typedef int Status;   //���庯��������

typedef int ElemType;//����ElemType����

typedef struct {	 
    ElemType *elem;  //���Ա����ݴ洢�ռ��ַ 
    int length;
    int listsize;
}SqList;// LISTΪ�û���������Ա�����




//��ʼ�������Ա�
Status InitList(SqList &L){ 
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem)exit(OVERFLOW);
	L.length=0;
	L.listsize=0;
	return OK;


}

//������Ա�Ԫ�� 
Status ClearList(SqList &L){ 
	L.length=0;
	return OK;

} 

//������Ա���
int ListLength(SqList L){ 

	return L.length;

}

//�����Ա�ָ��λ�ò���һ����Ԫ��
Status ListInsert(SqList &L, int pos, ElemType e){
//posΪ����ģ��߼���λ��,eΪ�����������Ԫ�ء�����ɹ��򷵻�1������������ֵΪ0��

	int i;
	ElemType *newbase;
	if(pos<1||pos>L.length+1)return ERROR;
	if(L.length>=L.listsize)
	{
		newbase=(ElemType *)realloc(L.elem,(L.listsize+LISTINCREMENT)*sizeof(ElemType));
	if(!newbase) exit (OVERFLOW);
	L.elem=newbase;
	L.listsize+=LISTINCREMENT;	
	}
	for(i=L.length-1;i>=pos-1;i--) L.elem[i+1]=L.elem[i];
	L.elem[pos-1]=e; 
	L.length++;
	return OK;
	

} 

//�����Ա���ɾ��ָ��λ���Ԫ��
Status ListDelete(SqList &L, int pos, ElemType &e)
{//posΪɾ���ģ��߼���λ��,��item���ر�ɾԪ�ء�ɾ���ɹ��򷵻�1������������ֵΪ0��

	int i;
	if(L.length==0) return ERROR;
	if(pos<1||pos>L.length)return ERROR;
	e=L.elem[pos-1];
	for(i=pos-1;i<L.length-1;i++)L.elem[i]=L.elem[i+1];
	L.length--;
	return OK;

}

//��ȡ˳�����ָ��λ���ϵ�����Ԫ�� 
Status GetElem(SqList L,int pos,ElemType &e){
//posΪָ��λ��,item���ڷ����ҵ�������Ԫ�أ������գ��򷵻�ERROR;

	if(pos<=0||pos>L.length){
		return ERROR;
	}
	if(L.length==0)return ERROR;
	e=L.elem[pos-1];
	return e;
	

} 

//�����Ա��в���Ԫ�أ����ص�һ����ָ��ֵƥ��Ԫ��λ��
int LocateElem(SqList L,ElemType e){
//itemΪ�����ҵ�����Ԫ��

	int i=0;
	if(L.length==0)return ERROR;
	while(i<L.length&&L.elem[i]!=e)i++;
	if(i<L.length)return i+1;
	else return ERROR;

} 

//����������Ա�
Status TraverseList(SqList L){

	int i;
	if(L.length==0)return ERROR;
	for(i=0;i<L.length;i++)
	{
		printf("%d  ",L.elem[i]);
	}
	printf("\n");
	return OK;

}

// ���ϲ�����LA=LA��LB
Status Union(SqList &La, SqList Lb){

	int i,La_len,Lb_len;
	ElemType e;
	La_len=ListLength(La);
	Lb_len=ListLength(Lb);
	for(i=1;i<=Lb_len;i++)
	{
		GetElem(Lb,i,e);
		if(!LocateElem(La,e))ListInsert(La,++La_len,e);
	}
	return OK;
}

// ���Ͻ�����LA=LA ��LB
Status Intersection(SqList &La, SqList Lb) {

	int i;
	ElemType e;
	i=1;
	while(i<=ListLength(La)){
		GetElem(La,i,e);
		if(!LocateElem(Lb,e))ListDelete(La,i,e);
		i++; 
	}
	return OK;

} 

// ���ϲ�����LA=LA-LB
Status Difference(SqList &La, SqList Lb) {

	int i;
	ElemType e;
	i=1;
	while(i<=ListLength(La)){
		GetElem(La,i,e);
		if(LocateElem(Lb,e))ListDelete(La,i,e);
		else ++i;
	}
	return OK;
}

// �����ϲ�LC=LA+LB
Status MergeList(SqList La, SqList Lb, SqList &Lc) {

	int i,j,k;
	int La_len,Lb_len;
	ElemType ai,bi;
	La_len=ListLength(La);
	Lb_len=ListLength(Lb);
	i=j=1;
	k=0;
	while(i<=La_len&&j<=Lb_len){
		GetElem(La,i,ai);
		GetElem(Lb,j,bi);
		if(ai>=bi){
			ListInsert(Lc,++k,bi);
			i++;
		}
		else{
			ListInsert(Lc,++k,ai);
			j++;
		}
	} 
	while(i<=La_len){
		GetElem(La,i,ai);
		ListInsert(Lc,++k,ai);
		i++;
	}
	while(j<=Lb_len){
		GetElem(Lb,i,bi);
		ListInsert(Lc,++k,bi);
		j++;
	}
	return OK;
}

Status Purge(SqList &Lc) {

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
	return OK;

} 

//������ 
int main(){
	SqList LA,LB,LC;				//����˳������
	ElemType Array1[]={2,8,27,39,66,77,89};		//˳���LA��Ԫ�� 
	ElemType Array2[]={6,18,27,59,65,77,89,120,140};//˳���LB��Ԫ�� 
	ElemType item;
	int i;
		
	//0.����׼��
	//0-1��ʼ�����Ա�LA,LB
	
	InitList(LA);
	InitList(LB);

	//0-2����˳���LA,LB

	for(int i=1;i<=7;i++)ListInsert(LA,i,Array1[i-1]);
	for(int i=1;i<=9;i++)ListInsert(LB,i,Array2[i-1]);

	//0-3���˳����Ԫ��

	TraverseList(LA);
	TraverseList(LB);
	//1. ����LA=LA��LB����������
	
	Union(LA,LB);
	printf("LA��LB=");
	TraverseList(LA);

	//2.����LA=LA ��LB����������

	ClearList(LA);
	for(int i=1;i<=7;i++)
		ListInsert(LA,i,Array1[i-1]);
	Intersection(LA,LB);
	printf("LA ��LB=");
	TraverseList(LA);

	//3.����LA=LA-LB����������

	ClearList(LB);
	for(int i=1;i<=7;i++)
		ListInsert(LA,i,Array1[i-1]);
	Difference(LA,LB);
	printf("LA-LB=");
	TraverseList(LA);
	
	//4.�����ϲ�LC=LA+LB����������

	ClearList(LB);
	for(int i=1;i<=7;i++)
		ListInsert(LA,i,Array1[i-1]);
	InitList(LC);
	MergeList(LA,LB,LC);
	printf("LA+LB=");
	TraverseList(LC);
	//5.ȥ��LC�ظ������Ԫ�� ����������

	Purge(LC);
	printf("PurgeLC=");
	TraverseList(LC);
	

	return 1;
}

