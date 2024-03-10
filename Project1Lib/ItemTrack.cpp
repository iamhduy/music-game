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

void ItemTrack::UpdateNotes(double elapsed, double timeOnTrack)
{
    double locationThreshold = 10;
    double initOffset = 20;
    double beatSize = mBeatSize;
    double beatsPerMeasure;

    for (auto note : mNotes)
    {
        beatsPerMeasure = note->GetBpMeasure();
        double currBeat = note->GetGame()->GetAbsoluteBeat();
        double noteBeat = (note->GetMeasure() - 1) * beatsPerMeasure + (note->GetBeat() - 1);

        if (note->GetFirstUpdate() == false)
        {
            note->SetX(mX1);
            note->SetY(mY1 - initOffset);
        }

        if (((currBeat + beatSize) >= noteBeat) && (note->GetStopAtKey() == false))
        {
            //set initial location at top of track
            if (note->GetFirstUpdate() == false)
            {
                note->SetX(mX1);
                note->SetY(mY1);
                note->SetFirstUpdate(true);
            }
            else if(abs(note->GetY() - mY2) <= locationThreshold) //within threshold of final location
            {
                note->SetStopAtKey(true);
                note->SetX(mX1);
                note->SetY(mY1-initOffset);
            }
            else //set new location if already linked to track
            {
                double newPosX = note->GetX() + ((mX2 - mX1)/timeOnTrack)*elapsed;
                double newPosY = note->GetY() + ((mY2 - mY1)/timeOnTrack)*elapsed;

                note->SetX(newPosX);
                note->SetY(newPosY);
            }

            double beatsCompleted = beatSize - (noteBeat-currBeat);

            double percent = mInitPercentOfSize + (1-mInitPercentOfSize)*(beatsCompleted/beatSize);
            note->SetPercentOfFullSize(percent);
        }
    }
}