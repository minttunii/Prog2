#ifndef PLAYER_HH
#define PLAYER_HH

#include <string>

class Player
{
public:
    Player(const std::string& name);
    const std::string& get_name();
    int get_points();
    bool has_won();
    void add_points(int points);

private:
    std::string name_;
    int score_;
};

#endif // PLAYER_HH
