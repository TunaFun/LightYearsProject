#pragma once
#include <string>

std::string GetResourceDirectory()
{
#ifdef NDEBUG //Release build!
    return "assets/";
#else
    return "F:/MniejszeProjekty/LightYearsProject/LightYearsGame/assets/";
#endif    
}
