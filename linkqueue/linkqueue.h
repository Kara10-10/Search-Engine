/*
#include <string>
#include <queue>
#include <vector>

typedef void (*linkhandler)(std::string);
class linkqueue 
{
    public:
    void Push(std::string url);
    void AddHandler (linkhandler);

    private:
    
    std::queue<std::string> urlqueue;
    std::vector<linkhandler> handlers;
};
*/