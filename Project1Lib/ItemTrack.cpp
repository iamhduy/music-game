/**
 * @file ItemTrack.cpp
 * @author hduy
 */
#include "pch.h"
#include "ItemTrack.h"
#include "ItemSoundBoard.h"
#include "Game.h"

using namespace std;

/// Image Directory
const std::wstring ImagesDir = L"./images/";

/// How close puck can be to key to stop (in pixels)
double LocationThreshold = 8.0;

/// Initial puck offset (in pixels)
double InitOffset = 20;

/// Max duration for short duration puck
double MaxDuration = 0.5;

/// Use for percent of full size
double NoSize = 0;

/// Score we get when we successfully hit a note
const int GoodSoundScore = 10;

/// The maximum bonus we can get for
/// holding for the duration for a long sound
const int MaxDurationBonus = 10;

/**
 * Constructor
 * @param soundBoard The soundboard holding this item
 *
 */
ItemTrack::ItemTrack(ItemSoundBoard *soundBoard)
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
    std::unique_ptr<wxImage> itemImage = std::make_unique<wxImage>(GetKeyImageFile(), wxBITMAP_TYPE_ANY);
    auto itemBitmap = std::make_unique<wxBitmap>(*itemImage);

    graphics->DrawBitmap(*itemBitmap,
                         int(x - mSizeX / 2),
                         int(y - mSizeY / 2),
                         mSizeX,
                         mSizeY);
}

/**
 * Update the notes play on this track
 * @param elapsed time from last update
 * @param beatsPerSecond bps
 */
void ItemTrack::UpdateNotes(double elapsed, double beatsPerSecond)
{
    double beatSize = mBeatSize;
    double timeOnTrack = beatSize / beatsPerSecond;
    double beatsPerMeasure;
    for(auto note : mNotes)
    {
        beatsPerMeasure = note->GetBpMeasure();
        double currBeat = note->GetGame()->GetAbsoluteBeat();
        double noteBeat = (note->GetMeasure() - 1) * beatsPerMeasure + (note->GetBeat() - 1); //when is the note dropped

        if (!note->IsDangerNote()) // auto play state will avoid playing danger notes
        {
            if(note->GetStopAtKey() && note->GetGame()->IsAutoPlay() && !note->IsSoundPlayed())
            {
                note->PlaySound(currBeat); //pass the currBeat in to save time when sound is played
            }
            else if(note->GetBeatAtPlay() != 0 && note->IsSoundPlayed())
            {
                if(currBeat - note->GetDuration() >= note->GetBeatAtPlay())
                {
                    note->PlayEnd();
                }
            }
        }

        if(!note->GetFirstUpdate())
        {
            note->SetX(mX1);
            note->SetY(mY1 - InitOffset);
            note->SetLongDurationX2(mX1);
            note->SetLongDurationY2(mY1);
            note->SetLongDurationX1(mX1);
            note->SetLongDurationY1(mY1);
        }

        if((currBeat > noteBeat) && !note->GetStopAtKey())
        {
            double beatsCompleted = currBeat - noteBeat;
            double percent = mInitPercentOfSize + (1 - mInitPercentOfSize) * (beatsCompleted / beatSize);
            note->SetPercentOfFullSize(percent);

            //set initial location at top of track
            if(!note->GetFirstUpdate())
            {
                note->SetX(mX1);
                note->SetY(mY1);
                note->SetFirstUpdate(true);
            }
            else if(note->GetY() > (mY2 - LocationThreshold)) //within threshold of final location
            {
                note->SetStopAtKey(true);
                note->SetContinueDurationLine(true);
                note->SetX(0);
                note->SetY(0);
                note->SetPercentOfFullSize(NoSize);

                if (note->GetGame()->IsAutoPlay())
                {
                    note->GetGame()->AddScore(GoodSoundScore);
                    note->GetGame()->AddNoteHit();
                    note->GetGame()->UpdateMeter();
                }
            }
            else //set new location if already linked to track
            {
                double newPosX = note->GetX() + ((mX2 - mX1) / timeOnTrack) * elapsed;
                double newPosY = note->GetY() + ((mY2 - mY1) / timeOnTrack) * elapsed;

                note->SetX(newPosX);
                note->SetY(newPosY);
            }

            //Draw long duration line
            if((note->GetDuration() > MaxDuration) && !note->GetContinueDurationLine())
            {
                double longDurationLengthY = (note->GetDuration() / beatSize) * (mY2 - mY1);
                double longDurationLengthX = (note->GetDuration() / beatSize) * (mX2 - mX1);
                note->SetLongDurationX1(note->GetX());
                note->SetLongDurationY1(note->GetY());
                if((note->GetY() - longDurationLengthY) > mY1)
                {
                    note->SetLongDurationX2(note->GetX() - longDurationLengthX);
                    note->SetLongDurationY2(note->GetY() - longDurationLengthY);
                }
                else
                {
                    note->SetLongDurationX2(mX1);
                    note->SetLongDurationY2(mY1);
                }
            }
            else if (note->GetDuration() <= MaxDuration) //don't draw line if duration for note if duration is under 0.5
            {
                note->SetLongDurationX2(mX1);
                note->SetLongDurationY2(mY1);
                note->SetLongDurationX1(mX1);
                note->SetLongDurationY1(mY1);
            }
        }
        else if(note->GetContinueDurationLine()
            && (note->GetDuration() > MaxDuration)) //continue drawing long duration line after puck stops
        {
            if(note->GetLongDurationY2() > mY2)
            {
                note->SetLongDurationX2(mX1);
                note->SetLongDurationY2(mY1);
                note->SetLongDurationX1(mX1);
                note->SetLongDurationY1(mY1);

                note->SetContinueDurationLine(false);
                if (note->GetGame()->IsAutoPlay())
                {
                    note->GetGame()->AddScore(MaxDurationBonus);
                }
            }
            else //stop drawing line once top of line gets to key
            {
                double newLongDurationX = note->GetLongDurationX2() + ((mX2 - mX1) / timeOnTrack) * elapsed;
                double newLongDurationY = note->GetLongDurationY2() + ((mY2 - mY1) / timeOnTrack) * elapsed;

                note->SetLongDurationX2(newLongDurationX);
                note->SetLongDurationY2(newLongDurationY);
                note->SetLongDurationX1(mX2);
                note->SetLongDurationY1(mY2);
            }

        }
    }
    int DeletedNotes = 0;
    for (auto it = mNotes.begin(); it != mNotes.end();)
    {
        auto& note = *it;
        if (note->GetStopAtKey())
        {
            note->IncrementStoppedTime(elapsed);

            if (note->IsReadyForDeletion())
            {
                DeletedNotes ++;
                it = mNotes.erase(it);
                continue;
            }
        }
        ++it;
    }
    if (DeletedNotes > mNotesPassed)
    {
        mNotesPassed = DeletedNotes;
    }
}
