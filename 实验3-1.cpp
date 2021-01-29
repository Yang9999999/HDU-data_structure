#define INFINITY 10000  
#include<stdio.h>                 //表示最大值∞

#define MAX_VERTEX_NUM  20       //最大顶点数

typedef int Status;

typedef enum {DG,DN,UDG,UDN} GraphKind;  //图的枚举类型

typedef int VRType;

typedef char InfoType;  

typedef struct ArcCell { 

        VRType adj  ;          //对无权图用1或0表示；对带权图，则为权值类型。

        InfoType *info;       //该边或弧相关信息的指针（字符串） 

} ArcCell, AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef char VertexType;

typedef struct{

        VertexType vexs[MAX_VERTEX_NUM];   //顶点数组，存放顶点信息

        AdjMatrix   arcs;                  //邻接矩阵

        int vexnum, arcnum;           //图中顶点总数与弧数

        GraphKind  kind;                 //图的种类标志

} MGraph;      
Status CreateMGraph(GraphKind GKind,MGraph &G,int vexnum,int arcnum,char *vexs,int *arcs)
{
	int i,j,k;
	G.vexnum=vexnum;
	G.arcnum=arcnum;
	G.kind=GKind;
	for(i=0;i<G.vexnum;i++) G.vexs[i]=vexs[i];
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++){
			if(GKind==UDG||GKind==DG)G.arcs[i][j].adj=0;
			else G.arcs[i][j].adj=INFINITY;
			G.arcs[i][j].info=NULL;
		}
	}
	for(k=0;k<G.arcnum;k++){
		i=arcs[3*k];
		j=arcs[3*k+1];
		G.arcs[i][j].adj=arcs[3*k+2];
		if(GKind==UDN||GKind==UDG)G.arcs[j][i]=G.arcs[i][j];
	}
}
Status OutMGraph(MGraph G){
	int i,j;
	printf("顶点集=（");
	for(i=0;i<G.vexnum;i++)
		printf("%c ",G.vexs[i]);
	printf(")\n");
	printf("邻接矩阵:\n");
	for(i=0;i<G.vexnum;i++){
		for(j=0;j<G.vexnum;j++){
			if(G.arcs[i][j].adj==INFINITY)
				printf("∞");
			else
				printf("%d ",G.arcs[i][j].adj);
		}
		printf("\n");
	}
}
Status VerDegree(MGraph G){
	int i,j,d;
	if(G.kind==UDG||G.kind==UDN)
		printf("各顶点的度\n");
	else
		printf("各顶点的出度：\n");
	for(i=0;i<G.vexnum;i++){
		printf("%c",G.vexs[i]);
		d=0;
		for(j=0;j<G.vexnum;j++)
			if(G.arcs[i][j].adj!=0&&G.arcs[i][j].adj!=INFINITY)d++;
		printf("%d\n",d);
	}
	if(G.kind==DG||G.kind==DN){
		printf("各顶点的入度:\n");
		for(i=0;i<G.vexnum;i++){
			printf("%c",G.vexs[i]);
			d=0;
			for(j=0;j<G.vexnum;j++)
				if(G.arcs[j][i].adj!=0&&G.arcs[j][i].adj!=INFINITY)d++;
			printf("%d\n",d);
		}
	}
}
int main()
{
	MGraph G;
	//输出并创建无向图
	char UDGvex[20]={'A','B','C','D'};
	int UDGarcs[20][3]={0,1,1,0,2,1,0,3,1,1,2,1,2,3,1};
	CreateMGraph(UDG,G,4,5,UDGvex,&UDGarcs[0][0]);
	printf("(1)无向图G\n");
	OutMGraph(G);
	printf("\n");
	VerDegree(G);
	printf("\n");
	//输出并创建有向图
	char DGvex[20]={'A','B','C','D'};
	int DGarcs[20][3]={0,1,1,1,0,1,1,2,1,2,0,1,2,1,1,3,1,1};
	CreateMGraph(DG,G,4,6,DGvex,&DGarcs[0][0]);
	printf("(2)有向图");
	OutMGraph(G);
	printf("\n");
	VerDegree(G);
	printf("\n");
	//创建并输出无向图
	char UDNvex[20]={'A','B','C','D'};
	int UDNarcs[20][3]={0,1,56,0,2,34,0,3,78,2,3,25};
	CreateMGraph(UDN,G,4,4,UDNvex,&UDNarcs[0][0]);
	printf("(3)无向网");
	OutMGraph(G);
	printf("\n");
	VerDegree(G);
	printf("\n");
	//创建并输出有向网
	char DNvex[20]={'A','B','C'};
	int DNarcs[20][3]={0,2,50,1,2,45,2,0,64};
	CreateMGraph(DN,G,3,3,DNvex,&DNarcs[0][0]);
	printf("(4)有向网G\n");
	OutMGraph(G);
	printf("\n");
	VerDegree(G);
	return 0;
}
