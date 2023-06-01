#include <iostream>
#include<list>
#define INF 0x3f3f3f3f

using namespace std;

class JobOfer{
    private:
        string name;
        string job;

    public: 
    string getName(){
        return this->name;
    }
    string getJob(){
        return this->job;
    }
    JobOfer(string name, string job){
        this->name  = name;
        this->job = job;
    }
    JobOfer(){};
};
bool notMatchedJob(list<string> *matches, string job){
    for(const auto& s: *matches){
        if(s==job){
            return false;
        }
    }
    return true;
}
int greedy(JobOfer **jobOfers, int jobs){
    string job = jobOfers[0]->getJob();
    list<string> * matches = new list<string>;
    matches->push_back(job);
    for(int i = 1;i<jobs;i++)
    {
        job = jobOfers[i]->getJob();
        if(notMatchedJob(matches, job)){
        matches->push_back(job);
        }
    }
    return matches->size();
}

    int main(int argc, char const *argv[])
{
    // Your code here
    int users, jobs, jobsOferCount;
    cin>> users>> jobs>> jobsOferCount;
    JobOfer **jobsOfer = new JobOfer*[jobsOferCount];
    for (int i = 0; i < jobsOferCount; i++)
    {
        string name, job;
        cin>> name>> job;
        jobsOfer[i] = new JobOfer(name, job);
    }

    std::cout<< "Guloso: "<<greedy(jobsOfer, jobsOferCount)<<endl;
    return 0;
}
