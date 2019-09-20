#include "config.h"
#include <QSettings>

static const char *kKeyEnableGroupByFileExtension = "enableGroupByFileExtension";
static const char *kKeyEnableSunburstMode = "enableSunburstMode";


Config::Config()
{

}

Config &Config::instance()
{
    static Config o;
    return o;
}

void Config::enableGroupByFileExtension(bool enable)
{
    QSettings settings;
    settings.setValue(kKeyEnableGroupByFileExtension,enable);
}

bool Config::isEnableGroupByFileExtension()
{
    QSettings settings;
    if (!settings.contains(kKeyEnableGroupByFileExtension)) {
        return false;
    }
    return settings.value(kKeyEnableGroupByFileExtension).toBool();
}

void Config::enableSunburstMode(bool enable)
{
    QSettings settings;
    settings.setValue(kKeyEnableSunburstMode,enable);
}

bool Config::isEnableSunburstMode()
{
    QSettings settings;
    if (!settings.contains(kKeyEnableSunburstMode)) {
        return false;
    }
    return settings.value(kKeyEnableSunburstMode).toBool();
}
