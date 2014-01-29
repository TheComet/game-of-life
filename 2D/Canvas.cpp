// ----------------------------------------------------------------------------
// Canvas.cpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <Canvas.hpp>
#include <iostream>
// ----------------------------------------------------------------------------
Canvas::Canvas( wxWindow* Parent, wxWindowID Id, const wxPoint& Position, const wxSize& Size, long Style ) :
    wxSFMLCanvas( Parent, Id, Position, Size, Style )
{
}

// ----------------------------------------------------------------------------
Canvas::~Canvas()
{
}

// ----------------------------------------------------------------------------
void Canvas::OnUpdate()
{
    std::cout << "update me" << std::endl;
}
