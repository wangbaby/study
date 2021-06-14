图论

graph theory

节点：vertex 边: edge

用于：
- 交通运输
- 社交网络
- 互联网
- 工作安排
- 脑区活动
- 程序状态执行

分类

无向图（undirected graph) 有向图(directed graph)

无权图 (unweighted graph) 有权图(weighted graph)

图的表示

邻接矩阵: adjacency matrix  用于稠密图 比如完全图  
邻接表：adjacency lists 用于稀疏图

遍历邻边： 邻接表比邻接矩阵高效

图的深度优先遍历

DFS（depth first search）

- 图中连通分量的个数
- 图中两个节点是否连接
- 图中两个节点之间是否有路径

复杂度：
- 稀疏图 邻接表 O(V+E)
- 稠密图 邻接矩阵 O(V^2)

图的广度优先遍历

BFS(breadth first search)
	
无权图的最短路径

复杂度：
- 稀疏图 邻接表 O(V+E)
- 稠密图 邻接矩阵 O(V^2)

dijkstra 单源最短路径算法
前提：图中不能负权边
复杂度：Elog(V)

bellman-ford 单源最短路径算法
处理负权边
拥有负权环，就没有最短路径

bellman-ford可以判断图中是否有负权环

复杂度O(EV)

带权图

最小生成树

针对 带权无向图 连通图
找v-1条边 连接v个顶点 使总权值最小
- 电缆设计
- 网络设计
- 电路设计

切分定理
cut property
把图中的结点分为两部分，成为一个切分
如果一个边的两个端点， 属于切分不同的两边， 这个边称为横切边 crossing edge

切分定理：给定任意切分，横切边中权值最小的边必定属于最小生成树。

lazy prim
使用最小堆
时间复杂度 Elog(E)

prim
使用最小索引堆
时间复杂度 Elog(V)

kruskal
使用并查集快速判断环
时间复杂度 Elog(E)