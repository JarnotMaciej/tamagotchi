#ifndef PROJECT_NAME_TOP_BAR_H
#define PROJECT_NAME_TOP_BAR_H

#include "SFML/Graphics/Text.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "../../mechanics/assetManager.h"
#include "../../functions.h"
#include "../../structures/tamagotchi.h"
#include "../../mechanics/tamagotchiMechanics.h"

/**
 * @brief Class for top bar -> tamagotchi name, coins, days alive
 */
class topBar {
private:
    sf::Text tamagotchiName; // tamagotchi name
    sf::Text coins; // coins
    sf::Text daysAlive; // days alive

public:
    /**
     * @brief Default constructor for top bar
     */
    topBar();

    /**
     * @brief Method used for drawing top bar
     * @param window - window to draw top bar on
     */
    void setPosition(sf::Window &window);

    /**
     * @brief Method used for drawing top bar
     * @param window - window to draw top bar on
     */
    void draw(sf::RenderWindow &window);

    // setters
    /**
     * @brief Method used for setting tamagotchi name
     * @param name - new tamagotchi name
     */
    void setTamagotchiName(const std::string &name);

    /**
     * @brief Method used for setting coins
     * @param coins - new coins
     * @param window - window to draw top bar on
     */
    void setCoins(int coins, sf::RenderWindow &window);

    /**
     * @brief Method used for setting days alive
     * @param bornTime - born time of tamagotchi
     * @param window - window to draw top bar on
     */
    void setDaysAlive(int bornTime, sf::RenderWindow &window);

    /**
     * @brief Method used for getting height of top bar
     * @return height of top bar
     */
    float getHeight();

    /**
     * @brief Method used for updating top bar
     * @param tamagotchi - tamagotchi to update
     * @param window - window to draw top bar on
     */
    void update(tamagotchi &tamagotchi, sf::RenderWindow &window);
};


#endif //PROJECT_NAME_TOP_BAR_H
