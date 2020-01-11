//
// Created by Jesson on 2020/1/9.
//

#include "huffman.h"

#include<iostream>
#include <vector>
#include <algorithm>
using namespace std;
/***
 * 编码实现build一颗树的过程
 */

class huffumanNode
{
public:
    int weight;
    huffumanNode *left;
    huffumanNode *right;
    //用来构造叶子节点
    huffumanNode(int setWeight)
    {

        this->weight = setWeight;
        this->left = NULL;
        this->right = NULL;
    }
    //用来构造中间的节点
    huffumanNode(int setWeight, huffumanNode *setLeft, huffumanNode *setRight)
    {
        this->weight = setWeight;
        this->left = setLeft;
        this->right = setRight;
    }
    //判断是否是叶子节点
    bool isLeaf()
    {
        return this->left == NULL && this->right == NULL;
    }

};

//降序排序比较函数，以wieght的大小降序排列
bool myHuffumanComepare(huffumanNode *node1, huffumanNode *node2)
{
    return node1->weight > node2->weight;
}

/*得到带权路径长度。所谓树的带权路径长度，就是树中所有的叶结点
的权值乘上其到根结点的 路径长度（若根结点为0层，叶结点到根结点的路径长度
为叶结点的层数）*/
void getHuffmanSum(huffumanNode *root,int length,int &sum)
{
    if (!root)
    {
        return;
    }
    if (root->isLeaf())
    {
        sum += root->weight*length;
    }
    length++;
    getHuffmanSum(root->left, length, sum);
    getHuffmanSum(root->right, length, sum);
}
//前序遍历打印
void prePrint(huffumanNode *root)
{
    if (!root)
    {
        return;
    }
    cout << root->weight << " ";
    prePrint(root->left);
    prePrint(root->right);
}

int buildHuffuman()
{
    int n;
    while (cin >> n)
    {
        vector<huffumanNode*> weightArray;
        while (n--)
        {
            int tempWeight;
            cin >> tempWeight;
            huffumanNode *newNode = new huffumanNode(tempWeight);
            weightArray.push_back(newNode);
        }
        sort(weightArray.begin(), weightArray.end(), myHuffumanComepare);//按照权重倒序排列
        while ((int)weightArray.size() > 1)
        {
            huffumanNode *minNode1 = weightArray[weightArray.size() - 1];
            huffumanNode *minNode2 = weightArray[weightArray.size() - 2];
            int fatherWeight = minNode1->weight + minNode2->weight;
            /*根据最小的两个权重节点，构造新节点*/
            huffumanNode *fatherNode = new huffumanNode(fatherWeight, minNode1, minNode2);

            weightArray.pop_back();
            weightArray.pop_back();
            weightArray.push_back(fatherNode);

            sort(weightArray.begin(), weightArray.end(), myHuffumanComepare);
        }
        prePrint(weightArray[0]);
        cout << endl;
        int length = 0;
        int sum = 0;
        getHuffmanSum(weightArray[0], length, sum);
        cout << "weightSum: " << sum << endl;
    }
    return 0;
}

//int main(){
//    // 5
//    //1 2 2 5 9
//    buildHuffuman();
//}


using namespace std;
typedef struct HTNode
{
    int weight;
    int parent,lchild,rchild;
} HTNode, *HuffmanTree;

typedef char **HuffmanCode;
int i,j,m,n,s1,s2,w[100];
void select(HuffmanTree HT,int n, int &s1, int &s2)
{
    for(i=1; i<=n; i++)
    {
        if(HT[i].parent==0)
        {
            s1=i;
            break;
        }
    }
    for(i=1; i<=n; i++)
    {
        if(HT[i].parent==0 && HT[s1].weight>HT[i].weight)
        {
            s1=i;
        }
    }
    for(i=1; i<=n; i++)
    {
        if(HT[i].parent==0 && i!=s1)
        {
            s2=i;
            break;
        }
    }
    for(i=1; i<=n; i++)
    {
        if(HT[i].parent==0 && HT[s2].weight>HT[i].weight && i!=s1)
        {
            s2=i;
        }
    }
}

void createhuffmantree(HuffmanTree &HT,int n)
{
    if(n<=1)
    {
        return;
    }
    m=(2*n)-1;
    HT=new HTNode[m+1];
    for(i=1; i<=m; i++)
    {
        HT[i].parent=0;
        HT[i].lchild=0;
        HT[i].rchild=0;
    }
    for(i=1; i<=n; i++)
    {
        cin>>HT[i].weight;
    }
    for(i=n+1; i<=m; i++)
    {
        select(HT,i-1,s1,s2);
        HT[s1].parent=i;
        HT[s2].parent=i;
        HT[i].lchild=s1;
        HT[i].rchild=s2;
        HT[i].weight=HT[s1].weight+HT[s2].weight;
    }
}
void creathuffmancode(HuffmanTree HT,HuffmanCode &HC,int n)
{
    int start,c;
    int f;
    HC=new char*[n+1];
    char *cd=new char[n];
    cd[n-1]='\0';
    for(i=1; i<=n; i++)
    {
        start=n-1;
        c=i;
        f=HT[c].parent;
        while(f!=0)
        {
            start--;
            if(HT[f].lchild==c)
            {
                cd[start]='0';
            }
            else
            {
                cd[start]='1';
            }
            c=f;
            f=HT[f].parent;
        }
        HC[i]=new char[n-start];
        strcpy(HC[i],&cd[start]);
    }
    delete cd;
}
void TranCode(HuffmanTree HT,char a[],char zf[],char b[],int n)
{
    int q=2*n-1;
    int k=0;
    for(i=0; a[i]!='\0'; i++)
    {
        if(a[i]=='0')
        {
            q=HT[q].lchild;
        }
        else if(a[i]=='1')
        {
            q=HT[q].rchild;
        }
        if(HT[q].lchild==0 && HT[1].rchild==0)
        {
            b[k++]=zf[q];
            q=2*n-1;
        }
    }
    b[k]='\0';
}
void show_help()
{
    cout<<"********************************************************************"<<endl;
    cout<<"********* 1.输入HuffmanTree的参数.                        **********"<<endl;
    cout<<"********* 2.初始化HuffmanTree参数(含有26字母及空格).      **********"<<endl;
    cout<<"********* 3.创建HuffmanTree和编码表.                      **********"<<endl;
    cout<<"********* 4.输出编码表.                                   **********"<<endl;
    cout<<"********* 5.输入编码，并翻译为字符.                       **********"<<endl;
    cout<<"********* 6.输入字符，并实现编码.                         **********"<<endl;
    cout<<"********* 7.退出.                                         **********"<<endl;
    cout<<"********************************************************************"<<endl;
}

int main()
{
    HuffmanTree HT;
    HuffmanCode HC;
    int operator_code;
    char a[100];
    char b[100];
    char c[100];
    char zf[100];
    show_help();
    while(1)
    {
        cout<<"请输入操作代码："<<endl;
        cin>>operator_code;
        if(operator_code==1)
        {
            cout<<"请输入需要编码的字符个数："<<endl;
            cin>>n;
        }
        else if(operator_code==2)
        {
            cout<<"请输入所有编码的字符："<<endl;
            for(i=1; i<=n; i++)
            {
                cin>>zf[i];
            }
            cout<<"请输入每一个字符的权值："<<endl;
            createhuffmantree(HT,n);
            cout<<"结点"<<"\t"<<"字符"<<"\t"<<"权值"<<"\t"<<"双亲"<<"\t"<<"左孩子"<<"\t"<<"右孩子"<<endl;
            for(int i=1;i<=n;i++)
            {
                cout<<i<<"\t"<<zf[i]<<"\t"<<HT[i].weight<<"\t"<<HT[i].parent<<"\t"<<HT[i].lchild<<"\t"<<HT[i].rchild<<endl;
            }
        }
        else if(operator_code==3)
        {
            creathuffmancode(HT,HC,n);
        }
        else if(operator_code==4)
        {
            cout<<"结点"<<"\t"<<"字符"<<"\t"<<"权值"<<"\t"<<"编码"<<endl;
            for(int i=1;i<=n;i++)
            {
                cout<<i<<"\t"<<zf[i]<<"\t"<< HT[i].weight<<"\t"<<HC[i]<<endl;
            }
            cout<<endl;
        }
        else if(operator_code==5)
        {
            cout<<"输入二进制编码："<<endl;
            cin>>a;
            TranCode(HT,a,zf,b,n);
            cout<<"结果为："<<b<<endl;

        }else if(operator_code==6)
        {
            cout<<"请输入一串字符"<<endl;
            cin>>c;
            for(i=0;i<sizeof(c)/sizeof(c[0]);i++)
            {
                for(j=1;i<=n;j++)
                {
                    if(c[i]==zf[j])
                    {
                        cout<<HC[j];
                        break;
                    }
                }
            }
            cout<<endl;
        }else if(operator_code==7)
        {
            break;
        }
    }
    return 0;
}
