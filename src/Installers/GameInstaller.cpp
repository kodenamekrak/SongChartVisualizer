#include "main.hpp"
#include "Installers/GameInstaller.hpp"
#include "UI/ChartView.hpp"
#include "ModConfig.hpp"

#include "GlobalNamespace/PlayerSpecificSettings.hpp"
#include "GlobalNamespace/GameplayModifiers.hpp"
#include "GlobalNamespace/IReadonlyBeatmapData.hpp"

#include "Zenject/DiContainer.hpp"
#include "Zenject/FromBinderNonGeneric.hpp"

DEFINE_TYPE(SongChartVisualizer::Installers, GameInstaller);

namespace SongChartVisualizer::Installers
{

    void GameInstaller::ctor(GlobalNamespace::GameplayCoreSceneSetupData *gameplayCoreSceneSetupData)
    {
        _gameplayCoreSceneSetupData = gameplayCoreSceneSetupData;
    }

    void GameInstaller::InstallBindings()
    {
        if (!getModConfig().showGraph.GetValue() || _gameplayCoreSceneSetupData->playerSpecificSettings->noTextsAndHuds || _gameplayCoreSceneSetupData->gameplayModifiers->zenMode || !_gameplayCoreSceneSetupData->transformedBeatmapData)
            return;

        auto container = get_Container();
        container->BindInterfacesAndSelfTo<ChartView *>()->AsSingle();
    }
}