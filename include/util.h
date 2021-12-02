#include <vector>
#include <string>
#include <dirent.h>
#include <stdlib.h>
class Util
{
private:
    /* data */
public:

    static bool is_numeric(std::string dirname) {
        for(char& ch:dirname) {
            if(ch > 57 || ch < 48) return false;
        } return true;
    }
    static std::vector<std::string> getDirs() {
        DIR *dir;
        dirent *ent;
        std::vector<std::string> dirs;
        if ((dir = opendir ("/proc/")) != NULL) {
            while ((ent = readdir (dir)) != NULL) {
                if(ent->d_type == DT_DIR) {
                    if(is_numeric(std::string(ent->d_name)))
                        dirs.push_back(std::string(ent->d_name));
                }
            }
            closedir (dir);
        } else {
            /* could not open directory */
            perror ("");
        }
        return dirs;
    }
};