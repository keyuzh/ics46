// Digraph_SanityCheckTests.cpp
//
// ICS 46 Winter 2021
// Project #5: Rock and Roll Stops the Traffic
//
// This is a set of "sanity checking" unit tests for your Digraph
// implementation, provided primarily as a mechanism for ensuring
// that your implementation is compatible with the unit tests we'll
// be using to test your implementation during grading, as well as
// to provide simple examples of how each member function is supposed
// to behave.
//
// While you'll certainly want all of these tests to pass before you
// consider yourself done with Digraph, there are plenty of interesting
// cases that are not tested here.  The phrase "sanity checking" was
// chosen for a reason; this is just a cursory check to be sure that
// the basics are in place.  It'll be up to you to round out that
// testing with your own, more thorough testing.

#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <gtest/gtest.h>
#include "Digraph.hpp"


TEST(Digraph_SanityCheckTests, canConstructAndDestroy)
{
    Digraph<int, int> d1;
    Digraph<std::string, std::string> d2;
}


TEST(Digraph_SanityCheckTests, canCopyConstructToCompatibleType)
{
    Digraph<unsigned int, std::string> d1;
    Digraph<char, double> d2;

    Digraph<unsigned int, std::string> dd1{d1};
    Digraph<char, double> dd2{d2};
}

TEST(Digraph_SanityCheckTests, copyConstructDoesNotChangeOriginal)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 1);
    d1.addVertex(2, 2);
    d1.addEdge(1, 2, 4);

    Digraph<int, int> dd1{d1};
    dd1.addVertex(3, 3);
    dd1.addEdge(3, 1, 5);

    ASSERT_EQ(2, d1.vertexCount());
    ASSERT_EQ(1, d1.edgeCount());
    ASSERT_EQ(3, dd1.vertexCount());
    ASSERT_EQ(2, dd1.edgeCount());
    ASSERT_THROW(d1.removeEdge(3, 1), DigraphException);
    ASSERT_THROW(d1.removeVertex(3), DigraphException);
}

TEST(Digraph_SanityCheckTests, copyConstructDoesNotChangeCopy)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 1);
    d1.addVertex(2, 2);
    d1.addEdge(1, 2, 4);

    Digraph<int, int> dd1{d1};
    d1.addVertex(3, 3);
    d1.addEdge(3, 1, 5);

    ASSERT_EQ(3, d1.vertexCount());
    ASSERT_EQ(2, d1.edgeCount());
    ASSERT_EQ(2, dd1.vertexCount());
    ASSERT_EQ(1, dd1.edgeCount());
    ASSERT_THROW(dd1.removeEdge(3, 1), DigraphException);
    ASSERT_THROW(dd1.removeVertex(3), DigraphException);
}


TEST(Digraph_SanityCheckTests, canMoveConstructToCompatibleType)
{
    Digraph<int, int> d1;
    Digraph<std::string, std::string> d2;

    Digraph<int, int> dd1 = std::move(d1);
    Digraph<std::string, std::string> dd2 = std::move(d2);
}


TEST(Digraph_SanityCheckTests, canAssignToCompatibleType)
{
    Digraph<std::string, double> d1;
    Digraph<std::string, double> d2;

    Digraph<int, int> d3;
    Digraph<int, int> d4;

    d1 = d2;
    d3 = d4;
}

TEST(Digraph_SanityCheckTests, assignmentDoesNotChangeOriginal)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 1);
    d1.addVertex(2, 2);
    d1.addEdge(1, 2, 4);

    Digraph<int, int> dd1 = d1;
    dd1.addVertex(3, 3);
    dd1.addEdge(3, 1, 5);

    ASSERT_EQ(2, d1.vertexCount());
    ASSERT_EQ(1, d1.edgeCount());
    ASSERT_EQ(3, dd1.vertexCount());
    ASSERT_EQ(2, dd1.edgeCount());
    ASSERT_THROW(d1.removeEdge(3, 1), DigraphException);
    ASSERT_THROW(d1.removeVertex(3), DigraphException);
}

TEST(Digraph_SanityCheckTests, assignmentDoesNotChangeCopy)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 1);
    d1.addVertex(2, 2);
    d1.addEdge(1, 2, 4);

    Digraph<int, int> dd1 = d1;
    d1.addVertex(3, 3);
    d1.addEdge(3, 1, 5);

    ASSERT_EQ(3, d1.vertexCount());
    ASSERT_EQ(2, d1.edgeCount());
    ASSERT_EQ(2, dd1.vertexCount());
    ASSERT_EQ(1, dd1.edgeCount());
    ASSERT_THROW(dd1.removeEdge(3, 1), DigraphException);
    ASSERT_THROW(dd1.removeVertex(3), DigraphException);
}

TEST(Digraph_SanityCheckTests, assignmentRemovesOriginal)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 1);
    d1.addVertex(2, 2);
    d1.addEdge(1, 2, 4);
    d1.addEdge(2, 1, 5);

    Digraph<int, int> dd1;
    dd1.addVertex(3, 3);
    dd1.addVertex(4, 4);
    dd1.addEdge(3, 4, 5);

    dd1 = d1;

    ASSERT_EQ(2, dd1.vertexCount());
    ASSERT_EQ(2, dd1.edgeCount());
    ASSERT_THROW(dd1.removeEdge(3, 4), DigraphException);
    ASSERT_THROW(dd1.removeVertex(3), DigraphException);
}

TEST(Digraph_SanityCheckTests, canMoveAssignToCompatibleType)
{
    Digraph<std::string, double> d1;
    Digraph<std::string, double> d2;

    Digraph<int, int> d3;
    Digraph<int, int> d4;

    d1 = std::move(d2);
    d3 = std::move(d4);
}

TEST(Digraph_SanityCheckTests, emptyGraphDoesNotContainAnyVertex)
{
    Digraph<std::string, std::string> d1;
    ASSERT_EQ(0, d1.vertices().size());
}

TEST(Digraph_SanityCheckTests, emptyGraphDoesNotContainAnyEdge)
{
    Digraph<std::string, std::string> d1;
    ASSERT_EQ(0, d1.edges().size());
}

TEST(Digraph_SanityCheckTests, canGetAllVertexNumbers)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    std::vector<int> vertices = d1.vertices();

    ASSERT_EQ(3, vertices.size());

    std::sort(vertices.begin(), vertices.end());
    ASSERT_EQ(1, vertices[0]);
    ASSERT_EQ(2, vertices[1]);
    ASSERT_EQ(3, vertices[2]);
}


TEST(Digraph_SanityCheckTests, canGetAllEdges)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    std::vector<std::pair<int, int>> edges = d1.edges();

    ASSERT_EQ(3, edges.size());

    std::sort(edges.begin(), edges.end());

    ASSERT_EQ(1, edges[0].first);
    ASSERT_EQ(2, edges[0].second);

    ASSERT_EQ(1, edges[1].first);
    ASSERT_EQ(3, edges[1].second);

    ASSERT_EQ(2, edges[2].first);
    ASSERT_EQ(3, edges[2].second);
}


TEST(Digraph_SanityCheckTests, canGetAllEdgesForOneVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    std::vector<std::pair<int, int>> edges = d1.edges(2);

    ASSERT_EQ(1, edges.size());
    ASSERT_EQ(2, edges[0].first);
    ASSERT_EQ(3, edges[0].second);
}

TEST(Digraph_SanityCheckTests, canGetMultipleEdgesForOneVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    std::vector<std::pair<int, int>> edges = d1.edges(1);
    std::sort(edges.begin(), edges.end());
    ASSERT_EQ(2, edges.size());
    ASSERT_EQ(1, edges[0].first);
    ASSERT_EQ(2, edges[0].second);
    ASSERT_EQ(1, edges[1].first);
    ASSERT_EQ(3, edges[1].second);
}


TEST(Digraph_SanityCheckTests, cannotGetEdgesForNonExistentVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    ASSERT_THROW({ d1.edges(4); }, DigraphException);
}


TEST(Digraph_SanityCheckTests, canGetVertexInfoForOneVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    ASSERT_EQ("Example1", d1.vertexInfo(1));
    ASSERT_EQ("Example2", d1.vertexInfo(2));
    ASSERT_EQ("Example3", d1.vertexInfo(3));
}


TEST(Digraph_SanityCheckTests, cannotGetVertexInfoForNonExistentVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    ASSERT_THROW({ d1.vertexInfo(4); }, DigraphException);
}


TEST(Digraph_SanityCheckTests, canGetEdgeInfoForOneEdge)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    ASSERT_EQ("Edge1", d1.edgeInfo(1, 2));
    ASSERT_EQ("Edge2", d1.edgeInfo(1, 3));
    ASSERT_EQ("Edge3", d1.edgeInfo(2, 3));
}


TEST(Digraph_SanityCheckTests, cannotGetEdgeInfoForNonExistentVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    ASSERT_THROW({ d1.edgeInfo(1, 1); }, DigraphException);
    ASSERT_THROW({ d1.edgeInfo(1, 4); }, DigraphException);
}


TEST(Digraph_SanityCheckTests, cannotGetVertexInfoAfterRemovingVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.removeVertex(2);

    ASSERT_THROW({ d1.vertexInfo(2); }, DigraphException);
}

TEST(Digraph_SanityCheckTests, cannotGetEdgesAfterRemovingVertex)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "1to2");
    d1.addEdge(2, 3, "2to3");

    ASSERT_EQ(1, d1.edgeCount(1));
    ASSERT_EQ(1, d1.edgeCount(2));

    d1.removeVertex(2);

    ASSERT_EQ(2, d1.vertexCount());
    ASSERT_EQ(0, d1.edgeCount());
    ASSERT_THROW({ d1.edgeCount(2); }, DigraphException);
    ASSERT_EQ(0, d1.edgeCount(1));
    ASSERT_EQ(0, d1.edgeCount(3));
}


TEST(Digraph_SanityCheckTests, cannotGetEdgeInfoAfterRemovingEdge)
{
    Digraph<std::string, std::string> d1;
    d1.addVertex(1, "Example1");
    d1.addVertex(2, "Example2");
    d1.addVertex(3, "Example3");

    d1.addEdge(1, 2, "Edge1");
    d1.addEdge(1, 3, "Edge2");
    d1.addEdge(2, 3, "Edge3");

    d1.removeEdge(1, 3);

    ASSERT_THROW({ d1.edgeInfo(1, 3); }, DigraphException);
}

TEST(Digraph_SanityCheckTests, cannotAddExistingVertices)
{
    Digraph<int, int> d1;

    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
        ASSERT_EQ(i, d1.vertexCount());
    }
    for (int i = 1; i <= 10; ++i)
    {
        ASSERT_THROW(d1.addVertex(i, i), DigraphException);
    }
}

TEST(Digraph_SanityCheckTests, addingVerticesIncreasesVertexCount)
{
    Digraph<int, int> d1;

    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
        ASSERT_EQ(i, d1.vertexCount());
    }
}

TEST(Digraph_SanityCheckTests, cannotAddExistingEdges)
{
    Digraph<int, int> d1;

    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }

    for (int i = 2; i <= 10; ++i)
    {
        d1.addEdge(1, i, 100);
        ASSERT_EQ(i - 1, d1.edgeCount());
    }
    for (int i = 2; i <= 10; ++i)
    {
        ASSERT_THROW(d1.addEdge(1, i, 100), DigraphException);
    }
}

TEST(Digraph_SanityCheckTests, addingEdgesIncreasesEdgeCount)
{
    Digraph<int, int> d1;

    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }

    for (int i = 2; i <= 10; ++i)
    {
        d1.addEdge(1, i, 100);
        ASSERT_EQ(i - 1, d1.edgeCount());
    }
}


TEST(Digraph_SanityCheckTests, addingEdgesIncreasesEdgeCountFromVertex)
{
    Digraph<int, int> d1;

    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }

    for (int i = 2; i <= 10; ++i)
    {
        d1.addEdge(1, i, 100);
        ASSERT_EQ(i - 1, d1.edgeCount(1));
        ASSERT_EQ(0, d1.edgeCount(2));
    }
}

TEST(Digraph_SanityCheckTests, cannotRemoveNonExistingVertex)
{
    Digraph<int, int> d1;
    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }
    ASSERT_EQ(10, d1.vertexCount());
    for (int i = 1; i <= 10; ++i)
    {
        d1.removeVertex(i);
        ASSERT_THROW(d1.removeVertex(i), DigraphException);
    }
}

TEST(Digraph_SanityCheckTests, removeVertexDecreaseCount)
{
    Digraph<int, int> d1;
    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }
    ASSERT_EQ(10, d1.vertexCount());
    for (int i = 1; i <= 10; ++i)
    {
        d1.removeVertex(i);
        ASSERT_EQ(10-i, d1.vertexCount());
    }
}

TEST(Digraph_SanityCheckTests, cannotRemoveNonExistingEdge)
{
    Digraph<int, int> d1;
    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }
    for (int i = 2; i <= 10; ++i)
    {
        d1.addEdge(1, i, 100);
        ASSERT_EQ(i - 1, d1.edgeCount(1));
        ASSERT_EQ(0, d1.edgeCount(2));
    }

    for (int i = 10; i >= 2; i--)
    {
        d1.removeEdge(1, i);
        ASSERT_THROW(d1.removeEdge(1, i), DigraphException);
    }
}

TEST(Digraph_SanityCheckTests, removingEdgeDecreaseEdgeCount)
{
    Digraph<int, int> d1;
    for (int i = 1; i <= 10; ++i)
    {
        d1.addVertex(i, i);
    }
    for (int i = 2; i <= 10; ++i)
    {
        d1.addEdge(1, i, 100);
        ASSERT_EQ(i - 1, d1.edgeCount(1));
        ASSERT_EQ(i - 1, d1.edgeCount());
        ASSERT_EQ(0, d1.edgeCount(2));
    }
    for (int i = 10; i >= 2; i--)
    {
        d1.removeEdge(1, i);
        ASSERT_EQ(i - 2, d1.edgeCount(1));
        ASSERT_EQ(i - 2, d1.edgeCount());
    }
}


TEST(Digraph_SanityCheckTests, isStronglyConnectedWhenAllPossibleEdgesArePresent)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 10);
    d1.addVertex(2, 20);
    d1.addVertex(3, 30);

    d1.addEdge(1, 1, 50);
    d1.addEdge(1, 2, 50);
    d1.addEdge(1, 3, 50);
    d1.addEdge(2, 1, 50);
    d1.addEdge(2, 2, 50);
    d1.addEdge(2, 3, 50);
    d1.addEdge(3, 1, 50);
    d1.addEdge(3, 2, 50);
    d1.addEdge(3, 3, 50);

    ASSERT_TRUE(d1.isStronglyConnected());
}

TEST(Digraph_SanityCheckTests, notStronglyConnected)
{
    Digraph<int, int> d1;
    d1.addVertex(1, 10);
    d1.addVertex(2, 20);
    d1.addVertex(3, 30);
    d1.addVertex(4, 40);

    d1.addEdge(1, 1, 50);
    d1.addEdge(1, 2, 50);
    d1.addEdge(2, 1, 50);
    d1.addEdge(2, 2, 50);

    d1.addEdge(3, 3, 50);
    d1.addEdge(3, 4, 50);
    d1.addEdge(4, 3, 50);
    d1.addEdge(4, 4, 50);

    ASSERT_FALSE(d1.isStronglyConnected());
}

TEST(Digraph_SanityCheckTests, canFindShortestPathWhenNoChoicesAreToBeMade)
{
    Digraph<int, double> d1;
    d1.addVertex(1, 10);
    d1.addVertex(2, 20);
    d1.addVertex(3, 30);

    d1.addEdge(1, 2, 5.0);
    d1.addEdge(2, 3, 17.0);

    std::map<int, int> paths = d1.findShortestPaths(
        1,
        [](double edgeInfo)
        {
            return edgeInfo;
        });

    ASSERT_EQ(3, paths.size());

    ASSERT_TRUE(paths.find(1) != paths.end());
    ASSERT_TRUE(paths.find(2) != paths.end());
    ASSERT_TRUE(paths.find(3) != paths.end());

    ASSERT_EQ(1, paths[1]);
    ASSERT_EQ(1, paths[2]);
    ASSERT_EQ(2, paths[3]);
}

TEST(Digraph_SanityCheckTests, findShortestPathValueIsSelfWhenNeverReached)
{
    Digraph<int, double> d1;
    d1.addVertex(1, 10);
    d1.addVertex(2, 20);
    d1.addVertex(3, 30);

    std::map<int, int> paths = d1.findShortestPaths(
        1,
        [](double edgeInfo)
        {
            return edgeInfo;
        });

    ASSERT_EQ(3, paths.size());

    ASSERT_TRUE(paths.find(1) != paths.end());
    ASSERT_TRUE(paths.find(2) != paths.end());
    ASSERT_TRUE(paths.find(3) != paths.end());

    ASSERT_EQ(1, paths[1]);
    ASSERT_EQ(2, paths[2]);
    ASSERT_EQ(3, paths[3]);
}


namespace
{
    template <typename T>
    T distance(T edgeInfo)
    {
        return edgeInfo;
    }
}

TEST(Digraph_SanityCheckTests, canFindShortestPathWithLectureExample)
{
    // use the example in lecture notes 
    Digraph<int, int> d1;
    d1.addVertex(1, 10);
    d1.addVertex(2, 20);
    d1.addVertex(3, 30);
    d1.addVertex(4, 40);
    d1.addVertex(5, 50);
    d1.addVertex(6, 60);
    d1.addVertex(7, 70);

    d1.addEdge(1, 2, 8);
    d1.addEdge(1, 3, 6);
    d1.addEdge(2, 4, 10);
    d1.addEdge(3, 4, 15);
    d1.addEdge(3, 5, 9);
    d1.addEdge(4, 5, 14);
    d1.addEdge(4, 6, 4);
    d1.addEdge(5, 6, 13);
    d1.addEdge(5, 7, 17);
    d1.addEdge(6, 7, 7);

    std::map<int, int> paths = d1.findShortestPaths(
        1,
        [](int edgeInfo)
        {
            return edgeInfo;
        });

    ASSERT_EQ(7, paths.size());

    ASSERT_TRUE(paths.find(1) != paths.end());
    ASSERT_TRUE(paths.find(2) != paths.end());
    ASSERT_TRUE(paths.find(3) != paths.end());
    ASSERT_TRUE(paths.find(4) != paths.end());
    ASSERT_TRUE(paths.find(5) != paths.end());
    ASSERT_TRUE(paths.find(6) != paths.end());
    ASSERT_TRUE(paths.find(7) != paths.end());

    ASSERT_EQ(1, paths[1]);
    ASSERT_EQ(1, paths[2]);
    ASSERT_EQ(1, paths[3]);
    ASSERT_EQ(2, paths[4]);
    ASSERT_EQ(3, paths[5]);
    ASSERT_EQ(4, paths[6]);
    ASSERT_EQ(6, paths[7]);
}

TEST(Digraph_SanityCheckTests, canFindShortestPathWithAppExample)
{
    Digraph<int, double> d1;
    d1.addVertex(0, 10);
    d1.addVertex(1, 20);
    d1.addVertex(2, 30);
    d1.addVertex(5, 40);
    d1.addVertex(4, 50);
    d1.addVertex(10, 60);
    d1.addVertex(9, 70);
    d1.addVertex(12, 80);

    d1.addEdge(0, 12, 0.06/40.0);
    d1.addEdge(5, 4, 2.0/24.5);
    d1.addEdge(2, 1, 2.0/27.5);
    d1.addEdge(5, 2, 2.3/40.5);
    d1.addEdge(9, 0, 0.05/39.5);
    d1.addEdge(4, 10, 0.1/37.1);
    d1.addEdge(1, 0, 1.5/27.5);
    d1.addEdge(10, 9, 3.2/59.3);

    std::map<int, int> paths = d1.findShortestPaths(
        5,
        [](double edgeInfo)
        {
            return edgeInfo;
        });
    
    ASSERT_TRUE(paths.find(1) != paths.end());
    ASSERT_TRUE(paths.find(2) != paths.end());
    ASSERT_TRUE(paths.find(0) != paths.end());
    ASSERT_TRUE(paths.find(4) != paths.end());
    ASSERT_TRUE(paths.find(5) != paths.end());
    ASSERT_TRUE(paths.find(9) != paths.end());
    ASSERT_TRUE(paths.find(10) != paths.end());
    ASSERT_TRUE(paths.find(12) != paths.end());

    ASSERT_EQ(0, paths[12]);
    ASSERT_EQ(9, paths[0]);
    ASSERT_EQ(10, paths[9]);
    ASSERT_EQ(4, paths[10]);
    ASSERT_EQ(5, paths[4]);

    ASSERT_EQ(2, paths[1]);
    ASSERT_EQ(5, paths[2]);
}

