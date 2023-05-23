//
// Created by menox on 01.04.2023.
//

// SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>

// C++
#include <iostream>

// Header files
#include "flyingElement.h"
#include "../assetManager.h"

#ifndef TAMAGOTCHI_MENU_COIN_H
#define TAMAGOTCHI_MENU_COIN_H

/**
 * @brief Class for button
 */
class coin : public flyingElement{
private:
    sf::Texture coinTexture; // texture of the coin
    sf::Sprite coinSprite; // sprite of the coin
    
public:
    /**
     * @brief Default constructor
     */
    coin();

/**
 * @brief Method used for drawing
 * 
 * @param window - window to draw
 */
    void draw(sf::RenderWindow &window) override;

/**
 * @brief Set the Random Position object
 * 
 * @param window - window to set position on
 */
    void setRandomPosition(sf::RenderWindow &window);

/**
 * @brief Method used for moving the coindown
 */
    void update();

/**
 * @brief Get the Sprite object
 * 
 * @return sf::Sprite - sprite of the coin
 */
    sf::Sprite getSprite() { return coinSprite; }
};

#endif //TAMAGOTCHI_MENU_COIN_H
