//
// Created by jeo on 23.09.2021.
//

#ifndef APHASIA_APHASIAFRAME_H
#define APHASIA_APHASIAFRAME_H

#include <vector>
#include <memory>
#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>

#define MAIN_PHRASE_WIDTH 150

template <typename Sub> struct CategorySelection {
    wxString Name;
    std::vector<Sub> Phrases;

    CategorySelection(const wxString &name) : Name() {
        Name = name;
    }
    template <int N> CategorySelection(const wxString &name, const Sub (&phrases)[N]) : CategorySelection(name) {
        for (int i = 0; i < N; i++) {
            Phrases.push_back(phrases[i]);
        }
    }
};

class AphasiaFrame : public wxFrame {
private:
    wxNotebook *tabControl;
    std::shared_ptr<std::vector<CategorySelection<CategorySelection<wxString>>>> mainCategories;
private:
    void UpdateSizes(const wxSize &size);
    void OnResize(wxSizeEvent &);
public:
    AphasiaFrame(const wxString &title);
};


#endif //APHASIA_APHASIAFRAME_H
