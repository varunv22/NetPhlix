#include "Recommender.h"
#include "UserDatabase.h"
#include "MovieDatabase.h"
#include "User.h"
#include "Movie.h"

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
using namespace std;


vector<MovieAndRank> Recommender::recommend_movies(const string& user_email, int movie_count) const
{
    if(movie_count <= 0){
        return vector<MovieAndRank>();
    }

    User* m_user = m_ud.get_user_from_email(user_email);

    if(m_user == nullptr){
        return vector<MovieAndRank>();
    }

    vector<string> movieswatched = m_user->get_watch_history();
    unordered_map<string, int> compatability_scores;

    for(int x = 0; x < movieswatched.size(); x++){
        Movie* m_movie = m_md.get_movie_from_id(movieswatched[x]);
        vector<string> dirs = m_movie->get_directors();
        for(int i = 0; i < dirs.size(); i++){
            vector<Movie*> moviesbydirs = m_md.get_movies_with_director(dirs[i]);
            for(int v = 0; v < moviesbydirs.size(); v++){
                    compatability_scores[moviesbydirs[v]->get_id()] += 20;
            }
        }

        vector<string> m_actors = m_movie->get_actors();
        for(int i = 0; i < m_actors.size(); i++){
            vector<Movie*> moviesbyactrs = m_md.get_movies_with_actor(m_actors[i]);
            for(int v = 0; v < moviesbyactrs.size(); v++){
                    compatability_scores[moviesbyactrs[v]->get_id()] += 30;
            }
        }


        vector<string> m_genres = m_movie->get_genres();
        for(int i = 0; i < m_genres.size(); i++){
            vector<Movie*> moviesbygenres = m_md.get_movies_with_genre(m_genres[i]);
            for(int v = 0; v < moviesbygenres.size(); v++){
                    compatability_scores[moviesbygenres[v]->get_id()] += 1;
            }
        }
    }



    for (auto it = movieswatched.begin(); it != movieswatched.end(); it++) {
          compatability_scores.erase((*it));
    }

    vector<MovieAndRank> result;
    for(auto b : compatability_scores){
        result.push_back(MovieAndRank(b.first, b.second));
    }

    
    sort(result.begin(), result.end(), [&](const MovieAndRank& a, const MovieAndRank& b) {
        if (a.compatibility_score != b.compatibility_score) {
            return b.compatibility_score < a.compatibility_score;
        }
        float a_rating = m_md.get_movie_from_id(a.movie_id)->get_rating();
        float b_rating = m_md.get_movie_from_id(b.movie_id)->get_rating();
        if (a_rating != b_rating) {
            return b_rating < a_rating;
        }
        string a_name = m_md.get_movie_from_id(a.movie_id)->get_title();
        string b_name = m_md.get_movie_from_id(b.movie_id)->get_title();
        return b_name > a_name;
    });
    
    

    vector<MovieAndRank> result2;
    unsigned long int stp;

    if(result.size() < movie_count){
        stp = result.size();
    } else{
        stp = movie_count;
    }
    for(int s = 0; s < stp; s++){
        result2.push_back(result[s]);
    }

    return result2;
}

