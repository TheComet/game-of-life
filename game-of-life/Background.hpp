// ----------------------------------------------------------------------------
// include files

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class RenderTarget;
}

class Background
{
public:

    /*!
     * @brief Default constructor
     */
    Background();

    /*!
     * @brief Default destructor
     */
    ~Background();

    /*!
     * @brief Generates a background with the default viewsize 100x100
     * @note Must be called before the background can be drawn
     */
    void generate();

    /*!
     * @brief Generates a background with the specified viewsize
     * The viewsize specifies how many times the underlying grid texture needs
     * to be tiled in order to fill up the entire screen. The viewsize is
     * specified in pixels. If you had a 800x600 render window for instance,
     * you would specify '800,600'.
     * @note Must be called before the background can be drawn
     * @param viewSize The size of the render area
     */
    void generate( const sf::Vector2i& viewSize );

    /*!
     * @brief Sets the view position
     * The view position is specified in pixels, and describes where the
     * camera is currently looking at. When the background is drawn, the tiling
     * of the background textures will be shifted according to this value, but
     * in the opposite direction, to emulate the feeling of being able to "look
     * around"
     * @param position The centre of the rendering area to look at
     */
    void setViewPosition( const sf::Vector2f& position );

    /*!
     * @brief Sets the zoom factor
     * A value of 1.0 is the nominal zoom factor. The larger the number, the
     * further you zoom in, the smaller the number, the further you zoom out.
     * @param factor The zoom factor
     */
    void setZoomFactor( double factor );

    /*!
     * @brief Sets the minimum and maximum allowed zoom factors
     * @param min The minimum zoom factor
     * @param max The maximum zoom factor
     */
    void setZoomLimits( double min, double max );

    /*!
     * @brief Will draw the background to the specified render target.
     */
    void draw( sf::RenderTarget* target );

private:
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;

    sf::Vector2f m_Scroll;
    sf::Vector2i m_ViewSize;

    double m_ZoomFactor;
    double m_ZoomMin;
    double m_ZoomMax;
};
