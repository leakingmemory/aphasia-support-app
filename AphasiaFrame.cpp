//
// Created by jeo on 23.09.2021.
//

#include <memory>
#include "AphasiaFrame.h"
#include "guistring.h"

#define FILL_SIZE 10000
#define TAB_HEIGHT 30
#define MAIN_PHRASE_WIDTH 150

AphasiaFrame::AphasiaFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)){
    std::shared_ptr<std::vector<CategorySelection<CategorySelection<wxString>>>> mainCategories = std::make_shared<std::vector<CategorySelection<CategorySelection<wxString>>>>();
    mainCategories->push_back(CategorySelection<CategorySelection<wxString>>(STR("Handlinger"),
                                     {
                                        CategorySelection<wxString>(
                                                STR("Gå til"),
                                                {
                                                        STR("Google Earth"),
                                                        STR("kafe"),
                                                        STR("skolen"),
                                                        STR("byen"),
                                                        STR("sykehuset")
                                                }
                                        ),
                                        CategorySelection<wxString>(STR("Gå fra")),
                                        CategorySelection<wxString>(STR("Kjøre til")),
                                        CategorySelection<wxString>(STR("Kjøre fra")),
                                        CategorySelection<wxString>(STR("Reise til")),
                                        CategorySelection<wxString>(STR("Reise fra")),
                                        CategorySelection<wxString>(STR("Klippe gress")),
                                        CategorySelection<wxString>(STR("Klippe hår")),
                                        CategorySelection<wxString>(STR("Male")),
                                        CategorySelection<wxString>(STR("Spikre")),
                                        CategorySelection<wxString>(STR("Fiske"))
                                     }));
    mainCategories->emplace_back(STR("Familie"));
    mainCategories->emplace_back(STR("Kjente"));
    mainCategories->emplace_back(STR("Natur"));
    mainCategories->emplace_back(STR("Reiser"));
    mainCategories->emplace_back(STR("Minner"));
    tabControl = new wxNotebook(this, wxID_ANY, wxPoint(0,0), wxSize(FILL_SIZE, TAB_HEIGHT));
    for (auto &mainCat : *mainCategories) {
        tabControl->AddPage(new wxPanel(tabControl), mainCat.Name, false);
    }
    struct ContextType {
        std::vector<CategorySelection<wxString>> *secondPhrase;

        ContextType() {
            secondPhrase = nullptr;
        }
    };
    std::shared_ptr<ContextType> Context = std::make_shared<ContextType>();
    tabControl->SetTabSize(wxSize(-1,  TAB_HEIGHT));
    tabControl->Bind(wxEVT_NOTEBOOK_PAGE_CHANGED, [this, mainCategories, Context] (wxBookCtrlEvent &event) {
        Context->secondPhrase = OnMainCatChanged(*mainCategories);
        if (Context->secondPhrase != nullptr) {
            OnPhraseChanged(*(Context->secondPhrase));
        }
    });
    mainPhrase = new wxListView(this, wxID_ANY, wxPoint(0, TAB_HEIGHT), wxSize(MAIN_PHRASE_WIDTH, -1));
    mainPhrase->AppendColumn(_T(""));
    mainPhrase->SetColumnWidth(0, MAIN_PHRASE_WIDTH);
    mainPhrase->Bind(wxEVT_LIST_ITEM_SELECTED, [this, Context] (wxListEvent &event) {
        if (Context->secondPhrase != nullptr) {
            OnPhraseChanged(*(Context->secondPhrase));
        }
    });
    secondPhrase = new wxListView(this, wxID_ANY, wxPoint(MAIN_PHRASE_WIDTH, TAB_HEIGHT), wxSize(MAIN_PHRASE_WIDTH, -1));
    secondPhrase->AppendColumn(_T(""));
    secondPhrase->SetColumnWidth(0, MAIN_PHRASE_WIDTH);
    Context->secondPhrase = OnMainCatChanged(*mainCategories);
    this->Bind(wxEVT_SIZE, &AphasiaFrame::OnResize, this);
}

std::vector<CategorySelection<wxString>> *AphasiaFrame::OnMainCatChanged(std::vector<CategorySelection<CategorySelection<wxString>>> &mainCats) {
    auto selection = tabControl->GetSelection();
    if (selection >= 0 && selection < mainCats.size()) {
        return &OnMainCatChanged(mainCats[selection]);
    } else {
        return nullptr;
    }
}

void AphasiaFrame::OnResize(wxSizeEvent &event) {
    UpdateSizes(event.GetSize());
}

void AphasiaFrame::UpdateSizes(const wxSize &size) {
    tabControl->SetSize(wxSize(size.GetWidth(), TAB_HEIGHT));
    mainPhrase->SetSize(wxSize(150, size.GetHeight() - TAB_HEIGHT));
    secondPhrase->SetSize(wxSize(150, size.GetHeight() - TAB_HEIGHT));
}

void AphasiaFrame::OnPhraseChanged(std::vector<CategorySelection<wxString>> &phrases) {
    auto selection = mainPhrase->GetFirstSelected();
    if (selection >= 0 && selection < phrases.size()) {
        OnPhraseChanged(phrases[selection]);
    }
}

void AphasiaFrame::ClearSecondaryPhrases() {
    secondPhrase->ClearAll();
}

std::vector<CategorySelection<wxString>> &AphasiaFrame::OnMainCatChanged(CategorySelection<CategorySelection<wxString>> &mainCat) {
    ClearSecondaryPhrases();
    mainPhrase->ClearAll();
    mainPhrase->AppendColumn(_T(""));
    mainPhrase->SetColumnWidth(0, MAIN_PHRASE_WIDTH);
    int i = 0;
    for (auto &phrase : mainCat.Phrases) {
        mainPhrase->InsertItem(i++, phrase.Name);
    }
    return mainCat.Phrases;
}

void AphasiaFrame::OnPhraseChanged(CategorySelection<wxString> &phrases) {
    secondPhrase->ClearAll();
    secondPhrase->AppendColumn(_T(""));
    secondPhrase->SetColumnWidth(0, MAIN_PHRASE_WIDTH);
    int i = 0;
    for (auto &phrase : phrases.Phrases) {
        secondPhrase->InsertItem(i++, phrase);
    }
}