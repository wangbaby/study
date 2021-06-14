#include "DenseGraph.h"
#include "KruskalMST.h"
#include "LazyPrimMST.h"
#include "PrimMST.h"
#include "ReadGraph.h"
#include "SparseGraph.h"

#include <iostream>

using namespace std;

int main() {
  {
    // 带权稀疏图和稠密图的输出
    string filename = "testG1.txt";
    int V = 8;
    cout << fixed << setprecision(2);

    // Test Weighted Dense Graph
    DenseGraph<double> g1(V, false);
    ReadGraph<DenseGraph<double>, double> readGraph(g1, filename);
    g1.show();
    cout << endl;

    // Test Weighted Sparse Graph
    SparseGraph<double> g2(V, false);
    ReadGraph<SparseGraph<double>, double> readGraph1(g2, filename);
    g2.show();
    cout << endl;
  }
  {
    // 测试Kruskal算法
    string filename = "testG1.txt";
    int V = 8;

    SparseGraph<double> g = SparseGraph<double>(V, false);
    ReadGraph<SparseGraph<double>, double> readGraph(g, filename);

    // Test Lazy Prim MST
    cout << "Test Lazy Prim MST:" << endl;
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMST(g);
    vector<Edge<double>> mst = lazyPrimMST.mstEdges();
    for (int i = 0; i < mst.size(); i++)
      cout << mst[i] << endl;
    cout << "The MST weight is: " << lazyPrimMST.result() << endl;

    cout << endl;

    // Test Prim MST
    cout << "Test Prim MST:" << endl;
    PrimMST<SparseGraph<double>, double> primMST(g);
    mst = primMST.mstEdges();
    for (int i = 0; i < mst.size(); i++)
      cout << mst[i] << endl;
    cout << "The MST weight is: " << primMST.result() << endl;

    cout << endl;

    // Test Kruskal MST
    cout << "Test Kruskal MST:" << endl;
    KruskalMST<SparseGraph<double>, double> kruskalMST(g);
    mst = kruskalMST.mstEdges();
    for (int i = 0; i < mst.size(); i++)
      cout << mst[i] << endl;
    cout << "The MST weight is: " << kruskalMST.result() << endl;
  }

  {
    // 比较Lazy Prim, Prim和Kruskal的时间性能
    string filename1 = "testG1.txt";
    int V1 = 8;

    string filename2 = "testG2.txt";
    int V2 = 250;

    string filename3 = "testG3.txt";
    int V3 = 1000;

    string filename4 = "testG4.txt";
    int V4 = 10000;

    // 读取文件
    SparseGraph<double> g1 = SparseGraph<double>(V1, false);
    ReadGraph<SparseGraph<double>, double> readGraph1(g1, filename1);
    cout << filename1 << " load successfully." << endl;

    SparseGraph<double> g2 = SparseGraph<double>(V2, false);
    ReadGraph<SparseGraph<double>, double> readGraph2(g2, filename2);
    cout << filename2 << " load successfully." << endl;

    SparseGraph<double> g3 = SparseGraph<double>(V3, false);
    ReadGraph<SparseGraph<double>, double> readGraph3(g3, filename3);
    cout << filename3 << " load successfully." << endl;

    SparseGraph<double> g4 = SparseGraph<double>(V4, false);
    ReadGraph<SparseGraph<double>, double> readGraph4(g4, filename4);
    cout << filename4 << " load successfully." << endl;

    clock_t startTime, endTime;

    // Test Lazy Prim MST
    cout << "Test Lazy Prim MST:" << endl;

    startTime = clock();
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMST1(g1);
    endTime = clock();
    cout << "Test for G1: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMST2(g2);
    endTime = clock();
    cout << "Test for G2: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMST3(g3);
    endTime = clock();
    cout << "Test for G3: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    LazyPrimMST<SparseGraph<double>, double> lazyPrimMST4(g4);
    endTime = clock();
    cout << "Test for G4: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    cout << endl;

    // Test Prim MST
    cout << "Test Prim MST:" << endl;

    startTime = clock();
    PrimMST<SparseGraph<double>, double> PrimMST1(g1);
    endTime = clock();
    cout << "Test for G1: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    PrimMST<SparseGraph<double>, double> PrimMST2(g2);
    endTime = clock();
    cout << "Test for G2: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    PrimMST<SparseGraph<double>, double> PrimMST3(g3);
    endTime = clock();
    cout << "Test for G3: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    PrimMST<SparseGraph<double>, double> PrimMST4(g4);
    endTime = clock();
    cout << "Test for G4: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;
    cout << endl;

    // Test Kruskal MST
    cout << "Test Kruskal MST:" << endl;

    startTime = clock();
    KruskalMST<SparseGraph<double>, double> KruskalMST1(g1);
    endTime = clock();
    cout << "Test for G1: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    KruskalMST<SparseGraph<double>, double> KruskalMST2(g2);
    endTime = clock();
    cout << "Test for G2: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    KruskalMST<SparseGraph<double>, double> KruskalMST3(g3);
    endTime = clock();
    cout << "Test for G3: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;

    startTime = clock();
    KruskalMST<SparseGraph<double>, double> KruskalMST4(g4);
    endTime = clock();
    cout << "Test for G4: " << (double)(endTime - startTime) / CLOCKS_PER_SEC
         << " s." << endl;
  }

  return 0;
}