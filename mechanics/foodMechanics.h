//
// Created by menox on 30.04.2023.
//

#ifndef PROJECT_NAME_FOODMECHANICS_H
#define PROJECT_NAME_FOODMECHANICS_H

// C++
#include <vector>
#include <filesystem>
#include <fstream>
#include <map>
#include <list>


// headers
#include "../structures/food.h"
#include "../functions.h"
#include "../structures/tamagotchi.h"
#include "errorHandler.h"

// modules

/**
 * @brief Food mechanics namespace
 */
namespace foodMechanics {
    /**
     * @brief Method used for searching for food in saves directory
     * @return map of food
     */
    std::map<food, int> loadGlobalFoods();

    /**
     * @brief Method used for printing foods
     */
    void printFoods(const std::map<food, int>& foods);

    /**
     * @brief Method used for saving foods to file
     * @param pet - tamagotchi object (theirs food will be saved)
     */
    void saveFood(tamagotchi &pet, bool saved);

    /**
     * @brief Method used for loading tamagotchi foods from file
     * @param fileName - file name
     * @param pet - tamagotchi object
     */
    void loadTamagotchiFoods(const std::string &fileName, tamagotchi &pet);
}

#endif //PROJECT_NAME_FOODMECHANICS_H
