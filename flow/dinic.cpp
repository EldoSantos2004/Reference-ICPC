// Si en el grafo todos los vertices distintos
// de s y t cumplen que solo tienen una arista
// de entrada o una de salida la y dicha arista 
// tiene capacidad 1 entonces la complejidad es
// O(E sqrt(v))

// si todas las aristas tinen capacidad 1
// el algoritmo tiene complejidad O(E sqrt(E))

// to find min cut run bfs from source and find all vertices that can be reached
// edges between vertices that can be reached and the ones that cant are the min cut
struct FlowEdge {
  int v, u;
  long long cap, flow = 0;
  FlowEdge(int v, int u, long long cap) : v(v), u(u), cap(cap) {}
};

struct Dinic {
  const long long flow_inf = 1e18;
  vector<FlowEdge> edges;
  vector<vector<int>> adj;
  int n, m = 0;
  int s, t;
  vector<int> level, ptr;
  queue<int> q;

  Dinic(int n, int s, int t) : n(n), s(s), t(t) {
      adj.resize(n);
      level.resize(n);
      ptr.resize(n);
  }

  void add_edge(int v, int u, long long cap) {
      edges.emplace_back(v, u, cap);
      edges.emplace_back(u, v, 0);
      adj[v].push_back(m);
      adj[u].push_back(m + 1);
      m += 2;
  }

  bool bfs() {
      while (!q.empty()) {
          int v = q.front();
          q.pop();
          for (int id : adj[v]) {
              if (edges[id].cap - edges[id].flow < 1)
                  continue;
              if (level[edges[id].u] != -1)
                  continue;
              level[edges[id].u] = level[v] + 1;
              q.push(edges[id].u);
          }
      }
      return level[t] != -1;
  }

  long long dfs(int v, long long pushed) {
      if (pushed == 0)
          return 0;
      if (v == t)
          return pushed;
      for (int& cid = ptr[v]; cid < (int)adj[v].size(); cid++) {
          int id = adj[v][cid];
          int u = edges[id].u;
          if (level[v] + 1 != level[u] || edges[id].cap - edges[id].flow < 1)
              continue;
          long long tr = dfs(u, min(pushed, edges[id].cap - edges[id].flow));
          if (tr == 0)
              continue;
          edges[id].flow += tr;
          edges[id ^ 1].flow -= tr;
          return tr;
      }
      return 0;
  }

  long long flow() {
      long long f = 0;
      while (true) {
          fill(level.begin(), level.end(), -1);
          level[s] = 0;
          q.push(s);
          if (!bfs())
              break;
          fill(ptr.begin(), ptr.end(), 0);
          while (long long pushed = dfs(s, flow_inf)) {
              f += pushed;
          }
      }
      return f;
  }


  vector<pair<int, int>> minCut(){
    vector<pair<int, int>> ans;
    queue<int> q;
    q.push(s);
    vector<bool> vis(n, 0);
    while((int)q.size()){
      int cur = q.front();
      q.pop();
      vis[cur] = 1;
      for(int id: adj[cur]){
        if(edges[id].cap - edges[id].flow <= 0) continue;
        if(vis[edges[id].u]) continue;
        vis[edges[id].u] = 1;
        q.push(edges[id].u);
      }
    }
    for(auto edge: edges){
      if(vis[edge.v] && !vis[edge.u] && edge.flow > 0) {
        ans.push_back({edge.v, edge.u});
      }
    }
    return ans;
  }

};
