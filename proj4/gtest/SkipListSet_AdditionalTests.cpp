// SkipListSet_AdditionalTests.cpp
// additional tests for skip list

#include <memory>
#include <string>
#include <gtest/gtest.h>
#include "SkipListSet.hpp"


TEST(SkipListSet_AdditionalTests, emptySetSizeIsZero)
{
    SkipListSet<int> s1;
    SkipListSet<std::string> s2;
    ASSERT_EQ(0, s1.size());
    ASSERT_EQ(0, s2.size());
}

TEST(SkipListSet_AdditionalTests, emptySetContainsNothing)
{
    SkipListSet<int> s1;
    ASSERT_FALSE(s1.contains(2));
    ASSERT_FALSE(s1.contains(1));
}

TEST(SkipListSet_AdditionalTests, emptySetContainsNothingOnLevels)
{
    SkipListSet<int> s1;
    ASSERT_FALSE(s1.isElementOnLevel(2, 0));
    ASSERT_FALSE(s1.isElementOnLevel(2, 1));
    ASSERT_FALSE(s1.isElementOnLevel(2, 100));
}

TEST(SkipListSet_AdditionalTests, emptySetHasOneLevel)
{
    SkipListSet<int> s1;
    ASSERT_EQ(1, s1.levelCount());
}

TEST(SkipListSet_AdditionalTests, emptySetHasNothingOnLevelZero)
{
    SkipListSet<int> s1;
    ASSERT_EQ(0, s1.elementsOnLevel(0));
}


TEST(SkipListSet_AdditionalTests, copyConstructCopiesContent)
{
    SkipListSet<int> s1;
    s1.add(1);
    s1.add(2);
    SkipListSet<int> s1Copy{s1};
    ASSERT_EQ(2, s1.size());
    ASSERT_EQ(2, s1Copy.size());
    ASSERT_EQ(s1.levelCount(), s1Copy.levelCount());
    ASSERT_TRUE(s1Copy.contains(1));
    ASSERT_TRUE(s1Copy.contains(2));
}

TEST(SkipListSet_AdditionalTests, copyConstructDoesNotChangeOriginal)
{
    SkipListSet<int> s1;
    s1.add(1);
    s1.add(2);
    SkipListSet<int> s1Copy{s1};
    s1Copy.add(4);
    ASSERT_EQ(2, s1.size());
    ASSERT_EQ(3, s1Copy.size());
    ASSERT_TRUE(s1Copy.contains(4));
    ASSERT_FALSE(s1.contains(4));
    s1.add(8);
    ASSERT_EQ(3, s1.size());
    ASSERT_FALSE(s1Copy.contains(8));
    ASSERT_TRUE(s1.contains(8));
}

TEST(SkipListSet_AdditionalTests, assignmentCopiesContent)
{
    SkipListSet<int> s1;
    s1.add(1);
    SkipListSet<int> s3;
    s3.add(7);
    s1 = s3;
    ASSERT_EQ(1, s1.size());
    ASSERT_TRUE(s1.contains(7));
    ASSERT_FALSE(s1.contains(1));
}

TEST(SkipListSet_AdditionalTests, assignmentDoesNotChangeOriginal)
{
    SkipListSet<int> s1;
    s1.add(1);
    SkipListSet<int> s3;
    s3.add(7);
    s1 = s3;
    s1.add(5);
    ASSERT_EQ(2, s1.size());
    ASSERT_EQ(1, s3.size());
    ASSERT_FALSE(s3.contains(5));
}


namespace
{
    template <typename ElementType>
    class GrowOnceSkipListLevelTester : public SkipListLevelTester<ElementType>
    {
    public:
        GrowOnceSkipListLevelTester();
        virtual ~GrowOnceSkipListLevelTester() = default;

        virtual bool shouldOccupyNextLevel(const ElementType& element) override;
        virtual std::unique_ptr<SkipListLevelTester<ElementType>> clone() override;
    private:
        bool called;
    };

    template <typename ElementType>
    GrowOnceSkipListLevelTester<ElementType>::GrowOnceSkipListLevelTester()
        : called{false}
    {
    }

    template <typename ElementType>
    bool GrowOnceSkipListLevelTester<ElementType>::shouldOccupyNextLevel(const ElementType& element)
    {
        if (called)
        {
            return false;
        }
        called = true;
        return true;        
    }


    template <typename ElementType>
    std::unique_ptr<SkipListLevelTester<ElementType>> GrowOnceSkipListLevelTester<ElementType>::clone()
    {
        return std::unique_ptr<SkipListLevelTester<ElementType>>{
            new GrowOnceSkipListLevelTester};
    }
}


TEST(SkipListSet_AdditionalTests, twoLevelIfOnlyGrowOnce)
{
    SkipListSet<int> s1{std::make_unique<GrowOnceSkipListLevelTester<int>>()};
    for (int i = 0; i < 10; ++i)
    {
        s1.add(i);
    }
    EXPECT_EQ(2, s1.levelCount());
    EXPECT_EQ(10, s1.elementsOnLevel(0));
    EXPECT_EQ(1, s1.elementsOnLevel(1));
    EXPECT_TRUE(s1.isElementOnLevel(0, 1));
    for (int i = 1; i < 10; i++)
    {
        EXPECT_TRUE(s1.contains(i));
        EXPECT_FALSE(s1.isElementOnLevel(i, 1));
        EXPECT_TRUE(s1.isElementOnLevel(i, 0));
    }
}
