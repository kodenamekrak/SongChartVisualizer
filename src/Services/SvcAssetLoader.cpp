#include "Services/SvcAssetLoader.hpp"

#include "UnityEngine/Resources.hpp"

UnityW<UnityEngine::Material> noGlowMaterial;
UnityW<UnityEngine::Sprite> circleSprite;

UnityW<UnityEngine::Material> get_NoGlowMaterial()
{
    if(!noGlowMaterial)
        noGlowMaterial = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>().front_or_default([](auto x){ return x->get_name() == "UINoGlow"; });
    return noGlowMaterial;
}

UnityW<UnityEngine::Sprite> get_circleSprite()
{
    if(!circleSprite)
        circleSprite = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Sprite*>().front_or_default([](UnityEngine::Sprite* x){ return x->get_name() == "Circle"; });
    return circleSprite;
}