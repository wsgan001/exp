//
// Created by Admin on 2018/4/1.
//

#ifndef TOL_LEVEL_DECIDING_H
#define TOL_LEVEL_DECIDING_H

#include "header.h"


namespace level_decide {
    int n, m;
    struct Vertex{
        int degree_mul;
        int level;
    };
    vector<vector<int>> graph;
    vector<vector<int>> rgraph;
    vector<Vertex> vertexes;


    void load_graph(string path) {
        ifstream ifs(path);
        if (!ifs) {
            log("file not found.");
        }
        ifs >> n >> m;
        graph.resize(n);
        rgraph.resize(n);
        vertexes.resize(n);
        int src, dst;
        for (int i = 0; i < m; i++) {
            ifs >> src >> dst;
            graph[src].push_back(dst);
            rgraph[dst].push_back(src);
        }
        ifs.close();
    }

    void multi_degree() {
        for(int i=0;i<n;i++){
            vertexes[i].degree_mul=graph[i].size()*rgraph[i].size();
        }
    }

    void decide_lvl(){
        //construct reverse Index
        map<int,set<int>> rindex;
        for(int i=0;i<n;i++){
            rindex[vertexes[i].degree_mul].insert(i);
        }

        int level=0;
        for(map<int,set<int>>::reverse_iterator deg_mul=rindex.rbegin();deg_mul!=rindex.rend();++deg_mul){
            for(set<int>::iterator vid=deg_mul->second.begin();vid!=deg_mul->second.end();++vid){
                vertexes[*vid].level=level;
                level++;
            }
        }
    }

    void output_for_butterfly(string path){
        ofstream ofs(path);
        if(!ofs){
            log("open file failed.");
        }
        ofs<<n<<" "<<m<<endl;
        for(int srcid=0;srcid<graph.size();srcid++){
            for(int j=0;j<graph[srcid].size();++j){
                int dstid=graph[srcid][j];
                ofs<<srcid<<" "<<dstid<<endl;
            }
        }
        for(int i=0;i<vertexes.size();i++){
            ofs<<vertexes[i].level<<" ";
        }
        ofs<<endl;
        ofs.close();
    }

    void output_for_dist(string path){
        ofstream ofs(path);
        if(!ofs){
            log("open file failed.");
        }
        for(int i=0;i<vertexes.size();i++){
            ofs<<i<<"\t"<<vertexes[i].level<<" ";
            ofs<<graph[i].size()<<" ";
            for(auto dst=graph[i].begin();dst!=graph[i].end();++dst){
                ofs<<*dst<<" ";
            }
            ofs<<rgraph[i].size()<<" ";
            for(auto src=rgraph[i].begin();src!=rgraph[i].end();++src){
                ofs<<*src<<" ";
            }
            ofs<<endl;
        }
        ofs.close();
    }

    void test() {
        load_graph("C:\\Users\\Admin\\CLionProjects\\tol\\data\\twitter_socialDAG");
        multi_degree();
        decide_lvl();
        output_for_butterfly("C:\\Users\\Admin\\CLionProjects\\tol\\data\\twitter_socialDAG_lvl_edgefmt");
//        output_for_dist("C:\\Users\\Admin\\CLionProjects\\tol\\data\\twitter_socialDAG_lvl_vertexfmt");
    }
}


#endif //TOL_LEVEL_DECIDING_H