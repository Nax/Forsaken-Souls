#include "Language.hpp"

LanguageManager::LanguageManager()
: _currentLang(Language::English)
{
    _lang[0] = {
#include "Translations/en.inc"
    };
    _lang[1] = {
#include "Translations/fr.inc"
    };
}

const char*
tr(const char* key)
{
    return LanguageManager::instance().getDictionary().at(key);
}
