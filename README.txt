Othello CS2 Final Project
By: Kavya Sreedhar and Shweta Dutta, aka Team AnnEnbErg

Describe how and what each group member contributed for the past two weeks.

We wrote and tested all the code together, meeting in Annenberg lab. We would trade
 off typing on each other's laptops and brainstormed ideas together. We first
 implemented a random player and then moved on to implement a basic heuristic. We
 then refined our intial heuristic implementation to beat SimplePlayer consistently. 

We also fixed an issue where we hard-coded what side we played and then Shweta worked
 on and implemented 2 and 3 layer minimax to beat ConstantTimePlayer.

Document the improvements your group made to your AI to make it tournament-worthy.
 Explain why you think your strategy(s) will work. Feel free to discuss any ideas
 that were tried but didn't work out.

- We took out our hardcoding of our bot as side black so that we could play both sides.
- We implemented minimax to 2 layers with the simple (number of squares we have -
 number of squares opponent has) heuristic. We thought this strategy would work
 because minimax looks more than just our next move, but also takes into account what
 move our opponent could counter our next move with that would minimize our score.
 This strategy still consistently beat SimplePlayer, but did not consistently beat
 ConstantTimePlayer, so we decided to experiment more with heuristics.
- We improved our heuristic to weight every square on the board according to a paper
 we found. We thought this strategy would work because this weights squares on the
 board depending on how "good" of a spot each square is. For example, we weighted
 corners highly because they are stable and once taken, cannot be taken away by our
 opponent, whereas squares next to corners were weighted negatively since they could
 give our opponent access to corners and more stable positions.
- we implemented minimax to 3 layers with the heuristic described in the above bullet
 point. We thought this strategy would work because the first layer involved choosing
 our best move, the second layer entailed assuming our opponent's are trying to
 minimize are score using our heuristic and choose the worst possible move for us,
 and the 3rd layer had us choosing our best move to minimize our risk and maximize
 our score given the two previous moves.
- We also tried to change the values of the weights in the heuristic, particularly
 for squares near corners. If we were considering a square near a corner and we had
 already taken the appropriate corner square, we weighted that adjacent square
 positively whereas if we did not have that corner square, we weighted it negatively.
 We thought this would be a good strategy because always weighting that move
 negatively even when we have a corner (which means this new square would be stable)
 might actually make us miss out on moves that could potentially increase our number
 of stable squares and our overall standing. However, this strategy did not pan out
 as well in implementation and we saw ourselves lose about 50% of the time to
 SimplePlayer, which we had previously been consistently beating with our simple
 heuristic.

References:
https://courses.cs.washington.edu/courses/cse573/04au/Project/mini1/RUSSIA/Final_Paper.pdf