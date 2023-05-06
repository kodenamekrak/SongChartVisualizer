#include "main.hpp"
#include "UI/SettingsViewcontroller.hpp"
#include "assets.hpp"
#include "ModConfig.hpp"

#include "bsml/shared/BSML.hpp"

#include "UnityEngine/RectTransform.hpp"

DEFINE_TYPE(SongChartVisualizer, SettingsViewController);

namespace SongChartVisualizer
{

    void SettingsViewController::DidActivate(bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling)
    {
        if (!firstActivation)
            return;

        BSML::parse_and_construct(IncludedAssets::SettingsView_bsml, get_transform(), this);

        incrementSettings = {
            standardPosXIncrement, standardPosYIncrement, standardPosZIncrement,
            standardRotXIncrement, standardRotYIncrement, standardRotZIncrement,
            nonStandardPosXIncrement, nonStandardPosYIncrement, nonStandardPosZIncrement,
            nonStandardRotXIncrement, nonStandardRotYIncrement, nonStandardRotZIncrement};

        for (int i = 0; i < incrementSettings.size(); i++)
        {
            auto inc = incrementSettings.at(i);
            auto rect = inc->get_gameObject()->get_transform()->Find("ValuePicker")->GetComponent<UnityEngine::RectTransform *>();
            rect->set_sizeDelta(UnityEngine::Vector2(25, rect->get_sizeDelta().y));
        }
    }

    DEFINE_VECTOR_INCREMENT(standardPos, standardLevelPosition);
    DEFINE_VECTOR_INCREMENT(standardRot, standardLevelRotation);
    DEFINE_VECTOR_INCREMENT(nonStandardPos, nonStandardLevelPosition);
    DEFINE_VECTOR_INCREMENT(nonStandardRot, nonStandardLevelRotation);

    DEFINE_BSML_PROPERTY(bool, showGraph);
    DEFINE_BSML_PROPERTY(bool, peakWarning);
    DEFINE_BSML_PROPERTY(bool, showBackground);
    DEFINE_BSML_PROPERTY(float, backgroundOpacity);

    DEFINE_BSML_PROPERTY(UnityEngine::Color, backgroundColor);
    DEFINE_BSML_PROPERTY(UnityEngine::Color, lineColor);
    DEFINE_BSML_PROPERTY(UnityEngine::Color, pointerColor);
}