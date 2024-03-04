/**
 * @file DeclarationMeter.cpp
 * @author hduy
 */
#include "pch.h"
#include "DeclarationMeter.h"
#include "Game.h"
#include <string>

/// Image Directory
const std::wstring ImagesDir = L"./images/";

using namespace std;
/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
DeclarationMeter::DeclarationMeter(Game *game) : Declaration(game)
{
}

/**
 * Load the attributes for an declaration node.
 * @param node The Xml node we are loading the declaration from
 */
void DeclarationMeter::XmlLoad(wxXmlNode *node)
{
    mCoverFile = node->GetAttribute(L"cover", "");
    mNeedleFile = node->GetAttribute(L"needle", "");

    Declaration::XmlLoad(node);
}

/**
 * Draw this item
 * @param dc Device context to draw on
 * @param x location x
 * @param y location y
 */
void DeclarationMeter::Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y)
{
    Declaration::Draw(graphics, x, y);

    if (mNeedleBitmap == nullptr) {
        wstring ItemImageFile = ImagesDir + mNeedleFile;
        mNeedleImage = make_unique<wxImage>(ItemImageFile, wxBITMAP_TYPE_ANY);
        mNeedleBitmap = make_unique<wxBitmap>(*mNeedleImage);
    }

//    int imgWid = mNeedleBitmap->GetWidth();
//    int imgHit = mNeedleBitmap->GetHeight();

    graphics->DrawBitmap(*mNeedleBitmap, int(x - GetSizeX()/2), int(y -  GetSizeY()/2),
                         int(GetSizeX()), int(GetSizeY()));

    if (mCoverBitmap == nullptr) {
        wstring ItemImageFile = ImagesDir + mCoverFile;
        mCoverImage = make_unique<wxImage>(ItemImageFile, wxBITMAP_TYPE_ANY);
        mCoverBitmap = make_unique<wxBitmap>(*mCoverImage);
    }

//    imgWid = mCoverBitmap->GetWidth();
//    imgHit = mCoverBitmap->GetHeight();

    graphics->DrawBitmap(*mCoverBitmap, int(x - GetSizeX()/2), int(y -  GetSizeY()/2),
                         int(GetSizeX()), int(GetSizeY()));
}
