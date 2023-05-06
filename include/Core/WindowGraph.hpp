#pragma once
#include "custom-types/shared/macros.hpp"

#include "UnityEngine/MonoBehaviour.hpp"
#include "UnityEngine/Color.hpp"
#include "UnityEngine/GameObject.hpp"
#include "UnityEngine/Canvas.hpp"
#include "UnityEngine/Vector2.hpp"

DECLARE_CLASS_CODEGEN(SongChartVisualizer, WindowGraph, UnityEngine::MonoBehaviour,
    
    DECLARE_INSTANCE_FIELD(UnityEngine::Canvas*, _canvas);

    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, CreateDotConnection, UnityEngine::Vector2 dotPositionA, UnityEngine::Vector2 dotPositionB, UnityEngine::Color linkColor);
    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, CreateCircle, UnityEngine::Vector2 anchoredPosition, bool makeDotsVisible);

    public:
        void ShowGraph(std::vector<float> valueList, UnityEngine::Color linkColor);
        void CreateNpsLines(std::pair<float, float> maxPoints, std::pair<float, float> minPoints);
        std::vector<UnityEngine::GameObject*> linkPositions;
        std::vector<UnityEngine::GameObject*> dotObjects;
)