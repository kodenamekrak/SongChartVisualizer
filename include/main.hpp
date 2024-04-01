#pragma once

// Include the modloader header, which allows us to tell the modloader which mod this is, and the version etc.
#include "scotland2/shared/modloader.h"

// beatsaber-hook is a modding framework that lets us call functions and fetch field values from in the game
// It also allows creating objects, configuration, and importantly, hooking methods to modify their values
#include "beatsaber-hook/shared/utils/logging.hpp"
#include "beatsaber-hook/shared/utils/il2cpp-functions.hpp"
#include "beatsaber-hook/shared/utils/hooking.hpp"

static constexpr auto Logger = Paper::ConstLoggerContext("SongChartVisualizer");
#define INFO(msg, ...) Logger.info(msg, ## __VA_ARGS__)
#define DEBUG(msg, ...) Logger.debug(msg, ## __VA_ARGS__)

#define SCV_EXPORT extern "C" __attribute((visibility("default")))