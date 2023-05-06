#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "Zenject/Installer.hpp"

#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"

DECLARE_CLASS_CODEGEN(SongChartVisualizer::Installers, GameInstaller, Zenject::Installer,

    DECLARE_PRIVATE_FIELD(GlobalNamespace::GameplayCoreSceneSetupData*, _gameplayCoreSceneSetupData);

    DECLARE_OVERRIDE_METHOD(void, InstallBindings, il2cpp_utils::il2cpp_type_check::MetadataGetter<&Zenject::Installer::InstallBindings>::get());

    DECLARE_CTOR(ctor, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetupData);
)