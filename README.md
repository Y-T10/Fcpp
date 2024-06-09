# Fcpp
[Fontconfig](https://www.freedesktop.org/wiki/Software/fontconfig/) のC++ ラッパーライブラリ.

## 使用例
フォントファミリー名からフォントを探す．([findFont.cpp](example/findFont.cpp))

```C++
#include <iostream>
#include <cstdlib>

#include "Fcpp.hpp"

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
```

## License
### fontconfig
fontconfig/COPYING

Copyright © 2000,2001,2002,2003,2004,2006,2007 Keith Packard
Copyright © 2005 Patrick Lam
Copyright © 2007 Dwayne Bailey and Translate.org.za
Copyright © 2009 Roozbeh Pournader
Copyright © 2008,2009,2010,2011,2012,2013,2014,2015,2016,2017,2018,2019,2020 Red Hat, Inc.
Copyright © 2008 Danilo Šegan
Copyright © 2012 Google, Inc.


Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation, and that the name of the author(s) not be used in
advertising or publicity pertaining to distribution of the software without
specific, written prior permission.  The authors make no
representations about the suitability of this software for any purpose.  It
is provided "as is" without express or implied warranty.

THE AUTHOR(S) DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
EVENT SHALL THE AUTHOR(S) BE LIABLE FOR ANY SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.
