/**
 * @file DeclarationSoundBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "DeclarationSoundBoard.h"
#include "Game.h"
#include <string>

/// Image Directory
const std::wstring ImagesDir = L"./images/";

/// Top clearance so we don't draw past the cover
/// as a fraction of the soundboard height. This
/// is where the pucks come in
const double TopClearance = 0.1;

using namespace std;

/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
DeclarationSoundBoard::DeclarationSoundBoard(Game *game) : Declaration(game)
{
}

/**
 * Load the attributes for an declaration node.
 * @param node The Xml node we are loading the declaration from
 */
void DeclarationSoundBoard::XmlLoad(wxXmlNode *node)
{
    mCoverFile = node->GetAttribute(L"cover", "");
    node->GetAttribute(L"top-width").ToInt(&mTopWidth);
    node->GetAttribute(L"size-beats").ToInt(&mSizeBeats);

    Declaration::XmlLoad(node);
}

/**
 * Draw this item
 * @param dc Device context to draw on
 * @param x location x
 * @param y location y
 */
void DeclarationSoundBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y)
{
    Declaration::Draw(graphics, x, y);

    if (mCoverBitmap == nullptr) {
        wstring ItemImageFile = ImagesDir + mCoverFile;
        mCoverImage = make_unique<wxImage>(ItemImageFile, wxBITMAP_TYPE_ANY);
        mCoverBitmap = make_unique<wxBitmap>(*mCoverImage);
    }

//    int imgWid = mCoverBitmap->GetWidth();
//    int imgHit = mCoverBitmap->GetHeight();

    graphics->DrawBitmap(*mCoverBitmap, int(x - GetSizeX()/2), int(y -  GetSizeY()/2),
                         int(GetSizeX()), int(GetSizeY()));
}



