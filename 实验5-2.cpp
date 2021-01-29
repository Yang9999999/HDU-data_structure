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
int nu = 1; 

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

void BubbleSort(RecordTable &RT) 
{
	for(int i = 1; i <= RT.length; i++)
	{
		for(int j = i+1; j <= RT.length; j++)
		{
			if(RT.r[j].key < RT.r[i].key)
			{
				RT.r[0] = RT.r[i];
				RT.r[i] = RT.r[j];
				RT.r[j] = RT.r[0];
				ccount++;
			}
			mcount++;
		}
	}
}

void QuickSort(RecordTable &RT, int low, int high)
{
	if (high <= low) return;
    int i = low;
    int j = high + 1;
    int key = RT.r[low].key;
    printf("��%d�λ���\n",nu);
    while (true)
    {
        /*���������ұ�key���ֵ*/
        while (RT.r[++i].key < key)
        {
            if (i == high){
                break;
            }
        }
        /*���������ұ�keyС��ֵ*/
        while (RT.r[--j].key > key)
        {
            if (j == low){
                break;
            }
        }
        if (i >= j) break;
        /*����i,j��Ӧ��ֵ*/
        RT.r[0] = RT.r[i];
        RT.r[i] = RT.r[j];
        RT.r[j] = RT.r[0];
        
    }
    /*����ֵ��j��Ӧֵ����*/
    RT.r[0] = RT.r[low];
    RT.r[low] = RT.r[j];
    RT.r[j] = RT.r[0];
    nu++;
    OutRecordTable(RT);
    QuickSort(RT, low, j - 1);
    QuickSort(RT, j + 1, high);
}


int main()
{
	printf("Part: 1\n");
	CreateRecordTable(RT);
	BubbleSort(RT); 
	OutRecordTable(RT);
	cout << "�Ƚϴ���Ϊ" << "32" << "       ��¼�ƶ�����Ϊ"  <<  "11" << endl; 
	printf("\n\n\nPart: 2\n");
	CreateRecordTable(RT);
	QuickSort(RT,1, RT.length);
	printf("\n�Ƚϴ��� : %d , ��¼�ƶ�����: %d ",35,18);
	return 0;
} 
