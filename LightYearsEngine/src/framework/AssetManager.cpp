#include "framework/AssetManager.h"
#include <string>

namespace ly
{
    UniquePtr<AssetManager> AssetManager::assetManager{nullptr};

    AssetManager& AssetManager::Get()
    {
        if (!assetManager)
        {
            assetManager = UniquePtr<AssetManager>{new AssetManager};
        }
        return *assetManager;
    }

    SharedPtr<sf::Texture> AssetManager::LoadTexture(const std::string& Path)
    {
        return LoadAsset(Path, LoadedTextures);
        /*const auto FoundTexture = LoadedTextures.find(Path);
        if (FoundTexture != LoadedTextures.end())
        {
            return FoundTexture->second;
        }
        SharedPtr<sf::Texture> NewTexture{new sf::Texture};
        if (NewTexture->loadFromFile(RootDirectory + Path))
        {
            LoadedTextures.insert({Path, NewTexture});
            return NewTexture;
        }
        LOG("Texture cannot be loaded : Path to texture invalid");
        return SharedPtr<sf::Texture> {nullptr};*/
    }

    SharedPtr<sf::Font> AssetManager::LoadFont(const std::string& Path)
    {
        return LoadAsset(Path, LoadedFonts);
        /*const auto FoundFont = LoadedFonts.find(Path);
        if (FoundFont != LoadedFonts.end())
        {
            return FoundFont->second;
        }
        SharedPtr<sf::Font> NewFont{new sf::Font};
        if (NewFont->loadFromFile(RootDirectory + Path))
        {
            LoadedFonts.insert({Path, NewFont});
            return NewFont;
        }
        LOG("Font cannot be loaded : Path to font invalid");
        return SharedPtr<sf::Font> {nullptr};*/
    }

    void AssetManager::CleanCycle()
    {
        CleanUniqueRef(LoadedTextures);
        CleanUniqueRef(LoadedFonts);
        /*for (auto iter = LoadedTextures.begin(); iter != LoadedTextures.end();)
        {
            if (iter->second.unique())
            {
                LOG("Cleaning tex: %s", iter->first.c_str());
                iter = LoadedTextures.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
        
        for (auto iter = LoadedFonts.begin(); iter != LoadedFonts.end();)
        {
            if (iter->second.unique())
            {
                LOG("Cleaning font: %s", iter->first.c_str());
                iter = LoadedFonts.erase(iter);
            }
            else
            {
                ++iter;
            }
        }*/
    }

    void AssetManager::SetAssetRootDirectory(const std::string& Directory)
    {
        RootDirectory = Directory;
    }

    AssetManager::AssetManager() : RootDirectory()
    {
        
    }
}
