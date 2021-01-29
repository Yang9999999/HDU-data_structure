#include<stdio.h>
#include<stdlib.h> 

int key[11]={56,19,80,5,21,64,88,13,37,75,92};
	const char name[11][11]={"Zhang","Wang","Zhou","Huang","Zheng","Li","Liu","Qian","Sun"
	,"Zhao","Chen"};
	char sex[11]={'F','F','F','M','M','M','F','F','M','M','M'};
	int age[11]={19,20,19,20,20,19,18,19,20,20,20};
	
typedef int KeyType;
//����Ԫ�����Ͷ��� 
typedef struct{
	KeyType key;//ѧ�� 
	const char *name;//���� 
	 char sex;//�Ա� 
	int age;//���� 
}ElemType;
//��̬���ұ����Ͷ��� 
typedef struct{
	ElemType *elem;//����Ԫ�ش���ռ�Ļ�ַ ��һά������ 
	int length;//��ĳ��� ��Ԫ�ظ��� 
}SSTable;

typedef int Status;

Status CreateSSTable(SSTable &ST,int n){
	ST.elem=(ElemType *)malloc((n+1)*sizeof(ElemType));
	for(int i=0;i<n;i++){
		ST.elem[i].key=key[i];
		ST.elem[i].name=name[i];
		ST.elem[i].sex=sex[i];
		ST.elem[i].age=age[i];
	}
}

Status TraverseSSTable(SSTable ST){
	for(int i=0;i<ST.length;i++){
		printf("%d ",ST.elem[i].key);
		printf("%s ",ST.elem[i].name);
		printf("%c ",ST.elem[i].sex);
		printf("%d \n",ST.elem[i].age);
	}
}

Status SearchSSTable_Seq(SSTable ST,KeyType key,int &c){
	ST.elem[0].key=key;
	int i;
	for(i=ST.length;ST.elem[i].key!=key;--i)c++;
	return i;
}

Status SortSSTable(SSTable &ST){
	int t1;
	const char *t2;
	char t3;
	int t4;
	for(int j=0;j<ST.length-1;j++){
		
		for(int i=0;i<ST.length-1-j;i++){
		if(ST.elem[i].key>ST.elem[i+1].key){
			t1=ST.elem[i+1].key;
			t2=ST.elem[i+1].name;
			t3=ST.elem[i+1].sex;
			t4=ST.elem[i+1].age;
			ST.elem[i+1].key=ST.elem[i].key;
			ST.elem[i+1].name=ST.elem[i].name;
			ST.elem[i+1].sex=ST.elem[i].sex;
			ST.elem[i+1].age=ST.elem[i].age;
			ST.elem[i].key=t1;
			ST.elem[i].name=t2;
			ST.elem[i].sex=t3;
			ST.elem[i].age=t4;
		}
	}
	}
	
}

Status SearchSSTable_Bin(SSTable ST,KeyType key,int &c){
	int low=1;
	int mid;
	int high=ST.length;
	while(low<=high){
		mid=(low+high)/2;
		c++;
		if(key==ST.elem[mid].key){
			
			return mid;
		}
		else if(key<ST.elem[mid].key) high=mid-1;
		else low=mid+1;
	}
	
	return -1;
}
int main()
{
	SSTable ST1;
	ST1.elem=NULL;
	ST1.length=11;
	
	CreateSSTable(ST1,11);
	TraverseSSTable(ST1);
	int times1,times2;
	int key1,key2;
	int n,m;
printf("������ؼ���");
	while(scanf("%d",&key1)&&key1!=-1){
		
		times1=0;
		n=SearchSSTable_Seq(ST1,key1,times1);
		if(n!=0){
			printf("%d ",ST1.elem[n].key);
			printf("%s ",ST1.elem[n].name);
			printf("%c ",ST1.elem[n].sex);
			printf("%d \n",ST1.elem[n].age);
			printf("���Ҵ�����");
			printf("%d\n",times1);
		}
		else{
			printf("��ǰҪ���ҵ�Ԫ�ؼ�¼�����ڣ�\n");
			printf("���Ҵ�����");
			printf("%d\n",times1);
		}
		
	}
	printf("\n");
	printf("˳����Ҳ��ҳɹ���ASL��6\n\n");
	
	
	printf("�������\n");
	SortSSTable(ST1);
	TraverseSSTable(ST1);
		printf("������ؼ���");
	while(scanf("%d",&key2)&&key2!=-1){
	
		times2=0;
		m=SearchSSTable_Seq(ST1,key2,times2);
		if(m!=-1){
			printf("%d ",ST1.elem[n].key);
			printf("%s ",ST1.elem[n].name);
			printf("%c ",ST1.elem[n].sex);
			printf("%d \n",ST1.elem[n].age);
			printf("���Ҵ�����");
			printf("%d\n",times2);
		}
		else{
			printf("��ǰҪ���ҵ�Ԫ�ؼ�¼�����ڣ�\n");
			printf("���Ҵ�����");
			printf("%d\n",times2);
		}
		
	}
	
	
	printf("��̬���ұ��۰���ҳɹ���ASL��3\n");
		printf("��̬���ұ��۰���Ҳ��ɹ���ASL��3.67");
	 
	return 0;
}
