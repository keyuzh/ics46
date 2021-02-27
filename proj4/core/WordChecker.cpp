// WordChecker.cpp
//
// ICS 46 Winter 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include <algorithm>
#include <set>
#include "WordChecker.hpp"



WordChecker::WordChecker(const Set<std::string>& words)
    : words{words}
{
}


bool WordChecker::wordExists(const std::string& word) const
{
    return words.contains(word);
}


std::vector<std::string> WordChecker::findSuggestions(const std::string& word) const
{
    // initialize an empty set for storing suggestions
    // we use std::set here because we dont want duplicates
    std::set<std::string> suggest;

    // generate suggestions base on the 5 algorithms
    // 1
    // Swapping each adjacent pair of characters in the word.
    swapAdjacentPair(suggest, word);
    // 2
    // In between each adjacent pair of characters in the word (also before the
    // first character and after the last character), each letter from 'A' through
    // 'Z' is inserted.
    insertChar(suggest, word);
    // 3
    // Deleting each character from the word.
    deleteChar(suggest, word);
    // 4
    // Replacing each character in the word with each letter from 'A' through 'Z'.
    replaceChar(suggest, word);
    // 5
    // Splitting the word into a pair of words by adding a space in between each
    // adjacent pair of characters in the word. It should be noted that this will
    // only generate a suggestion if both words in the pair are found in the word set.
    splitWord(suggest, word);

    std::vector<std::string> result;
    // copy from set to vector for return value
    for (auto& w : suggest)
    {
        result.push_back(w);
    }
    // sort the vector
    std::sort(result.begin(), result.end());
    return result;
}

void WordChecker::swapAdjacentPair(std::set<std::string>& sug, const std::string& wd) const
{
    for (unsigned int i = 0; i < wd.size()-1; i++)
    {
        // make a copy of the string so we can modify
        std::string copy = wd;
        // swap adjacent char
        std::swap(copy[i], copy[i+1]);
        if (wordExists(copy))
        {
            // is a valid suggestion
            sug.insert(copy);
        }
    }
}

void WordChecker::insertChar(std::set<std::string>& sug, const std::string& wd) const
{
    // insert from the beginning to end
    for (unsigned int i = 0; i < wd.size()+1; i++)
    {
        // insert A to Z
        for (char c = 'A'; c <= 'Z'; c++)
        {
            // insert the char
            std::string copy = wd;
            copy.insert(i, 1, c);
            if (wordExists(copy))
            {
                // valid
                sug.insert(copy);
            }
        }
    }
}

void WordChecker::deleteChar(std::set<std::string>& sug, const std::string& wd) const
{
    for (unsigned int i = 0; i < wd.size(); i++)
    {
        // delete one char
        std::string copy = wd;
        copy.erase(i, 1);
        if (wordExists(copy))
        {
            // valid
            sug.insert(copy);
        }
    }
}

void WordChecker::replaceChar(std::set<std::string>& sug, const std::string& wd) const
{
    // replace from the beginning to end
    for (unsigned int i = 0; i < wd.size(); i++)
    {
        // try insert A to Z
        for (char c = 'A'; c <= 'Z'; c++)
        {
            // replace
            std::string copy = wd;
            copy[i] = c;
            if (wordExists(copy))
            {
                // valid
                sug.insert(copy);
            }
        }
    }

}

void WordChecker::splitWord(std::set<std::string>& sug, const std::string& wd) const
{
    for (unsigned int i = 1; i < wd.size(); i++)
    {
        // split into 2 string
        std::string s1 = wd.substr(0, i);
        std::string s2 = wd.substr(i);
        if (wordExists(s1) && wordExists(s2))
        {
            // both must be valid, insert with a space
            sug.insert(s1 + " " + s2);
        }
    }
}
