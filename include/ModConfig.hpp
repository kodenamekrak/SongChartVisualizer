#include "config-utils/shared/config-utils.hpp"

#include "UnityEngine/Vector2.hpp"

DECLARE_CONFIG(ModConfig,
    CONFIG_VALUE(showGraph, bool, "Enabled", true);
    CONFIG_VALUE(peakWarning, bool, "PeakWarning", true);
    CONFIG_VALUE(showNpsLines, bool, "ShowNpsLines", false);

    CONFIG_VALUE(standardLevelPosition, UnityEngine::Vector3, "ChartStandardLevelPosition", UnityEngine::Vector3(0, -0.4f, 2.25f));
    CONFIG_VALUE(standardLevelRotation, UnityEngine::Vector3, "ChartStandardLevelRotation", UnityEngine::Vector3(35, 0, 0));
    CONFIG_VALUE(nonStandardLevelPosition, UnityEngine::Vector3, "Chart360LevelPosition", UnityEngine::Vector3(0, 3.5f, 3));
    CONFIG_VALUE(nonStandardLevelRotation, UnityEngine::Vector3, "Chart360LevelRotation", UnityEngine::Vector3(-30, 0, 0));

    CONFIG_VALUE(showBackground, bool, "ShowBackground", false);
    CONFIG_VALUE(backgroundOpacity, float, "BackgroundOpacity", 0.05f);

    CONFIG_VALUE(backgroundColor, UnityEngine::Color, "BackgroundColor", UnityEngine::Color::get_blue());
    CONFIG_VALUE(lineColor, UnityEngine::Color, "LineColor", UnityEngine::Color::get_white());
    CONFIG_VALUE(pointerColor, UnityEngine::Color, "PointerColor", UnityEngine::Color::get_green());
)