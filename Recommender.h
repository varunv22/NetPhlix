#ifndef RECOMMENDER_INCLUDED
#define RECOMMENDER_INCLUDED

#include <string>
#include <vector>
#include "MovieDatabase.h"
#include "UserDatabase.h"
using namespace std;

class UserDatabase;
class MovieDatabase;

struct MovieAndRank
{
    MovieAndRank(const std::string& id, int score)
     : movie_id(id), compatibility_score(score)
    {}

    std::string movie_id;
    int compatibility_score;
};

class Recommender
{
  public:
    Recommender(const UserDatabase& user_database, const MovieDatabase& movie_database) : m_ud(user_database), m_md(movie_database){}
    std::vector<MovieAndRank> recommend_movies(const std::string& user_email, int movie_count) const;
  private:
    const UserDatabase& m_ud;
    const MovieDatabase& m_md;
    
};

#endif // RECOMMENDER_INCLUDED
