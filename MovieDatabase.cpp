#include "MovieDatabase.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

MovieDatabase::MovieDatabase(){}

MovieDatabase::~MovieDatabase(){
    for(int x = 0; x < movieP.size(); x++){
        delete movieP[x];
        movieP[x] = nullptr;
    }
}


bool MovieDatabase::load(const string& filename)
{
    ifstream file(filename);
    if(!file || loaded == true){
        return false;
    }
    loaded = true;
    string s;
    
    while (file.peek() != EOF) {
        string movieID;
        string movieName;
        string movieYear;
        vector<string> movieDirs;
        vector<string> movieActors;
        vector<string> movieGenres;
        float movieRating;
        
        getline(file, movieID);
        getline(file, movieName);
        getline(file, movieYear);
        
        string ln;
        getline(file, ln);
        stringstream ss(ln);
        string name;
        while (getline(ss, name, ',')) {
            while (!name.empty() && isspace(name.front())) name.erase(name.begin());
            while (!name.empty() && isspace(name.back())) name.pop_back();
            if (!name.empty()) {
                movieDirs.push_back(name);
            }
        }
        
        getline(file, ln);
        stringstream ss2(ln);
        string name2;
        while (getline(ss2, name2, ',')) {
            while (!name2.empty() && isspace(name2.front())) name2.erase(name2.begin());
            while (!name2.empty() && isspace(name2.back())) name2.pop_back();
            if (!name2.empty()) {
                movieActors.push_back(name2);
            }
        }
        
        
        
        getline(file, ln);
        stringstream ss3(ln);
        string name3;
        while (getline(ss3, name3, ',')) {
            while (!name3.empty() && isspace(name3.front())) name3.erase(name3.begin());
            while (!name3.empty() && isspace(name3.back())) name3.pop_back();
            if (!name3.empty()) {
                movieGenres.push_back(name3);
            }
        }
        
        
        file >> movieRating;
        file.ignore(10000, '\n');
        
        Movie* x = new Movie(movieID, movieName, movieYear, movieDirs, movieActors, movieGenres, movieRating);
        movieP.push_back(x);
        
        makeLowercase(movieID);
        Movies.insert(movieID, x);
        
        for(int y = 0; y < movieDirs.size(); y++){
            makeLowercase(movieDirs[y]);
            Dirs.insert(movieDirs[y], x);
        }
        for(int y = 0; y < movieActors.size();y++){
            makeLowercase(movieActors[y]);
            Actors.insert(movieActors[y], x);
        }
        for(int y = 0; y < movieGenres.size();y++){
            makeLowercase(movieGenres[y]);
            Genres.insert(movieGenres[y], x);
        }
        file.ignore(10000,'\n');
    }
    
    return true;
}

Movie* MovieDatabase::get_movie_from_id(const string& id) const
{
    string l_id = Lowercase(id);
    TreeMultimap<std::string, Movie*>::Iterator x;
    x = Movies.find(l_id);
    if(x.is_valid()){
        return x.get_value();
    } else{
        return nullptr;
    }
    
}

vector<Movie*> MovieDatabase::get_movies_with_director(const string& director) const
{
    string dir = Lowercase(director);
    TreeMultimap<std::string, Movie*>::Iterator x;
    x = Dirs.find(dir);
    vector<Movie*> v;
    if(x.is_valid()){
        while(x.is_valid()){
            v.push_back(x.get_value());
            x.advance();
        }
    } else{
        return v;
    }
    return v;
}

vector<Movie*> MovieDatabase::get_movies_with_actor(const string& actor) const
{
    string m_actor = Lowercase(actor);
    TreeMultimap<std::string, Movie*>::Iterator x;
    x = Actors.find(m_actor);
    vector<Movie*> v;
    if(x.is_valid()){
        while(x.is_valid()){
            v.push_back(x.get_value());
            x.advance();
        }
    } else{
        return v;
    }
    return v;
}

vector<Movie*> MovieDatabase::get_movies_with_genre(const string& genre) const
{
    string m_genre = Lowercase(genre);
    TreeMultimap<std::string, Movie*>::Iterator x;
    x = Genres.find(m_genre);
    vector<Movie*> v;
    if(x.is_valid()){
        while(x.is_valid()){
            v.push_back(x.get_value());
            x.advance();
        }
    } else{
        return v;
    }
    return v;
}
