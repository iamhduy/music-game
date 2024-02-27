/**
 * @file SoundBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "SoundBoard.h"
#include <string>
using namespace std;
/// The maximum number of tracks
const int MaxTracks = 10;

/// What is the border of the left and right
/// of the tracks? This is the percentage of
/// the space to the left of the first track line
/// and to the right of the last track line
const double Border = 0.075;

/// Top clearance so we don't draw past the cover
/// as a fraction of the soundboard height. This
/// is where the pucks come in
const double TopClearance = 0.1;

/// Percentage down on the soundboard to the keys
/// This is where the pucks go under the key and
/// disappear.
const double KeyRow = 0.85;


SoundBoard::SoundBoard(Game* game) : Item(game)
{
}

void SoundBoard::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"id", &mId);
    node->GetAttribute(L"top-width", "300").ToInt(&mTopWidth);

    node->GetAttribute(L"image", &mImageFile);
    node->GetAttribute(L"cover", &mCoverFile);

    string size = node->GetAttribute(L"size", L"0,0").ToStdString();
    auto index = size.find(',');
    mSizeX = stoi(size.substr(index));
    mSizeY = stoi(size.substr(index+1, size.size()));

    Item::XmlLoad(node);
}


