#include "assetManager.h"
#include "../functions.h"

assetManager &assetManager::getInstance() {
    static assetManager instance;
    return instance;
}

sf::Texture &assetManager::getTexture(const std::string &id) {
    auto iter = m_textures.find(id);
    if (iter == m_textures.end()) {
        std::unique_ptr<sf::Texture> texture(new sf::Texture());

        std::filesystem::path path =
                std::filesystem::current_path().parent_path() / "resources" / "textures" / (id + ".png");
        try {
            if (!texture->loadFromFile(path.string())) {
                throw errorHandler(errorCode::TextureNotFound);
            }
        }
        catch (errorHandler &e) {
            return *m_defaultTexture;
        }
        iter = m_textures.emplace(id, std::move(texture)).first;
    }

    return *iter->second;
}

sf::SoundBuffer &assetManager::getSound(const std::string &id, const std::string &extension) {
    auto iter = m_sounds.find(id);
    if (iter == m_sounds.end()) {
        std::unique_ptr<sf::SoundBuffer> sound(new sf::SoundBuffer());
        std::filesystem::path path =
                std::filesystem::current_path().parent_path() / "resources" / "sounds" / (id + "." + extension);
        try {
            if (!sound->loadFromFile(path.string())) {
                throw errorHandler(errorCode::SoundNotFound);
            }
        } catch (errorHandler &e) {
            return *m_defaultSound;
        }
        iter = m_sounds.emplace(id, std::move(sound)).first;
    }
    return *iter->second;
}

sf::Font &assetManager::getFont(const std::string &id) {
    auto iter = m_fonts.find(id);
    if (iter == m_fonts.end()) {
        std::unique_ptr<sf::Font> font(new sf::Font());
        std::filesystem::path path =
                std::filesystem::current_path().parent_path() / "resources" / "fonts" / (id + ".ttf");
        try {
            if (!font->loadFromFile(path.string())) {
                throw errorHandler(errorCode::FontNotFound);
            }
        } catch (errorHandler &e) {
            return *m_defaultFont;
        }
        iter = m_fonts.emplace(id, std::move(font)).first;
    }
    return *iter->second;
}
