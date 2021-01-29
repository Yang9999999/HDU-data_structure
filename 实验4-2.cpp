//ʵ��4-2 ��̬���ҵ�ʵ��
/************************************/
/*     By 19270911 DingYingZhou    */
/************************************/
//Encoding:ANSI
//Preprocessing
#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
typedef int Status;
typedef int Bool;
//1. ��̬���ұ�Ĵ洢�ṹ��������ݵĶ���
typedef int KeyType; //�ؼ��ֵ���������
//����Ԫ�أ���¼�������Ͷ���
typedef struct
{
    KeyType key;  //ѧ��(�ؼ���)
    char name[8]; //����
    char sex[4];  //�Ա�
    int age;      //����
} ElemType;
//��̬���ұ�BST�����Ͷ���
typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild, *rchild; //ָ�����Һ��ӽ���ָ��
} BSTNode, *BSTree;
typedef struct
{
    ElemType *elem; //����Ԫ�ش洢�ռ�Ļ�ַ(һά������)
    int length;     //��ĳ��ȣ�Ԫ�ظ�����
} SSTable;
static ElemType sheet[] = {{56, "Zhang\0", "F\0", 19},
                           {19, "Wang\0", "F\0", 20},
                           {80, "Zhou\0", "F\0", 19},
                           {5, "Huang\0", "M\0", 20},
                           {21, "Zheng\0", "M\0", 20},
                           {64, "Li\0", "M\0", 19},
                           {88, "Liu\0", "F\0", 18},
                           {1, "Qian\0", "F\0", 19},
                           {7, "Sun\0", "M\0", 20},
                           {75, "Zhao\0", "M\0", 20},
                           {92, "Chen\0", "M\0", 20}};
KeyType checkKey[] = {0, 3, 6, 10, 20, 23, 61, 73, 78, 81, 89, 99};
static int n_checkKey = sizeof(checkKey) / sizeof(KeyType);
static int n_sheet = sizeof(sheet) / sizeof(ElemType);
static FILE *instream;// = fopen("IN\\Ex4-2.test", "r");  //stdin;
static FILE *outstream ;//= fopen("OUT\\Ex4-2.out", "w"); //stdout;
static int lookTimes = 0;
//2. ��̬���ұ����������ʵ��
//���ݶ���Ĵ洢�ṹ����д���л�������������C / C++ Դ���룺
//��1����дһ�����뺯��InsertDSTable_BST(BSTree &DT, ElemType e)������BST�����ʽ�����Ԫ��e���뵽��̬���ұ�DT�С���Ԫ��e��DT���Ѵ��ڣ������ʧ�ܣ�����FALSE��
Status CreateSSTable(SSTable &ST, int n)
{
    ST.length = n;
    ElemType *p = (ElemType *)calloc(1 + n, sizeof(ElemType));
    if (!p)
    {
        fprintf(stderr, "�ѷ���ʧ��\n");
        exit(ERROR);
        return ERROR;
    }
    ST.elem = p;
    for (int i = 1; i <= n; i++)
    {
        p[i] = sheet[i - 1];
    }
    return OK;
}
void printElem(ElemType &e)
{
    fprintf(outstream, "  %2d      %5s        %2s          %2d\n", e.key, e.name, e.sex, e.age);
}
void TraversSSTable(SSTable &ST)
{
    fprintf(outstream, "ѧ��key  ����name    �Ա�sex    ����age \n");
    ElemType *outPoint = ST.elem;
    int outNum = ST.length;
    for (int i = 1; i <= outNum; i++)
    {
        printElem(outPoint[i]);
    }
}
Bool InsertDSTable_BST(BSTree &DT, ElemType &e)
{
    if (DT == NULL)
    {
        DT = (BSTree)malloc(sizeof(BSTNode));
        DT->data = e;
        DT->lchild = DT->rchild = NULL;
        return true;
    }
    BSTree *addPlacePoint = NULL;
    BSTree *nowPoint = &DT;
    int standardNum = e.key;
    BSTree tempNodePoint = (BSTree)malloc(sizeof(BSTNode));
    if (!tempNodePoint)
    {
        fprintf(stderr, "�ѷ���ʧ�ܣ�\n");
        exit(0);
    }
    tempNodePoint->data = e;
    tempNodePoint->lchild = tempNodePoint->rchild = NULL;
    while (addPlacePoint == NULL)
    {
        if (*nowPoint == NULL)
        {
            addPlacePoint = nowPoint;
            *addPlacePoint = tempNodePoint;
            break;
        }
        int nowKey = (*nowPoint)->data.key;
        if (nowKey > standardNum)
        {
            nowPoint = &((*nowPoint)->lchild);
        }
        else if (nowKey < standardNum)
        {
            nowPoint = &((*nowPoint)->rchild);
        }
        else
        {
            return false;
        }
    }
    return true;
}
//��2����дһ��������̬���ұ�ĺ���CreateDSTable_BST(BSTree &DT, SSTable &ST)������STΪʵ��4-1�������ľ�̬���ұ��ú���Ҫ����InsertDSTable_BST()������
Status CreateDSTable_BST(BSTree &DT, SSTable &ST)
{
    ElemType *tempSheet = ST.elem;
    int lenSheet = ST.length;
    for (int i = 1; i <= lenSheet; i++)
    {
        if (!InsertDSTable_BST(DT, tempSheet[i]))
            return false;
    }
    return true;
}
//ע��Ϊ��߳�������ٶȣ��ú�������ֱ����ʵ��4-1�������ľ�̬���ұ�ST1�е�����Ԫ�ء�
//��3����дһ�������������TraversDSTable_InOrde(BSTree DT)�������̬���ұ�DT����������Ԫ�ء�
void TraversDSTable_InOrde(BSTree &DT)
{
    if (DT == NULL)
        return;
    TraversDSTable_InOrde(DT->lchild);
    printElem(DT->data);
    TraversDSTable_InOrde(DT->rchild);
    return;
}
//��4����дһ�����Һ��� BSTree SearchDSTable_BST(BSTree DT, KeyType key)�����в���keyΪҪ����Ԫ�صĹؼ��֡������ҳɹ����������ظùؼ���Ԫ�ؽ��ĵ�ַ��ָ�룩�����򣬲��Ҳ��ɹ�������NULL���ú��������õݹ��ǵݹ鷽ʽʵ�֣�ͬʱҪ�������ҹ����йؼ��ֱȽϵĴ�����������ȫ�ֱ���ʵ�֣���
BSTree *SearchDSTable_BST(BSTree &DT, KeyType key)
{
    lookTimes = 0;
    BSTree *nowPoint = &DT;
    while (*nowPoint != NULL)
    {
        int nowKey = (*nowPoint)->data.key;
        lookTimes++;
        if (nowKey > key)
        {
            nowPoint = &((*nowPoint)->lchild);
        }
        else if (nowKey < key)
        {
            nowPoint = &((*nowPoint)->rchild);
        }
        else
        {
            return nowPoint;
        }
    }
    //lookTimes++;
    return NULL;
}
//��5����дһ��ɾ������ DeleteDSTable_BST(BSTree &DT, KeyType key)�����в���keyΪҪɾ��Ԫ�صĹؼ��֣����ùؼ��ֵ�Ԫ����DT�в����ڣ������ʧ�ܣ�����FALSE��
Bool DeleteDSTable_BST(BSTree &DT, KeyType key)
{
    if (DT == NULL)
        return false;
    if (DT->data.key == key && DT->lchild == NULL && DT->rchild == NULL)
    { //ֻ��һ���ڵ��ʱ��
        free(DT);
        DT = NULL;
        return true;
    }
    if (DT->data.key == key && DT->lchild == NULL)
    {
        BSTree tempPoint = DT;
        DT = (DT->rchild);
        free(tempPoint);
        return true;
    }
    if (DT->data.key == key && DT->rchild == NULL)
    {
        BSTree tempPoint = DT;
        DT = (DT->lchild);
        free(tempPoint);
        return true;
    }
    else if (DT->data.key == key)
    {
        BSTree tempPoint = DT;
        BSTree *findPoint = &(DT->lchild);
        while ((*findPoint)->rchild != NULL)
        {
            findPoint = &((*findPoint)->rchild);
        }
        //delPoint=
        (*findPoint)->rchild = DT->rchild;
        DT = (DT->lchild);
        free(tempPoint);
        return true;
    }
    BSTree *delPoint = SearchDSTable_BST(DT, key);
    if (delPoint == NULL)
        return false;
    if ((*delPoint)->lchild == NULL && (*delPoint)->rchild == NULL)
    {
        BSTree *tempPoint = delPoint;
        *delPoint = NULL;
        free(*tempPoint);
        return true;
    }
    if ((*delPoint)->rchild == NULL)
    {
        BSTree *tempPoint = delPoint;
        delPoint = &((*delPoint)->lchild);
        free(*tempPoint);
        return true;
    }
    if ((*delPoint)->lchild == NULL)
    {
        BSTree *tempPoint = delPoint;
        delPoint = &((*delPoint)->rchild);
        free(*tempPoint);
        return true;
    }
    else
    {
        BSTree tempPoint = *delPoint;
        BSTree *findPoint = &((*delPoint)->lchild);
        while ((*findPoint)->rchild != NULL)
        {
            findPoint = &((*findPoint)->rchild);
        }
        //delPoint=
        (*findPoint)->rchild = (*delPoint)->rchild;
        *delPoint = (*delPoint)->lchild;
        free(tempPoint);
        return true;
    }
}
//3. ��дһ��������main()�������������������Ƿ���ȷ��ʵ�����²�����
int main()
{
    BSTree DT = NULL;
    SSTable ST;
    instream = stdin;
    outstream = stdout;
	//instream= fopen("IN\\Ex4-2.test", "r");  //stdin;
	//outstream= fopen("OUT\\Ex4-2.out", "w"); //stdout;
    //��1������һ����̬���ұ�ST1�������и�Ԫ�ص�ֵд��ST1��Ȼ�����ST1�ĸ�Ԫ�ص�ֵ��������Ͷ���Ͳ���������ֱ������ʵ��4-1.
    { //para 1
        fprintf(outstream, "para1:\n");
        CreateSSTable(ST, n_sheet);
        TraversSSTable(ST);
    }
    //��2������һ����̬���ұ�DT1������CreateDSTable_BST(DT1,ST1)���������ݾ�̬���ұ�ST1�е�����Ԫ�ش�����̬���ұ�DT1��Ȼ�����TraversDSTable_InOrder(DT1)�������DT1�еĵ���������Ԫ�ء�
    { //para 2
        fprintf(outstream, "para2:\n");
        CreateDSTable_BST(DT, ST);
        TraversDSTable_InOrde(DT);
    }
    //��3����дһ�δ��룬���������һ���ؼ��֣�����SearchDSTable_BST()���������Ҷ�̬���е�����Ԫ�أ������ҳɹ�������ҵ���Ԫ�أ���¼����ֵ�͹ؼ��ֵıȽϴ����������������ǰҪ���ҵļ�¼�����ڣ����͹ؼ��ֵıȽϴ������öδ�������ظ�����������Σ��ؼ������롰-1��ʱ������
    fprintf(outstream, "para3:\n");
    while (true)
    { //para 3
        int key;
        fprintf(outstream, "������һ��Ҫ���ҵ�key:");
        fscanf(instream, "%d", &key);
        if (outstream != stdout || instream != stdin)
            fprintf(outstream, "%d\n", key);
        if (key == -1)
            break;
        BSTree *temp = SearchDSTable_BST(DT, key);
        if (temp != NULL)
        {
            printElem((*temp)->data);
            fprintf(outstream, "������%d��\n", lookTimes);
        }
        else
        {
            fprintf(outstream, "δ�ҵ���key\n");
        }
    }
    //��4������ʹ�þ�̬���ұ�ST1�еĹؼ��ֵ���SearchDSTable_BST()���������Ҷ�̬���е�����Ԫ�أ����㲢������ҳɹ���ASL��
    { //para 4
        fprintf(outstream, "para4:\n");
        int sumTimes = 0;
        for (int i = 1; i <= ST.length; i++)
        {
            printElem((*SearchDSTable_BST(DT, ST.elem[i].key))->data);
            fprintf(outstream, "�Ƚ���%d��\n", lookTimes);
            sumTimes += lookTimes;
        }
        fprintf(outstream, "���������ҳɹ���ASL=%.4lf\n", sumTimes * 1.0 / ST.length);
    }
    //��5��ѡ��ʹ�ò��ھ�̬���ұ��еĹؼ��ֽ��в��ң����㲢������Ҳ��ɹ���ASL��
    { //para 5
        fprintf(outstream, "para5:\n");
        int sumTimes = 0;
        for (int i = 0; i < n_checkKey; i++)
        {
            SearchDSTable_BST(DT, checkKey[i]);
            fprintf(outstream, "����%d���Ƚ���%d��\n", checkKey[i], lookTimes);
            sumTimes += lookTimes;
        }
        fprintf(outstream, "����������ʧ�ܵ�ASL=%.4lf\n", sumTimes * 1.0 / n_checkKey);
    }
    //��6����дһ�δ��룬ʵ�ֶ�̬���ҵ�Ԫ�ز����������������(scanf)Ҫ����Ԫ��e�ĸ����������ֵ������InsertDSTable_BST(DT1, e)��Ԫ��e���뵽��̬���ұ��У�������ɹ�������TraversDSTable_InOrder(DT1)�������DT1�еĵ���������Ԫ�أ������������ǰҪ����ļ�¼�Ѵ��ڣ���ֹ���룡�����öδ�������ظ�����������Σ��ؼ������롰-1��ʱ������
    fprintf(outstream, "para6:\n");
    while (true)
    { //para 6
        ElemType e;
        fprintf(outstream, "������һ��Ҫ��ӵļ�¼:");
        fscanf(instream, "%d", &e.key);
        if (e.key == -1)
        {
            if (outstream != stdout || instream != stdin)
				fprintf(outstream, "%d\n", e.key);
                break;
        }
        fscanf(instream, "%s%s%d", &e.name, &e.sex, &e.age);
        if (outstream != stdout || instream != stdin)
            printElem(e);
        if (InsertDSTable_BST(DT, e))
            TraversDSTable_InOrde(DT);
        else
            fprintf(outstream, "��ǰҪ����ļ�¼�Ѵ��ڣ���ֹ���룡\n");
    }
    //��7����дһ�δ��룬ʵ�ֶ�̬���ҵ�Ԫ��ɾ����������������Ҫɾ��Ԫ�صĹؼ���ֵ������DeleteDSTable_BST(DT1, key)���ؼ���Ϊkey��Ԫ��e��DT1��ɾ������ɾ���ɹ�������TraversDSTable_InOrder(DT1)�������DT1�еĵ���������Ԫ�أ������������ǰҪɾ���ļ�¼�����ڣ���ֹɾ���������öδ�������ظ�����������Σ��ؼ������롰-1��ʱ������
    fprintf(outstream, "para7:\n");
    while (true)
    { //para 7
        int key;
        fprintf(outstream, "������һ��Ҫɾ����key:");
        fscanf(instream, "%d", &key);
        if (outstream != stdout || instream != stdin)
            fprintf(outstream, "%d\n", key);
        if (key == -1)
            break;
        if (!DeleteDSTable_BST(DT, key))
            fprintf(outstream, "��ǰҪɾ���ļ�¼�����ڣ���ֹɾ����\n");
        else
            TraversDSTable_InOrde(DT);
    }
    return 0;
}
