/**
 * @file MusicNote.cpp
 * @author hduy
 */

#include "MusicNote.h"


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

bool MusicNote::CheckIfHit(double currentBeat, double tolerance)
{
    if (abs(currentBeat - mHitTime) <= tolerance)
    {
        return true;
    }
    return false;
}
