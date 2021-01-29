//实验4-2 动态查找的实现
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
//1. 动态查找表的存储结构和相关内容的定义
typedef int KeyType; //关键字的数据类型
//数据元素（记录）的类型定义
typedef struct
{
    KeyType key;  //学号(关键字)
    char name[8]; //姓名
    char sex[4];  //性别
    int age;      //年龄
} ElemType;
//动态查找表BST的类型定义
typedef struct BSTNode
{
    ElemType data;
    struct BSTNode *lchild, *rchild; //指向左右孩子结点的指针
} BSTNode, *BSTree;
typedef struct
{
    ElemType *elem; //数据元素存储空间的基址(一维数组名)
    int length;     //表的长度（元素个数）
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
//2. 动态查找表基本操作的实现
//根据定义的存储结构，编写下列基本操作函数的C / C++ 源代码：
//（1）编写一个插入函数InsertDSTable_BST(BSTree &DT, ElemType e)，根据BST的性质将数据元素e插入到动态查找表DT中。若元素e在DT中已存在，则操作失败，返回FALSE。
Status CreateSSTable(SSTable &ST, int n)
{
    ST.length = n;
    ElemType *p = (ElemType *)calloc(1 + n, sizeof(ElemType));
    if (!p)
    {
        fprintf(stderr, "堆分配失败\n");
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
    fprintf(outstream, "学号key  姓名name    性别sex    年龄age \n");
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
        fprintf(stderr, "堆分配失败！\n");
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
//（2）编写一个创建动态查找表的函数CreateDSTable_BST(BSTree &DT, SSTable &ST)，其中ST为实验4-1所创建的静态查找表。该函数要调用InsertDSTable_BST()函数。
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
//注：为提高程序调试速度，该函数允许直接用实验4-1所创建的静态查找表ST1中的数据元素。
//（3）编写一个中序遍历函数TraversDSTable_InOrde(BSTree DT)，输出动态查找表DT的所有数据元素。
void TraversDSTable_InOrde(BSTree &DT)
{
    if (DT == NULL)
        return;
    TraversDSTable_InOrde(DT->lchild);
    printElem(DT->data);
    TraversDSTable_InOrde(DT->rchild);
    return;
}
//（4）编写一个查找函数 BSTree SearchDSTable_BST(BSTree DT, KeyType key)，其中参数key为要查找元素的关键字。若查找成功，函数返回该关键字元素结点的地址（指针），否则，查找不成功，返回NULL。该函数可以用递归或非递归方式实现，同时要计数查找过程中关键字比较的次数（可利用全局变量实现）。
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
//（5）编写一个删除函数 DeleteDSTable_BST(BSTree &DT, KeyType key)，其中参数key为要删除元素的关键字，若该关键字的元素在DT中不存在，则操作失败，返回FALSE。
Bool DeleteDSTable_BST(BSTree &DT, KeyType key)
{
    if (DT == NULL)
        return false;
    if (DT->data.key == key && DT->lchild == NULL && DT->rchild == NULL)
    { //只有一个节点的时候
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
//3. 编写一个主函数main()，检验上述操作函数是否正确，实现以下操作：
int main()
{
    BSTree DT = NULL;
    SSTable ST;
    instream = stdin;
    outstream = stdout;
	//instream= fopen("IN\\Ex4-2.test", "r");  //stdin;
	//outstream= fopen("OUT\\Ex4-2.out", "w"); //stdout;
    //（1）定义一个静态查找表ST1，将下列各元素的值写入ST1，然后输出ST1的各元素的值。相关类型定义和操作函数可直接利用实验4-1.
    { //para 1
        fprintf(outstream, "para1:\n");
        CreateSSTable(ST, n_sheet);
        TraversSSTable(ST);
    }
    //（2）定义一个动态查找表DT1，调用CreateDSTable_BST(DT1,ST1)函数，根据静态查找表ST1中的数据元素创建动态查找表DT1，然后调用TraversDSTable_InOrder(DT1)函数输出DT1中的的所有数据元素。
    { //para 2
        fprintf(outstream, "para2:\n");
        CreateDSTable_BST(DT, ST);
        TraversDSTable_InOrde(DT);
    }
    //（3）编写一段代码，根据输入的一个关键字，调用SearchDSTable_BST()函数，查找动态表中的数据元素，若查找成功，输出找到的元素（记录）的值和关键字的比较次数，否则输出“当前要查找的记录不存在！”和关键字的比较次数。该段代码可以重复上述操作多次，关键字输入“-1”时结束。
    fprintf(outstream, "para3:\n");
    while (true)
    { //para 3
        int key;
        fprintf(outstream, "请输入一个要查找的key:");
        fscanf(instream, "%d", &key);
        if (outstream != stdout || instream != stdin)
            fprintf(outstream, "%d\n", key);
        if (key == -1)
            break;
        BSTree *temp = SearchDSTable_BST(DT, key);
        if (temp != NULL)
        {
            printElem((*temp)->data);
            fprintf(outstream, "查找了%d次\n", lookTimes);
        }
        else
        {
            fprintf(outstream, "未找到该key\n");
        }
    }
    //（4）依次使用静态查找表ST1中的关键字调用SearchDSTable_BST()函数，查找动态表中的数据元素，计算并输出查找成功的ASL。
    { //para 4
        fprintf(outstream, "para4:\n");
        int sumTimes = 0;
        for (int i = 1; i <= ST.length; i++)
        {
            printElem((*SearchDSTable_BST(DT, ST.elem[i].key))->data);
            fprintf(outstream, "比较了%d次\n", lookTimes);
            sumTimes += lookTimes;
        }
        fprintf(outstream, "二叉树查找成功的ASL=%.4lf\n", sumTimes * 1.0 / ST.length);
    }
    //（5）选择使用不在静态查找表中的关键字进行查找，计算并输出查找不成功的ASL。
    { //para 5
        fprintf(outstream, "para5:\n");
        int sumTimes = 0;
        for (int i = 0; i < n_checkKey; i++)
        {
            SearchDSTable_BST(DT, checkKey[i]);
            fprintf(outstream, "查找%d，比较了%d次\n", checkKey[i], lookTimes);
            sumTimes += lookTimes;
        }
        fprintf(outstream, "二叉树查找失败的ASL=%.4lf\n", sumTimes * 1.0 / n_checkKey);
    }
    //（6）编写一段代码，实现动态查找的元素插入操作。首先输入(scanf)要插入元素e的各个数据项的值，调用InsertDSTable_BST(DT1, e)将元素e插入到动态查找表中，若插入成功，调用TraversDSTable_InOrder(DT1)函数输出DT1中的的所有数据元素，否则输出“当前要插入的记录已存在，禁止插入！”。该段代码可以重复上述操作多次，关键字输入“-1”时结束。
    fprintf(outstream, "para6:\n");
    while (true)
    { //para 6
        ElemType e;
        fprintf(outstream, "请输入一条要添加的记录:");
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
            fprintf(outstream, "当前要插入的记录已存在，禁止插入！\n");
    }
    //（7）编写一段代码，实现动态查找的元素删除操作。首先输入要删除元素的关键字值，调用DeleteDSTable_BST(DT1, key)将关键字为key的元素e从DT1中删除，若删除成功，调用TraversDSTable_InOrder(DT1)函数输出DT1中的的所有数据元素，否则输出“当前要删除的记录不存在，禁止删除！”。该段代码可以重复上述操作多次，关键字输入“-1”时结束。
    fprintf(outstream, "para7:\n");
    while (true)
    { //para 7
        int key;
        fprintf(outstream, "请输入一个要删除的key:");
        fscanf(instream, "%d", &key);
        if (outstream != stdout || instream != stdin)
            fprintf(outstream, "%d\n", key);
        if (key == -1)
            break;
        if (!DeleteDSTable_BST(DT, key))
            fprintf(outstream, "当前要删除的记录不存在，禁止删除！\n");
        else
            TraversDSTable_InOrde(DT);
    }
    return 0;
}
