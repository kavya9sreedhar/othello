#include "player.hpp"

// This is a small change to practice using git :P

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    board = Board();

    /*
     * TODO: Do any initialization you need to do here (setting up the board,
     * precalculating things, etc.) However, remember that you will only have
     * 30 seconds.
     */
}

/*
 * Destructor for the player.
 */
Player::~Player() {
}

/*
 * Compute the next move given the opponent's last move. Your AI is
 * expected to keep track of the board on its own. If this is the first move,
 * or if the opponent passed on the last move, then opponentsMove will be
 * nullptr.
 *
 * msLeft represents the time your AI has left for the total game, in
 * milliseconds. doMove() must take no longer than msLeft, or your AI will
 * be disqualified! An msLeft value of -1 indicates no time limit.
 *
 * The move returned must be legal; if there are no valid moves for your side,
 * return nullptr.
 */
Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    board.doMove(opponentsMove, WHITE);

    int max_x = -1;
    int max_y = -1;
    int max_score;

    bool valid = false;

    Board *copy = board.copy();
    Move *next = new Move(0, 0);
    for (int x = 0; x < SIZE_LEN; x++)
    {
        for (int y = 0; y < SIZE_LEN; y++)
        {
            copy = board.copy();
            *next = Move(x, y);

            if (board.checkMove(next, BLACK))
            {
                std::cerr << "Valid move" << std::endl;
                copy->doMove(next, BLACK);
                if (valid == false)
                {
                    max_score = copy->count(BLACK) - copy->count(WHITE);
                    max_x = next->getX();
                    max_y = next->getY();
                    std::cerr << "max_x 1: " << max_x << "max_y 1" << max_y << std::endl; 
                    if ( (x == 0 and y == 0) 
                        or (x == (SIZE_LEN - 1) and y == 0) 
                        or (x == 0 and y == (SIZE_LEN - 1)) 
                        or (x == (SIZE_LEN - 1) and y == (SIZE_LEN - 1)) )
                    {
                        max_score *= CORNER_MUL;
                    }

                    if ((x == 0) or (y == 0) or (x == SIZE_LEN - 1) or (y == SIZE_LEN - 1))
                    {
                        max_score *= EDGE_MUL;
                    }

                    if ((x == 1 and y == SIZE_LEN - 2) or 
                        (x == 1 and y == 1) or 
                        (x == SIZE_LEN - 2 and y == 1) or 
                        (x == SIZE_LEN - 2 and y == SIZE_LEN - 2))
                    {
                        max_score *= DIAG_CORN;
                    }

                    if ((x == 0 and y == 1) or (x == 0 and y == SIZE_LEN - 2) or
                        (x == SIZE_LEN - 1 and y == 1) or (x == SIZE_LEN - 1 and y == SIZE_LEN - 2) or
                        (x == 1 and y == 0) or (x == 1 and y == SIZE_LEN - 1) or
                        (x == SIZE_LEN - 2 and y == 0) or (x == SIZE_LEN - 2 and y == SIZE_LEN - 1))
                    {
                        max_score *= OTHER_CORN;
                    }

                    valid = true;
                }

                int difference = copy->count(BLACK) - copy->count(WHITE);
                
                std::cerr << copy->count(WHITE) << " " << copy->count(BLACK) << std::endl;
                std::cerr << "max_x 2: " << max_x << "max_y 2" << max_y << std::endl; 

                if ( (x == 0 and y == 0) 
                    or (x == (SIZE_LEN - 1) and y == 0) 
                    or (x == 0 and y == (SIZE_LEN - 1)) 
                    or (x == (SIZE_LEN - 1) and y == (SIZE_LEN - 1)) )
                {
                    difference *= CORNER_MUL;
                }

                if ((x == 0) or (y == 0) or (x == SIZE_LEN - 1) or (y == SIZE_LEN - 1))
                {
                        difference *= EDGE_MUL;
                }

                if ((x == 1 and y == SIZE_LEN - 2) or 
                        (x == 1 and y == 1) or 
                        (x == SIZE_LEN - 2 and y == 1) or 
                        (x == SIZE_LEN - 2 and y == SIZE_LEN - 2))
                {
                        difference *= DIAG_CORN;
                }

                if ((x == 0 and y == 1) or (x == 0 and y == SIZE_LEN - 2) or
                        (x == SIZE_LEN - 1 and y == 1) or (x == SIZE_LEN - 1 and y == SIZE_LEN - 2) or
                        (x == 1 and y == 0) or (x == 1 and y == SIZE_LEN - 1) or
                        (x == SIZE_LEN - 2 and y == 0) or (x == SIZE_LEN - 2 and y == SIZE_LEN - 1))
                {
                        difference *= OTHER_CORN;
                }

                if (difference > max_score)
                {
                    max_x = next->getX();
                    max_y = next->getY();
                    max_score = difference;
                    std::cerr << "max_x 3: " << max_x << "max_y 3" << max_y << std::endl; 
                    std::cerr << "updating...max_score: " << max_score << std::endl;
                }

                
            }
        }
    }


    std::cerr << "DONE max_x is " << max_x << std::endl;

    if ( max_x == -1 )
    {
        std::cerr << "null, max_x is " << max_x << std::endl;
        return nullptr;
    }

    *next = Move(max_x, max_y);
    board.doMove( next, BLACK );
    return next;
    
}
