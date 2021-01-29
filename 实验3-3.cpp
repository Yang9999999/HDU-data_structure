#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTEX_NUM 20
#define MAX_VERTEX_NUM  20//最大顶点数
#define OK 1
#define TRUE 1
#define FALSE 0

typedef int Status;

typedef enum {DG,DN,UDG,UDN} GraphKind;  //图的类型

typedef char VertexType; //顶点数据的类型(字符） 

//边(弧)结点数据类型 

typedef struct ArcNode {

       int                       adjvex ;       //该边(弧)所依附(指向)的顶点在顶点数组的下标

       struct ArcNode *nextarc;       //指向下一条边(弧)的指针

       int                       weight;        //边(弧)的权值，无权图其值为0

}ArcNode;


//顶点数组数据类型 

typedef struct VNode {

       VertexType  data;          //顶点数据 

       ArcNode  *firstarc;         //指向第一条依附该顶点的边(弧)的指针

}VNode, AdjList[MAX_VERTEX_NUM];


//图的邻接表数据类型 

typedef  struct {

       AdjList   vertices;                   //图的顶点数组 

       int         vexnum, arcnum;     //图的顶点数和边(弧)数 

       GraphKind kind;                    //图的类型 

}ALGraph;

Status CreateALGraph(GraphKind GKind,ALGraph &G,int vexnum,int arcnum, char *vexs,int *arcs){
	int i,j,k;
	ArcNode *s;
	G.vexnum=vexnum;
	G.arcnum=arcnum;
	G.kind=GKind;
	for(i=0;i<G.vexnum;i++){
		G.vertices[i].data=vexs[i];
		G.vertices[i].firstarc=NULL;
	}
	for(k=0;k<G.arcnum;k++){
		i=arcs[3*k];
		j=arcs[3*k+1];
		s=(ArcNode *)malloc(sizeof(ArcNode));
		s->adjvex=j;
		s->nextarc=G.vertices[i].firstarc;
		s->weight=arcs[3*k+2];
		G.vertices[i].firstarc=s;
		if(GKind==UDN||GKind==UDG){
			s=(ArcNode *)malloc(sizeof(ArcNode));
			s->adjvex=i;
			s->nextarc=G.vertices[j].firstarc;
			s->weight=arcs[3*k+2];
			G.vertices[j].firstarc=s;
		}
	}
	return OK;
}
int visited[MAX_VERTEX_NUM];

Status OutALGraph(ALGraph G){
	int i;
	ArcNode *p;
	printf("顶点集=(");
	for(i=0;i<G.vexnum;i++){
		printf("%c ",G.vertices[i].data);
	}
	printf(")\n");
	printf("邻接表:\n");
	for(i=0;i<G.vexnum;i++){
		printf("%c",G.vertices[i].data);
		p=G.vertices[i].firstarc;
		while(p){
			printf("->%d",p->adjvex);
			if(G.kind==UDN||G.kind==DN)
				printf("(%d)",p->weight);
			p=p->nextarc;
		}
		printf("\n");
	}
	return OK;
}

Status DFS(ALGraph G,int i){
	ArcNode *p;
	visited[i]=TRUE;
	printf("%c ",G.vertices[i].data);
	p=G.vertices[i].firstarc;
	while(p){
		if(!visited[p->adjvex])DFS(G,p->adjvex);
		p=p->nextarc;
	}
	return OK;
}

Status DFSTraverse(ALGraph G){
	int i;
	for(i=0;i<G.vexnum;i++)visited[i]=FALSE;
	for(i=0;i<G.vexnum;i++)
		if(!visited[i])DFS(G,i);
	return OK;
}

Status BFSTraverse(ALGraph G){
	int queue[MAX_VERTEX_NUM],head,tail;
	int i,j;
	ArcNode *p;
	head=-1; tail=-1;
	for(i=0;i<G.vexnum;i++)visited[i]=FALSE;
	for(i=0;i<G.vexnum;i++){
		if(!visited[i]){
			visited[i]=TRUE;
			printf("%c ",G.vertices[i].data);
			queue[++tail]=i;
			while(tail>tail){
				j=queue[++head];
				p=G.vertices[j].firstarc;
				while(p){
					if(!visited[p->adjvex]){
						printf("%c ",G.vertices[p->adjvex].data);
						visited[p->adjvex]=TRUE;
						queue[++tail]=p->adjvex;
					}
					p=p->nextarc;
				}
			}
		}
	}
}

int main(){
	ALGraph G;
	char UDGvex[20]={'A','B','C','D','E','F'};
	int UDGarcs[20][3]={4,5,1,3,4,1,2,5,1,1,4,1,1,3,1,0,2,1,0,1,1};
	CreateALGraph(UDG,G,6,7,UDGvex,&UDGarcs[0][0]);
	printf("无向图G1\n");
	OutALGraph(G);
	printf("\n");
	printf("图G1的深度优先遍历：\n");
	DFSTraverse(G);
	printf("\n");
	printf("图G1的广度优先遍历:\n");
	BFSTraverse(G);
	printf("\n");
	return OK; 
}
