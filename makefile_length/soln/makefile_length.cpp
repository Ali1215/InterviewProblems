// Remember, style matters!
/*
Name: Ali Muneer
Student ID: 1615694
CMPUT 275; Winter 2021
Weekly Exercise 7: Makefile Length*/
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <set>
#include <string>
#include <iostream>
using namespace std;

//global variable to map every string to an integer in the tree
unordered_map<string, int> mapping;
int ans = 0;

//Lines 20-117 is just the graph implementation from class
class Digraph
{
public:
  // No constructor or destructor are necessary this time.
  // A new instance will be an empty graph with no nodes.

  // add a vertex, does nothing if it already exists
  void addVertex(int v);

  // adds an edge, creating the vertices if they do not exist
  // if the edge already existed, does nothing
  void addEdge(int u, int v);

  // returns true if and only if v is a vertex in the graph
  bool isVertex(int v);

  // returns true if and only if (u,v) is an edge in the graph
  // will certainly return false if neither vertex is in the graph
  bool isEdge(int u, int v);

  // returns a const iterator to the neighbours of v
  unordered_set<int>::const_iterator neighbours(int v) const;

  // returns a const iterator to the end of v's neighour set
  unordered_set<int>::const_iterator endIterator(int v) const;

  // return the number of outgoing neighbours of v
  int numNeighbours(int v);

  // returns the number of nodes
  int size();

  // return a vector with all vertices
  vector<int> vertices();

  // returns true if 'walk' represents a walk on this graph
  // A walk is a sequence of vertices (perhaps with repeated vertices)
  // v0, v1, . . . , vk where (vi,vi+1) is an edge for each 0 <= i < k.
  // the length of a walk is the number of edges traversed

  // returns true if 'path' represents a path on this graph
  // a path is a walk with no repeated vertices

private:
  unordered_map<int, unordered_set<int>> nbrs;
};

void Digraph::addVertex(int v)
{
  // If it already exists, does nothing.
  // Otherwise, adds v with an empty adjacency set.
  nbrs[v];
}

void Digraph::addEdge(int u, int v)
{
  addVertex(v);
  nbrs[u].insert(v); // will also add u to nbrs if it was not there already
}

bool Digraph::isVertex(int v)
{
  return nbrs.find(v) != nbrs.end();
}

bool Digraph::isEdge(int u, int v)
{
  // check that u is in the keys and that it's associated set contains v
  return nbrs.find(u) != nbrs.end() && nbrs[u].find(v) != nbrs[u].end();
}

unordered_set<int>::const_iterator Digraph::neighbours(int v) const
{
  // this will crash the program if v is not a vertex
  return nbrs.find(v)->second.begin();
}

unordered_set<int>::const_iterator Digraph::endIterator(int v) const
{
  // this will crash the program if v is not a vertex
  return nbrs.find(v)->second.end();
}

int Digraph::numNeighbours(int v)
{
  // this will crash the program if v is not a vertex
  return nbrs.find(v)->second.size();
}

int Digraph::size()
{
  return nbrs.size();
}

vector<int> Digraph::vertices()
{
  vector<int> v;
  for (unordered_map<int, unordered_set<int>>::const_iterator it = nbrs.begin();
       it != nbrs.end(); it++)
  {
    v.push_back(it->first);
  }
  return v;
}

void dfs(int node, Digraph &graph, int dp[], bool vis[])
{
  /*
    Description:  Recursively searches through graph, calculating the deepest depth reached

    args: node  = current location within the tree
          graph = instance of directed graph class
          dp    = array of the depth of each node
          vis   = array of visited nodes 
    
    returns: none
  */
  // Mark as visited
  vis[node] = true;

  // Traverse for all its children
  for (auto iter = graph.neighbours(node); iter != graph.endIterator(node); iter++)
  {
    int nbr = *iter;

    //search neighbor if not visited
    if (!vis[nbr])
    {
      dfs(nbr, graph, dp, vis);
    }
    //update max depth of current node if 1+neighbors depth is higher
    dp[node] = max(dp[node], 1 + dp[nbr]);
  }
  //update max depth if it has been beaten
  ans = max(ans, dp[node]);
}

int findLongestPath(Digraph &graph, int n)
{
  /*
    Description:  Initializes visited and depth arrays, and calls depth search
                  on every unvisited vertex

    args: num_rows  = number of rows of new matrix
          num_columns = number of columns of new matrix
          init      = initial value to set all matrix elements to
    
    returns: none
   */
  // Depth array and visited array
  bool vis[n] = {false};
  int dp[n] = {0};

  // Call DFS for every unvisited vertex
  for (int i = 0; i < n; i++)
  {
    if (!vis[i])
      dfs(i, graph, dp, vis);
  }

  return ans;
}

int main()
{
  int numTargets;
  int numDepends;
  int n = 0;

  string target, depend;
  Digraph graph;

  cin >> numTargets;
  for (int i = 0; i < numTargets; i++)
  {
    cin >> numDepends >> target;
    target.pop_back(); //remove colon

    //see if it has already been mapped to an integer
    auto f = mapping.find(target);
    if (f == mapping.end())
    {
      mapping[target] = n;
      n++; //map the target to a unique integer for the graph
    }
    for (int j = 0; j < numDepends; j++)
    {
      cin >> depend;

      //see if it has already been mapped to an integer
      auto w = mapping.find(depend);
      if (w == mapping.end())
      {
        mapping[depend] = n;
        n++; //map dependancy to an integer
      }
      graph.addEdge(mapping[target], mapping[depend]); //add edge based on reps
    }
  }

  cout << findLongestPath(graph, n) << endl;

  return 0;
}