// Digraph.hpp
//
// ICS 46 Winter 2021
// Project #5: Rock and Roll Stops the Traffic
//
// This header file declares a class template called Digraph, which is
// intended to implement a generic directed graph.  The implementation
// uses the adjacency lists technique, so each vertex stores a linked
// list of its outgoing edges.
//
// Along with the Digraph class template is a class DigraphException
// and a couple of utility structs that aren't generally useful outside
// of this header file.
//
// In general, directed graphs are all the same, except in the sense
// that they store different kinds of information about each vertex and
// about each edge; these two types are the type parameters to the
// Digraph class template.

#ifndef DIGRAPH_HPP
#define DIGRAPH_HPP

#include <exception>
#include <functional>
#include <list>
#include <map>
#include <utility>
#include <vector>
#include <set>
#include <iostream>
#include <cmath>
#include <queue>



// DigraphExceptions are thrown from some of the member functions in the
// Digraph class template, so that exception is declared here, so it
// will be available to any code that includes this header file.

class DigraphException : public std::runtime_error
{
public:
    DigraphException(const std::string& reason);
};


inline DigraphException::DigraphException(const std::string& reason)
    : std::runtime_error{reason}
{
}



// A DigraphEdge lists a "from vertex" (the number of the vertex from which
// the edge points), a "to vertex" (the number of the vertex to which the
// edge points), and an EdgeInfo object.  Because different kinds of Digraphs
// store different kinds of edge information, DigraphEdge is a struct template.

template <typename EdgeInfo>
struct DigraphEdge
{
    int fromVertex;
    int toVertex;
    EdgeInfo einfo;
};



// A DigraphVertex includes two things: a VertexInfo object and a list of
// its outgoing edges.  Because different kinds of Digraphs store different
// kinds of vertex and edge information, DigraphVertex is a struct template.

template <typename VertexInfo, typename EdgeInfo>
struct DigraphVertex
{
    VertexInfo vinfo;
    std::list<DigraphEdge<EdgeInfo>> edges;
};



// Digraph is a class template that represents a directed graph implemented
// using adjacency lists.  It takes two type parameters:
//
// * VertexInfo, which specifies the kind of object stored for each vertex
// * EdgeInfo, which specifies the kind of object stored for each edge
//
// You'll need to implement the member functions declared here; each has a
// comment detailing how it is intended to work.
//
// Each vertex in a Digraph is identified uniquely by a "vertex number".
// Vertex numbers are not necessarily sequential and they are not necessarily
// zero- or one-based.

template <typename VertexInfo, typename EdgeInfo>
class Digraph
{
public:
    // The default constructor initializes a new, empty Digraph so that
    // contains no vertices and no edges.
    Digraph();

    // The copy constructor initializes a new Digraph to be a deep copy
    // of another one (i.e., any change to the copy will not affect the
    // original).
    Digraph(const Digraph& d);

    // The move constructor initializes a new Digraph from an expiring one.
    Digraph(Digraph&& d) noexcept;

    // The destructor deallocates any memory associated with the Digraph.
    ~Digraph() noexcept;

    // The assignment operator assigns the contents of the given Digraph
    // into "this" Digraph, with "this" Digraph becoming a separate, deep
    // copy of the contents of the given one (i.e., any change made to
    // "this" Digraph afterward will not affect the other).
    Digraph& operator=(const Digraph& d);

    // The move assignment operator assigns the contents of an expiring
    // Digraph into "this" Digraph.
    Digraph& operator=(Digraph&& d) noexcept;

    // vertices() returns a std::vector containing the vertex numbers of
    // every vertex in this Digraph.
    std::vector<int> vertices() const;

    // edges() returns a std::vector of std::pairs, in which each pair
    // contains the "from" and "to" vertex numbers of an edge in this
    // Digraph.  All edges are included in the std::vector.
    std::vector<std::pair<int, int>> edges() const;

    // This overload of edges() returns a std::vector of std::pairs, in
    // which each pair contains the "from" and "to" vertex numbers of an
    // edge in this Digraph.  Only edges outgoing from the given vertex
    // number are included in the std::vector.  If the given vertex does
    // not exist, a DigraphException is thrown instead.
    std::vector<std::pair<int, int>> edges(int vertex) const;

    // vertexInfo() returns the VertexInfo object belonging to the vertex
    // with the given vertex number.  If that vertex does not exist, a
    // DigraphException is thrown instead.
    VertexInfo vertexInfo(int vertex) const;

    // edgeInfo() returns the EdgeInfo object belonging to the edge
    // with the given "from" and "to" vertex numbers.  If either of those
    // vertices does not exist *or* if the edge does not exist, a
    // DigraphException is thrown instead.
    EdgeInfo edgeInfo(int fromVertex, int toVertex) const;

    // addVertex() adds a vertex to the Digraph with the given vertex
    // number and VertexInfo object.  If there is already a vertex in
    // the graph with the given vertex number, a DigraphException is
    // thrown instead.
    void addVertex(int vertex, const VertexInfo& vinfo);

    // addEdge() adds an edge to the Digraph pointing from the given
    // "from" vertex number to the given "to" vertex number, and
    // associates with the given EdgeInfo object with it.  If one
    // of the vertices does not exist *or* if the same edge is already
    // present in the graph, a DigraphException is thrown instead.
    void addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo);

    // removeVertex() removes the vertex (and all of its incoming
    // and outgoing edges) with the given vertex number from the
    // Digraph.  If the vertex does not exist already, a DigraphException
    // is thrown instead.
    void removeVertex(int vertex);

    // removeEdge() removes the edge pointing from the given "from"
    // vertex number to the given "to" vertex number from the Digraph.
    // If either of these vertices does not exist *or* if the edge
    // is not already present in the graph, a DigraphException is
    // thrown instead.
    void removeEdge(int fromVertex, int toVertex);

    // vertexCount() returns the number of vertices in the graph.
    int vertexCount() const noexcept;

    // edgeCount() returns the total number of edges in the graph,
    // counting edges outgoing from all vertices.
    int edgeCount() const noexcept;

    // This overload of edgeCount() returns the number of edges in
    // the graph that are outgoing from the given vertex number.
    // If the given vertex does not exist, a DigraphException is
    // thrown instead.
    int edgeCount(int vertex) const;

    // isStronglyConnected() returns true if the Digraph is strongly
    // connected (i.e., every vertex is reachable from every other),
    // false otherwise.
    bool isStronglyConnected() const;

    // findShortestPaths() takes a start vertex number and a function
    // that takes an EdgeInfo object and determines an edge weight.
    // It uses Dijkstra's Shortest Path Algorithm to determine the
    // shortest paths from the start vertex to every other vertex
    // in the graph.  The result is returned as a std::map<int, int>
    // where the keys are vertex numbers and the value associated
    // with each key k is the precedessor of that vertex chosen by
    // the algorithm.  For any vertex without a predecessor (e.g.,
    // a vertex that was never reached, or the start vertex itself),
    // the value is simply a copy of the key.
    std::map<int, int> findShortestPaths(
        int startVertex,
        std::function<double(const EdgeInfo&)> edgeWeightFunc) const;


private:
    // Add whatever member variables you think you need here.  One
    // possibility is a std::map where the keys are vertex numbers
    // and the values are DigraphVertex<VertexInfo, EdgeInfo> objects.
    std::map<int, DigraphVertex<VertexInfo, EdgeInfo>> adjList;

    struct Dijkstra
    {
        bool k;
        double d;
        int p;
    };


    // You can also feel free to add any additional member functions
    // you'd like (public or private), so long as you don't remove or
    // change the signatures of the ones that already exist.
    bool vertexExists(int vertex) const;
    bool edgeExists(const std::list<DigraphEdge<EdgeInfo>>& edges, int from, int to) const;
    EdgeInfo findEdge(const std::list<DigraphEdge<EdgeInfo>>& edges, int from, int to) const;
    void eraseEdge(std::list<DigraphEdge<EdgeInfo>>& edges, int from, int to);
    bool canReachEveryVertex(int vertex) const;
    void DFTr(std::set<int>& reached, int vertex) const;
};



// You'll need to implement the member functions below.  There's enough
// code in place to make them compile, but they'll all need to do the
// correct thing instead.

template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph()
    : adjList{}
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(const Digraph& d)
    : adjList{d.adjList}
{
    // std::cout << "this vertex: ";
    // for (auto& vertex : adjList)
    // {
    //     std::cout << &(vertex.first) << " ";
    // }
    // std::cout << std::endl << "this list: ";
    // for (auto& vertex : adjList)
    // {
    //     std::cout << &(vertex.second.edges) << " ";
    // }
    // std::cout << std::endl;
    // std::cout << "other vertex: ";
    // for (auto& vertex : d.adjList)
    // {
    //     std::cout << &(vertex.first) << " ";
    // }
    // std::cout << std::endl << "other list: ";
    // for (auto& vertex : d.adjList)
    // {
    //     std::cout << &(vertex.second.edges) << " ";
    // }
    // std::cout << std::endl;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::Digraph(Digraph&& d) noexcept
    : adjList{}
{
    std::swap(adjList, d.adjList);
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>::~Digraph() noexcept
{
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(const Digraph& d)
{
    if (this != &d)
    {
        adjList = d.adjList;
    }
    
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
Digraph<VertexInfo, EdgeInfo>& Digraph<VertexInfo, EdgeInfo>::operator=(Digraph&& d) noexcept
{
    if (this != &d)
    {
        std::swap(adjList, d.adjList);
    }
    
    return *this;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<int> Digraph<VertexInfo, EdgeInfo>::vertices() const
{
    std::vector<int> v;
    for (auto vertex : adjList)
    {
        v.push_back(vertex.first);
    }
    return v;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges() const
{
    std::vector<std::pair<int, int>> result;
    for (auto vertex : adjList)
    {
        std::vector<std::pair<int, int>> vertexEdge = edges(vertex.first);
        result.insert(result.end(), vertexEdge.begin(), vertexEdge.end());
    }
    return result;
}


template <typename VertexInfo, typename EdgeInfo>
std::vector<std::pair<int, int>> Digraph<VertexInfo, EdgeInfo>::edges(int vertex) const
{
    std::vector<std::pair<int, int>> edgeVector;
    try
    {
        std::list<DigraphEdge<EdgeInfo>> edgeList = adjList.at(vertex).edges;
        for (auto& e : edgeList)
        {
            edgeVector.push_back({e.fromVertex, e.toVertex});
        }
    }
    catch(const std::out_of_range& e)
    {
        throw DigraphException{"vertex not found"};
    }
    return edgeVector;
}


template <typename VertexInfo, typename EdgeInfo>
VertexInfo Digraph<VertexInfo, EdgeInfo>::vertexInfo(int vertex) const
{
    // if (!vertexExists(vertex))
    // {
    //     throw DigraphException{"vertex not found"};
    // }
    // return adjList.at(vertex).vinfo;
    try
    {
        return adjList.at(vertex).vinfo;
    }
    catch(const std::out_of_range& e)
    {
        throw DigraphException{"vertex not found"};
    }
}


template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::edgeInfo(int fromVertex, int toVertex) const
{
    if (!(vertexExists(fromVertex) && vertexExists(toVertex)))
    {
        throw DigraphException{"One vertex does not exist"};
    }
    return findEdge(adjList.at(fromVertex).edges, fromVertex, toVertex);
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addVertex(int vertex, const VertexInfo& vinfo)
{
    if (vertexExists(vertex))
    {
        // vertex found
        throw DigraphException{"vertex already exists"};
    }
    adjList[vertex] = DigraphVertex<VertexInfo, EdgeInfo>{vinfo, std::list<DigraphEdge<EdgeInfo>>{}};
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::addEdge(int fromVertex, int toVertex, const EdgeInfo& einfo)
{
    if (!(vertexExists(fromVertex) && vertexExists(toVertex)))
    {
        throw DigraphException{"One vertex does not exist"};
    }
    if (edgeExists(adjList.at(fromVertex).edges, fromVertex, toVertex))
    {
        throw DigraphException{"Edge already exists"};
    }        
    adjList.at(fromVertex).edges.push_back(DigraphEdge<EdgeInfo>{fromVertex, toVertex, einfo});
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeVertex(int vertex)
{
    if (!vertexExists(vertex))
    {
        throw DigraphException{"vertex does not exist"};
    }
    // remove ingoing edges first
    for (auto& v : adjList)
    {
        try
        {
            removeEdge(v.first, vertex);
        }
        catch(const DigraphException& e)
        {
            continue;
        }
    }
    // remove outgoing edges
    adjList.erase(vertex);
}


template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::removeEdge(int fromVertex, int toVertex)
{
    if (!(vertexExists(fromVertex) && vertexExists(toVertex)))
    {
        throw DigraphException{"One vertex does not exist"};
    }
    eraseEdge(adjList.at(fromVertex).edges, fromVertex, toVertex);
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::vertexCount() const noexcept
{
    return adjList.size();
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount() const noexcept
{
    int count{0};
    for (auto vertex : adjList)
    {
        count += edgeCount(vertex.first);
    }
    return count;
}


template <typename VertexInfo, typename EdgeInfo>
int Digraph<VertexInfo, EdgeInfo>::edgeCount(int vertex) const
{
    try
    {
        return adjList.at(vertex).edges.size();
    }
    catch(const std::out_of_range& e)
    {
        throw DigraphException{"vertex not found"};
    }
}


template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::isStronglyConnected() const
{
    for (auto& vertex : adjList)
    {
        if (!canReachEveryVertex(vertex.first))
        {
            return false;
        }
    }
    return true;
}


template <typename VertexInfo, typename EdgeInfo>
std::map<int, int> Digraph<VertexInfo, EdgeInfo>::findShortestPaths(
    int startVertex,
    std::function<double(const EdgeInfo&)> edgeWeightFunc) const
{
    // use a std::map to store the table for Dijkstra Algorithm
    std::map<int, Dijkstra> dijk;
    // initialize values in the table
    for (auto& vertex : vertices())
    {
        // set dv to inf or 0
        double dTemp = (vertex == startVertex) ? 0 : std::numeric_limits<double>::infinity();
        // we use the vertex number itself to represent none or unknown
        dijk[vertex] = Dijkstra{false, dTemp, vertex};
    }
    // empty priority queue; first elemet is priority, the second element is vertex
    std::priority_queue<std::pair<double, int>, std::vector<std::pair<double, int>>, 
                        std::greater<std::pair<double, int>>> pq;
    // enqueue start vertex with priority 0
    pq.push({0, startVertex});
    while (!pq.empty())
    {
        // get the vertex with smallest priority
        int v = pq.top().second;
        // dequeue it
        pq.pop();
        if (!dijk[v].k)  // if kv is false
        {
            dijk[v].k = true;  // set it to true
            // for each vertex w such that edge v → w exists
            for (auto& e : edges(v))
            {
                int w = e.second;        // vertex w
                double& dw = dijk[w].d;  // dw
                // dv + C(v, w)
                double dvPlusC = dijk[v].d + edgeWeightFunc(edgeInfo(v, w));
                if (dw > dvPlusC)        // if (dw > dv + C(v, w))
                {
                    dw = dvPlusC;        // dw = dv + C(v, w)
                    dijk[w].p = v;       // pw = v
                    pq.push({dw, w});    // enqueue w into pq with priority dw
                }
            }
        }
    }
    // after Dijkstra Algo, construct std::map for return value from table
    std::map<int, int> result;
    for (auto& i : dijk) 
    {
        result[i.first] = i.second.p;
    }
    return result;
}

template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::vertexExists(int vertex) const
{
    return (adjList.find(vertex) != adjList.end());
}

template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::edgeExists(const std::list<DigraphEdge<EdgeInfo>>& edges, int from, int to) const
{
    for (auto& e : edges)
    {
        if (e.fromVertex == from && e.toVertex == to)
        {
            return true;
        }
    }
    return false;
}

template <typename VertexInfo, typename EdgeInfo>
EdgeInfo Digraph<VertexInfo, EdgeInfo>::findEdge(const std::list<DigraphEdge<EdgeInfo>>& edges, int from, int to) const
{
    for (auto& e : edges)
    {
        if (e.fromVertex == from && e.toVertex == to)
        {
            return e.einfo;
        }
    }
    throw DigraphException{"Edge does not exist"};
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::eraseEdge(std::list<DigraphEdge<EdgeInfo>>& edges, int from, int to)
{
    for (auto e = edges.begin(); e != edges.end(); e++)
    {
        if (e->fromVertex == from && e->toVertex == to)
        {
            // found the edge
            edges.erase(e);
            return;
        }
    }
    throw DigraphException{"Edge does not exist"};
}

template <typename VertexInfo, typename EdgeInfo>
bool Digraph<VertexInfo, EdgeInfo>::canReachEveryVertex(int vertex) const
{
    std::set<int> reached;
    // do DFT on the vertex
    DFTr(reached, vertex);
    return (reached.size() == vertexCount());
}

template <typename VertexInfo, typename EdgeInfo>
void Digraph<VertexInfo, EdgeInfo>::DFTr(std::set<int>& reached, int vertex) const
{
    std::pair<std::set<int>::iterator, bool> success = reached.insert(vertex);
    if (success.second)
    {
        // vertex not visited, do recursive DFT from here
        std::vector<std::pair<int, int>> edgeFromVertex = edges(vertex);
        for (auto& e : edgeFromVertex)
        {
            DFTr(reached, e.second);
        }
    }
}

#endif // DIGRAPH_HPP

