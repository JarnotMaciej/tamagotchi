#define SILKSCREEN assetManager::getInstance().getFont("silkscreen")
#include "exitScreen.h"

exitScreen::exitScreen() {
    petSaved = false;
    foodSaved = false;
    petSaveStarted = false;
    foodSaveStarted = false;
    
    savingText.setString("Saving...");
    savingText.setFont(SILKSCREEN);
    savingText.setCharacterSize(48);
    savingText.setFillColor(sf::Color::White);
    savingText.setPosition(0, 0);
}

void exitScreen::draw(sf::RenderWindow &window) {
    if (petSaved) {
        window.close();
    }
}

void exitScreen::update(sf::RenderWindow &window, tamagotchi &pet) {
    if (!petSaveStarted) {
        petSaveStarted = true;
        auto petSaveFunction = [&]() {
            tamagotchiMechanics::saveTamagotchi(pet, petSaved);
        };
        std::thread petSaveThread(petSaveFunction);
        petSaveThread.detach();
    }
    if (!foodSaveStarted) {
        foodSaveStarted = true;
        auto foodSaveFunction = [&]() {
            foodMechanics::saveFood(pet, foodSaved);
        };
        std::thread foodSaveThread(foodSaveFunction);
        foodSaveThread.detach();
    }
}

void exitScreen::handleInput(sf::RenderWindow &window, ScreenName &_screenName) {
}

void exitScreen::setPositions(sf::RenderWindow &window) {
    savingText.setPosition(window.getSize().x / 2 - savingText.getGlobalBounds().width / 2,
                                     window.getSize().y / 2 - savingText.getGlobalBounds().height / 2);
}
