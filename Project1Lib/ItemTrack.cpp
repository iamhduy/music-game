/**
 * @file ItemTrack.cpp
 * @author hduy
 */
#include "pch.h"
#include "ItemTrack.h"

using namespace std;

/// Image Directory
const std::wstring ImagesDir = L"./images/";

/**
 * Constructor
 * @param soundBoard The soundboard holding this item
 *
 */
ItemTrack::ItemTrack(ItemSoundBoard *soundBoard) : mSoundBoard(soundBoard)
{
}

/**
 * Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void ItemTrack::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"track").ToInt(&mTrack);
    mKeyImageFile = node->GetAttribute(L"key-image", "").ToStdWstring();
    node->GetAttribute(L"key", &mKeyValue);

    wxString size = node->GetAttribute(L"key-size", L"0,0").ToStdWstring();
    size.BeforeFirst(',').ToInt(&mSizeX);
    size.AfterFirst(',').ToInt(&mSizeY);
}

/**
 * @return Key image file directory
 */
std::wstring ItemTrack::GetKeyImageFile()
{
    return ImagesDir + mKeyImageFile;
}

/**
 * Draw this item
 * @param graphics Device context to draw on
 * @param x location x
 * @param y location y
 */
void ItemTrack::Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y)
{
    unique_ptr<wxImage> itemImage = make_unique<wxImage>(GetKeyImageFile(), wxBITMAP_TYPE_ANY);
    auto itemBitmap = make_unique<wxBitmap>(*itemImage);

    graphics->DrawBitmap(*itemBitmap,
                         int(x - mSizeX / 2), //need to modify 17.5
                         int(y - mSizeY / 2),
                         mSizeX,
                         mSizeY);
}
