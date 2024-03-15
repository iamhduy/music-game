/**
 * @file MusicNote.cpp
 * @author hduy
 */
#include "pch.h"
#include "MusicNote.h"
#include "Game.h"

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

    mSound = this->GetGame()->FindSoundByName(mSoundName);
}

/**
 * Draw this note
 * @param graphics Device context to draw on
 * @param declaration declaration of this note
 */
void MusicNote::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration)
{
    wxPen longDurationPen(*wxRED, LongDurationLineWidth);
    graphics->SetPen(longDurationPen);
    graphics->StrokeLine(mLongDurationX1, mLongDurationY1, mLongDurationX2, mLongDurationY2);


    if (mItemBitmap == nullptr) {
        std::wstring ItemImageFile = ImagesDir + (declaration->GetImageFile()).ToStdWstring();
        mItemImage = std::make_unique<wxImage>(ItemImageFile, wxBITMAP_TYPE_ANY);
        mItemBitmap = std::make_unique<wxBitmap>(*mItemImage);
    }

    graphics->DrawBitmap(*mItemBitmap,
                         int(mX - (declaration->GetSizeX()*mPercentOfFullSize)/ 2),
                         int(mY - (declaration->GetSizeY()*mPercentOfFullSize) / 2),
                         int(declaration->GetSizeX()*mPercentOfFullSize),
                         int(declaration->GetSizeY()*mPercentOfFullSize));
}

/**
 * @param currentBeat current beat of the song
 * @param keyX x pos of the key
 * @param keyY y pos of the key
 * @return if this note hit
 */
bool MusicNote::CheckIfHit(double currentBeat, int keyX, int keyY)
{
//    if (abs(currentBeat - mHitTime) <= mNoteTolerance)
    if (abs(currentBeat - mBeatAtPlay) <= mNoteTolerance)
    {
//        std::cout << "Note" << std::endl;
//        std::cout << keyY << std::endl;
//        std::cout << mY << std::endl;
//        std::cout << keyX << std::endl;
//        std::cout << mX << std::endl;
        if (mY >= (keyY - mNoteTolerance) && mY <= (keyY + mNoteTolerance) && mX >= (keyX - mNoteTolerance) && mX <= (keyX + mNoteTolerance))
        {
            return true;
        }
    }
    return false;
}

/**
 * @return track num of the key
 */
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

/**
 * Play this sound corresponding to this note
 * @param beat beat of the song when played
 */
void MusicNote::PlaySound(double beat)
{
    mSound->LoadSound(GetGame()->GetAudioEngine());
    mSound->PlaySound();
    mIsPlayed = !mIsPlayed;
    mBeatAtPlay = beat;
}

/**
 * End the sound
 */
void MusicNote::PlayEnd()
{
    mSound->PlayEnd();
    mBeatAtPlay = 0;
}

/**
 * Increment stop time
 * @param elapsed time from last update
 */
void MusicNote::IncrementStoppedTime(double elapsed)
{
    if(mStopAtKey)
    {
        mStoppedTime += elapsed;
        if(mStoppedTime >= 2)
        {
            mReadyForDeletion = true;
        }
    }
}

/**
 * @return if the note is ready for delete
 */
bool MusicNote::IsReadyForDeletion() const {
    return mReadyForDeletion;
}

