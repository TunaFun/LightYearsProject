﻿#pragma once

#include <stdio.h>
#include <memory>
#include <map>
#include <unordered_map>

namespace ly
{

template<typename T>
    using UniquePtr = std::unique_ptr<T>;

template<typename T>
    using SharedPtr = std::shared_ptr<T>;

template<typename T>
    using WeakPtr = std::weak_ptr<T>;

template<typename T>
    using List = std::vector<T>;

template<typename KeyT, typename ValueT, typename Predicate = std::less<KeyT>>
    using Map = std::map<KeyT, ValueT, Predicate>;

template<typename KeyT, typename ValueT, typename Hasher = std::hash<KeyT>>
    using Dictionary = std::unordered_map<KeyT, ValueT, Hasher>;
    
    
//macro defining
#define LOG(M, ...) printf(M "\n", ##__VA_ARGS__)
}
