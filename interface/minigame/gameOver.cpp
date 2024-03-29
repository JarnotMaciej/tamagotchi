#include "gameOver.h"

gameOver::gameOver(const std::shared_ptr<minigameConnector> &_magicConnector) {
    magicConnector = _magicConnector;

    message.setString("Game over!");
    message.setFont(assetManager::getInstance().getFont("silkscreen"));
    message.setCharacterSize(64);
    message.setFillColor(sf::Color::White);
    message.setPosition(0, 0);

    coinsWon.setString(" ");
    coinsWon.setFont(assetManager::getInstance().getFont("silkscreen"));
    coinsWon.setCharacterSize(56);
    coinsWon.setFillColor(sf::Color::White);
    coinsWon.setPosition(0, 100);

    pressEscToContinue.setString("Press ESC to enter tamagotchi screen immediately");
    pressEscToContinue.setFont(assetManager::getInstance().getFont("silkscreen"));
    pressEscToContinue.setCharacterSize(32);
    pressEscToContinue.setFillColor(sf::Color::White);
    pressEscToContinue.setPosition(0, 200);

    isRunning = true;
    coinsValue = 0;

}

void gameOver::update(sf::RenderWindow &window, tamagotchi &pet) {
    if (gameOverTimeout == 0) {
        isRunning = false;
        gameOverTimeout = 5;
    }
    if (gameOverClock.getElapsedTime().asSeconds() >= 1 && gameOverTimeout > 0) {
        gameOverTimeout--;
        gameOverClock.restart();
    }
}

void gameOver::draw(sf::RenderWindow &window) {
    setPositions(window);
    window.draw(message);
    updateCoinsText();
    window.draw(coinsWon);
    window.draw(pressEscToContinue);
}

void gameOver::setPositions(sf::RenderWindow &window) {
    message.setPosition(window.getSize().x / 2 - message.getGlobalBounds().width / 2,
                        window.getSize().y / 5 * 2 - message.getGlobalBounds().height / 2);
    coinsWon.setPosition(window.getSize().x / 2 - coinsWon.getGlobalBounds().width / 2,
                         message.getPosition().y + message.getGlobalBounds().height + 40);
    pressEscToContinue.setPosition(window.getSize().x / 2 - pressEscToContinue.getGlobalBounds().width / 2,
                                   window.getSize().y / 5 * 4 - pressEscToContinue.getGlobalBounds().height / 2);
}

void gameOver::handleInput(sf::RenderWindow &window, ScreenName &_screenName) {
    if (!isRunning) {
        isRunning = true;
        changeScreen(_screenName, ScreenName::TAMAGOTCHI_SCREEN);
    }

    sf::Event event;
    while (window.pollEvent(event)) {
        switch (event.type) {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::KeyPressed:
                if (event.key.code == sf::Keyboard::Escape) {
                    changeScreen(_screenName, ScreenName::TAMAGOTCHI_SCREEN);
                }
            default:
                break;
        }
    }
}

void gameOver::updateCoinsText() {
    coinsValue = magicConnector->getCoinsValue();
    coinsWon.setString("Coins won: " + std::to_string(coinsValue));
}

