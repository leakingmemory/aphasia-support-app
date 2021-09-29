//
// Created by sigsegv on 9/26/21.
//

#include "PhrasesView.h"

PhrasesView::PhrasesView(wxWindow *parent, std::vector<CategorySelection<wxString>> &phrases) : wxPanel(parent), phrases(&phrases) {
    mainPhrase = new wxListView(this, wxID_ANY, wxPoint(0, 0), wxSize(MAIN_PHRASE_WIDTH, -1));
    mainPhrase->AppendColumn(_T(""));
    mainPhrase->SetColumnWidth(0, MAIN_PHRASE_WIDTH);
    mainPhrase->Bind(wxEVT_LIST_ITEM_SELECTED, [this] (wxListEvent &event) {
        OnPhraseChanged();
    });
    mainPhrase->ClearAll();
    mainPhrase->AppendColumn(_T(""));
    mainPhrase->SetColumnWidth(0, MAIN_PHRASE_WIDTH);
    int i = 0;
    for (auto &phrase : phrases) {
        mainPhrase->InsertItem(i++, phrase.Name);
    }
    secondPhrase = new wxListView(this, wxID_ANY, wxPoint(MAIN_PHRASE_WIDTH, 0), wxSize(MAIN_PHRASE_WIDTH, -1));
    secondPhrase->AppendColumn(_T(""));
    secondPhrase->SetColumnWidth(0, MAIN_PHRASE_WIDTH);
    this->Bind(wxEVT_SIZE, &PhrasesView::OnResize, this);
}

void PhrasesView::OnPhraseChanged() {
    auto selection = mainPhrase->GetFirstSelected();
    if (selection >= 0 && selection < phrases->size()) {
        OnPhraseChanged((*phrases)[selection]);
    }
}

void PhrasesView::ClearSecondaryPhrases() {
    secondPhrase->ClearAll();
}

void PhrasesView::OnResize(wxSizeEvent &event) {
    const wxSize &size = event.GetSize();
    mainPhrase->SetSize(wxSize(150, size.GetHeight()));
    secondPhrase->SetSize(wxSize(150, size.GetHeight()));
}

void PhrasesView::OnPhraseChanged(CategorySelection<wxString> &phrases) {
    secondPhrase->ClearAll();
    secondPhrase->AppendColumn(_T(""));
    secondPhrase->SetColumnWidth(0, MAIN_PHRASE_WIDTH);
    int i = 0;
    for (auto &phrase : phrases.Phrases) {
        secondPhrase->InsertItem(i++, phrase);
    }
}
