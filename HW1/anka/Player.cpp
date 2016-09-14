#include "Player.hpp"
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>

namespace ducks
{



    Player::Player()
    {


    // VI BEHÖVER A B PI som random initsaker
    // Sekvens i form av flygväg.
    //A = State transition (Hur stor chans är det att vi går från state x till y?)
        std::vector<double> tmpA = {5,5
            ,0.1,0.2,0.1,0.2,0.4
            ,0.4,0.1,0.1,0.2,0.2
            ,0.6,0.1,0.1,0.1,0.1
            ,0.4,0.1,0.3,0.1,0.1
            ,0.1,0.1,0.6,0.1,0.1};
    //B = Emission probability (Hur stor chans är det att vi ser b i state a)?
            std::vector<double> tmpB = {5,9
                ,0.1 ,0.2, 0.1, 0.1, 0.05,0.05,0.1, 0.2, 0.1
                ,0.1 ,0.05,0.1, 0.1, 0.2, 0.1, 0.25,0.05,0.05
                ,0.05,0.15,0.05,0.2, 0.05,0.25,0.05,0.1, 0.1
                ,0.1 ,0.1, 0.15,0.05,0.1, 0.05,0.05,0.2, 0.2
                ,0.2 ,0.1, 0.05,0.15,0.15,0.05,0.1, 0.1, 0.1};

                std::vector<double> tmpPI = {1,9
                    ,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.1,0.2}; 


    //std::cerr << "A load" << std::endl;
                    A.resize(tmpA[0]);
                    int iter = 2;
                    for(int i = 0; i < A.size(); ++i){
                        A[i].resize(tmpA[1]);
                        for(int j = 0; j < A[i].size(); ++j){
            //std::cerr << "i " << i << " j " << j << " iter " << iter << std::endl;
                            A[i][j] = tmpA[iter];
                            ++iter;
                        }
                    }


    //std::cerr << "B load" << std::endl;
                    B.resize(tmpB[0]);
                    iter = 2;
                    for(int i = 0; i < B.size(); ++i){
                        B[i].resize(tmpB[1]);
                        for(int j = 0; j < B[i].size(); ++j){
                            B[i][j] = tmpB[iter];
                            ++iter;
                        }
                    }

    //std::cerr << "PI load" << std::endl;
                    PI.resize(tmpPI[0]);
                    iter = 2;
                    for(int i = 0; i < PI.size(); ++i){
                        PI[i].resize(tmpPI[1]);
                        for(int j = 0; j < PI[i].size(); ++j){
                            PI[i][j] = tmpPI[iter];
                            ++iter;
                        }
                    }

                }

                std::vector<std::string> direction = {
                    "MOVE_DEAD",
                    "MOVE_UP_LEFT",
                    "MOVE_UP",
                    "MOVE_UP_RIGHT",
                    "MOVE_LEFT",
                    "MOVE_STOPPED",
                    "MOVE_RIGHT",
                    "MOVE_DOWN_LEFT",
                    "MOVE_DOWN",
                    "MOVE_DOWN_RIGHT",
                    "COUNT_MOVE"};

/* Migrating circling hunting drilling zig-zag
    Pigeon: vanlig                        -> Random
    Raven: flock, försvarar sitt område   -> 
    skylark:  Flyger upp o ner. Mating    -> 
    Swallow: Hunting, gliding, circling
    Snipe: Migrating, Cirklar, dives,  zig-zag
    Stork: Rare, i par, 
*/
    Action Player::shoot(const GameState &pState, const Deadline &pDue)
    {
    //std::cout << "roundcount: " << pState.getRound() << std::endl;
        if(old_round != pState.getRound()){
            init = true;
            old_round = pState.getRound();
        }

        if(init){
            init = false;
            birdcomps.clear();
            birdcomps.resize(pState.getNumBirds());
            for(int i = 0; i < pState.getNumBirds(); ++i){
                BirdComp b;
                b.A = A;
                b.B = B;
                b.PI = PI;
                b.my_bird = &pState.getBird(i);
                b.old_log =-std::numeric_limits<double>::max();
                b.id = i;
                birdcomps[i] = b;
            }
        }
    /*
     * Here you should write your clever algorithms to get the best action.
     * This skeleton never shoots.
     */
     for(int i = 0; i < pState.getNumBirds(); ++i){
        if(birdcomps[i].my_bird->getSeqLength() != 1){
            std::vector<int> tmp_seq;
            tmp_seq.resize(birdcomps[i].my_bird->getSeqLength());

            for(int j = 0; j < birdcomps[i].my_bird->getSeqLength(); ++j){
                tmp_seq[j] = birdcomps[i].my_bird->getObservation(j);
            }
            std::cerr << "\nBird #: " << i << " id: " << birdcomps[i].id << " with A[0][0]= " << birdcomps[i].A[0][0] << std::endl;
            BW(birdcomps[i].A, birdcomps[i].B, birdcomps[i].PI,tmp_seq);
            std::cerr << "Returned birds A[0][0]: " << birdcomps[i].A[0][0] <<std::endl;
        }
    }
    
    //std::cerr << "Number of birds: " << pState.getNumBirds() << std::endl; 
    //std::cerr << direction[fagel.getLastObservation()+1] << std::endl;


    // APPROACH:  För varje fågel, get observation, om inte död BW.
    //            Fågel ska ha: A B PI, Förra logen. 
    // This line choose not to shoot
    return cDontShoot;





    //This line would predict that bird 0 will move right and shoot at it

    //return Action(0, MOVE_RIGHT);
}

std::vector<ESpecies> Player::guess(const GameState &pState, const Deadline &pDue)
{
    /*
     * Here you should write your clever algorithms to guess the species of each bird.
     * This skeleton makes no guesses, better safe than sorry!
     */

     std::vector<ESpecies> lGuesses(pState.getNumBirds(), SPECIES_UNKNOWN);
     return lGuesses;
 }

 void Player::hit(const GameState &pState, int pBird, const Deadline &pDue)
 {
    /*
     * If you hit the bird you are trying to shoot, you will be notified through this function.
     */
     std::cerr << "HIT BIRD!!!" << std::endl;
 }

 void Player::reveal(const GameState &pState, const std::vector<ESpecies> &pSpecies, const Deadline &pDue)
 {
    /*
     * If you made any guesses, you will find out the true species of those birds in this function.
     */
 }


} /*namespace ducks*/
