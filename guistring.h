//
// Created by jeo on 24.09.2021.
//

#ifndef APHASIA_GUISTRING_H
#define APHASIA_GUISTRING_H

#include <wx/wx.h>

#if defined(_WIN32) || defined(WIN32)

#include <string>

wxString utf8guistr(const std::wstring &bit16str_utf8);

#define STR(str) (utf8guistr(_T(str)))

#else

#define STR(str) (_T(str))

#endif

#endif //APHASIA_GUISTRING_H
