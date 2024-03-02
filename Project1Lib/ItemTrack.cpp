/**
 * @file ItemTrack.cpp
 * @author hduy
 */
#include "pch.h"
#include "ItemTrack.h"

using namespace std;

/**
 * Constructor
 * @param game The level this item is a member of
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
    node->GetAttribute(L"key-image", &mKeyImageFile);
    node->GetAttribute(L"key", &mKeyValue);

    wxString size = node->GetAttribute(L"key-size", L"0,0").ToStdWstring();
    size.BeforeFirst(',').ToInt(&mSizeX);
    size.AfterFirst(',').ToInt(&mSizeY);
}
