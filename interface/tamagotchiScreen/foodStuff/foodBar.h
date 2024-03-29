#ifndef TAMAGOTCHI_FOODBAR_H
#define TAMAGOTCHI_FOODBAR_H

#include <vector>
#include <string>
#include <map>
#include "foodButton.h"
#include "../../../structures/food.h"
#include "../../../mechanics/assetManager.h"
#include "../../../structures/tamagotchi.h"

/**
 * @brief Class for food bar
 */
class foodBar {
private:
    std::map<std::string, foodButton> buttons; // map of buttons
    sf::Text equipmentMove; // instruction how to move in equipment
    sf::Text sellText; // instruction how to sell food
    sf::Text buyText; // instruction how to buy food
    sf::Text eatText; // instruction how to eat food
    short int activeButton; // index of active button
    sf::Sound foodBarSound; // sound of food bar
    sf::SoundBuffer foodBarBuffer; // buffer of food bar sound
    std::vector<sf::Text> foodStats; // vector of texts with food statistics

    /**
     * @brief Gets name of active button
     * @return name of active button
     */
    std::string getActiveButtonName() {
        auto it = buttons.begin();
        std::advance(it, activeButton);
        return it->first;
    }

public:

    /**
     * @brief Constructor of food bar
     * @param pet - map of food
     */
    explicit foodBar(const tamagotchi &pet);

    /**
     * @brief Default constructor
     */
    foodBar() = default;

    /**
     * @brief Draws food bar
     * @param window - window to draw on
     */
    void draw(sf::RenderWindow &window);

    /**
     * @brief Updates food bar
     * @param pet - pointer to pet
     * @param window - window to update on
     */
    void update(tamagotchi &pet, sf::RenderWindow &window);

    /**
     * @brief Sets positions of buttons
     * @param window - window to set positions on
     */
    void setPositions(sf::RenderWindow &window);

    /**
     * @brief Activates next button
     */
    void activateNextButton();

    /**
     * @brief Activates previous button
     */
    void activatePreviousButton();

    /**
     * @brief Buys food
     * @param pet - pointer to pet
     */
    void buyFood(tamagotchi &pet);

    /**
     * @brief Sells food
     * @param pet - pointer to pet
     */
    void sellFood(tamagotchi &pet);

    /**
     * @brief Eats food
     * @param pet - pointer to pet
     */
    void eatFood(tamagotchi &pet);

    void setStatsPositions(sf::RenderWindow &window);
};


#endif //TAMAGOTCHI_FOODBAR_H
