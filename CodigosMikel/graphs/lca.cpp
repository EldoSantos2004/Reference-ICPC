class Tree
{
public:
  const int root = 0;

  const vector<vector<int>> &adj;
  const int log2dist;
  vector<int> par;
  vector<vector<int>> pow2ends;
  vector<int> depth;
  /** works with 0 indexed graph ** /
  /** check if graph is connected, if not, just iterate trough all nodes **/
  /** use DFS to calculate the depths and parents of each node */
  void process(int at, int prev)
  {
    depth[at] = depth[prev] + 1;
    for (int n : adj[at])
    {
      if (n != prev)
      {
        process(n, at);
        par[n] = at;
      }
    }
  }

public:
  Tree(const vector<vector<int>> &adj)
      : adj(adj), log2dist(std::ceil(std::log2(adj.size()))), par(adj.size()),
        pow2ends(par.size(), vector<int>(log2dist + 1)), depth(adj.size())
  {
    par[root] = depth[root] = -1;
    process(root, root);

    for (int n = 0; n < par.size(); n++)
    {
      pow2ends[n][0] = par[n];
    }
    for (int p = 1; p <= log2dist; p++)
    {
      for (int n = 0; n < par.size(); n++)
      {
        int halfway = pow2ends[n][p - 1];
        if (halfway == -1)
        {
          pow2ends[n][p] = -1;
        }
        else
        {
          pow2ends[n][p] = pow2ends[halfway][p - 1];
        }
      }
    }
  }

  /** @return the kth parent of node n */
  int kth_parent(int n, int k)
  {
    if (k > par.size())
    {
      return -1;
    }
    int at = n;
    for (int pow = 0; pow <= log2dist; pow++)
    {
      if ((k & (1 << pow)) != 0)
      {
        at = pow2ends[at][pow];
        if (at == -1)
        {
          break;
        }
      }
    }
    return at;
  }

  /** @return the LCA of nodes n1 and n2 */
  int lca(int n1, int n2)
  {
    if (depth[n1] < depth[n2])
    {
      return lca(n2, n1);
    }
    // lift n1 up to the same height as n2
    n1 = kth_parent(n1, depth[n1] - depth[n2]);
    if (n1 == n2)
    {
      return n2; // in this case, n2 is a direct ancestor of n1
    }

    // move the nodes up as long as they don't meet
    for (int i = log2dist; i >= 0; i--)
    {
      if (pow2ends[n1][i] != pow2ends[n2][i])
      {
        n1 = pow2ends[n1][i];
        n2 = pow2ends[n2][i];
      }
    }
    // at this point, the lca will be the parent of either node
    return pow2ends[n1][0];
  }
};
