// ----------------------------------------------------------------------------
// Drawable.hpp
// ----------------------------------------------------------------------------

#ifndef __DRAWABLE_HPP__
#define __DRAWABLE_HPP__

// ----------------------------------------------------------------------------
// include files

#include <SFML/System/Vector2.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class RenderTarget;
}

/*!
 * @brief Base class for all drawable objects required to be rendered
 */
class Drawable
{
public:

    /*!
     * @brief Default constructor
     */
    Drawable();

    /*!
     * @brief Default destructor
     */
    ~Drawable();

    /*!
     * @brief Draws the object to a render target
     * @param target The render target to draw to
     * @param scroll The offset relative to the top left corner of the
     * rendertarget to draw to
     */
    virtual void draw( sf::RenderTarget* target, sf::Vector2f viewSize, sf::Vector2f scroll, float zoomFactor ) = 0;
};

#endif // __DRAWABLE_HPP__
