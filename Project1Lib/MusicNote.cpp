/**
 * @file MusicNote.cpp
 * @author hduy
 */

#include "MusicNote.h"

/// Image Directory
const std::wstring ImagesDir = L"./images/";

/**
 * Constructor
 * @param game The game this music is a member of
 *
 */
MusicNote::MusicNote(Game *game) : mGame(game)
{
}

/**
 * Destructor
 */
MusicNote::~MusicNote()
{
}

/**
 * Load the attributes for an music node.
 * @param node The Xml node we are loading the item from
 */
void MusicNote::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"id", &mId);
    node->GetAttribute(L"sound", &mSoundName);
    node->GetAttribute(L"measure").ToInt(&mMeasure);
    node->GetAttribute(L"beat").ToDouble(&mBeat);
    node->GetAttribute(L"duration").ToDouble(&mDuration);
}

void MusicNote::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration)
{
    if (mItemBitmap == nullptr) {
        std::wstring ItemImageFile = ImagesDir + (declaration->GetImageFile()).ToStdWstring();
        mItemImage = std::make_unique<wxImage>(ItemImageFile, wxBITMAP_TYPE_ANY);
        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    }

//    int imgWid = mItemBitmap->GetWidth();
//    int imgHit = mItemBitmap->GetHeight();

    graphics->DrawBitmap(*mItemBitmap,
                         int(mX - declaration->GetSizeX()/ 2),
                         int(mY - declaration->GetSizeY() / 2),
                         int(declaration->GetSizeX()),
                         int(declaration->GetSizeY()));
}