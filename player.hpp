#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include "common.hpp"
#include "board.hpp"
using namespace std;

#define CORNER_MUL 3
#define EDGE_MUL 2
#define DIAG_CORN -3
#define OTHER_CORN -2

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Side our_side;
    Side other_side;
    Board board;
};

#endif
