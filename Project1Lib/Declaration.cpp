/**
 * @file Declaration.cpp
 * @author hduy
 */

#include "pch.h"
#include "Declaration.h"
#include "Game.h"
using namespace std;

/**
 * Destructor
 */
Declaration::~Declaration()
{
}

/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
Declaration::Declaration(Game *game) : mGame(game)
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
void Declaration::XmlLoad(wxXmlNode* node)
{
    node->GetAttribute(L"id", &mId);

    wxString size = node->GetAttribute(L"size", L"0,0").ToStdWstring();
    size.BeforeFirst(',').ToInt(&mSizeX);
    size.AfterFirst(',').ToInt(&mSizeY);

    mImageFile = node->GetAttribute(L"image", "");
}

/**
 * Draw this item
 * @param dc Device context to draw on
 * @param x location x
 * @param y location y
 */
void Declaration::Draw(wxDC *dc, double x, double y)
{
    wstring ItemImageFile = mGame->GetImagesDirectory() + L"\\" + mImageFile;
    std::unique_ptr<wxImage> ItemImage = make_unique<wxImage>(ItemImageFile, wxBITMAP_TYPE_ANY);
    std::unique_ptr<wxBitmap> ItemBitmap = make_unique<wxBitmap>(*ItemImage);
    dc->DrawBitmap(*ItemBitmap,
                   int(x - mSizeX / 2),
                   int(y - mSizeY / 2));
}

