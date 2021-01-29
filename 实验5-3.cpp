#include<stdio.h>
#define MAXSIZE 20
#define OK 1
#define ERROR 0
typedef int KeyType;
typedef int Status;
typedef struct{
	KeyType key;
	const char *name;
	const char *sex;
	int age;
}RecordType;
typedef struct{
	RecordType r[MAXSIZE+1];
	int length;
}RecordTable;
int i,j,k;
	int t1;
	const char *t2;
	const char *t3;
	int t4;

Status CreateRecordTable(RecordTable &RT){
	int keys[]={56,19,80,5,21,64,88,13,37,75,92};
	const char *names[]={"Zhang","Wang","Zhou","Huang","Zheng","Li","Liu","Qian","Sun","Zhao","Chen"};
	const char *sexs[]={"F","F","F","F","M","M","M","M","M","M","M"};
	int ages[]={19,18,19,18,19,20,20,19,18,19,18};
	int i,n=11;
	for(i=1;i<=n;i++){
		RT.r[i].key=keys[i-1];
		RT.r[i].name=names[i-1];
		RT.r[i].sex=sexs[i-1];
		RT.r[i].age=ages[i-1];
	}
	RT.length=n;
	return OK;
}

Status OutRecordTable(RecordTable RT){
	printf("\n");
	for(i=1;i<=RT.length;i++){
		printf(" %2d ",RT.r[i].key);
		printf("%5s   ",RT.r[i].name);
		printf("%1s   ",RT.r[i].sex);
		printf("%2d\n",RT.r[i].age);
	}
}
int mcount=0;
int ccount=0;
int mcount1=0;
int ccount1=0;

Status SelectSort(RecordTable &RT){
	for(i=0;i<RT.length-1;i++){
		int min=i;
		for(j=i+1;j<RT.length;j++){
			if(RT.r[j].key<RT.r[min].key)
			{
				min=j;
				ccount++;
			} 
			t1=RT.r[min].key;
			t2=RT.r[min].name;
			t3=RT.r[min].sex;
			t4=RT.r[min].age;
			RT.r[min].key=RT.r[i].key;
			RT.r[min].name=RT.r[i].name;
			RT.r[min].sex=RT.r[i].sex;
			RT.r[min].age=RT.r[i].age;
			RT.r[i].key=t1;
			RT.r[i].name=t2;
			RT.r[i].sex=t3;
			RT.r[i].age=t4;
			mcount++;
		}
	}
}
Status HeapAdjust(RecordTable &H,int i,int m){
	H.r[0]=H.r[i];//保存H.r[i]
	for(j=2*i;j<=m;j*=2){
		if(j<m&&H.r[j].key<H.r[j+1].key){
			j++;
			ccount1++;
		}
		if(H.r[0].key>=H.r[j].key)break;
		H.r[i]=H.r[j];
		i=j;
	} 
	if(H.r[i].key!=H.r[0].key) H.r[i]=H.r[0];
	return OK;
}

Status HeapSort(RecordTable &RT){
	for(i=RT.length/2;i>0;i--){
		HeapAdjust(RT,i,RT.length);
	}
	for(i=RT.length;i>1;i--){
		t1=RT.r[1].key;
		t2=RT.r[1].name;
		t3=RT.r[1].sex;
		t4=RT.r[1].age;
		RT.r[1].key=RT.r[i].key;
		RT.r[1].name=RT.r[i].name;
		RT.r[1].sex=RT.r[i].sex;
		RT.r[1].age=RT.r[i].age;
		RT.r[i].key=t1;
		RT.r[i].name=t2;
		RT.r[i].sex=t3;
		RT.r[i].age=t4;
		mcount1++;
		HeapAdjust(RT,1,i-1);
	}
	return OK;
}
int main(){
	RecordTable RT1;
	
	CreateRecordTable(RT1);
	
	OutRecordTable(RT1);
	SelectSort(RT1);
	OutRecordTable(RT1);
	printf("关键字比较次数：%d",ccount);
	printf("记录移动次数:%d",mcount);
	CreateRecordTable(RT1);
	HeapSort(RT1);
	OutRecordTable(RT1);
	printf("关键字比较次数：%d",ccount1);
	printf("记录移动次数:%d",mcount1);
} 
