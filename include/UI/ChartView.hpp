#pragma once

#include "Core/WindowGraph.hpp"
#include "Models/NpsInfo.hpp"
#include "System/Object.hpp"

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/IReadonlyBeatmapData.hpp"
#include "GlobalNamespace/ComboUIController.hpp"
#include "GlobalNamespace/BeatmapKey.hpp"

#include "HMUI/CurvedTextMeshPro.hpp"

#include "UnityEngine/Color.hpp"

#include "Tweening/TimeTweeningManager.hpp"

#include "Zenject/IInitializable.hpp"
#include "Zenject/ITickable.hpp"

DECLARE_CLASS_CODEGEN_INTERFACES(SongChartVisualizer, ChartView, System::Object, Zenject::IInitializable*, Zenject::ITickable*) {

    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::AudioTimeSyncController*, _audioTimeSyncController);
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::IReadonlyBeatmapData*, _beatmapData);
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::BeatmapKey, _beatmapKey);
    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::ComboUIController*, _comboUIController);
    DECLARE_INSTANCE_FIELD_PRIVATE(Tweening::TimeTweeningManager*, _timeTweeningManager);
    DECLARE_INSTANCE_FIELD_PRIVATE(SongChartVisualizer::WindowGraph*, _windowGraph);
    DECLARE_INSTANCE_FIELD_PRIVATE(BSML::FloatingScreen*, _floatingScreen);
    DECLARE_INSTANCE_FIELD_PRIVATE(bool, _shouldNotRunTick);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::GameObject*, _selfCursor);
    DECLARE_INSTANCE_FIELD_PRIVATE(UnityEngine::GameObject*, _peakWarningGo);
    DECLARE_INSTANCE_FIELD_PRIVATE(HMUI::CurvedTextMeshPro*, _peakWarningText);

    DECLARE_INSTANCE_FIELD_PRIVATE(int, _currentSectionIdx);
    DECLARE_INSTANCE_FIELD_PRIVATE(int, _hardestSectionIdx);
    DECLARE_INSTANCE_FIELD_PRIVATE(float, _timeTillPeak);

    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, CreateSelfCursor, UnityEngine::Color color);
    DECLARE_INSTANCE_METHOD(void, PrepareWarningText);
    DECLARE_INSTANCE_METHOD(void, FadeInTextIfNeeded);
    DECLARE_INSTANCE_METHOD(void, FadeInText, HMUI::CurvedTextMeshPro* text, float t);

    std::vector<NpsInfo> GetNpsSections(GlobalNamespace::IReadonlyBeatmapData* beatmapData);

    DECLARE_OVERRIDE_METHOD_MATCH(void, Initialize, &Zenject::IInitializable::Initialize);
    DECLARE_OVERRIDE_METHOD_MATCH(void, Tick, &Zenject::ITickable::Tick);

    DECLARE_INJECT_METHOD(void, Inject, GlobalNamespace::AudioTimeSyncController* audioTimeSyncController, GlobalNamespace::IReadonlyBeatmapData* readonlyBeatmapData, GlobalNamespace::BeatmapKey beatmapKey, Tweening::TimeTweeningManager* timeTweeningManager);
    DECLARE_DEFAULT_CTOR();

    std::vector<NpsInfo> _npsSections;
    NpsInfo _currentSection;
};