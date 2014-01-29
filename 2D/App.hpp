// ----------------------------------------------------------------------------
// include files

#include <wx/app.h>

class App :
    public wxApp
{
public:

    App();
    ~App();
    virtual bool OnInit();
};

IMPLEMENT_APP( App );
