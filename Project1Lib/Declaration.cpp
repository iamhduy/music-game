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

    wxString size = node->GetAttribute(L"size", L"0,0").ToStdWstring();
    size.BeforeFirst(',').ToInt(&mSizeX);
    size.AfterFirst(',').ToInt(&mSizeY);

    node->GetAttribute(L"image", &mImageFile);
}
