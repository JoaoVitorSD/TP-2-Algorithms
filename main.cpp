#include <iostream>
#include<list>
#include "graph.hpp"
#define INF 0x3f3f3f3f

using namespace std;
class User
{
public:
    string name;
    list<string> jobs;

    User(string name)
    {
        this->name = name;
        jobs = list<string>();
    }

    User(string name, list<string> jobs)
    {
        this->name = name;
        this->jobs = jobs;
    }
    void addJob(string job)
    {
        jobs.push_back(job);
    }
};
class UserJobsOfer{
    public:
        string getName() { return name; }
        int getJobsCount() { return this->jobs.size();}
        void addJob(string job) { jobs.push_back(job);}
        list<string>  getJobs() { return jobs;}
        UserJobsOfer(const string& name,const  string& job){
            this->name = name;
            this->jobs =  list<string>();
            this->jobs.push_back(job);
        }
   
    private:
        std::string name;
        std::list<string>  jobs;
};
bool notMatchedJob(list<pair<User,string>> *matches, string job){
    for(const auto& s: *matches){
        if(s.second==job){
            return false;
        }
    }
    return true;
}
int greedy(list<UserJobsOfer *>  jobOfers, int jobs)
{
    list<pair<User,string>> * matches = new list<pair<User, string>>;
    for(auto & userJob: jobOfers)
    {
        list<string> jobs = userJob->getJobs();
        for(auto & job: jobs){
        if(notMatchedJob(matches, job)){
            matches->push_back(make_pair(User(userJob->getName(), jobs),job)); 
            break;
        }
        }
    }
    return matches->size();
}
bool trySwapJob(list<pair<User, string>> *matches, string user, list<string> jobList, string job)
{
    for (auto it = matches->begin(); it != matches->end(); ++it)
    {
        if (it->second == job)
        {
        for (auto &userJobs : it->first.jobs)
        {
            if (notMatchedJob(matches, userJobs))
            {
                matches->push_back(make_pair(User(user, jobList), job));
                it->second = userJobs;
                return true;
            }
        }
        }
    }
    return false;
}
bool compare( UserJobsOfer  u1, UserJobsOfer u2)
{
    return u1.getJobsCount() < u2.getJobsCount();
}

bool compareMatch(const pair<User, string> p1, const pair<User, string> &p2)
{
    return p1.first.name.compare(p2.first.name);
}
int main(int argc, char const *argv[]){
    // Lendo a Entrada
    int users, jobs, ofers;
    cin>> users>> jobs>> ofers;
    list<UserJobsOfer>  userJobs = list<UserJobsOfer>();
    string name, job, lastName;
    cin>> name>> job;
    lastName = name;
    UserJobsOfer  userJobsOfer =  UserJobsOfer(name, job);
    for (int i = 1; i < ofers; i++)
    {
        cin >> name >> job;
        if(name==lastName){
            userJobsOfer.addJob(job);
            
        }else{
            userJobs.push_back(userJobsOfer);
            userJobsOfer =  UserJobsOfer(name, job);
        }
        if (i == ofers - 1)
        {
            userJobs.push_back(userJobsOfer);
        }
        lastName = name;
    }
    // ************
    // Ordenando a lista, para evitar verificações de vagas livres
    userJobs.sort(compare);
    // ************
    Graph graph = Graph(users);
    int i = 0;
    for(auto & u: userJobs){
        list<string>  jobList = u.getJobs();
        for(auto & job : jobList){
            graph.addJob(i, job);
        }
        i++;
    }
    // std::cout<< "Guloso: "<<greedy(userJobs, ofers)<<endl; 
    std::cout << "Exato: " << graph.exact()<< endl;
    return 0;
}
