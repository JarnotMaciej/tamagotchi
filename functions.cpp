//
// Created by menox on 08.04.2023.
//

#include "functions.h"


void debug(const std::string& text)
{
    std::cout << "\t[DEBUG] " << text << std::endl;
}
bool nameValidation(const std::string& name)
{
//	std::regex nameRegex("[a-zA-Z]+");
    std::regex nameRegex("[a-zA-Z]{1,32}");
    return std::regex_match(name, nameRegex);
}

bool deadTamagotchiValidation(const std::string &name) {
    std::regex nameRegex("[a-zA-Z]{1,32}.dtf");
    return std::regex_match(name, nameRegex);
}
bool scoreLineValidation(const std::string &lineToValidate)
{
    std::regex lineRegex("[a-zA-Z]{1,32}\\s\\d{1,}\\s\\d{1,}");
    return std::regex_match(lineToValidate, lineRegex);
}
bool foodConfigValidation(const std::string &lineToValidate)
{
    std::regex lineRegex("[a-zA-Z]{1,32}\\s-?\\d+\\s-?\\d+\\s-?\\d+\\s-?\\d+\\s-?\\d+\\s-?\\d+");
    return std::regex_match(lineToValidate, lineRegex);
}
//long long int getTime()
//{
//	// to be more precise, this functions gets time in seconds since 1.1.1970
//	auto time = std::chrono::system_clock::now();
//	auto since_epoch = time.time_since_epoch();
//	auto seconds = std::chrono::duration_cast<std::chrono::seconds>(since_epoch);
//	return seconds.count();
//}

void setIcon(sf::RenderWindow &window) {
    auto path = std::filesystem::current_path().parent_path().string() + "/resources/icon/cat.png";
    sf::Image icon;
    icon.loadFromFile(path);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}

void setCursor(sf::RenderWindow &window) {
    auto path = std::filesystem::current_path().parent_path().string() + "/resources/cursor/cursor.png";
    sf::Image cursorImg;
    cursorImg.loadFromFile(path);

    // Create a new image with scaled dimensions
    float scale = 1.8;
    sf::Vector2u scaledSize(cursorImg.getSize().x * scale, cursorImg.getSize().y * scale);
    sf::Image scaledImage;
    scaledImage.create(scaledSize.x, scaledSize.y);

    // Scale the cursor image and copy it to the new image
    for (unsigned int x = 0; x < scaledSize.x; ++x)
    {
        for (unsigned int y = 0; y < scaledSize.y; ++y)
        {
            unsigned int originalX = x / scale;
            unsigned int originalY = y / scale;
            sf::Color color = cursorImg.getPixel(originalX, originalY);
            scaledImage.setPixel(x, y, color);
        }
    }

    // Create the custom cursor
    sf::Cursor cursor;
    cursor.loadFromPixels(scaledImage.getPixelsPtr(), scaledImage.getSize(), {0,0});

    // Set the window's cursor
    window.setMouseCursor(cursor);
}

bool tamagotchiSaveValidation(const std::string &tamagotchiFile) {
    std::regex fileRegex("[0-9]{1}\\n[a-zA-Z]{1,32}\\n\\d{1,3}\\n\\d{1,3}\\n\\d{1,3}\\n\\d{1,3}\\n\\d{1,3}\\n\\d{1,}\\n[0,1]{1}\\n\\d{1,}\\n\\d{1,}\\n\\d{1,}\\n?");
    return std::regex_match(tamagotchiFile, fileRegex);
}

bool foodSaveValidation(const std::string &lineToValidate) {
    std::regex lineRegex("[a-z]{1,}\\s\\d{1,3}");
    return std::regex_match(lineToValidate, lineRegex);
}
