// AVLSet_SanityCheckTests.cpp
//
// ICS 46 Winter 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// This is a set of "sanity checking" unit tests for your AVLSet
// implementation, provided primarily as a mechanism for ensuring that
// your implementation is compatible with the unit tests we'll be using
// to test it, and to give you a quick example of how each of the member
// functions works.  These tests don't verify all of the functionality
// you're implementing.
//
// As with the sanity-checking unit tests you saw in other projects, you
// should not modify these in any way -- don't add #include directives,
// and don't change the code within the tests.  These should all compile
// and pass before you submit your AVLSet implementation.

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "AVLSet.hpp"


TEST(AVLSet_SanityCheckTests, inheritFromSet)
{
    AVLSet<int> s1;
    Set<int>& ss1 = s1;
    int sz1 = ss1.size();
    sz1 = 0;

    AVLSet<std::string> s2;
    Set<std::string>& ss2 = s2;
    int sz2 = ss2.size();
    sz2 = 0;
}


TEST(AVLSet_SanityCheckTests, canCreateAndDestroy)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;
}


TEST(AVLSet_SanityCheckTests, heightOfEmptyIsNegativeOne)
{
    AVLSet<int> s;
    ASSERT_EQ(-1, s.height());
}

TEST(AVLSet_SanityCheckTests, sizeOfEmptyIsZero)
{
    AVLSet<int> s;
    ASSERT_EQ(0, s.size());
}

TEST(AVLSet_SanityCheckTests, emptySetDoesNotContainAnything)
{
    AVLSet<int> s;
    ASSERT_FALSE(s.contains(0));
}

TEST(AVLSet_SanityCheckTests, sizeOfOneElement)
{
    AVLSet<int> s;
    s.add(3);
    ASSERT_EQ(1, s.size());
}

TEST(AVLSet_SanityCheckTests, heightOfOneElement)
{
    AVLSet<int> s;
    s.add(4);
    ASSERT_EQ(0, s.height());
}

TEST(AVLSet_SanityCheckTests, noDuplicates)
{
    AVLSet<int> s;
    s.add(4);
    s.add(4);
    s.add(4);
    ASSERT_EQ(0, s.height());
    ASSERT_EQ(1, s.size());
    ASSERT_TRUE(s.contains(4));
}


TEST(AVLSet_SanityCheckTests, canCopyConstructToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s1Copy{s1};
    AVLSet<std::string> s2Copy{s2};
}

TEST(AVLSet_SanityCheckTests, sizeAndHeightIsCorrectAfterCopyConstruct)
{
    AVLSet<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);

    AVLSet<int> s1Copy{s1};
    ASSERT_EQ(3, s1.size());
    ASSERT_EQ(3, s1Copy.size());
    ASSERT_EQ(1, s1.height());
    ASSERT_EQ(1, s1Copy.height());
}

TEST(AVLSet_SanityCheckTests, copyConstructDoesNotChangeOriginal)
{
    AVLSet<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);

    AVLSet<int> s1Copy{s1};
    s1Copy.add(5);
    s1.add(6);
    
    ASSERT_EQ(4, s1Copy.size());
    ASSERT_TRUE(s1Copy.contains(5));
    ASSERT_FALSE(s1.contains(5));
    ASSERT_TRUE(s1.contains(6));
    ASSERT_FALSE(s1Copy.contains(6));
}


TEST(AVLSet_SanityCheckTests, canMoveConstructToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s1Copy{std::move(s1)};
    AVLSet<std::string> s2Copy{std::move(s2)};
}


TEST(AVLSet_SanityCheckTests, canAssignToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s3;
    AVLSet<std::string> s4;

    s1 = s3;
    s2 = s4;
}

TEST(AVLSet_SanityCheckTests, sizeAndHeightIsCorrectAfterAssignment)
{
    AVLSet<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);

    AVLSet<int> s2;
    s2.add(0);

    ASSERT_EQ(1, s2.size());
    ASSERT_EQ(3, s1.size());

    s2 = s1;
    ASSERT_EQ(3, s2.size());
    ASSERT_EQ(3, s1.size());
    ASSERT_FALSE(s2.contains(0));
}

TEST(AVLSet_SanityCheckTests, AssignmentDoesNotChangeOriginal)
{
    AVLSet<int> s1;
    s1.add(1);
    s1.add(2);
    s1.add(3);

    AVLSet<int> s2;
    s2 = s1;
    s2.add(5);
    s1.add(6);
    
    ASSERT_EQ(4, s1.size());
    ASSERT_EQ(4, s2.size());
    ASSERT_TRUE(s2.contains(5));
    ASSERT_FALSE(s1.contains(5));
    ASSERT_TRUE(s1.contains(6));
    ASSERT_FALSE(s2.contains(6));
}


TEST(AVLSet_SanityCheckTests, canMoveAssignToCompatibleType)
{
    AVLSet<int> s1;
    AVLSet<std::string> s2;

    AVLSet<int> s3;
    AVLSet<std::string> s4;

    s1 = std::move(s3);
    s2 = std::move(s4);
}


TEST(AVLSet_SanityCheckTests, isImplemented)
{
    AVLSet<int> s1;
    EXPECT_TRUE(s1.isImplemented());

    AVLSet<std::string> s2;
    EXPECT_TRUE(s2.isImplemented());
}


TEST(AVLSet_SanityCheckTests, containsElementsAfterAdding)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_TRUE(s1.contains(11));
    EXPECT_TRUE(s1.contains(1));
    EXPECT_TRUE(s1.contains(5));
}

TEST(AVLSet_SanityCheckTests, containsElementsAfterAddingOtherType)
{
    AVLSet<std::string> s1;
    s1.add("11");
    s1.add("1");
    s1.add("5");

    EXPECT_TRUE(s1.contains("11"));
    EXPECT_TRUE(s1.contains("1"));
    EXPECT_TRUE(s1.contains("5"));
}


TEST(AVLSet_SanityCheckTests, doesNotContainElementsNotAdded)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_FALSE(s1.contains(21));
    EXPECT_FALSE(s1.contains(2));
    EXPECT_FALSE(s1.contains(9));
}

TEST(AVLSet_SanityCheckTests, doesNotContainElementsNotAddedOtherType)
{
    AVLSet<std::string> s1;
    s1.add("11");
    s1.add("1");
    s1.add("5");

    EXPECT_FALSE(s1.contains("21"));
    EXPECT_FALSE(s1.contains("2"));
    EXPECT_FALSE(s1.contains("9"));
}


TEST(AVLSet_SanityCheckTests, sizeIsNumberOfElementsAdded)
{
    AVLSet<int> s1;
    s1.add(11);
    s1.add(1);
    s1.add(5);

    EXPECT_EQ(3, s1.size());
}

TEST(AVLSet_SanityCheckTests, canDetectImbalance)
{
    AVLSet<int> notBalanced{false};
    notBalanced.add(1);
    notBalanced.add(2);
    notBalanced.add(3);

    EXPECT_EQ(2, notBalanced.height());
    EXPECT_FALSE(notBalanced.isBalanced());
}

TEST(AVLSet_SanityCheckTests, canDetectImbalanceRecursive)
{
    AVLSet<int> notBalanced{false};
    notBalanced.add(0);
    notBalanced.add(1);
    notBalanced.add(2);
    notBalanced.add(3);
    notBalanced.add(-1);
    notBalanced.add(-2);
    notBalanced.add(-3);

    EXPECT_EQ(3, notBalanced.height());
    EXPECT_FALSE(notBalanced.isBalanced());
}

TEST(AVLSet_SanityCheckTests, heightDependsOnBalancing)
{
    AVLSet<int> balanced{true};
    balanced.add(1);
    balanced.add(2);
    balanced.add(3);

    AVLSet<int> notBalanced{false};
    notBalanced.add(1);
    notBalanced.add(2);
    notBalanced.add(3);

    EXPECT_EQ(1, balanced.height());
    EXPECT_EQ(2, notBalanced.height());
}

TEST(AVLSet_SanityCheckTests, sizeStayTheSameAfterBalancing)
{
    AVLSet<int> balanced{true};
    balanced.add(1);
    balanced.add(2);
    balanced.add(3);

    AVLSet<int> notBalanced{false};
    notBalanced.add(1);
    notBalanced.add(2);
    notBalanced.add(3);

    EXPECT_EQ(3, balanced.size());
    EXPECT_EQ(3, notBalanced.size());
}

TEST(AVLSet_SanityCheckTests, isBalancedAfterBalancing)
{
    AVLSet<int> balanced{true};
    balanced.add(1);
    balanced.add(2);
    balanced.add(3);

    EXPECT_TRUE(balanced.isBalanced());
}

TEST(AVLSet_SanityCheckTests, containTheSameElementsAfterBalancing)
{
    AVLSet<int> balanced{true};
    balanced.add(1);
    balanced.add(2);
    balanced.add(3);

    EXPECT_TRUE(balanced.contains(1));
    EXPECT_TRUE(balanced.contains(2));
    EXPECT_TRUE(balanced.contains(3));
    EXPECT_FALSE(balanced.contains(4));
}


TEST(AVLSet_SanityCheckTests, canProvideTraversals)
{
    AVLSet<int> s{false};
    s.add(10);
    s.add(20);
    s.add(30);
    s.add(40);
    s.add(50);

    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });

    std::vector<int> expectedPreElements{10, 20, 30, 40, 50};
    std::vector<int> expectedInElements{10, 20, 30, 40, 50};
    std::vector<int> expectedPostElements{50, 40, 30, 20, 10};

    ASSERT_EQ(5, preElements.size());
    ASSERT_EQ(5, inElements.size());
    ASSERT_EQ(5, postElements.size());

    for (unsigned int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}

TEST(AVLSet_SanityCheckTests, traversalIsCorrectAfterRRBalancing)
{
    AVLSet<int> s{true};
    s.add(10);
    s.add(20);
    s.add(30);
    s.add(40);
    s.add(50);

    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });

    std::vector<int> expectedPreElements{20, 10, 40, 30, 50};
    std::vector<int> expectedInElements{10, 20, 30, 40, 50};
    std::vector<int> expectedPostElements{10, 30, 50, 40, 20};

    ASSERT_EQ(5, preElements.size());
    ASSERT_EQ(5, inElements.size());
    ASSERT_EQ(5, postElements.size());

    for (unsigned int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}

TEST(AVLSet_SanityCheckTests, traversalIsCorrectAfterLLBalancing)
{
    AVLSet<int> s{true};
    s.add(50);
    s.add(40);
    s.add(30);
    s.add(20);
    s.add(10);

    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });

    std::vector<int> expectedPreElements{40, 20, 10, 30, 50};
    std::vector<int> expectedInElements{10, 20, 30, 40, 50};
    std::vector<int> expectedPostElements{10, 30, 20, 50, 40};

    ASSERT_EQ(5, preElements.size());
    ASSERT_EQ(5, inElements.size());
    ASSERT_EQ(5, postElements.size());

    for (unsigned int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}

TEST(AVLSet_SanityCheckTests, traversalIsCorrectAfterRLBalancing)
{
    AVLSet<int> s{true};
    s.add(10);
    s.add(20);
    s.add(15);
    s.add(30);
    s.add(25);

    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });

    std::vector<int> expectedPreElements{15, 10, 25, 20, 30};
    std::vector<int> expectedInElements{10, 15, 20, 25, 30};
    std::vector<int> expectedPostElements{10, 20, 30, 25, 15};

    ASSERT_EQ(5, preElements.size());
    ASSERT_EQ(5, inElements.size());
    ASSERT_EQ(5, postElements.size());

    for (unsigned int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}

TEST(AVLSet_SanityCheckTests, traversalIsCorrectAfterLRBalancing)
{
    AVLSet<int> s{true};
    s.add(15);
    s.add(10);
    s.add(12);
    s.add(7);
    s.add(8);

    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });

    std::vector<int> expectedPreElements{12, 8, 7, 10, 15};
    std::vector<int> expectedInElements{7, 8, 10, 12, 15};
    std::vector<int> expectedPostElements{7, 10, 8, 15, 12};

    ASSERT_EQ(5, preElements.size());
    ASSERT_EQ(5, inElements.size());
    ASSERT_EQ(5, postElements.size());

    for (unsigned int i = 0; i < 5; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}

TEST(AVLSet_SanityCheckTests, traversalIsCorrectAfterMultiBalancing)
{
    AVLSet<int> s{true};
    s.add(10);
    s.add(20);
    s.add(30);
    s.add(40);
    s.add(50);
    s.add(25);

    std::vector<int> preElements;
    std::vector<int> inElements;
    std::vector<int> postElements;

    s.preorder([&](const int& element) { preElements.push_back(element); });
    s.inorder([&](const int& element) { inElements.push_back(element); });
    s.postorder([&](const int& element) { postElements.push_back(element); });

    std::vector<int> expectedPreElements{30, 20, 10, 25, 40, 50};
    std::vector<int> expectedInElements{10, 20, 25, 30, 40, 50};
    std::vector<int> expectedPostElements{10, 25, 20, 50, 40, 30};

    ASSERT_EQ(6, preElements.size());
    ASSERT_EQ(6, inElements.size());
    ASSERT_EQ(6, postElements.size());

    for (unsigned int i = 0; i < 6; ++i)
    {
        EXPECT_EQ(preElements[i], expectedPreElements[i]);
        EXPECT_EQ(inElements[i], expectedInElements[i]);
        EXPECT_EQ(postElements[i], expectedPostElements[i]);
    }
}
