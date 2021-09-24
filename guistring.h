//
// Created by jeo on 24.09.2021.
//

#ifndef APHASIA_GUISTRING_H
#define APHASIA_GUISTRING_H

#include <wx/wx.h>
#include <string>

wxString utf8guistr(const std::wstring &bit16str_utf8);

#define STR(str) (utf8guistr(_T(str)))

#endif //APHASIA_GUISTRING_H
