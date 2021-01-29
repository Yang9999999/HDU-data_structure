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

typedef struct {	 
    ElemType *elem;  //线性表数据存储空间基址 
    int length;
    int listsize;
}SqList;// LIST为用户定义的线性表类型




//初始化空线性表
Status InitList(SqList &L){ 
	L.elem=(ElemType *)malloc(LIST_INIT_SIZE*sizeof(ElemType));
	if(!L.elem)exit(OVERFLOW);
	L.length=0;
	L.listsize=0;
	return OK;


}

//清空线性表元素 
Status ClearList(SqList &L){ 
	L.length=0;
	return OK;

} 

//求出线性表长度
int ListLength(SqList L){ 

	return L.length;

}

//向线性表指定位置插入一个新元素
Status ListInsert(SqList &L, int pos, ElemType e){
//pos为插入的（逻辑）位置,e为待插入的数据元素。插入成功则返回1；否则函数返回值为0。

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

//从线性表中删除指定位序的元素
Status ListDelete(SqList &L, int pos, ElemType &e)
{//pos为删除的（逻辑）位置,用item返回被删元素。删除成功则返回1；否则函数返回值为0。

	int i;
	if(L.length==0) return ERROR;
	if(pos<1||pos>L.length)return ERROR;
	e=L.elem[pos-1];
	for(i=pos-1;i<L.length-1;i++)L.elem[i]=L.elem[i+1];
	L.length--;
	return OK;

}

//获取顺序表中指定位置上的数据元素 
Status GetElem(SqList L,int pos,ElemType &e){
//pos为指定位置,item用于返回找到的数据元素，如果表空，则返回ERROR;

	if(pos<=0||pos>L.length){
		return ERROR;
	}
	if(L.length==0)return ERROR;
	e=L.elem[pos-1];
	return e;
	

} 

//从线性表中查找元素，返回第一个与指定值匹配元素位置
int LocateElem(SqList L,ElemType e){
//item为待查找的数据元素

	int i=0;
	if(L.length==0)return ERROR;
	while(i<L.length&&L.elem[i]!=e)i++;
	if(i<L.length)return i+1;
	else return ERROR;

} 

//遍历输出线性表
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

// 集合并运算LA=LA∪LB
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

// 集合交运算LA=LA ∩LB
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

// 集合差运算LA=LA-LB
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

// 有序表合并LC=LA+LB
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

//主函数 
int main(){
	SqList LA,LB,LC;				//定义顺序表变量
	ElemType Array1[]={2,8,27,39,66,77,89};		//顺序表LA的元素 
	ElemType Array2[]={6,18,27,59,65,77,89,120,140};//顺序表LB的元素 
	ElemType item;
	int i;
		
	//0.数据准备
	//0-1初始化线性表LA,LB
	
	InitList(LA);
	InitList(LB);

	//0-2生成顺序表LA,LB

	for(int i=1;i<=7;i++)ListInsert(LA,i,Array1[i-1]);
	for(int i=1;i<=9;i++)ListInsert(LB,i,Array2[i-1]);

	//0-3输出顺序表表元素

	TraverseList(LA);
	TraverseList(LB);
	//1. 计算LA=LA∪LB，并输出结果
	
	Union(LA,LB);
	printf("LA∪LB=");
	TraverseList(LA);

	//2.计算LA=LA ∩LB，并输出结果

	ClearList(LA);
	for(int i=1;i<=7;i++)
		ListInsert(LA,i,Array1[i-1]);
	Intersection(LA,LB);
	printf("LA ∩LB=");
	TraverseList(LA);

	//3.计算LA=LA-LB，并输出结果

	ClearList(LB);
	for(int i=1;i<=7;i++)
		ListInsert(LA,i,Array1[i-1]);
	Difference(LA,LB);
	printf("LA-LB=");
	TraverseList(LA);
	
	//4.有序表合并LC=LA+LB，并输出结果

	ClearList(LB);
	for(int i=1;i<=7;i++)
		ListInsert(LA,i,Array1[i-1]);
	InitList(LC);
	MergeList(LA,LB,LC);
	printf("LA+LB=");
	TraverseList(LC);
	//5.去掉LC重复多余的元素 ，并输出结果

	Purge(LC);
	printf("PurgeLC=");
	TraverseList(LC);
	

	return 1;
}

