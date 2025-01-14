/**
 * @file ItemSoundBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "ItemSoundBoard.h"
#include "ItemTrack.h"
#include "MusicNote.h"
#include <memory>
#include "Game.h"

using namespace std;

/// Width of the track line. The line is
/// drawn a wxBLACK.
const int TrackLineWidth = 5;

/// The maximum number of tracks
const int MaxTracks = 10;

/// The minimum number of tracks
const int MinTracks = 8;

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

/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
ItemSoundBoard::ItemSoundBoard(Game* game) : Item(game)
{
}

/**
 * AddItem an itemTrack to the soundboard
 * @param itemTrack New itemTrack to add
 */
void ItemSoundBoard::Add(std::shared_ptr<ItemTrack> itemTrack)
{
    mTracks.push_back(itemTrack);
}

/**
 * Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void ItemSoundBoard::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

    auto child = node->GetChildren();
    for( ; child; child=child->GetNext())
    {
        shared_ptr<ItemTrack> itemTrack = make_shared<ItemTrack>(this);
        itemTrack->XmlLoad(child);
        Add(itemTrack);
    }
}

/**
 * Set the track values
 * @param declaration the declaration of this soundboard
 * @param y1Track y1 pos of the track
 * @param y2Track y2 pos of the track
 * @param x1Space space between track
 * @param x2Space space between track
 * @param x1InitLeftTrack
 * @param x2InitLeftTrack
 * @param x1InitRightTrack
 * @param x2InitRightTrack
 */
void ItemSoundBoard::GetTrackValues(std::shared_ptr<Declaration> declaration, double& y1Track, double& y2Track,
                                    double& x1Space, double& x2Space, double& x1InitLeftTrack, double& x2InitLeftTrack,
                                    double& x1InitRightTrack, double& x2InitRightTrack)
{
    double xSoundBoardSize = declaration->GetSizeX();
    double ySoundBoardSize = declaration->GetSizeY();
    double soundBoardTW = declaration->GetTopWidth();

    //find length of sound board at KeyRow and TopClearance
    double soundBoardLengthAtX1Init = ((xSoundBoardSize-soundBoardTW)/ySoundBoardSize)*(ySoundBoardSize*TopClearance) + soundBoardTW;
    double soundBoardLengthAtX2Init = ((xSoundBoardSize-soundBoardTW)/ySoundBoardSize)*(ySoundBoardSize*KeyRow) + soundBoardTW;

    //x1 and x2 for leftmost and rightmost track
    x1InitLeftTrack = (GetX()-(soundBoardLengthAtX1Init/2)) + (soundBoardLengthAtX1Init*Border);
    x2InitLeftTrack = (GetX()-(soundBoardLengthAtX2Init/2)) + (soundBoardLengthAtX2Init*Border);

    x1InitRightTrack = (GetX()+(soundBoardLengthAtX1Init/2)) - (soundBoardLengthAtX1Init*Border);
    x2InitRightTrack = (GetX()+(soundBoardLengthAtX2Init/2)) - (soundBoardLengthAtX2Init*Border);

    //y1 and y2 for all tracks
    double overlapCorrection = 7; //track is too long otherwise
    y1Track = (GetY() - (ySoundBoardSize/2)) + (ySoundBoardSize*TopClearance) + overlapCorrection;
    y2Track = (GetY() - (ySoundBoardSize/2)) + (ySoundBoardSize*KeyRow);

    //space between each track
    x1Space = (x1InitRightTrack - x1InitLeftTrack)/(MaxTracks - 1);
    x2Space = (x2InitRightTrack - x2InitLeftTrack)/(MaxTracks - 1);

    //set y1 and y2 for all tracks (start and end of for y position)
    for (auto track : mTracks)
    {
        track->SetY1(y1Track);
        track->SetY2(y2Track);
        track->SetBeatSize(declaration->GetBeatSize());
        track->SetInitPercentOfSize(soundBoardLengthAtX1Init/soundBoardLengthAtX2Init);
    }
}

/**
 * Draw extra parts of SoundBoard (tracks)
 * @param graphics Device context to draw on
 * @param declaration Declaration object associated with
 */
void ItemSoundBoard::Draw(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration)
{
    double y1Track, y2Track, x1Space, x2Space, x1InitLeftTrack, x2InitLeftTrack, x1InitRightTrack, x2InitRightTrack;
    GetTrackValues(declaration, y1Track, y2Track, x1Space, x2Space, x1InitLeftTrack, x2InitLeftTrack,
                   x1InitRightTrack, x2InitRightTrack);

    //draw tracks
    wxPen linePen(*wxBLACK, TrackLineWidth);
    graphics->SetPen(linePen);

    int tracksCount = mTracks.size();

    double shiftX1 = 0;
    double shiftX2 = 0;
    for (int i = 0; i < MaxTracks; ++i)
    {
        if((i == 4 && tracksCount == MinTracks) || (i == 5 && tracksCount == MinTracks)){
            shiftX1 += x1Space;
            shiftX2 += x2Space;
            continue;
        }


        graphics->StrokeLine(x1InitLeftTrack + shiftX1, y1Track, x2InitLeftTrack + shiftX2, y2Track);

        if (tracksCount == MinTracks && i > 5)
        {
            //set x1 and x2 for tracks (start and end of for x position)
            mTracks[i-2]->SetX1(x1InitLeftTrack + shiftX1);
            mTracks[i-2]->SetX2(x2InitLeftTrack + shiftX2);
        }
        else
        {
            //set x1 and x2 for tracks (start and end of for x position)
            mTracks[i]->SetX1(x1InitLeftTrack + shiftX1);
            mTracks[i]->SetX2(x2InitLeftTrack + shiftX2);
        }

        shiftX1 += x1Space;
        shiftX2 += x2Space;
    }
}

/**
 * Draw keys on top
 * @param graphics Device context to draw on
 * @param declaration Declaration object associated with
 */
void ItemSoundBoard::DrawOnTop(std::shared_ptr<wxGraphicsContext> graphics, std::shared_ptr<Declaration> declaration)
{
    double y1Track, y2Track, x1Space, x2Space, x1InitLeftTrack, x2InitLeftTrack, x1InitRightTrack, x2InitRightTrack;
    GetTrackValues(declaration, y1Track, y2Track, x1Space, x2Space, x1InitLeftTrack, x2InitLeftTrack,
                   x1InitRightTrack, x2InitRightTrack);

    if (GetGame()->GetCurrentLevel() == 2)
    {
       keyCodes = {'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ';'};
    }
    else
    {
        keyCodes = {'A', 'S', 'D', 'F', 'J', 'K', 'L', ';'};

    }

    int tracksCount = mTracks.size();

    double shiftX1 = 0;
    double shiftX2 = 0;

    double totalWidth = x2InitRightTrack - x2InitLeftTrack;
    double keySpacing = totalWidth / (MaxTracks-1);
    for (int i = 0; i < MaxTracks; ++i)
    {
        if((i == 4 && tracksCount == MinTracks) || (i == 5 && tracksCount == MinTracks)){
            shiftX1 += x1Space;
            shiftX2 += x2Space;
            continue;
        }
        if (tracksCount == MinTracks && i > 5)
        {
            mTracks[i-2]->Draw(graphics, x2InitLeftTrack + shiftX2, y2Track);
            if (GetGame()->GetCurrentLevel() != 2)
            {
                keyPositions[keyCodes[i - 2]] = std::make_pair(x2InitLeftTrack + shiftX2, y2Track);
            }
        }
        else
        {
            mTracks[i]->Draw(graphics, x2InitLeftTrack + shiftX2, y2Track);
            if (GetGame()->GetCurrentLevel() != 2)
            {
                keyPositions[keyCodes[i]] = std::make_pair(x2InitLeftTrack + shiftX2, y2Track);
            }
        }

        double keyXPos = x2InitLeftTrack + (keySpacing * i);

        if (GetGame()->GetCurrentLevel() == 2)
        {
            keyPositions[keyCodes[i]] = std::make_pair(keyXPos, y2Track);
        }

        shiftX1 += x1Space;
        shiftX2 += x2Space;
    }
}

/**
 * Add note to tracks
 * @param note to add
 */
void ItemSoundBoard::AddNote(std::shared_ptr<MusicNote> note)
{
    //add note to its track
    for (auto track : mTracks)
    {
        //cout << track->GetTrackNum() << endl;
        if (track->GetTrackNum() == note->GetTrackNum())
        {
            char trackKey = track->GetKey();
            note->SetAssociatedKey(trackKey);
            track->AddNote(note);
        }
    }
}

/**
 * Update the soundboard during the game
 * @param elapsed time from last update
 * @param timeOnTrack how long the notes played
 */
void ItemSoundBoard::Update(double elapsed, double timeOnTrack)
{
    //update each note in all tracks
    for (auto track : mTracks)
    {
        track->UpdateNotes(elapsed, timeOnTrack);
    }
}

/**
 * @param keycode key code
 * @return the key X pos
 */
int ItemSoundBoard::GetKeyXPosition(wxChar keycode){
    auto it = keyPositions.find(keycode);
    if (it != keyPositions.end()) {
        return keyPositions[keycode].first;
    }
    return 0;
}

/**
 * @param keycode key code
 * @return the key Y pos
 */
int ItemSoundBoard::GetKeyYPosition(wxChar keycode)
{
    auto it = keyPositions.find(keycode);
    if(it != keyPositions.end())
    {
        return keyPositions[keycode].second;
    }
    return 0;
}

/**
 * @return total note passed
 */
int ItemSoundBoard::GetTotalNotesPassed() const
{
    int totalPassed = 0;
    for(const auto& track : mTracks) {
        totalPassed += track->GetNotesPassed();
    }
    return totalPassed;
}