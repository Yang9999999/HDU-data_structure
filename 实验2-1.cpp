#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define OK 1
#define ERROR 0
#define TRUE 1
#define FLASE 0
#define INFEASIBLE -1
#define OVERFLOW -2

typedef int Status;
	int flag=0;

typedef unsigned char TElemType;

typedef struct BiTNode{
	TElemType data;
	struct BiTNode *lchild,*rchild;
}BiTNode,*BiTree;

int n=0;
int m=0;

char chars[30]={'A','B','D',' ','F',' ',' ',' ','C','E',' ',' ',' '};
int front=0;

Status CreateBiTree(BiTree &T){
	char ch;
	ch=chars[front++];
	if(ch==' ') T=NULL;
	else{
		T=(BiTree)malloc(sizeof(BiTNode));
		T->data=ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return OK;
}

Status PreOrderTraverse(BiTree T){
	if(T!=NULL){
		printf("%c",T->data);
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	
	}

	return OK;
}

Status InOrderTraverse(BiTree T){
	if(T!=NULL){
		InOrderTraverse(T->lchild);
		printf("%c",T->data);
		InOrderTraverse(T->rchild);
	}

	return OK;
}

Status PostOrderTraverse(BiTree T){
	if(T!=NULL){
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		printf("%c",T->data);
	}
	
}
Status PrintElement(TElemType e){
	printf("%c",e);
	return OK;
}


Status NRPreOrderTraverse(BiTree T){
	BiTree stack[100]={0},p;
	int top;
	top=0;p=T;
	printf("\n");
	while(p||top>0){
		while(p){
		printf("%c",p->data);
		printf("\n");
		stack[top++]=p;
		printf("元素入栈，栈内元素<");
		for(int i=0;i<top;i++){
			printf("%c",stack[i]->data);
		}
		printf(">\n");
		p=p->lchild;
		}
		if(top>0){
		p=stack[--top];
		printf("元素出栈，栈内元素<");
		for(int i=0;i<top;i++){
			printf("%c",stack[i]->data);
		}
		printf(">\n");
		p=p->rchild;
	}
	}
	
	return OK;
}

Status NRInOrderTraverse(BiTree T){
	BiTree stack[100],p;
	int top;
	top=0;p=T;
	printf("\n");
	while(p||top>0){
		while(p){
			stack[top++]=p;
			printf("元素入栈，栈内元素<");
			for(int i=0;i<top;i++){
			printf("%c",stack[i]->data);
			}
		printf(">\n");
			p=p->lchild;
		}
		if(top>0){
			p=stack[--top];
				printf("元素出栈，栈内元素<");
		for(int i=0;i<top;i++){
			printf("%c",stack[i]->data);
		}
		printf(">\n");
			printf("%c",p->data);
			printf("\n");
			p=p->rchild;
		}
	}
	return OK;
}
Status NRPostOrderTraverse(BiTree T){
	BiTree stack[100],p,pre;
	int top;printf("\n");
	top=0;p=T;
	while(p||top>0){
		while(p){
			stack[top++]=p;
			printf("元素入栈，栈内元素<");
			for(int i=0;i<top;i++){
			printf("%c",stack[i]->data);
			}
		printf(">\n");
			
			
			p=p->lchild;
		}
		if(top>0){
			p=stack[top-1];
			printf("元素出栈，栈内元素<");
		for(int i=0;i<top;i++){
			printf("%c",stack[i]->data);
		}
		printf(">\n");
		
			if(!p->rchild||p->rchild==pre){
				printf("%c",p->data);top--;printf("\n");
				pre=p;p=NULL; 
			}
			else p=p->rchild;
		}
	}
}

Status TNodes(BiTree T,int d){

	if(T!=NULL){
		if(d==0){
			if(T->lchild==NULL&&T->rchild==NULL)flag++;
		}
		if(d==1){
			if(T->lchild==NULL&&T->rchild!=NULL)flag++;
			if(T->rchild==NULL&&T->lchild!=NULL)flag++;
		}
		if(d==2){
			if(T->lchild!=NULL&&T->rchild==NULL)flag++;
		}
		
		TNodes(T->lchild,d);
		TNodes(T->rchild,d);
	
	}
	
	return flag;
}

Status High(BiTree T){
	int h1;
	int h2;
	if(!T)
		return 0;
		else{
		h1 = High(T->lchild);
		h2 = High(T->rchild);
		return h1>h2?++h1:++h2;
	}
}

Status CreateBST(BiTree &T,const char ch)
{
	if(T==NULL){
		T=(BiTree)malloc(sizeof(BiTNode));
		T->data=ch;
		T->lchild=NULL;
		T->rchild=NULL;
	}
	if(T!=NULL){
		if(ch>T->data){
			CreateBST(T->rchild,ch);
		}
		else if(ch<T->data){
			CreateBST(T->lchild,ch);
		}
	}
	return OK;
}
void CreateBSTree(BiTree &T,const char *chars){
	for(int i=0;chars[i]!=NULL;i++)CreateBST(T,chars[i]);
}

int main(){
	BiTree T,T1,T2;
	T1=NULL;
	T2=NULL;
	CreateBiTree(T);

	printf("先序遍历：");PreOrderTraverse(T);	printf("\n");
	printf("中序遍历：");InOrderTraverse(T);	printf("\n");
	printf("后序遍历：");PostOrderTraverse(T);	printf("\n");
	printf("先序遍历：");NRPreOrderTraverse(T);	printf("\n");
	printf("中序遍历：");NRInOrderTraverse(T);	printf("\n");
	printf("后序遍历：");NRPostOrderTraverse(T);	printf("\n");
	printf("结点为0的节点数");
	printf("%d\n",TNodes(T,0));
	flag=0;
	printf("结点为1的节点数");
	printf("%d\n",TNodes(T,1));
	flag=0;
	printf("结点为2的节点数");
	printf("%d\n",TNodes(T,2));
	printf("T1中序遍历："); 
	CreateBSTree(T1,"DBFCAEG");
	InOrderTraverse(T1);
	printf("\nT1高度：");
	printf("%d",High(T1));
	printf("\nT2中序遍历："); 
	CreateBSTree(T2,"ABCDEFG");
	InOrderTraverse(T2);
	printf("\nT2高度：");
	printf("%d",High(T2));
	
	
}
