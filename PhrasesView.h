//
// Created by sigsegv on 9/26/21.
//

#ifndef APHASIA_PHRASESVIEW_H
#define APHASIA_PHRASESVIEW_H

#include <wx/wx.h>
#include "AphasiaFrame.h"

class PhrasesView : public wxPanel {
private:
    std::vector<CategorySelection<wxString>> *phrases;
    wxListView *mainPhrase;
    wxListView *secondPhrase;
    void OnPhraseChanged();
    void ClearSecondaryPhrases();
    void OnResize(wxSizeEvent &);
    void OnPhraseChanged(CategorySelection<wxString> &);
public:
    PhrasesView(wxWindow *parent, std::vector<CategorySelection<wxString>> &);
};


#endif //APHASIA_PHRASESVIEW_H
