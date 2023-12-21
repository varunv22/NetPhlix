#include "UserDatabase.h"
#include "User.h"

#include <string>
#include <vector>
#include <fstream>
using namespace std;

UserDatabase::UserDatabase()
{}

bool UserDatabase::load(const string& filename)
{
    ifstream file(filename);
    if(!file || loaded == true){
        return false;
    }
    loaded = true;
    string s;
    while (file.peek() != EOF) {
        string m_name;
        string m_email;
        int n_movies;
        vector<string> movieID;
        getline(file, m_name);
        getline(file, m_email);
        file >> n_movies;
        file.ignore(10000,'\n');
        for(int x = 0; x < n_movies; x++){
            string s_ID;
            getline(file, s_ID);
            movieID.push_back(s_ID);
        }
        User* x = new User(m_name, m_email, movieID);
        userP.push_back(x);
        Users.insert(m_email, x);
        file.ignore(10000,'\n');
    }
    return true;
    
}

User* UserDatabase::get_user_from_email(const string& email) const
{
    TreeMultimap<std::string, User*>::Iterator x;
    x = Users.find(email);
    if(x.is_valid()){
        return x.get_value();
    } else{
        return nullptr;
    }
    
}
