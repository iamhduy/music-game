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

/// Positive or negative rotations of this amount will move
/// the needle to the limit in that direction.
/// A meter score of 0 will be a rotation of -0.9
/// A meter score of 100% (11) will be a rotation of 0.9
const double MaxNeedleRotation = 0.9;

/// This is how far down the need image the pivot point is
/// as a percentage of the height of the image.
const double NeedlePivotYOffset = 0.80;

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
 * @param graphics Device context to draw on
 * @param x location x
 * @param y location y
 */
void DeclarationMeter::Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y)
{
    Declaration::Draw(graphics, x, y);

    mScorePct = 0.25; //< constant set for now. Need to figure out how to get percentage from scoreboard

    if (mNeedleBitmap == nullptr) {
        wstring ItemImageFile = ImagesDir + mNeedleFile;
        mNeedleImage = make_unique<wxImage>(ItemImageFile, wxBITMAP_TYPE_ANY);
        mNeedleBitmap = make_unique<wxBitmap>(*mNeedleImage);
    }

    int wid = mNeedleBitmap->GetWidth();
    int hit = mNeedleBitmap->GetHeight();
    int needlePivotY = (int)(hit * NeedlePivotYOffset);

    graphics->PushState();
    graphics->Translate(x, y + needlePivotY - hit/2);
    graphics->Rotate(-MaxNeedleRotation + (mScorePct * MaxNeedleRotation * 2));
    graphics->DrawBitmap(*mNeedleBitmap, -wid/2, -needlePivotY,
                         wid, hit);

    graphics->PopState();

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
