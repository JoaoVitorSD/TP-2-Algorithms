#include <iostream>
#include<list>
#include "graph.hpp"
#define INF 0x3f3f3f3f

using namespace std;
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

bool compare( UserJobsOfer * u1, UserJobsOfer * u2)
{
    return u1->getJobsCount() < u2->getJobsCount();
}

int main(int argc, char const *argv[]){
    // Lendo a Entrada
    int users, jobs, ofers;
    cin>> users>> jobs>> ofers;
    list<UserJobsOfer*>  userJobs = list<UserJobsOfer*>();
    string name, job, lastName;
    cin>> name>> job;
    lastName = name;
    UserJobsOfer  * userJobsOfer = new UserJobsOfer(name, job);
    for (int i = 1; i < ofers; i++)
    {
        // Se o usuário desta interação for diferente da passada, salva o usuário e suas ofertas em uma lista separada
        cin >> name >> job;
        if(name==lastName){
            userJobsOfer->addJob(job);
            
        }else{
            userJobs.push_back(userJobsOfer);
            userJobsOfer =  new UserJobsOfer(name, job);
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
    // Montando o grafo
    Graph * graph = new Graph(users);
    int i = 0;
    for(auto & u: userJobs){
        list<string>  jobList = u->getJobs();
        for(auto & jobName : jobList){
            graph->addJob(i, jobName);
        }
        i++;
    }
    // *******************
    std::cout<< "Guloso: "<<graph->greedy()<<endl;
    std::cout << "Exato: " << graph->perfectMatch() << endl;
    return 0;
}
