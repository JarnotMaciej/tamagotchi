//
// Created by menox on 27.04.2023.
//

#include "tamagotchiMechanics.h"

int tamagotchiMechanics::transformSecondsToDays(long long int bornTime) {
    return (getTime() - bornTime) / 86400;
}

void tamagotchiMechanics::saveTamagotchi(tamagotchi &pet, bool &isSaved) {
    debug("saving tamagotchi");
    namespace fs = std::filesystem;

    // getting a path
    fs::path path = fs::current_path().parent_path();
    path /= "saves";

    //getting tamagotchi name
    std::string name = pet.getName();

    // creating a file with a name of tamagotchi
    std::ofstream tamagotchiFile;
    path /= name + ".tmg"; // tamagotchi file extension

    try {
        tamagotchiFile.open(path);
        if (!tamagotchiFile.is_open()) {
            throw errorHandler(errorCode::FileError);
        }
        tamagotchiFile << static_cast<int>(pet.getTamagotchiType()) << std::endl;
        tamagotchiFile << name << std::endl;

        tamagotchiFile << pet.getHealth() << std::endl;
        tamagotchiFile << pet.getHunger() << std::endl;
        tamagotchiFile << pet.getHappiness() << std::endl;
        tamagotchiFile << pet.getHygiene() << std::endl;
        tamagotchiFile << pet.getEnergy() << std::endl;
        tamagotchiFile << pet.getMoney() << std::endl;
        tamagotchiFile << pet.getIsSleeping() << std::endl;
        tamagotchiFile << pet.getBornTime() << std::endl;
        tamagotchiFile << pet.getSleepStart() << std::endl;
        tamagotchiFile << getTime() << std::endl;

        tamagotchiFile.close();

    } catch (errorHandler &e) {
        isSaved = false;
        return;
    }

    isSaved = true;
}

int tamagotchiMechanics::realDaysToGameDays(long long int bornTime) {
    return (getTime() - bornTime) / 86400 * 4;
}

std::string tamagotchiMechanics::searchForTamagotchi() {
    debug("searching for tamagotchi");
    namespace fs = std::filesystem;

    // getting a path
    fs::path path = fs::current_path().parent_path();
    path /= "saves";
    debug(path.string());

    try {
        if (fs::is_empty(path)) {
            throw errorHandler(errorCode::FileError);
        } else {
            std::vector<std::string> tamagotchiNames;
            for (const auto &entry: fs::directory_iterator(path)) {
                debug(entry.path().filename().string());
                tamagotchiNames.push_back(entry.path().filename().string());
                // entering directory and checking if the name of tamagotchi is the same as the name of directory
                fs::path tamagotchiPath = path;
                tamagotchiPath /= entry.path().filename().string();
                if (entry.path().filename().string() == entry.path().filename().string() && nameValidation(
                        entry.path().filename().string().substr(0, entry.path().filename().string().length() - 4))) {
                    debug("tamagotchi found");
                    // return file name without extension
                    return entry.path().filename().string().substr(0, entry.path().filename().string().length() - 4);
                }
            }
        }
        throw errorHandler(errorCode::FileError);
    } catch (errorHandler &e) {
        return "";
    }
}

[[maybe_unused]] void tamagotchiMechanics::subtractIndicators(tamagotchi &pet, long long int &lastSaved) {
    debug("subtracting indicators");
    long long int timeDifference = getTime() - lastSaved;

    float minutes = timeDifference / 60;

    float hunger = pet.getHunger() - minutes * 0.5;
    debug("hunger: " + std::to_string(hunger));
    if (hunger < 0) {
        hunger = 0;
    }
    pet.setHunger(hunger);

    float happiness = pet.getHappiness() - minutes * 0.2;
    debug("happiness: " + std::to_string(happiness));
    if (happiness < 0) {
        happiness = 0;
    }
    pet.setHappiness(happiness);

    float hygiene = pet.getHygiene() - minutes * 0.3;
    debug("hygiene: " + std::to_string(hygiene));
    if (hygiene < 0) {
        hygiene = 0;
    }
    pet.setHygiene(hygiene);

    float energy = pet.getEnergy() - minutes * 0.4;
    debug("energy: " + std::to_string(energy));
    if (energy < 0) {
        energy = 0;
    }
    pet.setEnergy(energy);

    // if pet was hungry, it's health will be decreased
    if (hunger == 0) {
        float health = pet.getHealth() - minutes * 0.1;
        debug("health: " + std::to_string(health));
        if (health < 0) {
            health = 0;
        }
        pet.setHealth(health);
    }
}

std::vector<score> tamagotchiMechanics::getScores() {
    std::vector<score> scores;

    debug("getting scores");
    namespace fs = std::filesystem;

    fs::path path = fs::current_path().parent_path();
    path /= "scores";

    //Iterating through all files in directory
    for (const auto &entry: fs::directory_iterator(path)) {
        if (fs::is_regular_file(entry)) {
            const std::string filename = entry.path().filename().string();
            debug(filename);
            if (deadTamagotchiValidation(filename)) {
                std::ifstream scoreFile;
                scoreFile.open(entry.path());

                std::string line;
                while (std::getline(scoreFile, line)) {
                    try {
                        // Validate the line using the scoreLineValidation function
                        if (!scoreLineValidation(line)) {
                            // Invalid line, handle the error or skip it
                            throw errorHandler(errorCode::ValidationError);
                        }
                        std::istringstream iss(line);
                        std::string name;
                        int score, daysAlive;
                        if (!(iss >> name >> score >> daysAlive)) {
                            // Invalid line format, handle the error or skip it
                            throw errorHandler(errorCode::ValidationError);
                        }

                        scores.emplace_back(name, score, daysAlive);
                    } catch (errorHandler &e) {
                        continue;
                    }
                }

                scoreFile.close();
            }
        }
    }

    debug("leaving getScores() function");
    return scores;
}

[[maybe_unused]] void tamagotchiMechanics::printScores(const std::vector<score> &scores) {
    std::cout << "Scores: " << std::endl;
    for (auto &myScore: scores) {
        std::cout << "Name: " << myScore.getTamagotchiName() << std::endl;
        std::cout << "Score: " << myScore.getScoreNumber() << std::endl;
        std::cout << "Age: " << myScore.getDaysAlive() << std::endl;
        std::cout << "---" << std::endl;
    }
}

void tamagotchiMechanics::sleepMechanics(tamagotchi &pet) {
    if (pet.getEnergy() == 100) {
        pet.setIsSleeping(false);
        pet.setSleepStart(0);
        return;
    }

    if (pet.getSleepStart() != 0) {
        long long int sleepTime = getTime() - pet.getSleepStart();
        // half an hour - energy will be full
        sleepTime /= 18; // 18 seconds -> +1 energy point

        if (sleepTime != 0) {
            pet.setSleepStart(pet.getSleepStart() + sleepTime * 18);
            int energy = pet.getEnergy() + sleepTime;
            if (energy > 100) {
                energy = 100;
            }
            pet.setEnergy(energy);
        }
    }

}

tamagotchi tamagotchiMechanics::loadTamagotchi(const std::string &name) {

    // opening file using filesystem
    namespace fs = std::filesystem;
    fs::path path = fs::current_path().parent_path();
    path /= "saves";
    path /= name + ".tmg";
    tamagotchi toReturn;

    std::ifstream tamagotchiFile;
    try {
        tamagotchiFile.open(path);

        if (!tamagotchiFile.is_open()) {
            throw errorHandler(errorCode::FileError);
        }

        // read file content into a string
        std::stringstream buffer;
        buffer << tamagotchiFile.rdbuf();
        tamagotchiFile.close();

        std::string fileContent = buffer.str();

        // validate file content using tamagotchiSaveValidation function
        if (!tamagotchiSaveValidation(fileContent)) {
            throw errorHandler(errorCode::ValidationError);
        }
        // create a stringstream from the file content string
        std::stringstream fileStream(fileContent);

        int petType;
        std::string petName;
        int health, hunger, happiness, hygiene, energy, money;
        bool isSleeping;
        long long int bornTime, sleepStart, lastSaved;

        // reading data from the file stream
        fileStream >> petType;

        // switch case for pet type -> in the future there will be more types of pets
        // CAT
        // DOG
        // FISH

        switch (petType) {
            case 0:
                toReturn = cat();
                break;
            default:
                toReturn = cat();
                break;
        }

        fileStream >> petName;
        fileStream >> health;
        fileStream >> hunger;
        fileStream >> happiness;
        fileStream >> hygiene;
        fileStream >> energy;
        fileStream >> money;
        fileStream >> isSleeping;
        fileStream >> bornTime;
        fileStream >> sleepStart;
        fileStream >> lastSaved;

        // setting data to pet
        toReturn.setName(petName);
        toReturn.setHealth(health);
        toReturn.setHunger(hunger);
        toReturn.setHappiness(happiness);
        toReturn.setHygiene(hygiene);
        toReturn.setEnergy(energy);
        toReturn.setMoney(money);
        toReturn.setIsSleeping(isSleeping);
        toReturn.setBornTime(bornTime);
        toReturn.setSleepStart(sleepStart);

        // according to last saved time, we need to update pet's stats
        long long int timeDifference = getTime() - lastSaved;

        // function for the mechanism -> sleeping YES/NO
        if (isSleeping) {
            sleepMechanics(toReturn);
        } else {
            toReturn.setSleepStart(0);
            energyDecreaseMechanics(toReturn, timeDifference);
        }

        // indicator mechanisms
        hungerMechanics(toReturn, timeDifference);
        hygieneMechanics(toReturn, timeDifference);
        happinessMechanics(toReturn, timeDifference);
        healthMechanics(toReturn, timeDifference);

        if (toReturn.getHealth() <= 0) {
            tamagotchiMechanics::killTamagotchi(toReturn);
            return cat();
        }

        // f00d
        std::map<food, int> foodsToAdd = foodMechanics::loadGlobalFoods();
        if (foodsToAdd.empty()) {
            throw errorHandler(errorCode::FileError);
        }

        toReturn.setFoods(foodsToAdd);

        foodMechanics::loadTamagotchiFoods(name, toReturn);
    } catch (errorHandler &e) {
        return cat();
    }

    return toReturn;
}

void tamagotchiMechanics::energyDecreaseMechanics(tamagotchi &tamagotchiToModify, long long int difference) {
    // energy is decreasing over time -> 1 energy point per 5 minutes
    int energy = tamagotchiToModify.getEnergy() - difference / 300;
    if (energy < 0) {
        energy = 0;
    } else if (energy > 100) {
        energy = 100;
    } else {
        tamagotchiToModify.setEnergy(energy);
    }
}

void tamagotchiMechanics::hungerMechanics(tamagotchi &tamagotchiToModify, long long int difference) {
    // hunger is decreasing over time -> 1 hunger point per 10 minutes
    int hunger = tamagotchiToModify.getHunger() - difference / 600;
    if (hunger < 0) {
        hunger = 0;
    } else if (hunger > 100) {
        hunger = 100;
    } else {
        tamagotchiToModify.setHunger(hunger);
    }
}

void tamagotchiMechanics::hygieneMechanics(tamagotchi &tamagotchiToModify, long long int difference) {
    // hygiene is decreasing over time -> 1 hygiene point per 7.5 minutes
    int hygiene = tamagotchiToModify.getHygiene() - difference / 450;
    if (hygiene < 0) {
        hygiene = 0;
    } else if (hygiene > 100) {
        hygiene = 100;
    } else {
        tamagotchiToModify.setHygiene(hygiene);
    }
}

void tamagotchiMechanics::happinessMechanics(tamagotchi &tamagotchiToModify, long long int difference) {
    // happiness is decreasing over time -> 1 happiness point per 3 minutes
    int happiness = tamagotchiToModify.getHappiness() - difference / 180;
    if (happiness < 0) {
        happiness = 0;
    } else if (happiness > 100) {
        happiness = 100;
    } else {
        tamagotchiToModify.setHappiness(happiness);
    }
}

void tamagotchiMechanics::healthMechanics(tamagotchi &tamagotchiToModify, long long int difference) {
    // health is decreasing over time, but it is also based on other stats, according to the stats, multiplier will be calculated and then health will be decreased
    int health = tamagotchiToModify.getHealth();
    float multiplier = 1.0;

    // if hunger is less or equal 10, multiplier will be multiplied by 1.2
    if (tamagotchiToModify.getHunger() <= 10) {
        multiplier *= 1.2;
    }
    // if hygiene is less  or equal 10, multiplier will be multiplied by 2.2
    if (tamagotchiToModify.getHygiene() <= 10) {
        multiplier *= 2.2;
    }
    // if happiness is less or equal 0, multiplier will be multiplied by 1.1
    if (tamagotchiToModify.getHappiness() <= 0) {
        multiplier *= 1.1;
    }
    // if energy is less or equal 0, multiplier will be multiplied by 1.8
    if (tamagotchiToModify.getEnergy() <= 0) {
        multiplier *= 1.8;
    }

    // multiplier to int
    int intMultiplier = (int) multiplier;

    // health is decreasing over time -> 1 health point per 15 minutes multiplied by multiplier
    health -= difference / 900 * intMultiplier;

    if (health < 0) {
        health = 0;
    } else if (health > 100) {
        health = 100;
    } else {
        tamagotchiToModify.setHealth(health);
    }
}

tamagotchi tamagotchiMechanics::checkIfTamagotchiExistsThenReturn(std::string basicString) {
    if (!basicString.empty()) {
        return tamagotchiMechanics::loadTamagotchi(basicString);
    }
    debug("You don't have any tamagotchi yet!");
    tamagotchi toReturn = cat();
    toReturn.setFoods(foodMechanics::loadGlobalFoods());
    toReturn.printInfo();
    return toReturn;
}

void tamagotchiMechanics::killTamagotchi(tamagotchi &pet) {
    std::string name = pet.getName();
    int daysAlive = tamagotchiMechanics::realDaysToGameDays(pet.getBornTime());
    int scoreNumber = tamagotchiMechanics::calculateScore(pet);


    // tamagotchi paths -> tamagotchi file and food file
    // filesystem used
    std::filesystem::path tamagotchiPath = std::filesystem::current_path().parent_path() / "saves" / (name + ".tmg");
    std::filesystem::path foodPath = std::filesystem::current_path().parent_path() / "saves" / (name + ".tmgfood");

    // score file path
    std::filesystem::path scorePath = std::filesystem::current_path().parent_path() / "scores" / (name + ".dtf");

    try {
        // check if the score file exists, if yes -> open it and save best score, if not -> create it and save best score
        if (std::filesystem::exists(scorePath)) {
            std::ifstream scoreFile(scorePath);

            if (!scoreFile.is_open()) {
                throw errorHandler(errorCode::FileError);
            }

            std::string scoreName;
            int scoreScore;
            int scoreDaysAlive;

            scoreFile >> scoreName >> scoreScore >> scoreDaysAlive;

            scoreFile.close();

            if (scoreNumber > scoreScore) {
                std::ofstream scoreFile(scorePath);

                if (!scoreFile.is_open()) {
                    throw errorHandler(errorCode::FileError);
                }

                scoreFile << name << " " << scoreNumber << " " << daysAlive;
                scoreFile.close();
            }
        } else {
            std::ofstream scoreFile(scorePath);

            if (!scoreFile.is_open()) {
                throw errorHandler(errorCode::FileError);
            }

            scoreFile << name << " " << scoreNumber << " " << daysAlive;
            scoreFile.close();
        }
    } catch (errorHandler &e) {
        return;
    }

    // removing tamagotchi and food files
    std::filesystem::remove(tamagotchiPath);
    std::filesystem::remove(foodPath);

    std::cout << "Your tamagotchi " << name << " died after " << daysAlive << " days of life. Your score is " << scoreNumber << " points." << std::endl;
}

int tamagotchiMechanics::calculateScore(tamagotchi &pet) {
    int score = 0;

    score += pet.getHealth() * 2;
    score += pet.getHappiness() * 2;
    score += pet.getHygiene() * 2;
    score += pet.getHunger() * 2;
    score += pet.getEnergy() * 2;
    score += tamagotchiMechanics::realDaysToGameDays(pet.getBornTime()) * 3;
    score += pet.getMoney() * 3;

    return score;
}

std::vector<std::pair<std::string, int>> tamagotchiMechanics::readCreditsFile() {
    std::vector<std::pair<std::string, int>> creditsVector;

    // Open the credits file
    std::filesystem::path creditsFilePath = std::filesystem::current_path().parent_path() / "config" / "credits.md";
    std::ifstream creditsFile(creditsFilePath);
    try {
        if (!creditsFile.is_open()) {
            throw errorHandler(errorCode::FileError);
        }
        std::string line;

        // Read the file line by line
        // Count how many # are in the line before first space or letter -> int
        // #s need to be removed from the line
        while (std::getline(creditsFile, line)) {
            int count = 0;
            for (char c : line) {
                if (c == '#') {
                    count++;
                } else if (c == ' ') {
                    break;
                } else {
                    count = 0;
                    break;
                }
            }

            // remove #s and space from the line
            if (count != 0) {
                line.erase(0, count+1);
            }

            // links are in format [text](link) -> they need to be divided into text and link parts in different strings
            if (line.find('[') != std::string::npos) {
                std::string text = line.substr(line.find('[') + 1, line.find(']') - line.find('[') - 1);
                std::string link = line.substr(line.find('(') + 1, line.find(')') - line.find('(') - 1);
                creditsVector.emplace_back(text, -1);
                creditsVector.emplace_back(link, -2);
                continue;
            }

            // bullet points are in format - text -> they need to have -3 as count, - and space are removed
            // but if there are 3 -s in the line, it's a horizontal line -> it needs to have -4 as count
            if (line.find('-') != std::string::npos) {
                if (line.find('-') == line.find_last_of('-')) {
                    creditsVector.emplace_back(line.substr(line.find('-') + 1), -3);
                } else {
                    creditsVector.emplace_back("", -4);
                }
                continue;
            }

            creditsVector.emplace_back(line, count);
        }

    } catch (errorHandler &e) {
        return {};
    }

    // Close the file
    creditsFile.close();

    return creditsVector;
}

std::vector<sf::Text> tamagotchiMechanics::createCreditsTexts(const std::vector<std::pair<std::string, int>> &credits) {
    std::vector<sf::Text> texts;
    for (const auto &credit : credits) {
        sf::Text text;
        text.setString(credit.first);
        text.setFont(assetManager::getInstance().getFont("Silkscreen"));

        switch (credit.second) {
            case -1:
                text.setCharacterSize(30);
                break;
            case -2:
                text.setCharacterSize(22);
                break;
            case -3:
                text.setCharacterSize(36);
                break;
            case -4:
                text.setCharacterSize(100);
                break;
            case 0:
                text.setCharacterSize(32);
                break;
            case 1:
                text.setCharacterSize(72);
                break;
            case 2:
                text.setCharacterSize(64);
                break;
            case 3:
                text.setCharacterSize(48);
                break;
            case 4:
                text.setCharacterSize(42);
                break;
            default:
                text.setCharacterSize(32);
                break;
        }

        text.setFillColor(sf::Color::White);
        text.setPosition(0, 0);
        texts.push_back(text);
    }

    return texts;
}

// TODO -> testing tamagotchiMechanics
