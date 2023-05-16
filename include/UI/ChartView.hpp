#pragma once

#include "Core/WindowGraph.hpp"
#include "Models/NpsInfo.hpp"

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "bsml/shared/BSML/FloatingScreen/FloatingScreen.hpp"

#include "GlobalNamespace/AudioTimeSyncController.hpp"
#include "GlobalNamespace/IReadonlyBeatmapData.hpp"
#include "GlobalNamespace/ComboUIController.hpp"

#include "HMUI/CurvedTextMeshPro.hpp"

#include "UnityEngine/Color.hpp"

#include "Tweening/TimeTweeningManager.hpp"

#include "Zenject/IInitializable.hpp"
#include "Zenject/ITickable.hpp"

#define INTERFACES { classof(Zenject::IInitializable*), classof(Zenject::ITickable*) }

___DECLARE_TYPE_WRAPPER_INHERITANCE(SongChartVisualizer, ChartView, Il2CppTypeEnum::IL2CPP_TYPE_CLASS, Il2CppObject, "SongChartVisualizer", INTERFACES, 0, nullptr,
    
    DECLARE_PRIVATE_FIELD(GlobalNamespace::AudioTimeSyncController*, _audioTimeSyncController);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::IReadonlyBeatmapData*, _beatmapData);
    DECLARE_PRIVATE_FIELD(GlobalNamespace::ComboUIController*, _comboUIController);
    DECLARE_PRIVATE_FIELD(Tweening::TimeTweeningManager*, _timeTweeningManager);
    DECLARE_PRIVATE_FIELD(SongChartVisualizer::WindowGraph*, _windowGraph);
    DECLARE_PRIVATE_FIELD(BSML::FloatingScreen*, _floatingScreen);
    DECLARE_PRIVATE_FIELD(bool, _shouldNotRunTick);
    DECLARE_PRIVATE_FIELD(UnityEngine::GameObject*, _selfCursor);
    DECLARE_PRIVATE_FIELD(UnityEngine::GameObject*, _peakWarningGo);
    DECLARE_PRIVATE_FIELD(HMUI::CurvedTextMeshPro*, _peakWarningText);

    DECLARE_PRIVATE_FIELD(int, _currentSectionIdx);
    DECLARE_PRIVATE_FIELD(int, _hardestSectionIdx);
    DECLARE_PRIVATE_FIELD(float, _timeTillPeak);

    DECLARE_INSTANCE_METHOD(UnityEngine::GameObject*, CreateSelfCursor, UnityEngine::Color color);
    DECLARE_INSTANCE_METHOD(void, PrepareWarningText);
    DECLARE_INSTANCE_METHOD(void, FadeInTextIfNeeded);
    DECLARE_INSTANCE_METHOD(void, FadeInText, HMUI::CurvedTextMeshPro* text, float t);

    std::vector<NpsInfo> GetNpsSections(GlobalNamespace::IReadonlyBeatmapData* beatmapData);

    DECLARE_OVERRIDE_METHOD(void, Initialize, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::IInitializable::Initialize>::get());
    DECLARE_OVERRIDE_METHOD(void, Tick, il2cpp_utils::il2cpp_type_check::MetadataGetter<&::Zenject::ITickable::Tick>::get());

    DECLARE_CTOR(ctor, GlobalNamespace::AudioTimeSyncController* audioTimeSyncController, GlobalNamespace::IReadonlyBeatmapData* readonlyBeatmapData, Tweening::TimeTweeningManager* timeTweeningManager);

    std::vector<NpsInfo> _npsSections;
    NpsInfo _currentSection;
)