#include <iostream>
#include <cstdlib>

#include "Fcpp.hpp"

/// フォントファミリーにマッチしたフォントのパスを返す．
/// フォントファミリーは第一引数にて受け取る．
/// usage: findFont "font family name"
int main(int argc, char* argv[]) {
    FcInit();

    if (argc <= 1) {
        return EXIT_FAILURE;
    }

    const auto SearchPattern = Fcpp::CreatePattern({
        {FC_FAMILY, (const FcChar8*)(argv[1])}
    });

    const auto FoundFath = Fcpp::SearchFont(Fcpp::CurrentDefaultConfig(), SearchPattern);
    if(!FoundFath.empty()) {
        std::cout << FoundFath.generic_string() << std::endl;
    }

    FcFini();
    return 0;
}