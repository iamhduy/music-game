/**
 * @file MusicNote.cpp
 * @author hduy
 */

#include "MusicNote.h"

/// Image Directory
const std::wstring ImagesDir = L"./images/";

/// Width of the long duration lines. These
/// lines are drawn as wxRED
const int LongDurationLineWidth = 12;

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
    wxPen longDurationPen(*wxRED, LongDurationLineWidth);
    graphics->SetPen(longDurationPen);
    graphics->StrokeLine(mX, mY, mLongDurationX, mLongDurationY);


    if (mItemBitmap == nullptr) {
        std::wstring ItemImageFile = ImagesDir + (declaration->GetImageFile()).ToStdWstring();
        mItemImage = std::make_unique<wxImage>(ItemImageFile, wxBITMAP_TYPE_ANY);
        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    }

//    int imgWid = mItemBitmap->GetWidth();
//    int imgHit = mItemBitmap->GetHeight();

    graphics->DrawBitmap(*mItemBitmap,
                         int(mX - (declaration->GetSizeX()*mPercentOfFullSize)/ 2),
                         int(mY - (declaration->GetSizeY()*mPercentOfFullSize) / 2),
                         int(declaration->GetSizeX()*mPercentOfFullSize),
                         int(declaration->GetSizeY()*mPercentOfFullSize));
}
bool MusicNote::CheckIfHit(double currentBeat, double tolerance)
{
    if (abs(currentBeat - mHitTime) <= tolerance)
    {
        return true;
    }
    return false;
}

int MusicNote::GetTrackNum()
{
    int trackNum = 0;
    int multiplier = 1;

    for (int i = mId.length() - 1; i >= 0; --i) {
        char c = mId[i];
        if (isdigit(c)) {
            trackNum += (c - '0') * multiplier;
            multiplier *= 10;
        }
        else {
            break;
        }
    }

    return trackNum;
}