#include "coin.h"

coin::coin()
{
    coinTexture = assetManager::getInstance().getTexture("coin");
    coinSprite.setTexture(coinTexture);
    coinSprite.setScale(2, 2);
}

void coin::draw(sf::RenderWindow &window)
{
    this->coinSprite.setTexture(coinTexture);
    window.draw(coinSprite);
}

void coin::setRandomPosition(sf::RenderWindow &window)
{
    int randExtent = window.getSize().x - coinSprite.getGlobalBounds().width;
    int x = rand() % randExtent;
    int y = rand() % 30;
    coinSprite.setPosition(x, y);
}

void coin::update()
{
    coinSprite.move(0, 4);
}
