#include <wx/wx.h>
#include <wx/textctrl.h>
#include "AphasiaFrame.h"

class AphasiaApp : public wxApp {
public:
    bool OnInit() override {
        AphasiaFrame *main = new AphasiaFrame(_T("Klar tale"));
        main->Show(true);
        return true;
    }
};

IMPLEMENT_APP(AphasiaApp)

