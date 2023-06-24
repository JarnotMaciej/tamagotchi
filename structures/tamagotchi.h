//
// Created by menox on 19.03.2023.
//

#ifndef TAMAGOTCHI_TAMAGOTCHI_H
#define TAMAGOTCHI_TAMAGOTCHI_H

// C++
#include <iostream>
#include <string>
#include <vector>
#include <filesystem>
#include <fstream>

// Headers
#include "food.h"
#include "../functions.h"
#include "../mechanics/errorHandler.h"

// modules
import getTime;

/**
 * @brief Tamagotchi class
 */
class tamagotchi
{
 private:
	std::string name; // Tamagotchi name
	int health; // Tamagotchi health (in percent)
	int hunger; // Tamagotchi hunger (in percent)
	int happiness; // Tamagotchi happiness (in percent)
	int hygiene; // Tamagotchi hygiene (in percent)
	int energy; // Tamagotchi energy (in percent)
	int money; // Tamagotchi money (in gold coins)
    bool isSleeping; // Is tamagotchi sleeping?
    long long int bornTime; // Tamagotchi born time (in seconds)
    long long int sleepStart; // Tamagotchi sleep start time (in seconds)
    std::map<food, int> foods; // Tamagotchi foods -> food, quantity

 public:
    /**
     * @brief Constructor
     */
	tamagotchi();

    /**
     * @brief Constructor
     * @param _name - Tamagotchi name
     */
	explicit tamagotchi(std::string _name);

    /**
     * @brief Get tamagotchi equipment
     * @return Tamagotchi equipment
     */
	std::string getName() const;

    /**
     * @brief Get tamagotchi health
     * @return Tamagotchi health
     */
	int getHealth();

    /**
     * @brief Get tamagotchi hunger
     * @return Tamagotchi hunger
     */
	int getHunger();

    /**
     * @brief Get tamagotchi happiness
     * @return Tamagotchi happiness
     */
	int getHappiness();

    /**
     * @brief Get tamagotchi hygiene
     * @return Tamagotchi hygiene
     */
	int getHygiene();

    /**
     * @brief Get tamagotchi energy
     * @return Tamagotchi energy
     */
	int getEnergy();

    /**
     * @brief Get tamagotchi money
     * @return Tamagotchi money
     */
	int getMoney();

    /**
     * @brief Get tamagotchi born time
     * @return Tamagotchi born time
     */
	long long int getBornTime() const;

    /**
     * @brief Set tamagotchi name
     * @param name - Tamagotchi name
     */
	void setName(std::string name);

    /**
     * @brief Set tamagotchi health
     * @param health - Tamagotchi health
     */
	void setHealth(int health);

    /**
     * @brief Set tamagotchi hunger
     * @param hunger - Tamagotchi hunger
     */
	void setHunger(int hunger);

    /**
     * @brief Set tamagotchi happiness
     * @param happiness - Tamagotchi happiness
     */
	void setHappiness(int happiness);

    /**
     * @brief Set tamagotchi hygiene
     * @param hygiene - Tamagotchi hygiene
     */
	void setHygiene(int hygiene);

    /**
     * @brief Set tamagotchi energy
     * @param energy - Tamagotchi energy
     */
	void setEnergy(int energy);

    /**
     * @brief Set tamagotchi money
     * @param money - Tamagotchi money
     */
	void setMoney(int money);

    /**
     * @brief Set tamagotchi born time
     * @param bornTime - Tamagotchi born time
     */
	void setBornTime(long long int bornTime);

    /**
     * @brief Print tamagotchi info // Used for debugging, should be removed in final version
     */
	void printInfo();

    /**
     * @brief Get tamagotchi foods
     * @return Tamagotchi foods
     */
    [[nodiscard]] std::map<food, int> getFoods() const;

    /**
     * @brief Set tamagotchi foods
     * @param _foods - Tamagotchi foods
     */
    void setFoods(std::map<food, int> _foods);

    /**
     * @brief Enum class for tamagotchi types
     */
    enum class tamagotchiType
    {
        CAT,
        DOG,
        FISH
    };

    /**
     * @brief Get tamagotchi type
     * @return Tamagotchi type
     */
    tamagotchiType getTamagotchiType();

    /**
     * @brief Get sleeping bool
     * @return Sleeping bool
     */
    bool getIsSleeping() const;

    /**
     * @brief Set sleeping bool
     * @param isSleeping - Sleeping bool
     */
    void setIsSleeping(bool isSleeping);

    /**
     * @brief Get sleepMechanics start time
     * @return Sleep start time
     */
    long long int getSleepStart() const;

    /**
     * @brief Set sleepMechanics start time
     * @param sleepStart - Sleep start time
     */
    void setSleepStart(long long int sleepStart);

    /**
     * @brief Eat food
     * @param foodName - Food name
     * @return True if food was eaten, false if not
     */
    bool eatFood(const std::string& foodName);

    /**
     * @brief Buy food
     * @param foodName - Food name
     * @return True if food was bought, false if not
     */
    bool buyFood(const std::string& foodName);

    /**
     * @brief Sell food
     * @param foodName - Food name
     * @return True if food was sold, false if not
     */
    bool sellFood(const std::string& foodName);

    /**
     * @brief Add food - method used during opening save file
     * @param foodName - Food name
     * @param quantity - Food quantity
     */
    void addFood(const std::string &foodName, int quantity);

    /**
     * @brief Find food
     * @param foodName - Food name
     * @return Food
     */
    food findFood(const std::string& foodName) const;
};

/**
 * @brief Function for normalizing tamagotchi indicators
 * @param value - Indicator value
 */
int indicatorFunction(int value);


#endif //TAMAGOTCHI_TAMAGOTCHI_H
