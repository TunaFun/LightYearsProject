#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"

namespace ly
{
    class AssetManager
    {
    public:
        static AssetManager& Get();
        SharedPtr<sf::Texture> LoadTexture(const std::string& Path);
        SharedPtr<sf::Font> LoadFont(const std::string& Path);

        template <typename T>
        SharedPtr<T> LoadAsset(const std::string& Path, Dictionary<std::string, SharedPtr<T>>& Container);

        template <typename T>
        void CleanUniqueRef(Dictionary<std::string, SharedPtr<T>>& Container);
        void CleanCycle();
        
        void SetAssetRootDirectory(const std::string& Directory);
    protected:
        AssetManager();
    private:
        static UniquePtr<AssetManager> assetManager;
        Dictionary<std::string, SharedPtr<sf::Texture>> LoadedTextures;
        Dictionary<std::string, SharedPtr<sf::Font>> LoadedFonts;
        std::string RootDirectory;
    };

    template <typename T>
    SharedPtr<T> AssetManager::LoadAsset(const std::string& Path, Dictionary<std::string, SharedPtr<T>>& Container)
    {
        const auto FoundAsset = Container.find(Path);
        if (FoundAsset != Container.end())
        {
            return FoundAsset->second;
        }
        SharedPtr<T> NewAsset{new T};
        if (NewAsset->loadFromFile(RootDirectory + Path))
        {
            Container.insert({Path, NewAsset});
            return NewAsset;
        }
        LOG("Asset cannot be loaded : Path to asset invalid");
        return SharedPtr<T> {nullptr};
    }

    template <typename T>
    void AssetManager::CleanUniqueRef(Dictionary<std::string, SharedPtr<T>>& Container)
    {
        for (auto iter = Container.begin(); iter != Container.end();)
        {
            if (iter->second.unique())
            {
                LOG("Cleaning asset: %s", iter->first.c_str());
                iter = Container.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }
}
