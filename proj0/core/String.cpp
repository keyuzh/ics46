// String.cpp
//
// ICS 46 Winter 2021
// Project #0: Getting to Know the ICS 46 VM
//
// Implement all of your String member functions in this file.
//
// Note that the entire standard library -- both the C Standard
// Library and the C++ Standard Library -- is off-limits for this
// task, as the goal is to exercise your low-level implementation
// skills (pointers, memory management, and so on).

#include "String.hpp"
#include "OutOfBoundsException.hpp"


namespace
{
    unsigned int countLength(const char* chars)
    {
        // returns the length of given c-style string, not including \0
        unsigned int len = 0;
        while (chars[len] != 0)
        {
            len++;
        }
        return len;
    }
}


String::String()
    : content{nullptr}
{
    try
    {
        // initiate the string empty, only one null terminator
        content = new char[1];
        content[0] = 0;
    }
    catch (...)
    {
        delete[] content;
        throw;
    }
}


String::String(const char* chars)
    : content{nullptr}
{
    // initiate string from c-style string
    try
    {
        unsigned int lengthIncludingNullTerminator = countLength(chars) + 1;
        content = new char[lengthIncludingNullTerminator];
        // copy from c-style string
        for (unsigned int i = 0; i < lengthIncludingNullTerminator; i++)
        {
            content[i] = chars[i];
        }
    }
    catch (...)
    {
        delete[] content;
        throw;
    }
}


String::String(const String& s)
    : content{nullptr}
{
    // initiate a copy of another string class
    try
    {
        unsigned int len = s.length();
        content = new char[len+1];
        // copy content from the other string
        for (unsigned int i = 0; i < len; i++)
        {
            content[i] = s.at(i);
        }
        content[len] = 0;  // add null terminator
    }
    catch (...)
    {
        delete[] content;
        throw;
    }
}


String::~String() noexcept
{
    delete[] content;
}

    
String& String::operator=(const String& s)
{
    // copy assign from another string
    if (this != &s)
    {
        char* newContent = nullptr;
        try
        {
            unsigned int len = s.length();
            newContent = new char[len+1];
            for (unsigned int i = 0; i < len; i++)
            {
                newContent[i] = s.at(i);
            }
            newContent[len] = 0;
        }
        catch (...)
        {
            delete[] newContent;
            throw;
        }
        delete[] content;
        content = newContent;
    }
    return *this;
}


void String::append(const String& s)
{
    unsigned int oldLength = length();
    unsigned int newLength = s.length();
    char* resultString = nullptr;
    try 
    {
        resultString = new char[oldLength + newLength + 1];

        // first copy old string content
        for (unsigned int i = 0; i < oldLength; i++)
        {
            resultString[i] = at(i);
        }
        // then copy from the other string
        for (unsigned int i = 0; i < newLength; i++)
        {
            resultString[oldLength + i] = s.at(i);
        }
        // finally add \0
        resultString[oldLength + newLength] = 0;
    }
    catch (...)
    {
        delete[] resultString;
        throw;
    }
    // replace old string
    delete[] content;
    content = resultString;
}


char String::at(unsigned int index) const
{
    if (index >= length())
    {
        throw OutOfBoundsException{};
    }
    return content[index];
}


char& String::at(unsigned int index)
{
    if (index >= length())
    {
        throw OutOfBoundsException{};
    }
    return content[index];
}


void String::clear()
{
    // make a empty string and replace original
    char* empty = nullptr; 
    try 
    {
        empty = new char[1];
        empty[0] = 0;
    }
    catch (...)
    {
        delete[] empty;
        throw;
    }
    delete[] content;
    content = empty;
}


int String::compareTo(const String& s) const noexcept
{
    for (unsigned int i = 0; i < length(); i++)
    {
        try
        {
            int difference = at(i) - s.at(i);
            if (difference != 0)
            {
                // different char
                return difference;
            }
        }
        catch(const OutOfBoundsException e)
        {
            // all char so far are the same, and this.length() > s.length()
            // return positive value
            return at(i);
        }
    }
    if (length() < s.length())
    {
        // all char so far are the same, but this.length() < s.length()
        // return negative value
        return -s.at(length());
    }
    return 0; // all char are exactly the same
}


String String::concatenate(const String& s) const
{
    String result{*this}; // first make a copy of current string
    result.append(s); // append the other string to the end then return
    return result;
}


bool String::contains(const String& substring) const noexcept
{
    if (find(substring) == -1)
    {
        return false;
    }
    return true;
}


bool String::equals(const String& s) const noexcept
{
    if (compareTo(s) == 0)
    {
        return true;
    }
    return false;
}


int String::find(const String& substring) const noexcept
{
    if (substring.isEmpty())
    {
        return 0;  // return 0 if given empty string
    }
    for (unsigned int i = 0; i < length(); i++)
    {
        // check if char at current index is equal to beginning of substring
        if (at(i) == substring.at(0))
        {
            bool equal = true;
            for (unsigned int j = 0; j < substring.length(); j++)
            {
                // if char is different, keep searching
                // if out of bounds, then it means not found
                try
                {
                    if (at(i+j) != substring.at(j))
                    {
                        equal = false;
                        break;  // keep searching through the string
                    }
                }
                catch(const OutOfBoundsException e)
                {
                    return -1;  // not found
                }
            }
            // if the loop completed, it means we found a match
            if (equal)
            {
                return i;
            }
        }
    }
    return -1;
}


bool String::isEmpty() const noexcept
{
    // empty means length == 0
    if (length() == 0)
    {
        return true;
    }
    return false;
}


unsigned int String::length() const noexcept
{
    return countLength(content);
}


String String::substring(unsigned int startIndex, unsigned int endIndex) const
{
    if (startIndex > endIndex)
    {
        return String{};
    }
    char* substringChars = nullptr;
    try
    {
        // at() may throw exception, need to clean up memory here
        substringChars = new char[endIndex - startIndex + 1];
        // copy
        for (unsigned int i = 0; i < endIndex - startIndex; i++)
        {
            substringChars[i] = at(i + startIndex);
        }
        // add \0 to the end
        substringChars[endIndex - startIndex] = 0;
        // create new String object
        String substr{substringChars};
        delete[] substringChars;
        return substr;
    }
    catch (...)
    {
        delete[] substringChars;
        throw;
    }
}


const char* String::toChars() const noexcept
{
    // already storing chars as a c-style string, simply return array of char
    return content;
}
