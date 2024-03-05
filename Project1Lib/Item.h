/**
 * @file Item.h
 * @author Milo Baran
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEM_H
#define PROJECT1_PROJECT1LIB_ITEM_H
#include <wx/xml/xml.h>
#include "Declaration.h"
class Game;

/**
 * Item Base Class
 *
 */
class Item
{
private:
    /// The game this item is contained in
    Game *mGame;

    /// Item's id
    wxString mId;

    // Item location in the game
    double mX = 0;     ///< X location for the center of the item
    double mY = 0;     ///< Y location for the center of the item

    /// The underlying image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

protected:
    Item(Game *game);

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    virtual ~Item();

    /**
     * The X location of the item
     * @returns X location in pixels
     */
    double GetX() const { return mX; }

    /**
     * The Y location of the item
     * @returns Y location in pixels
     */
    double GetY() const { return mY; }

    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    virtual void SetLocation(double x, double y)
    {
        mX = x;
        mY = y;
    }

//    virtual void Draw(wxDC *dc);

    /**
     * Get the pointer to the Level object
     * @return Pointer to Level object
     */
    Game *GetGame() { return mGame; }

    /**
     *
     * @return the id of this object
     */
    wxString GetId() { return mId; }

    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Handle updates for animation
     * @param elapsed The time since the last update
     */
    virtual void Update(double elapsed) {}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration);

    virtual bool HitTest(int x, int y);
};
#endif //PROJECT1_PROJECT1LIB_ITEM_H
