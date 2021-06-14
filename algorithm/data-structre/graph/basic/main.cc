#include "DenseGraph.h"
#include "RandomGraph.h"
#include "SparseGraph.h"

#include "ReadGraph.h"

#include "Component.h"

#include "Path.h"
#include "ShortestPath.h"

#include <ctime>
#include <iostream>

using namespace std;

int main() {

  {
    int N = 20;
    int M = 100;

    srand(time(NULL));

    // Sparse graph
    SparseGraph g1(N, false);
    for (int i = 0; i < M; i++) {
      int a = rand() % N;
      int b = rand() % N;
      g1.addEdge(a, b);
    }

    // O(E)
    for (int v = 0; v < N; v++) {
      cout << v << " : ";
      SparseGraph::adjIterator adj(g1, v);
      for (int w = adj.begin(); !adj.end(); w = adj.next())
        cout << w << " ";
      cout << endl;
    }

    cout << endl;

    // Dense graph
    DenseGraph g2(N, false);
    for (int i = 0; i < M; i++) {
      int a = rand() % N;
      int b = rand() % N;
      g2.addEdge(a, b);
    }

    // O(V^2)
    for (int v = 0; v < N; v++) {
      cout << v << " : ";
      DenseGraph::adjIterator adj(g2, v);
      for (int w = adj.begin(); !adj.end(); w = adj.next())
        cout << w << " ";
      cout << endl;
    }
  }

  {
    // 使用两种图的存储方式读取testG1.txt文件
    string filename = "testG1.txt";
    SparseGraph g1(13, false);
    ReadGraph<SparseGraph> readGraph1(g1, filename);
    cout << "test G1 in Sparse graph:" << endl;
    g1.show();

    cout << endl;

    DenseGraph g2(13, false);
    ReadGraph<DenseGraph> readGraph2(g2, filename);
    cout << "test G1 in Dense graph:" << endl;
    g2.show();

    cout << endl;

    // 使用两种图的存储方式读取testG2.txt文件
    filename = "testG2.txt";
    SparseGraph g3(6, false);
    ReadGraph<SparseGraph> readGraph3(g3, filename);
    cout << "test G2 in Sparse graph:" << endl;
    g3.show();

    cout << endl;

    DenseGraph g4(6, false);
    ReadGraph<DenseGraph> readGraph4(g4, filename);
    cout << "test G2 in Dense graph:" << endl;
    g4.show();
  }

  {
    // 随机生成一个图, 求其连通性
    int V = 100;
    int E = V * (V - 1) / 2 / 10;
    bool directed = false;

    SparseGraph g1 = SparseGraph(V, directed);
    RandomGraph<SparseGraph>(g1, V, E);

    Component<SparseGraph> component1(g1);
    cout << "Test Random Graph, Component Count: " << component1.count()
         << endl;
  }

  {
    // 读取testG1和testG2, 求其连通性
    // TestG1.txt
    string filename1 = "testG1.txt";
    SparseGraph g1 = SparseGraph(13, false);
    ReadGraph<SparseGraph> readGraph1(g1, filename1);
    Component<SparseGraph> component1(g1);
    cout << "TestG1.txt, Component Count: " << component1.count() << endl;

    cout << endl;

    // TestG2.txt
    string filename2 = "testG2.txt";
    SparseGraph g2 = SparseGraph(6, false);
    ReadGraph<SparseGraph> readGraph2(g2, filename2);
    Component<SparseGraph> component2(g2);
    cout << "TestG2.txt, Component Count: " << component2.count() << endl;
  }

  {
    // 测试深度优先遍历和广度优先遍历的寻路算法
    string filename = "testG2.txt";
    SparseGraph g = SparseGraph(6, false);
    ReadGraph<SparseGraph> readGraph(g, filename);
    g.show();
    cout << endl;

    Path<SparseGraph> dfs(g, 0);
    cout << "DFS : ";
    dfs.showPath(5);

    ShortestPath<SparseGraph> bfs(g, 0);
    cout << "BFS : ";
    bfs.showPath(5);
  }

  return 0;
}