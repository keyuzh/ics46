#include <cctype>
#include <iostream>
#include <set>
#include <string>
#include <vector>


int translate(char c)
{
    if (std::isdigit(c))
    {
        return (c - '0') * 2;
    }
    else if (std::isupper(c) || std::islower(c))
    {
        return ((std::tolower(c) - 'a') * 2) + 26;
    }
    else
    {
        return -1;
    }
}


std::vector<unsigned int> translate(const std::string& ucinetid)
{
    std::set<unsigned int> used;

    std::vector<unsigned int> result;
    result.reserve(ucinetid.size());

    for (char c : ucinetid)
    {
        int translated = translate(c);

        if (translated != -1 &&
            used.find(translated) == used.end())
        {
            result.push_back(translate(c));
            used.insert(translated);
        }
    }

    return result;
}


std::vector<unsigned int> intersperse(
    const std::vector<unsigned int>& hardCoded,
    const std::vector<unsigned int>& translated)
{
    std::vector<unsigned int> result;
    result.reserve(hardCoded.size() + translated.size());

    unsigned int maxSize = std::max(hardCoded.size(), translated.size());

    for (unsigned int i = 0; i < maxSize; ++i)
    {
        if (i < hardCoded.size())
        {
            result.push_back(hardCoded.at(i));
        }

        if (i < translated.size())
        {
            result.push_back(translated.at(i));
        }
    }

    return result;
}


int main()
{
    std::cout << "Enter your UCInetID: ";

    std::string ucinetid;
    std::getline(std::cin, ucinetid);

    std::vector<unsigned int> hardCoded{53, 37, 63, 25, 97, 99, 51};
    std::vector<unsigned int> translated = translate(ucinetid);
    std::vector<unsigned int> interspersed = intersperse(hardCoded, translated);

    for (unsigned int i : interspersed)
    {
        std::cout << i << " ";
    }

    std::cout << std::endl;

    return 0;
}

