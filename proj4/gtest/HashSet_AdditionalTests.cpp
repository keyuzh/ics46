// HashSet_AdditionalTests.cpp
// additional tests for hash set

#include <string>
#include <gtest/gtest.h>
#include "HashSet.hpp"


namespace
{
    template <typename T>
    unsigned int zeroHash(const T& t)
    {
        return 0;
    }

    template <typename T>
    unsigned int oneHash(const T& t)
    {
        return 1;
    }
}


TEST(HashSet_AdditionalTests, sizeOfEmpty)
{
    HashSet<int> empty{zeroHash<int>};
    ASSERT_EQ(0, empty.size());
}

TEST(HashSet_AdditionalTests, emptySetContainsNoKeys)
{
   HashSet<int> empty{zeroHash<int>};
   ASSERT_FALSE(empty.contains(0));
   ASSERT_FALSE(empty.contains(1));
}

TEST(HashSet_AdditionalTests, duplicateDoesNotChangeSize)
{
   HashSet<int> empty{zeroHash<int>};
   empty.add(1);
   empty.add(1);
   ASSERT_EQ(1, empty.size());
   ASSERT_EQ(1, empty.elementsAtIndex(0));
   ASSERT_TRUE(empty.contains(1));
}

TEST(HashSet_AdditionalTests, sizeOfEmptyOtherType)
{
    HashSet<std::string> empty{zeroHash<std::string>};
    ASSERT_EQ(0, empty.size());
}

TEST(HashSet_AdditionalTests, emptySetOtherType)
{
   HashSet<std::string> empty{zeroHash<std::string>};
   ASSERT_FALSE(empty.contains("0"));
   ASSERT_FALSE(empty.contains("1"));
}


TEST(HashSet_AdditionalTests, elementsAtIndexAccordingToDifferentHash)
{
    HashSet<int> s1{oneHash<int>};
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_EQ(0, s1.elementsAtIndex(0));
    EXPECT_EQ(3, s1.elementsAtIndex(1));

    EXPECT_TRUE(s1.isElementAtIndex(11, 1));
    EXPECT_TRUE(s1.isElementAtIndex(1, 1));
    EXPECT_TRUE(s1.isElementAtIndex(5, 1));

    EXPECT_FALSE(s1.isElementAtIndex(11, 0));
    EXPECT_FALSE(s1.isElementAtIndex(1, 0));
    EXPECT_FALSE(s1.isElementAtIndex(5, 0));
}


TEST(HashSet_AdditionalTests, copyConstructDoesNotChangeOriginal)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(1);
    s1.add(2);
    HashSet<int> s1Copy{s1};
    ASSERT_TRUE(s1Copy.contains(1));
    ASSERT_TRUE(s1Copy.contains(2));
    ASSERT_EQ(2, s1Copy.size());
    s1Copy.add(45);
    s1.add(46);
    ASSERT_TRUE(s1Copy.contains(45));
    ASSERT_FALSE(s1.contains(45));
    ASSERT_TRUE(s1.contains(46));
    ASSERT_FALSE(s1Copy.contains(46));
}

TEST(HashSet_AdditionalTests, assignmentChangeOriginal)
{
    HashSet<int> s1{zeroHash<int>};
    s1.add(1);
    s1.add(2);
    HashSet<int> s2{oneHash<int>};
    s2.add(4);
    
    s2 = s1;
    ASSERT_EQ(2, s2.size());
    ASSERT_TRUE(s2.contains(1));
    ASSERT_TRUE(s2.contains(2));
    ASSERT_FALSE(s2.contains(4));
    ASSERT_EQ(2, s2.elementsAtIndex(0));
}
