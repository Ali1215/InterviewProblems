
#include <queue>
#include "dijkstra.h"


//comparision so heap considers the cost for ordering purposes
class mycomparison
{
public:
    bool operator()(const PIPIL &lhs, const PIPIL &rhs) const
    {

        return (lhs.second.second > rhs.second.second);
    }
};

void dijkstra(const WDigraph &graph, int startVertex,
              unordered_map<int, PIL> &searchTree)
{
    /*
    Description:  calls dijkstra's algorithm to construct
                    a searchTree with the shortest path from a start vertex
                    to different verticies. 

    args: 
            graph (WDigraph) = filled graph to search to find shortest path
            searchTree (unordered map) = empty unordered map that will be changed via reference to have shortest paths
            startVertex (int) = start vertex to begin searching from
    
    returns: none    */

    // All active fires stored as follows:
    // say an entry is (v, (u, d)), then there is a fire that started at u
    // and will burn the u->v edge, reaching v at time d
    priority_queue<PIPIL, std::vector<PIPIL>, mycomparison> fires;

    // at time 0, the startVertex burns, we use -1 to indicate there is
    // no "predecessor" of the startVertex
    fires.push(PIPIL(startVertex, PIL(-1, 0)));

    // while there is an active fire
    while (!fires.empty())
    {
        // find the fire that reaches its endpoint "v" earliest,
        // represented as an iterator into the list
        auto earliestFire = fires.top();

        // to reduce notation in the code below, this u,v,d agrees with
        // the intuition presented in the comment when PIPIL is typedef'ed
        int v = earliestFire.first, u = earliestFire.second.first, d = earliestFire.second.second;

        // remove this fire
        fires.pop();

        // if v is already "burned", there nothing to do
        if (searchTree.find(v) != searchTree.end())
        {
            continue;
        }

        // declare that v is "burned" at time d with a fire that spawned from u
        searchTree[v] = PIL(u, d);

        // now start fires from all edges exiting vertex v
        for (auto iter = graph.neighbours(v); iter != graph.endIterator(v); iter++)
        {
            int nbr = *iter;

            // the fire starts at v at time d and will reach nbr
            // at time d + (length of v->nbr edge)
            long long burn = d + graph.getCost(v, nbr);
            fires.push(PIPIL(nbr, PIL(v, burn)));
        }
    }
}