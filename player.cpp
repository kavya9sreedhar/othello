#include "player.hpp"

/*
 * Constructor for the player; initialize everything here. The side your AI is
 * on (BLACK or WHITE) is passed in as "side". The constructor must finish
 * within 30 seconds.
 */
Player::Player(Side side) {
    // Will be set to true in test_minimax.cpp.
    testingMinimax = false;

    our_side = side;

    other_side = (side == WHITE) ? BLACK : WHITE; // TERNARY OPERATOR GET HYPE

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

int Player::applyHeuristic(Board *board)
{
    int score = 0;

    for (int i = 0; i < SIZE_LEN; i++) 
    {
        for (int j = 0; j < SIZE_LEN; j++)
        {
            if (board->ourside_taken(i, j, our_side)) 
            {
                score += static_heuristic[i + 8*j];
            }
            
        }
    }

    return score;
}

int Player::get_worst_case(Board *board) 
{
    Board *copy = board->copy();

    Move *next = new Move(0, 0);

    int worst_score = BEST_SCORE + 1;

    int worst_x = -1;
    int worst_y = -1;

    int check;

    for (int i = 0; i < SIZE_LEN; i++) 
    {
        for (int j = 0; j < SIZE_LEN; j++)
        {   
            check = 0;
            copy = board->copy();
            *next = Move(i, j);
            if (board->checkMove(next, other_side))
            {
                copy->doMove(next, other_side);                
                check = applyHeuristic(copy);

                if (check < worst_score) 
                {
                    worst_score = check;
                    worst_x = i;
                    worst_y = j;
                }
            }

        }
    }

    if (worst_score == BEST_SCORE + 1) // means no legal moves were found for the other team
    {
        delete next;
        return BEST_SCORE; // This is a great move if it gets the other team stuck
    }

    *next = Move(worst_x, worst_y);
    copy = board->copy();
    copy->doMove(next, other_side);

    Board *next_copy = copy->copy();

    worst_score = BEST_SCORE + 1;

    for (int i = 0; i < SIZE_LEN; i++) 
    {
        for (int j = 0; j < SIZE_LEN; j++)
        {   
            check = 0;
            next_copy = copy->copy();
            *next = Move(i, j);
            if (board->checkMove(next, other_side))
            {
                copy->doMove(next, other_side);                
                check = applyHeuristic(next_copy);

                if (check < worst_score) 
                {
                    worst_score = check;
                }
            }

        }
    }

    if (worst_score == BEST_SCORE + 1) // means no legal moves were found for our team
    {
        delete next;
        return WORST_SCORE; // this is definitely a bad move
    }

    delete next;
    return worst_score;
}

Move *Player::doMove(Move *opponentsMove, int msLeft) {
    /*
     * TODO: Implement how moves your AI should play here. You should first
     * process the opponent's opponents move before calculating your own move
     */

    board.doMove(opponentsMove, other_side);

    int best_x = -1;
    int best_y = -1;

    int minimax = WORST_SCORE - 1;
    int check;

    Board *copy = board.copy();
    Move *next = new Move(0, 0);
    for (int x = 0; x < SIZE_LEN; x++)
    {
        for (int y = 0; y < SIZE_LEN; y++)
        {
            copy = board.copy();
            *next = Move(x, y);
            if (board.checkMove(next, our_side))
            {
                copy->doMove(next, our_side);
                
                check = get_worst_case(copy);
                if (check > minimax) 
                {
                    minimax = check;
                    best_x = x;
                    best_y = y;
                }
            }
        }
    }

    if ( minimax == WORST_SCORE - 1 ) // we didn't find any legal moves for us
    {
        return nullptr;
    }

    *next = Move(best_x, best_y);
    board.doMove(next, our_side);
    return next;
}