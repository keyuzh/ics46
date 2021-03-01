#include <gtest/gtest.h>
#include <array>
#include <string>
#include <vector>
#include "problem4.hpp"


TEST(DisjointSetForestTests, whenConstructingWithInitializerList_AllElementsAreInOrder)
{
    DisjointSetForest<std::string> forest{"aaa", "bbb", "ccc", "ddd", "eee"};

    EXPECT_EQ("aaa", forest.at(0));
    EXPECT_EQ(0, forest.indexOf("aaa"));

    EXPECT_EQ("bbb", forest.at(1));
    EXPECT_EQ(1, forest.indexOf("bbb"));

    EXPECT_EQ("ccc", forest.at(2));
    EXPECT_EQ(2, forest.indexOf("ccc"));

    EXPECT_EQ("ddd", forest.at(3));
    EXPECT_EQ(3, forest.indexOf("ddd"));

    EXPECT_EQ("eee", forest.at(4));
    EXPECT_EQ(4, forest.indexOf("eee"));
}


TEST(DisjointSetForestTests, whenConstructingWithInitializerList_ElementCountIsCorrect)
{
    DisjointSetForest<int> forest{9, 3, -6, 0};

    EXPECT_EQ(4, forest.elementCount());
}


TEST(DisjointSetForestTests, whenConstructingWithInitializerList_AllElementsAreInSeparateSets)
{
    DisjointSetForest<std::string> forest{"x", "y", "z", "w"};

    EXPECT_EQ(4, forest.setCount());
    EXPECT_EQ(0, forest.findRoot("x"));
    EXPECT_EQ(1, forest.findRoot("y"));
    EXPECT_EQ(2, forest.findRoot("z"));
    EXPECT_EQ(3, forest.findRoot("w"));
}


TEST(DisjointSetForestTests, whenConstructingWithIterators_AllElementsAreInOrder)
{
    std::vector<std::string> elements{"aaa", "bbb", "ccc", "ddd", "eee"};

    DisjointSetForest<std::string> forest(elements.begin(), elements.end());

    EXPECT_EQ("aaa", forest.at(0));
    EXPECT_EQ(0, forest.indexOf("aaa"));

    EXPECT_EQ("bbb", forest.at(1));
    EXPECT_EQ(1, forest.indexOf("bbb"));

    EXPECT_EQ("ccc", forest.at(2));
    EXPECT_EQ(2, forest.indexOf("ccc"));

    EXPECT_EQ("ddd", forest.at(3));
    EXPECT_EQ(3, forest.indexOf("ddd"));

    EXPECT_EQ("eee", forest.at(4));
    EXPECT_EQ(4, forest.indexOf("eee"));
}


TEST(DisjointSetForestTests, whenConstructingWithIterators_ElementCountIsCorrect)
{
    int a[4] = { 9, 3, -6, 0};

    DisjointSetForest<int> forest(a, a + 4);

    EXPECT_EQ(4, forest.elementCount());
}


TEST(DisjointSetForestTests, whenConstructingWithIterators_AllElementsAreInSeparateSets)
{
    std::array<std::string, 4> a = {"x", "y", "z", "w"};

    DisjointSetForest<std::string> forest(a.begin(), a.end());

    EXPECT_EQ(4, forest.setCount());

    EXPECT_EQ(0, forest.findRoot("x"));
    EXPECT_EQ(1, forest.weightOf("x"));

    EXPECT_EQ(1, forest.findRoot("y"));
    EXPECT_EQ(1, forest.weightOf("y"));

    EXPECT_EQ(2, forest.findRoot("z"));
    EXPECT_EQ(1, forest.weightOf("z"));

    EXPECT_EQ(3, forest.findRoot("w"));
    EXPECT_EQ(1, forest.weightOf("w"));
}


TEST(DisjointSetForestTests, unionSetsReducesSetCount_WhenDisjoint)
{
    DisjointSetForest<std::string> forest{"a", "b", "c", "d", "e", "f", "g"};

    EXPECT_TRUE(forest.unionSets("b", "f"));
    EXPECT_EQ(6, forest.setCount());

    EXPECT_TRUE(forest.unionSets("a", "g"));
    EXPECT_EQ(5, forest.setCount());

    EXPECT_TRUE(forest.unionSets("d", "e"));
    EXPECT_EQ(4, forest.setCount());
}


TEST(DisjointSetForestTests, unionSetsCombinesWeights)
{
    DisjointSetForest<std::string> forest{"a", "b", "c", "d", "e", "f", "g"};

    EXPECT_TRUE(forest.unionSets("b", "f"));
    EXPECT_EQ(2, forest.weightOf("b"));
    EXPECT_EQ(2, forest.weightOf("f"));

    EXPECT_TRUE(forest.unionSets("a", "g"));
    EXPECT_EQ(2, forest.weightOf("a"));
    EXPECT_EQ(2, forest.weightOf("g"));

    EXPECT_TRUE(forest.unionSets("a", "f"));
    EXPECT_EQ(4, forest.weightOf("a"));
    EXPECT_EQ(4, forest.weightOf("b"));
    EXPECT_EQ(4, forest.weightOf("f"));
    EXPECT_EQ(4, forest.weightOf("g"));
}


TEST(DisjointSetForestTests, unionSetsReturnsFalseWhenAlreadyInSameSet)
{
    DisjointSetForest<std::string> forest{"a", "b", "c", "d", "e", "f", "g"};

    EXPECT_TRUE(forest.unionSets("b", "f"));
    EXPECT_TRUE(forest.unionSets("f", "g"));
    EXPECT_TRUE(forest.unionSets("a", "f"));

    EXPECT_FALSE(forest.unionSets("a", "b"));
    EXPECT_FALSE(forest.unionSets("a", "f"));
    EXPECT_FALSE(forest.unionSets("a", "g"));
    EXPECT_FALSE(forest.unionSets("b", "a"));
    EXPECT_FALSE(forest.unionSets("b", "f"));
    EXPECT_FALSE(forest.unionSets("b", "g"));
    EXPECT_FALSE(forest.unionSets("g", "a"));
    EXPECT_FALSE(forest.unionSets("g", "b"));
    EXPECT_FALSE(forest.unionSets("g", "f"));
}

