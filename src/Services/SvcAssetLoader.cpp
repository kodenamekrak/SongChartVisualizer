#include "Services/SvcAssetLoader.hpp"

#include "UnityEngine/Resources.hpp"

UnityEngine::Material* noGlowMaterial;
UnityEngine::Sprite* circleSprite;

UnityEngine::Material* get_noGlowMaterial()
{
    if(!noGlowMaterial || !noGlowMaterial->m_CachedPtr.m_value)
        noGlowMaterial = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Material*>().First([](auto x){ return x->get_name() == "UINoGlow"; });
    return noGlowMaterial;
}

UnityEngine::Sprite* get_circleSprite()
{
    if(!circleSprite || !circleSprite->m_CachedPtr.m_value)
        circleSprite = UnityEngine::Resources::FindObjectsOfTypeAll<UnityEngine::Sprite*>().FirstOrDefault([](UnityEngine::Sprite* x){ return x->get_name() == "Circle"; });
    return circleSprite;
}