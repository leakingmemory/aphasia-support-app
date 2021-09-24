//
// Created by jeo on 24.09.2021.
//

#include <iostream>
#include <string>
#include <locale>
#include <codecvt>
#include <memory>

#include "guistring.h"

static std::vector<std::shared_ptr<wxString>> strings{};

wxString utf8guistr(const std::wstring &bit16str_utf8) {
    wxString guistr{};
    {
        std::string str{};
        str.reserve(bit16str_utf8.size());
        {
            struct CharStr {
                char *bytes;

                CharStr(int size) : bytes((char *) malloc(size)) {}

                ~CharStr() {
                    if (bytes != nullptr) {
                        free(bytes);
                        bytes = nullptr;
                    }
                }
            };
            std::unique_ptr<CharStr> bytes = std::make_unique<CharStr>(bit16str_utf8.size() + 1);
            int i = 0;
            for (wchar_t ch: bit16str_utf8) {
                bytes->bytes[i++] = (char) ch;
            }
            bytes->bytes[i] = 0;
            str.append(bytes->bytes, 0, i);
        }
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wstr = converter.from_bytes(str);
        guistr.append(wstr.c_str(), wstr.size());
    }
    return guistr;
}