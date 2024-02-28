/**
 * @file Declaration.cpp
 * @author hduy
 */

#include "pch.h"
#include "Declaration.h"
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

    string size = node->GetAttribute(L"p", L"0,0").ToStdString();
    auto index = size.find(',');
    mSizeX = stoi(size.substr(index));
    mSizeY = stoi(size.substr(index+1, size.size()));

    node->GetAttribute(L"image", &mImageFile);
}
