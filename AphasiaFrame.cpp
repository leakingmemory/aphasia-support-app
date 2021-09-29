//
// Created by jeo on 23.09.2021.
//

#include <memory>
#include "AphasiaFrame.h"
#include "guistring.h"
#include "PhrasesView.h"

#define FILL_SIZE 10000
#define TAB_HEIGHT 30

AphasiaFrame::AphasiaFrame(const wxString &title) : wxFrame(nullptr, wxID_ANY, title, wxDefaultPosition, wxSize(800, 600)), mainCategories() {
    mainCategories = std::make_shared<std::vector<CategorySelection<CategorySelection<wxString>>>>();
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
    tabControl = new wxNotebook(this, wxID_ANY, wxPoint(0,0), wxSize(FILL_SIZE, FILL_SIZE));
    for (auto &mainCat : *mainCategories) {
        tabControl->AddPage(new PhrasesView(tabControl, mainCat.Phrases), mainCat.Name, false);
    }
    struct ContextType {
        std::vector<CategorySelection<wxString>> *secondPhrase;

        ContextType() {
            secondPhrase = nullptr;
        }
    };
    std::shared_ptr<ContextType> Context = std::make_shared<ContextType>();
#ifndef __linux__
    tabControl->SetTabSize(wxSize(-1,  TAB_HEIGHT));
#endif
    this->Bind(wxEVT_SIZE, &AphasiaFrame::OnResize, this);
}

void AphasiaFrame::OnResize(wxSizeEvent &event) {
    UpdateSizes(event.GetSize());
}

void AphasiaFrame::UpdateSizes(const wxSize &size) {
    tabControl->SetSize(wxSize(size.GetWidth(), size.GetHeight() - TAB_HEIGHT));
}
