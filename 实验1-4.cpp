#include <stdio.h>
#include <stdlib.h>

#define OK 		1
#define ERROR   0
#define TRUE	1
#define FALSE	0
#define INFEASIBLE 	-1
#define OVERFLOW	-2

typedef int Status;
typedef struct {

      char *ch;       //若是非空串，则按串长分配存储区，否则ch为NULL。

       int  length;   //串长度

} HString;           //堆分配串的类型定义
Status InitString(HString &S){
	S.ch=NULL;
	S.length=0;
	return OK;
}
Status StrAssign(HString &S,const char *chars){
	int n;
	
	const char *c;
	if(S.ch)free(S.ch);
	
	for(n=0,c=chars;*c;++n,++c);
	
	if(n==0){
		S.ch=NULL;
		S.length=0;
	}
	else{
		S.ch=(char*)malloc(n*sizeof(char));
		if(!S.ch)exit(OVERFLOW);
		for(int i=0;i<n;i++)S.ch[i]=chars[i];
		S.length=n;
	}
	return OK;
}

Status Compare(HString S,HString T){
	int i;
	for(i=0;i<S.length&&i<T.length;++i){
		if(S.ch[i]>T.ch[i])return 1;
		else if(S.ch[i]<T.ch[i])return -1;
		
	}
	if(S.length==T.length)return 0;
	else if(S.length>T.length)return 1;
	else return -1;
}

Status StrLength(HString S){
	return S.length;
}

Status Concat(HString &S,HString T1,HString T2){
	if(S.ch)free(S.ch);
	int n=T1.length+T2.length;
	S.ch=(char *)malloc(n*sizeof(char));
	if(!S.ch)exit(OVERFLOW);
	for(int i=0;i<T1.length;i++)S.ch[i]=T1.ch[i];
	for(int i=0;i<T2.length;i++)S.ch[T1.length+i]=T2.ch[i];
	S.length=T1.length+T2.length;
}

Status SubString(HString &Sub,HString S,int pos,int len){
	if(pos<1||pos>S.length||len<0||len>S.length-pos+1)return ERROR;
	if(Sub.ch)free(Sub.ch);
	if(len==0){
		Sub.ch=NULL;
		Sub.length=0;
	}
	else{
		Sub.ch=(char *)malloc(len*sizeof(char));
		if(!Sub.ch)exit(OVERFLOW);
		for(int i=0;i<len;i++)Sub.ch[i]=S.ch[pos+i-1];
		Sub.length=len;
	}
	return OK;
}

Status Traverse(HString S){
	for(int i=0;i<S.length;i++)printf("%c",S.ch[i]);
	printf("\n");
}

Status StrCopy(HString &S,HString T){
	HString T1;
	InitString(T1);
	Concat(S,T,T1);
	return OK;
}



Status Index(HString S,HString T,int pos){
	int i=0,m,n;
	HString sub;
	
	InitString(sub);
	m=StrLength(S);
	n=StrLength(T);
	if(pos<1||pos>m-n+1){
		return 0;
	}
	i=pos;
	while(i<=m-n+1){
		SubString(sub,S,i,n);
		if(Compare(sub,T)==0)return i;
		else ++i;
	}
	
	/*int i=pos-1;
	int j=0;
	while(i<S.length&&j<T.length)
	{
		if(S.ch[i]==T.ch[j])
		{
			i++;
			j++;
		}
		else{
			i=i-j+1;
			j=0;
		}
	}
	if(j==T.length)return i-T.length+1;
	else return 0;*/
}

Status Replace(HString &S,HString T1,HString T2){
	int i,m,n;
	HString S1,S2,sub;
	InitString(S1);
	InitString(S2);
	InitString(sub);
	m=StrLength(S);
	n=StrLength(T1);
	i=1;
	while(i<=m-n+1){
		SubString(sub,S,i,n);
		StrCopy(S1,S2);
		if(Compare(sub,T1)==0){
			Concat(S2,S1,T2);
			i=i+n;
		}
		else{
			SubString(sub,S,i,1);
			Concat(S2,S1,sub);
			i++;
		}
	}
	SubString(sub,S,i,n-1);
	Concat(S1,S2,sub);
	StrCopy(S,S1);
	return OK; 
}


Status Insert(HString &S,int pos,HString T){
	int i=0,m;
	HString S1,S2,sub;
	InitString(S1);
	InitString(S2);
	
	InitString(sub);
	m=StrLength(S); 
	if(pos==(m+1))Concat(S1,S,T);
	else if(pos==1)Concat(S1,T,S);
	else{
		SubString(sub,S,1,pos-1);
		StrCopy(S1,sub);
		Concat(S2,S1,T);
		SubString(sub,S,pos,m-pos+1);
		Concat(S1,S2,sub);
		
		
	}
	StrCopy(S,S1); 
	return OK;
} 


int main()
{
	int pos,Strlength;
	HString T1,T2,T3,S;
	InitString(T1);
	InitString(T2);
	InitString(T3);
	
	char a[]="abc";
	char b[]="def";
	char c[]="ghi";
	printf("T1串为abc  T2串为def   T3串为ghi\n");
	StrAssign(T1,a);
	StrAssign(T2,b);
	StrAssign(T3,c);
	printf("T1=");
	Traverse(T1);
	printf("\nT2=");
	Traverse(T2);
	printf("\nT3=");
	Traverse(T3);
	printf("\n将T1赋给串S，S的值为S=");
	StrCopy(S,T1);
	Traverse(S);

	printf("\n将T2插入到S的尾部 S的值为S=");
	Strlength=StrLength(S);
	Insert(S,Strlength+1,T2);
	
	Traverse(S);
	
	
	
	printf("\n将S中的T1换成T3 S的值为S=");
	Replace(S,T1,T3);

	Traverse(S);
	 
	
	printf("\nT2在S中的位置为"); 
	pos=Index(S,T2,1);
	printf("%d\n",pos);
	
	printf("\n删除S中的字串T2，S的值为S=");
	Traverse(T3); 
	
	
	return 0;
}
