#include<stdio.h>
#include<stdlib.h>
#define OK 1
#define MAX_VERTEX_NUM  20//最大顶点数

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
Status VerDegree(ALGraph G){
	int i,j,d;
	ArcNode *p;
	if(G.kind==UDG||G.kind==UDN)
		printf("各顶点的度:\n");
	else
		printf("各顶点的出度\n");
	for(i=0;i<G.vexnum;i++){
		printf("%c:",G.vertices[i].data);
		d=0;
		p=G.vertices[i].firstarc;
		while(p){
			d++;
			p=p->nextarc;
		}
		printf("%d\n",d);
	}
	if(G.kind==DG||G.kind==DN){
		printf("各顶点的入度:\n");
		for(i=0;i<G.vexnum;i++){
			printf("%c:",G.vertices[i].data);
			d=0;
			for(j=0;j<G.vexnum;j++){
				p=G.vertices[j].firstarc;
				while(p){
					if(p->adjvex==i)d++;
					p=p->nextarc;
				}
			}
			printf("%d\n",d);
		}
	}
	return OK;
}
int main(){
	ALGraph G;
	char UDGvex[20]={'A','B','C','D'};
	int UDGarcs[20][3]={0,1,1,0,2,1,0,3,1,1,2,1,2,3,1};
	CreateALGraph(UDG,G,4,5,UDGvex,&UDGarcs[0][0]);
	printf("(1)无向图G1\n");
	OutALGraph(G);
	printf("\n");
	VerDegree(G);
	printf("\n");
	
	char DGvex[20]={'A','B','C','D'};
	int DGarcs[20][3]={0,1,1,1,0,1,1,2,1,2,0,1,2,1,1,3,1,1};
	CreateALGraph(DG,G,4,6,DGvex,&DGarcs[0][0]);
	printf("(2)有向图G2\n");
	OutALGraph(G);
	printf("\n");
	VerDegree(G);
	printf("\n");
	
	char UDNvex[20]={'A','B','C','D'};
	int UDNarcs[20][3]={0,1,56,0,2,34,0,3,78,2,3,25};
	CreateALGraph(UDN,G,4,4,UDNvex,&UDNarcs[0][0]);
	printf("(3)无向网G3\n");
	OutALGraph(G);
	printf("\n");
	VerDegree(G);
	printf("\n");
	
	char DNvex[20]={'A','B','C'};
	int DNarcs[20][3]={0,2,50,1,2,45,2,0,64};
	CreateALGraph(DN,G,3,3,DNvex,&DNarcs[0][0]);
	printf("(4)有向图");
	OutALGraph(G);
	printf("\n");
	VerDegree(G);
	printf("\n");
	
	char DNvex1[20]={'A','B','C'};
	int DNarcs1[20][3]={2,0,50,2,1,45,0,2,64};
	CreateALGraph(DN,G,3,3,DNvex1,&DNarcs1[0][0]);
	printf("(5)有向网G4的逆邻接表\n");
	OutALGraph(G);
	printf("\n");
	return OK;
}

