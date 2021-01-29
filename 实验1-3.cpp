#include <stdio.h>
#include <stdlib.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2
#define STACK_INIT_SIZE    10

#define STACKINCREMENT  5

#define OVERFLOW	-2
#define MAXQSIZE 10    //���е���󳤶�


typedef int SElemType;  //����SElemType������

typedef int Status;         //��������������


typedef struct  { 

        SElemType *base;  //˳��ջ���ݴ洢�ռ��ַ 

        SElemType *top;    //˳��ջջ��ָ�� 

        int stacksize;

}SqStack;  // SqStackΪ�û������˳��ջ����

Status InitStack(SqStack &S){
	S.base=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	S.top=S.base;
	S.stacksize=STACK_INIT_SIZE;
	
	
}

Status ClearStack(SqStack &S){
	S.top=S.base;
}

Status StackLength(SqStack S){
	return S.top-S.base;
}

Status GetTop(SqStack S,SElemType &e){
	if(S.top==S.base) return ERROR;
	e=*(S.top-1);
}

Status Push(SqStack &S,SElemType e){
	if(S.top-S.base>=S.stacksize){
		S.base=(SElemType *)realloc(S.base,(S.stacksize+STACKINCREMENT)*sizeof(SElemType));
		S.top=S.base+S.stacksize;
	}
	*S.top++=e;
}

Status Pop(SqStack &S,SElemType &e){
	if(S.top==S.base)return ERROR;
	e=*--S.top;
}
Status StackEmpty(SqStack S){
	if(S.top==S.base)return 1;
	else return 0;
}

Status Conversion(){
	SqStack S;
	int n;
	SElemType e;
	InitStack(S);
	printf("������һ��ʮ��������"); 
	scanf("%d",&n);
	while(n){
		Push(S,n%8);
		n=n/8;
	}
	printf("ת��Ϊ�˽��ƣ�");
	while(!(S.top==S.base)){
		Pop(S,e);
		
		printf("%d",e);
	}
}

typedef int QElemType;  //����SElemType������

typedef int Status;          //��������������


typedef struct {

       QElemType *base;    //��ʼ������ʱ��̬����洢�ռ�ĵ�ַ(������)

       int front;                 //ͷԪ�ص��±����

       int rear;                   //βԪ�ص��±����

} SqQueue;   // SqQueueΪ�û������ѭ����������

Status InitQueue(SqQueue &Q){
	Q.base=(QElemType *)malloc(MAXQSIZE*sizeof(QElemType));
	if(!Q.base)exit(OVERFLOW);
	Q.front=Q.rear=0; 
}

Status ClearQueue(SqQueue &Q){
	Q.front=Q.rear=0;
}

Status QueueLength(SqQueue Q){
	return Q.rear-Q.front;
}

Status EnQueue(SqQueue &Q,QElemType e){
	if((Q.rear+1)%MAXQSIZE==Q.front)return ERROR;
	Q.base[Q.rear]=e;
	Q.rear=(Q.rear+1)%MAXQSIZE;
	
}

Status DeQueue(SqQueue &Q,QElemType &e){
	if(Q.front==Q.rear) return ERROR;
	e=Q.base[Q.front];
	Q.front=(Q.front+1)%MAXQSIZE;
}
Status QueueEmpty(SqQueue Q){
	if(Q.rear==Q.front)return 1;
	else return 0;
}
Status QueueReverse(SqQueue &Q){
	SqStack S;int d;
	InitStack(S);
	while (!QueueEmpty(Q)) {

    DeQueue(Q,d);  Push(S,d);

    }

    while (! StackEmpty(S)) {

    Pop(S,d); EnQueue(Q,d);
	printf("%d ",d);
    }
}

int main()
{
	Conversion();
	
	SqQueue Q;
	InitQueue(Q);
	int e;
	QElemType Array1[]={1,2,3,4,5,6,7,8,9};
	for(int k=1;k<=9;k++)EnQueue(Q,Array1[k-1]);
	printf("\n<1>��9�����ֱַ�Ϊ1  2  3  4  5  6  7  8  9  \n");
	printf("");
	printf("front��ֵΪ");
	printf("%d\n",Q.base[Q.front]);
	printf("rear��ֵΪ");
	printf("%d\n",Q.base[Q.rear-1]);
	
	printf("<2>����ӵ�����Ϊ10\n");
	printf("%d\n",EnQueue(Q,10));
	printf("ѭ���������������ܲ��롣\n");
	
	printf("<3>����5����������ӵ�2��������11 12\n"); 
	for(int i = 0;i<5;i++){
		DeQueue(Q,e);
	}

	EnQueue(Q,11);
	EnQueue(Q,12);
	printf("front��ֵΪ");
	printf("%d\n",Q.base[Q.front]);
	printf("rear��ֵΪ");
	printf("%d\n",Q.base[Q.rear-1]);
	
	printf("<4>������Ԫ���������Ų����\n");
	QueueReverse(Q);
	
	
}
