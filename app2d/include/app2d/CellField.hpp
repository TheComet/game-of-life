// ----------------------------------------------------------------------------
// CellField.hpp
// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------
// include files

#include <iostream>

#include <app2d/Drawable.hpp>
#include <gol/GenericCellField.hxx>
#include <gol/Vector2.hxx>

#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Sprite.hpp>

/*!
 * @brief Simulates the game of life
 */
class CellField :
    public GOL::GenericCellField< GOL::Vector2<int> >,
    public Drawable
{
public:

    /*!
     * @brief Default constructor
     */
    CellField();

    /*!
     * @brief Default destructor
     */
    ~CellField();

    /*!
     * @brief
     */
    void draw( sf::RenderTarget* target, sf::Vector2f viewSize, sf::Vector2f viewPosition, float zoomFactor );

private:

    sf::Texture m_CellTexture;
    sf::Sprite m_CellSprite;

};
