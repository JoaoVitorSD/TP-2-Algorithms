#include <iostream>
#include <list>

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
    }

    bool swapJob(string job, int oldUser, int newUser)
    {
        for (auto &userJob : userJobs[oldUser])
        {
            if (getJobMatch(userJob)==-1)
            {
                jobsMatches.push_back(make_pair(userJob, newUser));
                replaceMatch(job, newUser);
                return true;
            }
        }
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
            matchesCounter +=matchUserJob(user);
        }
        return matchesCounter;
    }
    int matchUserJob(int user){
        for (auto &job : userJobs[user])
        {
            int indexFilled = getJobMatch(job);
            if (indexFilled == -1)
            {
                jobsMatches.push_back(make_pair(job, user));
                return true;
            }
            else
            {
                if (swapJob(job, indexFilled, user))
                {
                    return true;
                }
            }
        }
        return false;
    }
};