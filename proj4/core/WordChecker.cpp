// WordChecker.cpp
//
// ICS 46 Winter 2021
// Project #4: Set the Controls for the Heart of the Sun
//
// Replace and/or augment the implementations below as needed to meet
// the requirements.

#include <algorithm>
#include <iostream>
// #include <utility>
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
    // // Nonsensical code because the compiler requires the member variables
    // // 'words' to be used somewhere, or else it becomes a warning (which
    // // turns into an error).
    // words.isImplemented();


    // initialize an empty vector for storing suggestions
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
    for (auto& w : suggest)
    {
        // std::cout << w << std::endl;        
        result.push_back(w);
    }
    std::sort(result.begin(), result.end());


    return result;
}

void WordChecker::swapAdjacentPair(std::set<std::string>& sug, const std::string& wd) const
{
    // std::cout << "swap adjacent pair" << std::endl;
    // std::cout << "org: " << wd << std::endl;
    for (unsigned int i = 0; i < wd.size()-1; i++)
    {
        // make a copy of the string so we can modify
        std::string copy = wd;
        // swap adjacent char
        std::swap(copy[i], copy[i+1]);
        // std::cout << "aft: " << copy << std::endl;
        if (wordExists(copy))
        {
            sug.insert(copy);
        }
    }
}

void WordChecker::insertChar(std::set<std::string>& sug, const std::string& wd) const
{
    // std::cout << "insert between each pos" << std::endl;
    // std::cout << "org: " << wd << std::endl;
    // insert from the beginning to end
    for (unsigned int i = 0; i < wd.size()+1; i++)
    {
        // try insert A to Z
        for (char c = 'A'; c <= 'Z'; c++)
        {
            std::string copy = wd;
            copy.insert(i, 1, c);
            // std::cout << "aft: " << copy << std::endl;
            if (wordExists(copy))
            {
                sug.insert(copy);
            }
        }
    }
}

void WordChecker::deleteChar(std::set<std::string>& sug, const std::string& wd) const
{
    // std::cout << "delete at each pos" << std::endl;
    // std::cout << "org: " << wd << std::endl;
    for (unsigned int i = 0; i < wd.size(); i++)
    {
        std::string copy = wd;
        copy.erase(i, 1);
        // std::cout << "aft: " << copy << std::endl;
        if (wordExists(copy))
        {
            sug.insert(copy);
        }
    }
}

void WordChecker::replaceChar(std::set<std::string>& sug, const std::string& wd) const
{
    // std::cout << "replace between each pos" << std::endl;
    // std::cout << "org: " << wd << std::endl;
    // replace from the beginning to end
    for (unsigned int i = 0; i < wd.size(); i++)
    {
        // try insert A to Z
        for (char c = 'A'; c <= 'Z'; c++)
        {
            std::string copy = wd;
            copy[i] = c;
            // std::cout << "aft: " << copy << std::endl;
            if (wordExists(copy))
            {
                sug.insert(copy);
            }
        }
    }

}

void WordChecker::splitWord(std::set<std::string>& sug, const std::string& wd) const
{
    // std::cout << "split word" << std::endl;
    // std::cout << "org: " << wd << std::endl;
    for (unsigned int i = 1; i < wd.size(); i++)
    {
        std::string s1 = wd.substr(0, i);
        std::string s2 = wd.substr(i);
        // std::cout << "aft: " << s1 << " " << s2 << std::endl;
        if (wordExists(s1) && wordExists(s2))
        {
            sug.insert(s1 + " " + s2);
            // sug.insert(s2);
        }
    }
    

}
