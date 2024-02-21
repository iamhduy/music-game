/**
 * @file Item.h
 * @author Milo Baran
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_ITEM_H
#define PROJECT1_PROJECT1LIB_ITEM_H

class Level;

class Item
{
private:
    /// The game this item is contained in
    Level   *mLevel;

    // Item location in the game
    double  mX = 0;     ///< X location for the center of the item
    double  mY = 0;     ///< Y location for the center of the item

    /// The underlying image
    std::unique_ptr<wxImage> mItemImage;

    /// The bitmap we can display for this item
    std::unique_ptr<wxBitmap> mItemBitmap;

protected:
    Item(Level* aquarium, const std::wstring &filename);

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item &) = delete;

    ~Item();

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
    virtual void SetLocation(double x, double y) { mX = x; mY = y; }

    virtual void Draw(wxDC *dc);

    /**
     * Get the pointer to the Level object
     * @return Pointer to Level object
     */
    Level *GetGame() { return mLevel;  }

    void XmlLoad(wxXmlNode *node);
};

#endif //PROJECT1_PROJECT1LIB_ITEM_H