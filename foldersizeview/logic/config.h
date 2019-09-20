#ifndef CONFIG_H
#define CONFIG_H


#define kAppVersion "0.7"


class Config
{
public:
    Config();

    static Config & instance();

    void enableGroupByFileExtension(bool enable);
    bool isEnableGroupByFileExtension();

    void enableSunburstMode(bool enable);
    bool isEnableSunburstMode();
};

#endif // CONFIG_H
