/**
 * @file Item.cpp
 * @author Milo Baran
 */
#include "pch.h"
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
 * @param level The level this item is a member of
 * @param filename The name of the file to display for this item
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

    string size = node->GetAttribute(L"p", L"0,0").ToStdString();
    auto index = size.find(',');
    mX = stoi(size.substr(index));
    mY = stoi(size.substr(index+1, size.size()));
}
