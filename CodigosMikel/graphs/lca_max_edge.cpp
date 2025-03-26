class Tree //if lca needed just copy lca and kth_parent functions from lca.cpp or change return from max_edge_cost function
{
private:
  const int root = 0;
 
  const vector<vector<int>> &adj;
  const vector <vector<int>> &weight;
  const int log2dist;
  vector<int> par;
  vector<int> edgepar;
  vector<vector<int>> pow2ends;
  vector<vector<int>> maxedge;
  vector<int> depth;
 
  /** use DFS to calculate the depths and parents of each node */
  void process(int at, int prev)
  {
    int cont = 0;
    depth[at] = depth[prev] + 1;
    for (int n : adj[at])
    {
      if (n != prev)
      {
        process(n, at);
        par[n] = at;
        edgepar[n] = weight[at][cont];
      }
      cont++;
    }
  }
 
public:
  Tree(const vector<vector<int>> &adj, const vector <vector<int>> &weight)
      : adj(adj), weight(weight), log2dist(std::ceil(std::log2(adj.size()))), par(adj.size()), edgepar(adj.size()),
        pow2ends(par.size(), vector<int>(log2dist + 1)), maxedge(par.size(), vector <int>(log2dist + 1)), depth(adj.size())
  {
    par[root] = depth[root] = -1;
    edgepar[root] = 0;
    process(root, root);
 
    for (int n = 0; n < par.size(); n++)
    {
      pow2ends[n][0] = par[n];
      maxedge[n][0] = edgepar[n];
    }
    for (int p = 1; p <= log2dist; p++)
    {
      for (int n = 0; n < par.size(); n++)
      {
        int halfway = pow2ends[n][p - 1];
        if (halfway == -1)
        {
          pow2ends[n][p] = -1;
          maxedge[n][p] = -1;
        }
        else
        {
          pow2ends[n][p] = pow2ends[halfway][p - 1];
          maxedge[n][p] = max(maxedge[n][p - 1], maxedge[halfway][p - 1]);
        }
      }
    }
  }
 
  /** @return the kth parent of node n with max edge cost */
  pair <int, int> kth_parent_with_max_edge(int n, int k)
  {
    if (k > par.size())
    {
      pair <int, int> temp;
      temp.first = -1;
      temp.second = 0;
      return temp;
    }
    int at = n, maxcost = 0;
    for (int pot = 0; pot <= log2dist; pot++)
    {
      if ((k & (1 << pot)) != 0)
      {
        maxcost = max(maxedge[at][pot], maxcost);
        at = pow2ends[at][pot];
        if (at == -1)
        {
          break;
        }
      }
    }
    pair <int, int> ans;
    ans.first = at;
    ans.second = maxcost;
    return ans;
  }
 
 
  int max_edge_cost(int n1, int n2)
  {
    if (depth[n1] < depth[n2])
    {
      return max_edge_cost(n2, n1);
    }
    int maxcost;
    // lift n1 up to the same height as n2 and find max edge of lifting
    pair <int, int> temp = kth_parent_with_max_edge(n1, depth[n1] - depth[n2]);
    n1 = temp.first;
    maxcost = temp.second;
    if (n1 == n2)
    {
      return maxcost; // in this case, n2 is a direct ancestor of n1, return maxcost
    }
 
    // move the nodes up as long as they don't meet
    for (int i = log2dist; i >= 0; i--)
    {
      if (pow2ends[n1][i] != pow2ends[n2][i])
      {
        maxcost = max(maxcost, maxedge[n1][i]);
        n1 = pow2ends[n1][i];
        maxcost = max(maxcost, maxedge[n2][i]);
        n2 = pow2ends[n2][i];
      }
    }
    maxcost = max(maxcost, maxedge[n1][0]);
    maxcost = max(maxcost, maxedge[n2][0]);
    // at this point, the lca will be the parent of either node
    return maxcost;
  }
};
