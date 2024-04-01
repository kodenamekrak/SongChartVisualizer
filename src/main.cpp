#include "main.hpp"
#include "ModConfig.hpp"
#include "Installers/GameInstaller.hpp"
#include "UI/SettingsViewcontroller.hpp"

#include "bsml/shared/BSML.hpp"

#include "lapiz/shared/zenject/Zenjector.hpp"
#include "lapiz/shared/AttributeRegistration.hpp"

static modloader::ModInfo modInfo{MOD_ID, VERSION, 0};

// Called at the early stages of game loading
SCV_EXPORT void setup(CModInfo* info)
{
    *info = modInfo.to_c();

    getModConfig().Init(modInfo);
    INFO("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
SCV_EXPORT void late_load()
{
    il2cpp_functions::Init();

    INFO("Installing SongChartVisualizer...");

    custom_types::Register::AutoRegister();
    Lapiz::Attributes::AutoRegister();

    BSML::Register::RegisterSettingsMenu<SongChartVisualizer::SettingsViewController*>("SongChartVisualizer");
    BSML::Register::RegisterMainMenu<SongChartVisualizer::SettingsViewController*>("SongChartVisualizer", "SongChartVisualizer", "SongChartVisualizer settings menu!");

    using namespace Lapiz::Zenject;
    auto zenjector = Zenjector::Get();
    zenjector->Install<SongChartVisualizer::Installers::GameInstaller*>(Location::StandardPlayer | Location::Multi);

    INFO("Installed SongChartVisualizer!");
}