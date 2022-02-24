#include <bits/stdc++.h>

using namespace std;

class Contributor {
public:
    string name;
    int numberOfSkills;
    map<string, int> skills;

    Contributor() {

    }

    Contributor(string _name, int _numberOfSkills, map<string, int> _skills) {
        name = _name;
        numberOfSkills = _numberOfSkills;
        skills = _skills;
    }


};

//class Skill{
//public:
//    string name;
//    vector<Contributor> cons;
//
//};

class Project {
public:
    string name;
    int days;
    int score;
    int bestBefore;
    int numberOfRoles;
    vector<pair<string, int>> roles;

    Project(string _name, int _days, int _score, int _bestBefore, int _numberOfRoles,
            vector<pair<string, int>> _roles) {
        name = _name;
        days = _days;
        score = _score;
        bestBefore = _bestBefore;
        numberOfRoles = _numberOfRoles;
        roles = _roles;
    }
};

int numberOfContributors, numberOfProjects;
vector<Contributor> contributors;
vector<Project> projects;
map<string, pair<int,Contributor>> maximumLevel;

vector<string> namesOfCons;
map<string,bool> taken;

bool canDo(Project p) {
    for (int i = 0; i < p.numberOfRoles; i++) {
        string skillName = p.roles[i].first;
        int level = p.roles[i].second;
        pair<int,Contributor> con = maximumLevel[skillName];
        if (con.first == level && !taken[maximumLevel[skillName].second.name]) {
            namesOfCons.push_back(maximumLevel[skillName].second.name);
            con.second.skills[skillName]++;
            taken[maximumLevel[skillName].second.name] = true;
        }else if (con.first > level && !taken[maximumLevel[skillName].second.name]) {
            namesOfCons.push_back(maximumLevel[skillName].second.name);
            taken[maximumLevel[skillName].second.name] = true;
        }else{
            return false;
        }
    }
    return true;
}


int main() {
    freopen("f.txt","r",stdin);
    freopen("fout.txt","w",stdout);
    cin >> numberOfContributors >> numberOfProjects;


    for (int i = 0; i < numberOfContributors; i++) {
        string n;
        int cntSkills;
        cin >> n >> cntSkills;
        map<string, int> skills;
        for (int j = 0; j < cntSkills; j++) {
            string skill;
            int level;
            cin >> skill >> level;
            skills[skill] = level;
        }
        Contributor c(n, cntSkills, skills);
        contributors.push_back(c);
    }

    for (int i = 0; i < numberOfContributors; i++) {
        for (auto skill: contributors[i].skills) {
            string name = skill.first;
            int level = skill.second;
            pair<int,Contributor> con = maximumLevel[name];
            if (con.first < level) {
                maximumLevel[name] = {level,contributors[i]};
            }
        }
    }

    for (int i = 0; i < numberOfProjects; i++) {
        string n;
        int d, s, b, r;
        cin >> n >> d >> s >> b >> r;
        vector<pair<string, int>> roles;
        for (int j = 0; j < r; j++) {
            string skill;
            int level;
            cin >> skill >> level;
            roles.push_back({skill, level});
        }
        Project p(n, d, s, b, r, roles);
        projects.push_back(p);
    }
    vector<pair<string,vector<string>>> output;
    sort(projects.begin(),projects.end(),[&](Project p1, Project p2){
        return p1.score / p1.days >  p2.score / p2.days;
    });
    int time = 0;
    for (int i = 0; i < numberOfProjects; i++) {
        if (canDo(projects[i]) && time < projects[i].bestBefore) {
            output.push_back({projects[i].name, namesOfCons});
            time += projects[i].days;
        }
        namesOfCons.clear();
        taken.clear();
    }
    cout << output.size() << endl;
    for(auto project : output){
        cout << project.first << endl;
        for(auto role : project.second){
            cout << role << ' ';
        }
        cout << endl;
    }
    return 0;
}
