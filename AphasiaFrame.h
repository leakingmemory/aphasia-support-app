//
// Created by jeo on 23.09.2021.
//

#ifndef APHASIA_APHASIAFRAME_H
#define APHASIA_APHASIAFRAME_H

#include <wx/wx.h>
#include <wx/notebook.h>
#include <wx/listctrl.h>

template <typename Sub> struct CategorySelection {
    typedef typename Sub phrase_t;

    wxString Name;
    std::vector<phrase_t> Phrases;

    CategorySelection(const wxString &name) : Name() {
        Name = name;
    }
    template <int N> CategorySelection(const wxString &name, const phrase_t (&phrases)[N]) : CategorySelection(name) {
        for (int i = 0; i < N; i++) {
            Phrases.push_back(phrases[i]);
        }
    }
};

class AphasiaFrame : public wxFrame {
private:
    wxNotebook *tabControl;
    wxListView *mainPhrase;
    wxListView *secondPhrase;
private:
    void UpdateSizes(const wxSize &size);
    std::vector<CategorySelection<wxString>> *OnMainCatChanged(std::vector<CategorySelection<CategorySelection<wxString>>> &);
    void OnPhraseChanged(std::vector<CategorySelection<wxString>> &);
    void ClearSecondaryPhrases();
    void OnResize(wxSizeEvent &);
public:
    AphasiaFrame(const wxString &title);
    std::vector<CategorySelection<wxString>> &OnMainCatChanged(CategorySelection<CategorySelection<wxString>> &);
    void OnPhraseChanged(CategorySelection<wxString> &);
};


#endif //APHASIA_APHASIAFRAME_H
