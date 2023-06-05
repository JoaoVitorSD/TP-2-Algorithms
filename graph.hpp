#include <iostream>
#include <list>
#include "jobnode.hpp"
class Graph{
    public: 
    list<JobNode*> jobs;
    bool ** bpGraph;
    list<pair<string, string>> matches;
    Graph(int jobs, int users){
        this->jobs =  list<JobNode*>();
    }

    list<pair<string, list<JobNode*> >> users;

    void addJob(string jobName, string userName){
        for(auto& job: jobs){
            if(job->name == job->name){
                job->addUser(userName);
                return;
            }
        }
        jobs.push_back(new JobNode(jobName, userName));
    }
    bool matchUser(string jobName, string userName){
        for (auto &job : jobs)
        {
            if (job->name == job->name && job->empty())
            {
                job->matchUser(userName);
                return true;
            }
        }
        return false;
    }
    list<string> * getUsers(string jobName){
        for(auto& job: jobs){
            if(job->name == jobName){
                return job->users;
            }
        }
    }
    bool swapJob(string userName,list<string> userJobs) {
        for (auto &job : userJobs)
        {
            if(matchUser(job, userName)){
                return true;
            }else{
                for(auto & user: *getUsers(job)){
                    if(swapJob()){

                    }
                }
            }
        }
    }
};