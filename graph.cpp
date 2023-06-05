
#include "graph.hpp"
Graph::Graph(int usersCount)
{
    this->userJobs = new list<string>[usersCount];
    this->usersCount = usersCount;
    this->jobUsers = list<pair<string, list<int>>>();
    this->jobsMatches = list<pair<string, int>>();
}
void Graph::addJob(int user, string jobName)
{
    this->userJobs[user].push_back(jobName);
}
int Graph::greedy()
{
    // Checa se o elemeto foi adicionado ao vetor, se sim, passa para o próxima oferta do usuário
    std::vector<std::string> jobs;
    for (int i = 0; i < usersCount; i++)
    {
        for (auto &job : userJobs[i])
        {
            auto it = std::find(jobs.begin(), jobs.end(), job);
            if (it == jobs.end())
            {
                jobs.push_back(job);
                break;
            }
        }
    }
    return jobs.size();
}
int Graph::perfectMatch()
{
    int matchesCounter = 0;
    // Tenta fazer um match de todos os usuários. Se a tentativa for bem sucessidada, adiciona ao contador como uma possibilidade válida
    for (int user = 0; user < usersCount; user++)
    {
        list<pair<int, string>> *visitedPairs = new list<pair<int, string>>();
        matchesCounter += matchUserJob(user, visitedPairs);
        delete visitedPairs;
    }
    return matchesCounter;
}
int Graph::matchUserJob(int user, list<pair<int, string>> *visitedPairs)
{
    for (auto &job : userJobs[user])
    {
        // Se não tiver sido visitado, ignora a iteracão 
        if (visited(visitedPairs, user, job))
        {
            continue;
        }
        // Adiciona o par usuároio - serviço a lista de visitados
        visitedPairs->push_back(make_pair(user, job));
        int indexFilled = getJobMatch(job);
        // Se o emprego não tiver um par, adiciona a lista de pares, se não, inicia uma chamada recursiva com o usuário que possui o emprego ocupado
        if (indexFilled == -1)
        {

            jobsMatches.push_back(make_pair(job, user));
            return true;
        }
        else
        {
            if (matchUserJob(indexFilled, visitedPairs))
            {
                // Substitui o par ocupado pelo outro usuario com o usuário atual 
                replaceMatch(job, user);
                return true;
            }
        }
    }
    return false;
}
int Graph::getJobMatch(string job)
{
    // Se um usuário está ocupando uma vaga, retorna seu número, se não, retorna -1
    for (auto &jobMatch : jobsMatches)
    {
        if (jobMatch.first == job)
        {
            return jobMatch.second;
        }
    }
    return -1;
}
bool Graph::visited(list<pair<int, string>> *visitedPairs, int user, string job)
{
    //  Checa se um par usuário - emprego foi preenchido como verdadeiro
    for (auto &pair : *visitedPairs)
    {
        if (pair.first == user && pair.second == job)
        {
            return true;
        }
    }
    return false;
}
void Graph::replaceMatch(string job, int newUser)
{
    // Substitui um par com o valor de um novo usuário
    for (auto &match : jobsMatches)
    {
        if (match.first == job)
        {
            match.second = newUser;
            return;
        }
    }
}