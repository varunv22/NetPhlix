#ifndef MOVIEDATABASE_INCLUDED
#define MOVIEDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class Movie;

class MovieDatabase
{
  public:
    MovieDatabase();
    bool load(const std::string& filename);
    Movie* get_movie_from_id(const std::string& id) const;
    std::vector<Movie*> get_movies_with_director(const std::string& director) const;
    std::vector<Movie*> get_movies_with_actor(const std::string& actor) const;
    std::vector<Movie*> get_movies_with_genre(const std::string& genre) const;
    ~MovieDatabase();

    

  private:
    bool loaded = false;
    TreeMultimap<std::string, Movie*> Movies;
    TreeMultimap<std::string, Movie*> Dirs;
    TreeMultimap<std::string, Movie*> Actors;
    TreeMultimap<std::string, Movie*> Genres;
    std::vector<Movie*> movieP;    
    void makeLowercase(std::string& x){
        for(char& c: x){
            c = tolower(c);
        }
    }
    std::string Lowercase(const std::string& x) const {
        std::string result = x;
        for(char& c : result){
            c = tolower(c);
        }
        return result;
    }
    
};

#endif // MOVIEDATABASE_INCLUDED
