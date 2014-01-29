// ----------------------------------------------------------------------------
// MainFrame.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <wx/frame.h>

class MainFrame :
    public wxFrame
{
public:

    /*!
     * @brief Constructor
     */
    MainFrame();

    /*!
     * @brief Destructor
     */
    ~MainFrame();

    void OnAbout( wxCommandEvent& event );
    void OnExit( wxCommandEvent& event );

    wxDECLARE_EVENT_TABLE();
};

enum{
};

wxBEGIN_EVENT_TABLE( MainFrame, wxFrame )
    EVT_MENU( wxID_EXIT, MainFrame::OnExit )
    EVT_MENU( wxID_ABOUT, MainFrame::OnAbout )
wxEND_EVENT_TABLE()
