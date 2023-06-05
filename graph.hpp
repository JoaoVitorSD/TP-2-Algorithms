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

    Graph(int usersCount){
        this->userJobs = new list<string>[usersCount];
        this->usersCount = usersCount;
        this->jobUsers = list<pair<string, list<int>>>();
        this->jobsMatches =  list<pair<string, int>>();
    }


    void replaceMatch(string job, int newUser){
        for (auto &match : jobsMatches){
            if(match.first == job){
                match.second = newUser;
                return;
            }
        }
    }
    void addJob(int user, string jobName){
        this->userJobs[user].push_back(jobName);
    }
    int getJobMatch(string job)
    {
        for (auto &jobMatch : jobsMatches)
        {
            if(jobMatch.first == job){
                return jobMatch.second;
            }
        }
        return -1;
    }
    int exact(){
        int matchesCounter = 0;
        for(int user = 0; user < usersCount;user++ ){
            list<pair<int, string>>*  visitedPairs = new list<pair<int, string>>();
            matchesCounter += matchUserJob(user, visitedPairs);
            delete visitedPairs;
        }
        return matchesCounter;
    }
    int matchUserJob(int user, list<pair<int, string>> *visitedPairs)
    {
        for (auto &job : userJobs[user])
        {
            if(visited(visitedPairs, user, job)){
                continue;
            }
            visitedPairs->push_back(make_pair(user, job));
            int indexFilled = getJobMatch(job);
            if (indexFilled == -1)
            {

                jobsMatches.push_back(make_pair(job, user));
                return true;
            }
            else
            {
                if (matchUserJob(indexFilled, visitedPairs))
                {
                    replaceMatch(job, user);
                    return true;
                }
            }
        }
        return false;
    }
    bool visited(list<pair<int, string>> *visitedPairs, int user, string job)
    {
        for(auto & pair: *visitedPairs){
            if(pair.first == user && pair.second == job ){
                return true;
            }
        }
        return false;
    }
    bool swapJob(string job, int oldUser, int newUser)
    {
        for (auto &userJob : userJobs[oldUser])
        {
            int userFilled = getJobMatch(userJob);
            if (userFilled == -1)
            {
                jobsMatches.push_back(make_pair(userJob, oldUser));
                replaceMatch(job, newUser);
                return true;
            }
        }
        return false;
    }
    int greedy()
    {
        std::vector<std::string> jobs;
        for (int i = 0; i < usersCount; i++)
        {
            for(auto & job: userJobs[i]){
                auto it = std::find(jobs.begin(), jobs.end(), job);
                if(it == jobs.end()){
                    jobs.push_back(job);
                    break;
                }
            }
       }
        return jobs.size();
    }
    bool jobIsEmpty(list<string> jobs, string job)
    {
        for(auto & jobName:jobs){
            if(jobName== job){
                return false;
            }
        }
        return true;
    }
};