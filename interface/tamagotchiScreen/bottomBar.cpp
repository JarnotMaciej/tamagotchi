#include "bottomBar.h"

bottomBar::bottomBar() {
    buttons.emplace_back("Eat", "Q");
    buttons.emplace_back("Play", "W");
    buttons.emplace_back("Wash", "E");
    buttons.emplace_back("Sleep", "R");
    buttons.emplace_back("Quit", "Esc");
}

void bottomBar::draw(sf::RenderWindow &window) {
    for (auto &button: buttons) {
        button.draw(window);
    }
}

void bottomBar::setPositions(sf::RenderWindow &window) {
    int buttonWidth = buttons[0].getSprite().getGlobalBounds().width;
    int buttonHeight = buttons[0].getSprite().getGlobalBounds().height;
    int buttonSpacing = (window.getSize().x - buttons.size() * buttonWidth) / (buttons.size() + 1);

    int i = 0;
    for (auto &button: buttons) {
        button.setPosition(buttonSpacing + i * (buttonSpacing + buttonWidth),
                           window.getSize().y - buttonHeight / 2 - 100);
        i++;
    }
}