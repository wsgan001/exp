//
// Created by Admin on 2018/4/1.
//

#ifndef TOL_LEVEL_DECIDING_H
#define TOL_LEVEL_DECIDING_H

#include "header.h"


namespace level_decide {
    int n, m;
    struct Vertex {
        long long degree_mul;
        int level;
    };
    vector<vector<int> > graph;
    vector<vector<int> > rgraph;
    vector<Vertex> vertexes;


    void load_graph(string path) {
//        ifstream ifs(path);
//        if (!ifs) {
//            log("file not found.");
//        }
//        ifs >> n >> m;
//        graph.resize(n);
//        rgraph.resize(n);
//        vertexes.resize(n);
//        int src, dst;
//        for (int i = 0; i < m; i++) {
//            ifs >> src >> dst;
//            graph[src].push_back(dst);
//            rgraph[dst].push_back(src);
//        }
//        ifs.close();
    }

    void load_graph2(string path) {
        FILE *fp = fopen(path.c_str(), "rb");
        if (fp == NULL) {
            log("file not found.");
            return;
        }
        fread(&n, sizeof(int), 1, fp);
        fread(&m, sizeof(int), 1, fp);
//        n=12407621;
//        m=13857091;

        graph.resize(n);
        rgraph.resize(n);
        vertexes.resize(n);
        int src, dst;
        for (int i = 0; i < m; i++) {
            fread(&src, sizeof(int), 1, fp);
            fread(&dst, sizeof(int), 1, fp);
            graph[src].push_back(dst);
            rgraph[dst].push_back(src);
        }
        log("graph with %d vertexes and %d edges loaded.",n,m);
        if(feof(fp))
            log("end of file reached.")
        else
            log("not reach the end of the file.")
        fclose(fp);
    }

    void multi_degree() {
        for (int i = 0; i < n; i++) {
            vertexes[i].degree_mul = (long long)graph[i].size() * (long long)rgraph[i].size();
        }
    }

    void decide_lvl() {
        log("start deciding level")
        //construct reverse Index
        log("construct reverse index")
        map<long long, vector<int> > rindex;
        for (int i = 0; i < n; i++) {
            rindex[vertexes[i].degree_mul].push_back(i);
        }
        log("finish construct reverse index and start inital level vertex")
        int level = 0;
        for (map<long long, vector<int> >::reverse_iterator deg_mul = rindex.rbegin(); deg_mul != rindex.rend(); ++deg_mul) {
            for (vector<int>::iterator vid = deg_mul->second.begin(); vid != deg_mul->second.end(); ++vid) {
                vertexes[*vid].level = level;
                level++;
            }
        }
        log("finish deciding level")
    }

    void output_for_butterfly(const char * path) {
        log("start output_for_butterfly")
        ofstream ofs(path);
        if (!ofs) {
            log("open file failed.");
        }
        ofs << n << " " << m << endl;
        for (int srcid = 0; srcid < graph.size(); srcid++) {
            for (int j = 0; j < graph[srcid].size(); ++j) {
                int dstid = graph[srcid][j];
                ofs << srcid << " " << dstid << endl;
            }
        }
        for (int i = 0; i < vertexes.size(); i++) {
            ofs << vertexes[i].level << " ";
        }
        ofs << endl;
        ofs.close();
        log("finish output_for_butterfly")
    }

    void output_for_dist(const char * path) {
        log("start output_for_dist")
        ofstream ofs(path);
        if (!ofs) {
            log("open file failed.");
        }
        for (int i = 0; i < vertexes.size(); i++) {
            ofs << i << "\t" << vertexes[i].level << " ";
            ofs << graph[i].size() << " ";
            for (vector<int>::iterator dst = graph[i].begin(); dst != graph[i].end(); ++dst) {
                ofs << *dst << " ";
            }
            ofs << rgraph[i].size() << " ";
            for (vector<int>::iterator src = rgraph[i].begin(); src != rgraph[i].end(); ++src) {
                ofs << *src << " ";
            }
            ofs << endl;
        }
        ofs.close();
        log("finish output_for_dist")
    }

    void test() {//5.55s
//        load_graph("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_socialDAG");
        //DAG 7245617 vertexes and 7314324 Edges
//        load_graph2("E:\\twitter_big\\Twitter-dataset\\data\\edges_DAG.csv.bin");
        load_graph2("E:/WEBSPAM-UK2007/graph/uk-2007-05.dag.edge.bin");
        multi_degree();
        decide_lvl();
//        output_for_butterfly("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_socialDAG_lvl_edgefmt");
//        output_for_dist("C:\\Users\\Admin\\CLionProjects\\exp\\data\\twitter_socialDAG_lvl_vertexfmt");
//        output_for_butterfly("E:\\twitter_big\\Twitter-dataset\\data\\edges_DAG_lvl_edgefmt");
//        output_for_dist("E:\\twitter_big\\Twitter-dataset\\data\\edges_DAG_lvl_vertexfmt");
        output_for_butterfly("E:/WEBSPAM-UK2007/graph/uk-2007-05.dag.edge.lvl.bin");
        output_for_dist("E:/WEBSPAM-UK2007/graph/uk-2007-05.dag.vertex.lvl.bin");
    }
}


#endif //TOL_LEVEL_DECIDING_H
