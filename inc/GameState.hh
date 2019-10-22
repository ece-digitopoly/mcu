#ifndef GAMESTATE_HH_
#define GAMESTATE_HH_

class GameState {
public:
    GameState();
    virtual ~GameState();

    int player_money[4];
};
#endif /* GAMESTATE_HH_ */
