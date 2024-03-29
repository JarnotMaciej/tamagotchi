#include "indicatorBar.h"

indicatorBar::indicatorBar() {
    indicators.emplace_back("health", sf::Color{210, 15, 57}, 100);
    indicators.emplace_back("hunger", sf::Color{223, 142, 29}, 100);
    indicators.emplace_back("happiness", sf::Color{234, 118, 203}, 100);
    indicators.emplace_back("hygiene", sf::Color{4, 165, 229}, 100);
    indicators.emplace_back("energy", sf::Color{64, 160, 43}, 100);
}

void indicatorBar::draw(sf::RenderWindow &window) {
    for (auto &indicator: indicators) {
        indicator.draw(window);
    }
}

void indicatorBar::setPositions(sf::RenderWindow &window) {
    std::mutex posMutex;
    std::vector<std::thread> posThreads;

    int indicatorWidth = 100;
    int margin = 120;
    int x = (window.getSize().x - (indicatorWidth * indicators.size() + margin * (indicators.size() - 1))) / 2;
    int y = 100;

    for (int i = 0; i < indicators.size(); ++i) {
        posThreads.emplace_back([=, &posMutex]() {
            std::lock_guard<std::mutex> lock(posMutex);
            indicators[i].setPosition(x, y);
        });
        x += indicatorWidth + margin;
    }

    for (auto &thread: posThreads) {
        thread.join();
    }
}

void indicatorBar::update(tamagotchi &pet) {
    std::thread t1([&]() {
        indicators[0].update(pet.getHealth());
    });
    std::thread t2([&]() {
        indicators[1].update(pet.getHunger());
    });
    std::thread t3([&]() {
        indicators[2].update(pet.getHappiness());
    });
    std::thread t4([&]() {
        indicators[3].update(pet.getHygiene());
    });
    std::thread t5([&]() {
        indicators[4].update(pet.getEnergy());
    });

    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}
