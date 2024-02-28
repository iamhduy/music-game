/**
 * @file ItemTrack.cpp
 * @author hduy
 */
#include "pch.h"
#include "ItemTrack.h"
#include <string>

using namespace std;

/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
ItemTrack::ItemTrack(Game *game) : Item(game)
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

    string size = node->GetAttribute(L"key-size", L"0,0").ToStdString();
    auto index = size.find(',');
    mSizeX = stoi(size.substr(index));
    mSizeY = stoi(size.substr(index+1, size.size()));
}
