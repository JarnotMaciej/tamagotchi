#include "keycapButton.h"

keycapButton::keycapButton(const std::string &name, const std::string &texture) {
    buttonName.setString(name);
    buttonName.setFillColor(sf::Color::White);
    buttonName.setCharacterSize(28);
    buttonName.setFont(assetManager::getInstance().getFont("silkscreen"));

    buttonTexture = assetManager::getInstance().getTexture(texture);
    sprite.setTexture(buttonTexture);
    sprite.setScale(6.5, 6.5);
}

void keycapButton::draw(sf::RenderWindow &window) {
    this->sprite.setTexture(buttonTexture);
    window.draw(sprite);
    window.draw(buttonName);
}

void keycapButton::setPosition(float x, float y) {
    sprite.setPosition(x, y);
    buttonName.setPosition(x + (sprite.getGlobalBounds().width / 2) - (buttonName.getGlobalBounds().width / 2) - 7,
                           y + sprite.getGlobalBounds().height);
}

keycapButton::keycapButton() {}
