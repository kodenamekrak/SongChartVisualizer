#pragma once

#include "custom-types/shared/macros.hpp"

#include "HMUI/ViewController.hpp"
#include "UnityEngine/Color.hpp"

#include "bsml/shared/macros.hpp"
#include "bsml/shared/BSML/Components/Settings/IncrementSetting.hpp"

#include "macros.hpp"

DECLARE_CLASS_CODEGEN(SongChartVisualizer, SettingsViewController, HMUI::ViewController) {

    DECLARE_OVERRIDE_METHOD_MATCH(void, DidActivate, &HMUI::ViewController::DidActivate, bool firstActivation, bool addedToHierarchy, bool screenSystemEnabling);

    DECLARE_VECTOR_INCREMENT(standardPos);
    DECLARE_VECTOR_INCREMENT(standardRot);
    DECLARE_VECTOR_INCREMENT(nonStandardPos);
    DECLARE_VECTOR_INCREMENT(nonStandardRot);

    DECLARE_BSML_PROPERTY(bool, showGraph);
    DECLARE_BSML_PROPERTY(bool, peakWarning);
    DECLARE_BSML_PROPERTY(bool, showBackground);
    DECLARE_BSML_PROPERTY(float, backgroundOpacity);
    DECLARE_BSML_PROPERTY(bool, showNpsLines);

    DECLARE_BSML_PROPERTY(UnityEngine::Color, backgroundColor);
    DECLARE_BSML_PROPERTY(UnityEngine::Color, lineColor);
    DECLARE_BSML_PROPERTY(UnityEngine::Color, pointerColor);

private:
    std::vector<BSML::IncrementSetting*> incrementSettings;
};