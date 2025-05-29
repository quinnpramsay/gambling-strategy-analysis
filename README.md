# Gambling Strategy Analysis
As me and my friends at university have all turned 21 the notion of gambling has been brought around. As I am not a big gambler myself but I see others heading to casino's and online betting sites it drew my attention as someone who is studying statistical analysis and probability. I began to question, it is a well known fact that gambling is a losing game, but do there exists strategies that I can write models for and test that have positive EV outcomes above the normal. My goal with this project is to look into different casino games and try out different strategies at different levels. Now it is time to see, are there good strategies, or is it all a get rich quick falsehood and a losing game?

# Roulette
Roulette is one of the more popular games and the first game that came to my mind when talking about beating the odds at the casino and different strategical approaches. First off we need to look at all of the different outcomes percentages and payouts. 

Now assuming we are dealing with a double 0 roulette board, here are all the seperate outcomes:

- Red (ball lands on a number the color red): 47% chance / 1 to 1 payout
- Black (ball lands on a number the color black): 47% chance / 1 to 1 payout
- 1 - 18 (ball lands on a number from 1 to 18): 47% chance / 1 to 1 payout
- Even (ball lands on an even number): 47% chance / 1 to 1 payout
- Odd (ball lands on an odd number): 47% chance / 1 to 1 payout
- 19 - 36 (ball lands on a number from 19 to 36): 47% chance / 1 to 1 payout
- 1st 12 (ball lands on a number from 1 to 12): 31.6% chance / 2 to 1 payout
- 2nd 12 (ball lands on a number from 13 to 24): 31.6% chance / 2 to 1 payout
- 3rd 12 (ball lands on a number from 25 to 36): 31.6% chance / 2 to 1 payout
- Column bets (betting on one of the three vertical columns on the table): 31.6% chance / 2 to 1 payout
- Single number (Straight up): 1 in 38 chance (2.63%) / 35 to 1 payout
- Split bet (betting on two adjacent numbers): 2 in 38 chance (5.26%) / 17 to 1 payout
- Street bet (betting on a row of three numbers): 3 in 38 chance (7.89%) / 11 to 1 payout
- Corner bet (betting on a block of four numbers): 4 in 38 chance (10.5%) / 8 to 1 payout
- Line bet (betting on two adjacent rows – six numbers): 6 in 38 chance (15.8%) / 5 to 1 payout

# Roulette: First Step

First thing I did witht the roulette analysis was build my own roulette game program to get a feel of how it works and how it could be applied to a strategy. The code in provided within this github repository. I wanted to test out how this would work and how the outcomes would be and trends would be not only on a large scale but also playing the game spin by spin myself. Obviously as I didn't understand any of the strategy's or the game yet, I lost. 

# Roulette: Martingale Strategy






