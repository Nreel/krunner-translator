#ifndef TRANSLATOR_CONFIG_KEYS_H
#define TRANSLATOR_CONFIG_KEYS_H

#include <QStringList>

static const char CONFIG_PRIMARY[] = "primaryLanguage";
static const char CONFIG_SECONDARY[] = "secondaryLanguage";
static const char CONFIG_TARGET[] = "targetLanguage";
static const char CONFIG_TRIGGER_PHRASES[] = "triggerPhrases";
static const char CONFIG_BAIDU_APPID[] = "baiduAPPID";
static const char CONFIG_BAIDU_APIKEY[] = "baiduAPIKey";
static const char CONFIG_YOUDAO_APPID[] = "youdaoAPPID";
static const char CONFIG_YOUDAO_APPSEC[] = "youdaoAPPSec";
static const char CONFIG_BAIDU_ENABLE[] = "baiduEnable";
static const char CONFIG_YOUDAO_ENABLE[] = "youdaoEnable";
static const char CONFIG_DEEPL_APIKEY[] = "deeplAPIKey";
static const char CONFIG_DEEPL_ENABLE[] = "deeplEnable";
static const char CONFIG_GOOGLE_ENABLE[] = "googleEnable";
static const char CONFIG_BING_ENABLE[] = "bingEnable";

// Trigger phrases are optional prefixes that select the default target language.
// "tr" deliberately mirrors the Flow Launcher plugin, but it shadows the Turkish
// language code; remove it in the settings if you translate into Turkish often.
static inline QStringList defaultTriggerPhrases() {
    return {QStringLiteral("tr"), QStringLiteral("transl"), QStringLiteral("translate")};
}

#endif
