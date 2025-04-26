#pragma once

#include "custom-types/shared/macros.hpp"
#include "lapiz/shared/macros.hpp"

#include "Zenject/Installer.hpp"

#include "GlobalNamespace/GameplayCoreSceneSetupData.hpp"

DECLARE_CLASS_CODEGEN(SongChartVisualizer::Installers, GameInstaller, Zenject::Installer) {

    DECLARE_INSTANCE_FIELD_PRIVATE(GlobalNamespace::GameplayCoreSceneSetupData*, _gameplayCoreSceneSetupData);

    DECLARE_OVERRIDE_METHOD_MATCH(void, InstallBindings, &Zenject::Installer::InstallBindings);

    DECLARE_CTOR(ctor, GlobalNamespace::GameplayCoreSceneSetupData* gameplayCoreSceneSetupData);
};