#include <iostream>
#include <list>
#include <algorithm>
#include <vector>
using namespace std;
class Graph{
    public: 
    list<string>  * userJobs;
    list<pair<string, list<int>>>   jobUsers;
    list<pair<string, int>> jobsMatches;
    int usersCount;
    Graph(int usersCount);
    void replaceMatch(string job, int newUser);
    void addJob(int user, string jobName);
    int getJobMatch(string job);
    int perfectMatch();
    int matchUserJob(int user, list<pair<int, string>> *visitedPairs);
    bool visited(list<pair<int, string>> *visitedPairs, int user, string job);
    bool swapJob(string job, int oldUser, int newUser);
    int greedy();
    bool jobIsEmpty(list<string> jobs, string job);
};