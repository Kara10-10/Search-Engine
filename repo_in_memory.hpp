#include "repo.hpp"
#include <set>
#include <vector>
#include <map>
#include <string>
class RepoInMemory : public Repo
{
    public:
    virtual void SaveLink(std::string link);
    virtual void SaveSite(std::string url, std::string content);
    virtual std::string GetSite(std::string url);

    private:
    std::set<std::string> _links; 
    std::map<std::string, std::string> _sites;
};