/**
 * @file Item.cpp
 * @author Milo Baran
 */
#include "pch.h"
#include "Item.h"

using namespace std;

/**
 * Destructor
 */
Item::~Item()
{

}


///**
// * Draw a item
// * @param dc Device context to draw on
// */
//void Item::Draw(wxDC *dc)
//{
//    double wid = mItemBitmap->GetWidth();
//    double hit = mItemBitmap->GetHeight();
//    dc->DrawBitmap(*mItemBitmap,
//                   int(GetX() - wid / 2),
//                   int(GetY() - hit / 2));
//}

/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
Item::Item(Game *game) : mGame(game)
{
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"id", &mId);

    wxString size = node->GetAttribute(L"p", L"0,0").ToStdWstring();
    size.BeforeFirst(',').ToDouble(&mX);
    size.AfterFirst(',').ToDouble(&mY);
}

/**
 * Draw this item
 * @param graphics Device context to draw on
 * @param declaration Declaration object associated with this item
 */
void Item::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration)
{
}
