/**
 * @file Item.cpp
 * @author Milo Baran
 */

#include "Item.h"
using namespace std;

/**
 * Destructor
 */
Item::~Item()
{

}


/**
 * Draw a item
 * @param dc Device context to draw on
 */
void Item::Draw(wxDC *dc)
{
    double wid = mItemBitmap->GetWidth();
    double hit = mItemBitmap->GetHeight();
    dc->DrawBitmap(*mItemBitmap,
                   int(GetX() - wid / 2),
                   int(GetY() - hit / 2));
}

/**
 * Constructor
 * @param level The level this item is a member of
 * @param filename The name of the file to display for this item
 */
Item::Item(Level *level, const std::wstring &filename) : mLevel(level)
{
    mItemImage = make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mItemBitmap = make_unique<wxBitmap>(*mItemImage);
}