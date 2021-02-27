// WordChecker_AdditionalTests.cpp
// additional tests for word checker

#include <string>
#include <vector>
#include <gtest/gtest.h>
#include "ListSet.hpp"
#include "WordChecker.hpp"


TEST(WordChecker_AdditionalTests, canGenerateSuggestionsBySwapAdjacentPair)
{
    ListSet<std::string> set;
    set.add("ABDC");
    set.add("BACD");
    set.add("ACBD");

    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ABCD");
    ASSERT_EQ(3, suggestions.size());
    ASSERT_EQ("ABDC", suggestions[0]);
    ASSERT_EQ("ACBD", suggestions[1]);
    ASSERT_EQ("BACD", suggestions[2]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByAddCharAtFront)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("BCD");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByAddCharInMid)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ACD");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByAddCharAtBack)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ABC");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByDeleteCharAtFront)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("AABCD");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByDeleteCharInMid)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ABXCD");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByDeleteCharAtBack)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ABCDE");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByReplaceCharAtFront)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ZBCD");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByReplaceCharInMid)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ABXD");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsByReplaceCharAtBack)
{
    ListSet<std::string> set;
    set.add("ABCD");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ABCE");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, canGenerateSuggestionsBySplit)
{
    ListSet<std::string> set;
    set.add("ABCD");
    set.add("EF");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ABCDEF");
    ASSERT_EQ(1, suggestions.size());
    ASSERT_EQ("ABCD EF", suggestions[0]);
}

TEST(WordChecker_AdditionalTests, bothWordNeedToBeValid)
{
    ListSet<std::string> set;
    set.add("ABC");
    set.add("EF");
    WordChecker checker{set};
    std::vector<std::string> suggestions = checker.findSuggestions("ABCDEF");
    ASSERT_EQ(0, suggestions.size());
}
