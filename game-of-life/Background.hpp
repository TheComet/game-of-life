// ----------------------------------------------------------------------------
// include files

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include <Drawable.hpp>

// ----------------------------------------------------------------------------
// forward declarations

namespace sf {
    class RenderTarget;
}

class Background :
    public Drawable
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
     * @brief Will draw the background to the specified render target.
     */
    void draw( sf::RenderTarget* target, sf::Vector2f viewSize, sf::Vector2f scroll, float zoomFactor );

private:
    sf::Texture m_Texture;
    sf::Texture m_ZoomedOutTexture;
    sf::Sprite m_Sprite;
};
