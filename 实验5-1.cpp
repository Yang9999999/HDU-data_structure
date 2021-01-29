#include<iostream>
#include<cstdio>
#include<string.h>

using namespace std;

#define MAXSIZE 20         //�ļ��м�¼���������ֵ
typedef int  KeyType;          //����ؼ�������Ϊ��������

typedef struct  {
        KeyType  key;             //ѧ�ţ���¼�Ĺؼ��֣�
        char name[11];     //����
        char sex[2];         //�Ա� 
        int  age;                     //���� 
} RecordType;  

typedef struct{
          RecordType  r[MAXSIZE+1];      //r[0]���û��������ڱ�����Ԫ
          int length;                                  //��¼�ĸ���
}RecordTable;     

int ccount = 0;
int mcount = 0;
int key1[11] = {56,19,80,5,21,64,88,13,37,75,92};
char name[11][6] = {"Zhang","Wang","Zhou","Huang","Zheng","Li","Liu","Qian","Sun","Zhao","Chen"};
char sexx[11][2] = {"F","F","F","M","M","M","F","F","M","M","M"};
int ag[11] = {19,20,19,20,20,19,18,19,20,20,20};
RecordTable RT;

void CreateRecordTable(RecordTable &RT)
{
	RT.length = 11;
	for(int i = 1; i <= 11; i++)
	{
		RT.r[i].key = key1[i-1];
		strcpy(RT.r[i].name, name[i-1]);
		strcpy(RT.r[i].sex, sexx[i-1]);
		RT.r[i].age = ag[i-1];
	}
}

void OutRecordTable(RecordTable RT)
{
	printf("Key   ����    �Ա�    ����\n");
	for(int i = 1; i <= RT.length; i++)
	{
		cout << RT.r[i].key << "     " << RT.r[i].name << "     " << RT.r[i].sex << "     " << RT.r[i].age;
		cout << endl;
	} 
}

void InsertSort(RecordTable &RT)
{
	int i,j;
    for (i=2; i<=RT.length; i++) 
	{   
	    RT.r[0] = RT.r[i];              
        for (j = i-1; RT.r[0].key < RT.r[j].key; --j,mcount++) 
        {
        	RT.r[j+1]=RT.r[j];
			ccount++;      
        }
        mcount++;
        if(j<i-1)
		{
			RT.r[j+1] = RT.r[0];           
		} 
    }
}

void ShellSort(RecordTable &RT)
{	
	int d;
	int i,j;
    d=RT.length/2;
    while(d>=1) 
	{
		printf("\n");
		printf("d=%d\n",d);
	   	for(i=d+1; i<=RT.length; i++)  
	    {  
	        RT.r[0]=RT. r[i];      
	        j=i-d;                   
	        while(RT.r[0].key < RT.r[j].key && j>0) 
			{
				mcount++;
				ccount++;
	      		RT.r[j+d]=RT.r[j];     
			    j=j-d;   		 
			    
	        }
	        mcount++;
	        RT.r[j+d]=RT.r[0];     
	 	}
	 	OutRecordTable(RT);
	 	d=d/2;
	 	
	 	
    }
}

int main()
{
	printf("Part 1:\n");
	CreateRecordTable(RT);
	OutRecordTable(RT);
	printf("\n\nPart 2:\n");
	InsertSort(RT);
	OutRecordTable(RT);
	cout << "�Ƚϴ���Ϊ" << mcount << "       ��¼�ƶ�����Ϊ"  <<  ccount << endl; 
	mcount = ccount = 0;
	printf("\n\nPart 3:\n");
	CreateRecordTable(RT);
	ShellSort(RT);
	OutRecordTable(RT);
	cout << "�Ƚϴ���Ϊ" << mcount << "       ��¼�ƶ�����Ϊ"  <<  ccount << endl; 
	
	return 0;
}
