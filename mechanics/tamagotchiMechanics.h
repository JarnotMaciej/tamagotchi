//
// Created by menox on 27.04.2023.
//

// C++
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>

// headers
#include "../functions.h"
#include "../structures/tamagotchi.h"
#include "../structures/score.h"
#include "../structures/cat.h"
#include "foodMechanics.h"
#include "errorHandler.h"
#include "assetManager.h"

// SFML
#include <SFML/Graphics.hpp>

// modules
import getTime;

#ifndef PROJECT_NAME_MECHANICS_TAMAGOTCHIMECHANICS_H_
#define PROJECT_NAME_MECHANICS_TAMAGOTCHIMECHANICS_H_

/**
 * @brief Tamagotchi mechanics namespace
 */
namespace tamagotchiMechanics {
    // Mechanics
    /**
     * @brief Method used for searching for tamagotchi in saves directory
     * @return tamagotchi name
     */
    std::string searchForTamagotchi();

    /**
     * @brief Method used for saving tamagotchi
     * @param pet - tamagotchi object
     * @param isSaved - is tamagotchi saved
     */
    void saveTamagotchi(tamagotchi &pet, bool &isSaved);

    /**
     * @brief Method used for loading tamagotchi from file
     * @param name - tamagotchi name
     * @return tamagotchi object
     */
	tamagotchi loadTamagotchi(const std::string &name);

    /**
     * @brief Method used for transforming seconds to days
     * @param bornTime
     * @return days
     */
    int transformSecondsToDays(long long int bornTime);

    /**
     * @brief Method used for transforming real days to game days
     * @param bornTime
     * @return game days
     */
    int realDaysToGameDays(long long int bornTime); // Transform real days to game days, 1 real day = 4 game days

    /**
     * @brief Method used for subtracting tamagotchi indicators (health, hunger, happiness, hygiene, energy) after loading tamagotchi from file
     * @param pet - tamagotchi object
     * @param lastSaved - last saved time
     */
    [[maybe_unused]] void subtractIndicators(tamagotchi &pet,
                            long long int &lastSaved); // Subtracts tamagotchi indicators (health, hunger, happiness, hygiene, energy) after loading tamagotchi from file


    /**
     * @brief Method used for killing tamagotchi
     * @param pet
     */
    void killTamagotchi(tamagotchi &pet); // Transforms tamagotchi to dead tamagotchi (function calculates score)

    /**
     * @brief Method used for getting scores from file
     * @return vector of scores
     */
    std::vector<score> getScores(); // Get scores from file

    /**
     * @brief Method used for printing scores
     * @param scores - vector of scores
     */
    [[maybe_unused]] void printScores(const std::vector<score>& scores);

    /**
     * @brief Method used for adding energy to tamagotchi during sleeping
     * @param pet
     */
    void sleepMechanics(tamagotchi &pet);

    /**
     * @brief Method used for decreasing tamagotchi energy
     * @param pet - tamagotchi object
     * @param difference - difference between last saved time and current time
     */
    void energyDecreaseMechanics(tamagotchi &tamagotchiToModify, long long int difference);

    /**
     * @brief Method used for decreasing tamagotchi hunger
     * @param tamagotchiToModify - tamagotchi object
     * @param difference - difference between last saved time and current time
     */
    void hungerMechanics(tamagotchi &tamagotchiToModify, long long int difference);

    /**
     * @brief Method used for decreasing tamagotchi hygiene
     * @param tamagotchiToModify - tamagotchi object
     * @param difference - difference between last saved time and current time
     */
    void hygieneMechanics(tamagotchi &tamagotchiToModify, long long int difference);

    /**
     * @brief Method used for decreasing tamagotchi happiness
     * @param tamagotchiToModify - tamagotchi object
     * @param difference - difference between last saved time and current time
     */
    void happinessMechanics(tamagotchi &tamagotchiToModify, long long int difference);

    /**
     * @brief Method used for decreasing tamagotchi health
     * @param tamagotchiToModify - tamagotchi object
     * @param difference - difference between last saved time and current time
     */
    void healthMechanics(tamagotchi &tamagotchiToModify, long long int difference);

    /**
     * @brief Method used for checking if tamagotchi exists
     * @param tamagotchiName - tamagotchi name
     * @return tamagotchi object
     */
    tamagotchi checkIfTamagotchiExistsThenReturn(std::string basicString);

    /**
     * @brief Method used for calculating score
     * @param pet - pet object
     * @return score
     */
    int calculateScore(tamagotchi &pet);

    /**
     * @brief Method used for reading credits file
     * @return vector of pairs (name, score)
     */
    std::vector<std::pair<std::string, int>> readCreditsFile();

    /**
     * @brief Method used for converting vector of pairs (name, score) to vector of texts
     * @param credits - vector of pairs (name, score)
     * @return vector of texts
     */
    std::vector<sf::Text> createCreditsTexts(const std::vector<std::pair<std::string, int>> &credits);

}

#endif //PROJECT_NAME_MECHANICS_TAMAGOTCHIMECHANICS_H_
