#include "main.hpp"
#include "ModConfig.hpp"
#include "Installers/GameInstaller.hpp"
#include "UI/SettingsViewcontroller.hpp"

#include "bsml/shared/BSML.hpp"

#include "lapiz/shared/zenject/Zenjector.hpp"
#include "lapiz/shared/AttributeRegistration.hpp"

static ModInfo modInfo;

Logger &getLogger()
{
    static Logger *logger = new Logger(modInfo);
    return *logger;
}

// Called at the early stages of game loading
extern "C" void setup(ModInfo &info)
{
    info.id = MOD_ID;
    info.version = VERSION;
    modInfo = info;

    getLogger().info("Completed setup!");
}

// Called later on in the game loading - a good time to install function hooks
extern "C" void load()
{
    il2cpp_functions::Init();

    getModConfig().Init(modInfo);

    getLogger().info("Installing SongChartVisualizer...");

    custom_types::Register::AutoRegister();
    Lapiz::Attributes::AutoRegister();

    BSML::Register::RegisterSettingsMenu<SongChartVisualizer::SettingsViewController*>("SongChartVisualizer");
    BSML::Register::RegisterMainMenu<SongChartVisualizer::SettingsViewController*>("SongChartVisualizer", "SongChartVisualizer", "SongChartVisualizer settings menu!");

    auto zenjector = Lapiz::Zenject::Zenjector::Get();
    zenjector->Install<SongChartVisualizer::Installers::GameInstaller*>(Lapiz::Zenject::Location::StandardPlayer);
    zenjector->Install<SongChartVisualizer::Installers::GameInstaller*>(Lapiz::Zenject::Location::Multi);

    getLogger().info("Installed SongChartVisualizer!");
}