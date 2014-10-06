// ----------------------------------------------------------------------------
// wxSFMLCanvas.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <SFML/Graphics/RenderWindow.hpp>
#include <wx/control.h>

class wxSFMLCanvas :
    public wxControl,
    public sf::RenderWindow
{
public:

    /*!
     * @brief Constructor
     */
    wxSFMLCanvas( wxWindow* Parent = NULL,
                  wxWindowID Id = -1,
                  const wxPoint& Position = wxDefaultPosition,
                  const wxSize& Size = wxDefaultSize,
                  long Style = 0 );

    /*!
     * @brief Destructor
     */
    virtual ~wxSFMLCanvas();

private:

    virtual void OnUpdate() = 0;

    void OnIdle( wxIdleEvent& event );
    void OnPaint( wxPaintEvent& event );
    void OnEraseBackground( wxEraseEvent& event );

    //wxDECLARE_EVENT_TABLE();
};
