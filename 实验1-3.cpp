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
#define MAXQSIZE 10    //队列的最大长度


typedef int SElemType;  //声明SElemType的类型

typedef int Status;         //声明函数类型名


typedef struct  { 

        SElemType *base;  //顺序栈数据存储空间基址 

        SElemType *top;    //顺序栈栈顶指针 

        int stacksize;

}SqStack;  // SqStack为用户定义的顺序栈类型

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
	printf("请输入一个十进制数："); 
	scanf("%d",&n);
	while(n){
		Push(S,n%8);
		n=n/8;
	}
	printf("转换为八进制：");
	while(!(S.top==S.base)){
		Pop(S,e);
		
		printf("%d",e);
	}
}

typedef int QElemType;  //声明SElemType的类型

typedef int Status;          //声明函数类型名


typedef struct {

       QElemType *base;    //初始化队列时动态分配存储空间的地址(数组名)

       int front;                 //头元素的下标变量

       int rear;                   //尾元素的下标变量

} SqQueue;   // SqQueue为用户定义的循环队列类型

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
	printf("\n<1>设9个数字分别为1  2  3  4  5  6  7  8  9  \n");
	printf("");
	printf("front的值为");
	printf("%d\n",Q.base[Q.front]);
	printf("rear的值为");
	printf("%d\n",Q.base[Q.rear-1]);
	
	printf("<2>设入队的数字为10\n");
	printf("%d\n",EnQueue(Q,10));
	printf("循环队列已满，不能插入。\n");
	
	printf("<3>出队5个整数，入队的2个整数是11 12\n"); 
	for(int i = 0;i<5;i++){
		DeQueue(Q,e);
	}

	EnQueue(Q,11);
	EnQueue(Q,12);
	printf("front的值为");
	printf("%d\n",Q.base[Q.front]);
	printf("rear的值为");
	printf("%d\n",Q.base[Q.rear-1]);
	
	printf("<4>将队列元素逆序重排并输出\n");
	QueueReverse(Q);
	
	
}
