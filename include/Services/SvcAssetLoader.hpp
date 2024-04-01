#include "UnityEngine/Material.hpp"
#include "UnityEngine/Sprite.hpp"

UnityW<UnityEngine::Material> get_NoGlowMaterial();
static __declspec(property(get=get_noGlowMaterial)) UnityW<UnityEngine::Material> NoGlowMaterial;

UnityW<UnityEngine::Sprite> get_CircleSprite();
static __declspec(property(get=get_CircleSprite)) UnityW<UnityEngine::Sprite> CircleSprite;;