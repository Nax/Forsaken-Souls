#ifndef LANGUAGE_HPP
#define LANGUAGE_HPP

#include <Lums>
#include <unordered_map>

const char*     tr(const char* str);

enum class Language
{
    English,
    French
};

class LanguageManager : public lm::Singleton<LanguageManager>
{
public:
    using Dictionary = std::unordered_map<std::string, const char*>;
    LanguageManager();
    Language            get() const { return _currentLang; }
    const Dictionary&   getDictionary() const { return _lang[int(_currentLang)]; }
    void                set(Language lang) { _currentLang = lang; }

private:
    Dictionary  _lang[2];
    Language    _currentLang;
};

#endif
