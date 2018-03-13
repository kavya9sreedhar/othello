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

#define WORST_SCORE -56
#define BEST_SCORE  56

class Player {

public:
    Player(Side side);
    ~Player();

    Move *doMove(Move *opponentsMove, int msLeft);
    int applyHeuristic(Board *board);
    int get_worst_case(Board *board);

    int static_heuristic [64] = { 4, -3,  2,  2,  2,  2, -3,  4,
                                 -3, -4, -1, -1, -1, -1, -4, -3,
                                  2, -1,  1,  0,  0,  1, -1,  2,
                                  2, -1,  0,  1,  1,  0, -1,  2,
                                  2, -1,  0,  1,  1,  0, -1,  2,
                                  2, -1,  1,  0,  0,  1, -1,  2,
                                 -3, -4, -1, -1, -1, -1, -4, -3,
                                  4, -3,  2,  2,  2,  2, -3,  4 };

    // Flag to tell if the player is running within the test_minimax context
    bool testingMinimax;
    Side our_side;
    Side other_side;
    Board board;
};

#endif
