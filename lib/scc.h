//
// Created by admin on 2018/4/1.
//

#ifndef EXP_SCC_H
#define EXP_SCC_H

#include<cstdio>
#include<algorithm>
#include<cstring>
#include "header.h"
using namespace std;

namespace scc{
    struct vertex{
        int DFN;
        int LOW;
        bool visited= false;
    };
    vector<vertex> vertexes;
    vector<vector<int>> edges;
    vector<int> new_stack;
    int time=0;

    struct node {
        int v,next;
    }edge[1001];
    int DFN[1001],LOW[1001];
    int stack[1001],heads[1001],visit[1001],cnt=0,tot=0,index=0;

    void add(int x,int y)
    {
        edge[++cnt].next=heads[x];
        edge[cnt].v = y;
        heads[x]=cnt;
    }
    void tarjan2(int vid){
        time++;
        vertexes[vid].DFN=vertexes[vid].LOW=time;
        vertexes[vid].visited=true;
        new_stack.push_back(vid);

        for(int i=edges[vid].size()-1;i>=0;i--){
            int childvid=edges[vid][i];
            if(!vertexes[childvid].DFN){//如果没访问过
                tarjan2(childvid);
                vertexes[vid].LOW=min(vertexes[vid].LOW,vertexes[childvid].LOW);
            } else if(vertexes[childvid].visited){//如果访问过，并且还在栈里。
                vertexes[vid].LOW=min(vertexes[vid].LOW,vertexes[childvid].DFN);
            }
        }
        if(vertexes[vid].LOW==vertexes[vid].DFN){
            while(true){
                int stack_top=new_stack.back();
                printf("%d ",stack_top+1);
                vertexes[stack_top].visited=false;
                new_stack.pop_back();
                if(stack_top==vid){
                    printf("\n");
                    break;
                }
            }
        }
    }
    void tarjan(int x)//代表第几个点在处理。递归的是点。
    {
        DFN[x]=LOW[x]=++tot;// 新进点的初始化。
        stack[++index]=x;//进站
        visit[x]=1;//表示在栈里
        for(int i=heads[x];i!=-1;i=edge[i].next)
        {
            if(!DFN[edge[i].v]) {//如果没访问过
                tarjan(edge[i].v);//往下进行延伸，开始递归
                LOW[x]=min(LOW[x],LOW[edge[i].v]);//递归出来，比较谁是谁的儿子／父亲，就是树的对应关系，涉及到强连通分量子树最小根的事情。
            }
            else if(visit[edge[i].v ]){  //如果访问过，并且还在栈里。
                LOW[x]=min(LOW[x],DFN[edge[i].v]);//比较谁是谁的儿子／父亲。就是链接对应关系
            }
        }
        if(LOW[x]==DFN[x]) //发现是整个强连通分量子树里的最小根。
        {
            do{
                printf("%d ",stack[index]);
                visit[stack[index]]=0;
                index--;
            }while(x!=stack[index+1]);//出栈，并且输出。
            printf("\n");
        }
        return ;
    }
    int test()
    {
        streambuf *backup;
        ifstream fin;
        fin.open("C:\\Users\\Admin\\CLionProjects\\exp\\data\\tarjan_test");
        if(!fin.is_open()){
            cerr<<"file not found"<<endl;
            exit(1);
        }
        backup = cin.rdbuf();   // back up cin's streambuf
        cin.rdbuf(fin.rdbuf()); // assign file's streambuf to cin
// ... cin will read from file
//    cin.rdbuf(backup);     // restore cin's original streambuf

        memset(heads,-1,sizeof(heads));
        int n,m;//n nodes and m edges
        cin>>n>>m;
        vertexes.resize(n);
        edges.resize(n);

        int x,y;
        for(int i=0;i<m;i++)
        {
            cin>>x>>y;
            edges[x-1].push_back(y-1);
            add(x,y);
        }
        for(int i=0;i<10;i++)
        {
            printf("Edge[%d]{v:%d, next:%d}\n",i,edge[i].v,edge[i].next);
        }

        for(int i=0;i<10;i++)
        {
            printf("heads[%d]%d\n",i,heads[i]);
        }

        for(int i=1;i<=n;i++) {
            if (!DFN[i]) tarjan(i);//当这个点没有访问过，就从此点开始。防止图没走完
        }
        printf("output of new algorithm\n");
        for(int i=0;i<vertexes.size();i++){
            if(!vertexes[i].DFN) tarjan2(i);
        }
        return 0;
    }
}




#endif //EXP_SCC_H
