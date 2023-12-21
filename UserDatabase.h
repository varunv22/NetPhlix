#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"
#include "User.h"

class User;
class UserDatabase
{
  public:
    UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;
    ~UserDatabase(){
        for(int x = 0; x < userP.size(); x++){
            delete userP[x];
            userP[x] = nullptr;
        }
    }

  private:
    bool loaded = false;
    TreeMultimap<std::string, User*> Users;
    std::vector<User*> userP;
};

#endif // USERDATABASE_INCLUDED
