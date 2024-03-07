/**
 * @file Music.cpp
 * @author hduy
 */

#include "Music.h"
/**
 * Constructor
 * @param game The game this music is a member of
 *
 */
Music::Music(Game *game) : mGame(game)
{
}

/**
 * Destructor
 */
Music::~Music()
{
}

/**
 * Load the attributes for an music node.
 * @param node The Xml node we are loading the item from
 */
void Music::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"id", &mId);
    node->GetAttribute(L"sound", &mSoundName);
    node->GetAttribute(L"measure").ToInt(&mMeasure);
    node->GetAttribute(L"beat").ToDouble(&mBeat);
    node->GetAttribute(L"duration").ToDouble(&mDuration);
}
