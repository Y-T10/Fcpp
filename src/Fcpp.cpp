#include "Fcpp.hpp"

void intrusive_ptr_add_ref(FcPattern *p) {
    FcPatternReference(p);
}
void intrusive_ptr_release(FcPattern *p) {
    FcPatternDestroy(p);
}
void intrusive_ptr_add_ref(FcConfig *p) {
    FcConfigReference(p);
}
void intrusive_ptr_release(FcConfig *p) {
    FcConfigDestroy(p);
}

namespace {
    using namespace Fcpp;

    const Pattern FontMatch(const Config& conf, const Pattern& pattern) noexcept {
        FcResult result;
        Pattern fontPattern = CreateFcPtr<FcFontMatch>(conf.get(), pattern.get(), &result);
        if(fontPattern.get() == nullptr) {
            return nullptr;
        }
        if(result != FcResult::FcResultMatch) {
            return nullptr;
        }
        return fontPattern;
    }

    const Pattern SubstitutePattern(const Config& conf, const Pattern& pattern) noexcept {
        static_assert(!!FcTrue);
        static_assert(!FcFalse);

        Pattern SubstitutedPattern = CreateFcPtr<FcPatternDuplicate>(pattern.get());
        if(!FcConfigSubstitute(conf.get(), SubstitutedPattern.get(), FcMatchPattern)) {
            return nullptr;
        }
        FcDefaultSubstitute(SubstitutedPattern.get());
        return SubstitutedPattern;
    }
}

const std::filesystem::path Fcpp::SearchFont(const Config& conf, const Pattern& pattern) noexcept {
    const auto SearchPattern = SubstitutePattern(conf, pattern);
    if (!SearchPattern) {
        return "";
    }
    const Pattern fontPattern = FontMatch(conf, SearchPattern);
    if(!fontPattern) {
        return "";
    }
    FcChar8* filePaht;
    FcPatternGetString(fontPattern.get(), FC_FILE, 0, &filePaht);
    return std::filesystem::path((char*)filePaht);
};

const Fcpp::Config Fcpp::CurrentDefaultConfig() noexcept {
    return Config(FcConfigGetCurrent());
}

const Fcpp::Pattern Fcpp::CreatePattern(const std::map<std::string, std::basic_string<FcChar8>>& param) noexcept {
    Pattern pattern = CreateFcPtr<FcPatternCreate>();
    if(pattern.get() == nullptr) {
        return nullptr;
    }
    if(param.empty()) {
        return pattern;
    }
    for(const auto& p: param) {
        if(!FcPatternAddString(pattern.get(), p.first.c_str(), p.second.c_str())) {
            return nullptr;
        }
    }
    return pattern;
}