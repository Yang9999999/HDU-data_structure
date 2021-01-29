    #include<stdlib.h>
    #include<stdio.h>
    #include<string.h>
    //�����������ṹ
    typedef struct {
        int weight;//���Ȩ��
        int parent, left, right;//����㡢���ӡ��Һ����������е�λ���±�
    }HTNode, *HuffmanTree;
    //��̬��ά���飬�洢����������
    typedef char ** HuffmanCode;
    //HT�����д�ŵĹ���������end��ʾHT�����д�Ž�������λ�ã�s1��s2���ݵ���HT������Ȩ��ֵ��С����������������е�λ��
    void Select(HuffmanTree HT, int end, int *s1, int *s2)
    {
        int min1, min2;
        //���������ʼ�±�Ϊ 1
        int i = 1;
        //�ҵ���û�������Ľ��
        while(HT[i].parent != 0 && i <= end){
            i++;
        }
        min1 = HT[i].weight;
        *s1 = i;
       
        i++;
        while(HT[i].parent != 0 && i <= end){
            i++;
        }
        //���ҵ����������Ƚϴ�С��min2Ϊ��ģ�min1ΪС��
        if(HT[i].weight < min1){
            min2 = min1;
            *s2 = *s1;
            min1 = HT[i].weight;
            *s1 = i;
        }else{
            min2 = HT[i].weight;
            *s2 = i;
        }
        //�������ͺ���������δ���������Ľ�����Ƚ�
        for(int j=i+1; j <= end; j++)
        {
            //����и���㣬ֱ��������������һ��
            if(HT[j].parent != 0){
                continue;
            }
            //�������С�Ļ�С����min2=min1��min1��ֵ�µĽ����±�
            if(HT[j].weight < min1){
                min2 = min1;
                min1 = HT[j].weight;
                *s2 = *s1;
                *s1 = j;
            }
            //�����������֮�䣬min2��ֵΪ�µĽ���λ���±�
            else if(HT[j].weight >= min1 && HT[j].weight < min2){
                min2 = HT[j].weight;
                *s2 = j;
            }
        }
    }
    //HTΪ��ַ���ݵĴ洢�������������飬wΪ�洢���Ȩ��ֵ�����飬nΪ������
    void CreateHuffmanTree(HuffmanTree *HT, int *w, int n)
    {
        if(n<=1) return; // ���ֻ��һ��������൱��0
        int m = 2*n-1; // ���������ܽڵ�����n����Ҷ�ӽ��
        *HT = (HuffmanTree) malloc((m+1) * sizeof(HTNode)); // 0��λ�ò���
        HuffmanTree p = *HT;
        // ��ʼ�����������е����н��
        for(int i = 1; i <= n; i++)
        {
            (p+i)->weight = *(w+i-1);
            (p+i)->parent = 0;
            (p+i)->left = 0;
            (p+i)->right = 0;
        }
        //��������±� n+1 ��ʼ��ʼ�����������г�Ҷ�ӽ����Ľ��
        for(int i = n+1; i <= m; i++)
        {
            (p+i)->weight = 0;
            (p+i)->parent = 0;
            (p+i)->left = 0;
            (p+i)->right = 0;
        }
        //������������
        for(int i = n+1; i <= m; i++)
        {
            int s1, s2;
            Select(*HT, i-1, &s1, &s2);
            (*HT)[s1].parent = (*HT)[s2].parent = i;
            (*HT)[i].left = s1;
            (*HT)[i].right = s2;
            (*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;
        }
    }
    //HTΪ����������HCΪ�洢������������Ķ�ά��̬���飬nΪ���ĸ���
    void HuffmanCoding(HuffmanTree HT, HuffmanCode *HC,int n){
        *HC = (HuffmanCode) malloc((n+1) * sizeof(char *));
        char *cd = (char *)malloc(n*sizeof(char)); //��Ž�������������ַ�������
        cd[n-1] = '\0';//�ַ���������
       
        for(int i=1; i<=n; i++){
            //��Ҷ�ӽ��������õ��Ĺ���������������ģ���Ҫ���ַ���������������
            int start = n-1;
            //��ǰ����������е�λ��
            int c = i;
            //��ǰ���ĸ�����������е�λ��
            int j = HT[i].parent;
            // һֱѰ�ҵ������
            while(j != 0){
                // ����ý���Ǹ������������Ӧ·������Ϊ0������Ϊ�Һ��ӱ���Ϊ1
                if(HT[j].left == c)
                    cd[--start] = '0';
                else
                    cd[--start] = '1';
                //�Ը����Ϊ���ӽ�㣬�����������ķ������
                c = j;
                j = HT[j].parent;
            }
            //����ѭ����cd�����д��±� start ��ʼ����ŵľ��Ǹý��Ĺ���������
            (*HC)[i] = (char *)malloc((n-start)*sizeof(char));
            strcpy((*HC)[i], &cd[start]);
        }
        //ʹ��malloc�����cd��̬������Ҫ�ֶ��ͷ�
        free(cd);
    }
    //��ӡ����������ĺ���
    void PrintHuffmanCode(HuffmanCode htable,int *w,int n)
    {
        printf("Huffman code : \n");
        for(int i = 1; i <= n; i++)
            printf("%d code = %s\n",w[i-1], htable[i]);
    }
    int main(void)
    {
        int w[8] = {5, 29, 7, 8, 14,23,3,11};
        int n = 8;
        HuffmanTree htree;
        HuffmanCode htable;
        CreateHuffmanTree(&htree, w, n);
        printf("1.HT���ݣ�HT[0].weight=5\n HT[1].weight=29\nHT[2].weight=7\nHT[3].weight=8\nHT[4].weight=14\nHT[5].weight=23\nHT[6].weight=3\nHT[7].weight=11\n");
        printf("2.HT���ݣ�\n");
		printf("          100         \n"); 
		printf("          /  \\       \n"); 
		printf("        58   42       \n"); 
		printf("       / \\  / \\     \n"); 
		printf("     29  29 23  19    \n"); 
		printf("    / \\        / \\  \n"); 
		printf("  14  15       8  11  \n"); 
		printf("     / \\             \n"); 
		printf("     8  7             \n"); 
		printf("    / \\              \n"); 
		printf("   3   5              \n"); 
	
		HuffmanCoding(htree, &htable, n);
        PrintHuffmanCode(htable,w, n);
        return 0;
    }
