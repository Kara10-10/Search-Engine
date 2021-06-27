#include "indexer.hpp"
#include <sstream>
#include <iostream>
#include <iterator>
#include <algorithm>
void Indexer::AddSite(std::string url, std::string contents)
{
    //std::cout<< "Indexing: " << url << std::endl;
    //Split the contents into words
    std::map<std::string, uint> word_counts;
    std::stringstream str(contents);
    std::string word;

    //Get word occurance count
    while(str >> word)
    {
        if(word_counts.find(word) == word_counts.end())
        {
            word_counts[word] = 0;
        }
        else
        {
            word_counts[word]++;
        }
    }

    //Store in index
    for(auto i=word_counts.begin(); i!= word_counts.end(); ++i)
    {
        auto word = i->first;
        auto count = i->second;

        //if(index.find(word)==index.end())
        {
           pthread_mutex_lock(&mutex);
            _index[word][count] = url;
            pthread_mutex_unlock(&mutex);
        }
    }

    //std::cout << "Index size: " << _index.size() << std::endl;
}

std::vector<std::string> Indexer::GetRelevantURLs(std::string word, uint count)
{
    //Check if the word presents

    std::cout << "Index size: " << _index.size() << ", " << word << "match size " << _index[word].size()<< std::endl;
    std::vector<std::string> matches;
    int i =0;
    for(auto iter = _index[word].begin(); iter!=_index[word].end() && i<count; iter++, i++)
    {
        matches.push_back(iter->second);
    }
    return matches;
}