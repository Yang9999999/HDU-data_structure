#include<stdio.h>
#include<stdlib.h>
#define SUCCESS 1
#define UNSUCCESS 0
#define ERROR 0
#define OK 1
typedef int KeyType;
typedef int Status;
typedef struct{
	KeyType *key;
	int count;
	int size;
}HashTable;

typedef struct KeyNode{
	KeyType key;
	struct KeyNode *next;
}KeyNode,*KeyLink;

typedef struct{
	KeyLink *elem;
	int count;
	int size;
}HashLink;
int Hash(KeyType key){
	return key % 13;
}
int i,j,k;
Status CreateHashTable(HashTable &HT,int HT_Length,KeyType key[],int KeyNum){
	HT.key=(KeyType *)malloc(HT_Length*sizeof(KeyType));
	HT.count=KeyNum;
	HT.size=HT_Length;
	for(i=0;i<HT.size;i++){
		HT.key[i]=-1;
	}
	for(i=0;i<HT.count;i++){
		k=Hash(key[i]);
		if(HT.key[k]==-1)HT.key[k]=key[i];
		else{
			j=(k+1)%HT_Length;
			while(j!=k&&HT.key[j]!=-1)j=(j+1)%HT_Length;
			if(HT.key[j]==-1)HT.key[j]=key[i];
			else return ERROR;
		}
	}
	return OK;
}

Status SearchHashTable(HashTable HT,KeyType key,int &p,int &c){
	p=Hash(key);
	c=0;
	while(HT.key[p]!=-1&&((p+1)%HT.size)!=Hash(key)&&HT.key[p]!=key){
		c++;
		p=(p+1)%HT.size;
	}
	if(HT.key[p]==key){
		c++;
		return SUCCESS;
	}
	else{
		p=-1;
		return UNSUCCESS;
	} 
}

Status CreateHashLink(HashLink &HL,int HL_Length,KeyType key[],int KeyNum){
	KeyLink s;
	HL.elem=(KeyLink *)malloc(HL_Length*sizeof(KeyLink));
	HL.count=KeyNum;
	HL.size=HL_Length;
	for(i=0;i<HL.size;i++){
		HL.elem[i]=NULL;
	}
	for(i=0;i<HL.count;i++){
		s=(KeyLink)malloc(sizeof(KeyNode));
		s->key=key[i];
		k=Hash(key[i]);
		s->next=HL.elem[k];
		HL.elem[k]=s;
	}
	return OK;
}

Status SearchHashLink(HashLink HL,KeyType key,KeyLink &p,int &c){
	p=HL.elem[Hash(key)];
	c=0;
	while(p&&p->key!=key){
		c++;
		p=p->next;
	}
	if(p){
		c++;
		return SUCCESS;
	}
	else return UNSUCCESS;
}

Status OutHashLink(HashLink HL){
	for(i=0;i<HL.size;i++){
		if(HL.elem[i]!=NULL){
			printf("%d\n",HL.elem[i]->key);
			HL.elem[i]=HL.elem[i]->next;
		}
	}
}

Status OutHashTable(HashTable HL){
	for(i=0;i<HL.size;i++){
		printf("%d\n",HL.key[i]);
	}
}

int main()
{
	int a[12];
	HashTable HT;
	HashLink HL;
	int keys[12]={19,14,23,01,68,20,84,27,55,11,10,79};
	printf("关键字：\n");
	for(i=0;i<12;i++)printf("%d ",keys[i]);
	CreateHashTable(HT,16,keys,12);printf("\n");
	OutHashTable(HT);
	int p;
	int c;
	KeyLink q;
	double sum;
	for(i=0;i<12;i++){
		c=0;
		SearchHashTable(HT,keys[i],p,c);
		sum=c+sum;
		printf("关键字：%d  ",keys[i]);
		printf("下标：%d  ",p);
	    printf("比较次数：%d\n",c); 
	}
	printf("查找成功的ASL：%lf\n",sum/12);
	
	CreateHashLink(HL,13,keys,12);
	OutHashTable(HT);
	
	sum=0;
	for(i=0;i<12;i++){
		c=0;
		SearchHashLink(HL,keys[i],q,c);
		sum=c+sum;
		printf("关键字：%d  ",keys[i]);
	    printf("比较次数：%d\n",c); 
	}
	printf("查找成功的ASL：%lf\n",sum/12);
	
	//线性散列：
	sum=0;
	int key1[13]={26,40,15,29,30,18,32,46,60,74,36,24,38};
	for(i=0;i<13;i++){
		c=0;
		SearchHashTable(HT,key1[i],p,c);
			sum=c+sum;
			printf("关键字：%d  ",key1[i]);
	
	    printf("比较次数：%d\n",c); 
		
	}
	printf("HT查找不成功的ASL：%lf\n",sum/13);
	sum=0;
	for(i=0;i<13;i++){
		c=0;
		SearchHashLink(HL,key1[i],q,c);
			sum=c+sum;
			printf("关键字：%d  ",key1[i]);
	    printf("比较次数：%d\n",c); 
		
	}
	printf("HL查找不成功的ASL：%lf",sum/13);
	
	
	
	
	
	
	return 0;
} 
