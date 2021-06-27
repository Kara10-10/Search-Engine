#include <string>
#include <vector>
#include <map>
#include <pthread.h>
class Indexer
{
    public:
        void AddSite(std::string url, std::string contents);
        std::vector<std::string> GetRelevantURLs(std::string word, uint count =10);

    private:
       // word -> (relevance, URL)
       std::map<std::string, std::map<float, std::string>> _index;
       pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
};