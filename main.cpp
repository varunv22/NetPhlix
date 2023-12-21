#include "UserDatabase.h"
#include "treemm.h" // DELETE THIS;
#include "User.h"
#include <iostream>
#include <string>
#include "MovieDatabase.h"
#include "Movie.h"
#include "Recommender.h"

using namespace std;

//////////////////////////i/////////////////////////////////////////////////////
//
// You are free to do whatever you want with this file, since you won't
// be turning it in.  Presumably, you will make changes to help you test
// your classes.  For example, you might try to implement only some User
// member functions to start out with, and so replace our main routine with
// one that simply creates a User and verifies that the member functions you
// implemented work correctly.
//
//////////////////////////i/////////////////////////////////////////////////////


  // If your program is having trouble finding these files. replace the
  // string literals with full path names to the files.  Also, for test
  // purposes, you may want to create some small, simple user and movie
  // data files to makde debuggiing easier, so you can replace the string
  // literals with the names of those smaller files.

const string USER_DATAFILE  = "users.txt";
const string MOVIE_DATAFILE = "movies.txt";

void findMatches(const Recommender& r, const MovieDatabase& md, const string& user_email, int num_recommendations) {
 // get up to ten movie recommendations for the user
    vector<MovieAndRank> recommendations = r.recommend_movies(user_email, num_recommendations);
    if (recommendations.empty())
        cout << "We found no movies to recommend :(.\n";
    else {
        for (int i = 1; i < recommendations.size() + 1; i++) {
            const MovieAndRank& mr = recommendations[i - 1];
            Movie* m = md.get_movie_from_id(mr.movie_id);
            cout << i << ". " << m->get_title() << " ("
            << m->get_release_year() << ")\n Rating: "
            << m->get_rating() << "\n Compatibility Score: "
            << mr.compatibility_score << "\n" << endl; 
        }
    }
}


int main()
{
    MovieDatabase udb;
    UserDatabase mdb;
    if(!udb.load("movies.txt")){
        cerr << "Didn't load movie!" << endl;
        return 0;
    }
    if(!mdb.load("users.txt")){
        cerr << "Didn't load user!" << endl;
        return 0;
    }
    for (;;)
    {
        cout << "Enter movieID (or quit): ";
        string email = "climberkip@gMail.com";
        getline(cin, email);
        if (email == "quit")
            return 0;
//            Movie* u = udb.get_movie_from_id(email);
//                if (u == nullptr)
//                    cout << "No movie in the database has that ID." << endl;
        else{
//                    vector<Movie*> res = udb.get_movies_with_genre(email);
//                        for(int x = 0; x < res.size(); x++){
//                            cout << res[x]->get_title() << endl;
//                        }
//                        cout << u->get_title() << endl;
            //        }
            
            //        Recommender x(mdb, udb);
            //        x.recommend_movies(email, 10);
            
            findMatches(Recommender(mdb, udb), udb, email, 10);
        }
    }
    
    
    
}
