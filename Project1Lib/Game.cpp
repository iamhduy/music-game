/**
 * @file Game.cpp
 * @author Milo Baran
 */
#include "pch.h"
#include "Game.h"
#include "ItemImage.h"
#include "ItemSoundBoard.h"
#include "ItemScoreBoard.h"
#include "ItemMeter.h"
#include "DeclarationImage.h"
#include "DeclarationSoundBoard.h"
#include "DeclarationScoreBoard.h"
#include "DeclarationMeter.h"
#include "DeclarationNote.h"
#include "ItemVisitor.h"
#include "Music.h"
#include "SoundboardAddNote.h"
#include "TotalNotesVisitor.h"
#include <memory>

using namespace std;
/// Image Directory
const wstring ImagesDir = L"./images";
/// level dir
const wxString levelDir = L"levels/";

///Seconds in a minute
const double SecondsPerMinute = 60;

/// Level file names
const vector<wxString> LevelFileNames {L"level0.xml", L"level1.xml", L"level2.xml", L"level3.xml"};

/**
 * Game Constructor
 * @param PEngine audio engine
 */
Game::Game(ma_engine *PEngine) : mAudioEngine(PEngine)
{
    //mBackground = wxBitmap(L"images/background1.png", wxBITMAP_TYPE_ANY);
}

/**
 * Clear the aquarium data.
 *
 * Deletes all known items in the aquarium.
 */
void Game::Clear()
{
    mItems.clear();
    mDeclarations.clear();
    mScore = 0;
}

/**
 * draw background
 * @param graphics device context
 * @param width X-size of the window view
 * @param height Y-size of the window view
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(mPixelWidth);
    auto scaleY = double(height) / double(mPixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - mPixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > mPixelHeight * mScale)
    {
        mYOffset = (double)((height - mPixelHeight * mScale) / 2.0);
    }

    mYOffset = mYOffset + (15*mScale); //< Offset in the Y direction to account for NAV bar.

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    //
    // Draw in virtual pixels on the graphics context
    //
    for (auto const declaration : mDeclarations)
    {
        for (auto const item : mItems)
        {
            if (declaration->GetId() == item->GetId())
            {
                declaration->Draw(graphics, item->GetX(), item->GetY());
                item->Draw(graphics, declaration);
                break;
            }
        }
    }

    //draw every note
    for (auto const note : mMusicNotes)
    {
        for (auto const declaration : mDeclarations)
        {
            if (declaration->GetId() == note->GetId())
            {
                note->Draw(graphics, declaration);
                break;
            }
        }
    }

    //Draw images that should be on top
    for (auto const declaration : mDeclarations)
    {
        for (auto const item : mItems)
        {
            if (declaration->GetId() == item->GetId())
            {
                declaration->DrawOnTop(graphics, item->GetX(), item->GetY());
                item->DrawOnTop(graphics, declaration);
            }
        }
    }
}

/**
 * Load the game from XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game from.
 */
void Game::Load(int levelNumber)
{
    mLevelNumber = levelNumber;
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(levelDir + LevelFileNames[levelNumber]))
    {
        wxMessageBox(L"Unable to load Xml file");
        return;
    }

    Clear();
    // Get the XML document root node
    auto root = xmlDoc.GetRoot();
    wxString size = root->GetAttribute(L"size", L"0,0").ToStdWstring();
    size.BeforeFirst(',').ToInt(&mPixelWidth);
    size.AfterFirst(',').ToInt(&mPixelHeight);

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for( ; child; child=child->GetNext())
    {
        auto name = child->GetName();
        if(name == L"items")
        {
            auto childItem = child->GetChildren();
            for( ; childItem; childItem=childItem->GetNext())
            {
                XmlItem(childItem);
            }
        }
        else if (name == L"declarations")
        {
            auto childDeclaration = child->GetChildren();
            for( ; childDeclaration; childDeclaration=childDeclaration->GetNext())
            {
                XmlDeclaration(childDeclaration);
            }
        }
        else if (name == L"audio")
        {
            auto childAudio = child->GetChildren();
            for( ; childAudio; childAudio=childAudio->GetNext())
            {
                shared_ptr<Sound> sound = make_shared<Sound>(this);
                if (sound != nullptr)
                {
                    sound->XmlLoad(childAudio);
                    AddAudio(sound);
                }
            }
        }
        else if (name == L"music")
        {
            mMusic.XmlLoad(child);
            auto childMusic = child->GetChildren();
            for( ; childMusic; childMusic=childMusic->GetNext())
            {
                shared_ptr<MusicNote> musicNote = make_shared<MusicNote>(this);
                if (musicNote != nullptr)
                {
                    musicNote->XmlLoad(childMusic);
                    musicNote->SetBpMeasure(mMusic.GetBpMeasure());
                    AddMusicNote(musicNote);
                }
            }
        }
    }

    //this will add notes to the track it is associated with
    for (auto note: mMusicNotes)
    {
        SoundboardAddNote visitor(note);
        Accept(&visitor);
    }

//    for (auto note : mMusicNotes)
//    {
//        for (auto sound : mAudio)
//        {
//            if (sound->GetSoundName() == note->GetSoundName())
//            {
//                note->SetSound(sound);
//                break;
//            }
//        }
//    }
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Game::XmlItem(wxXmlNode *node)
{
    shared_ptr<Item> item;

    // We have an item. What type?
    auto name = node->GetName();

    if (name == L"image")
    {
        item = make_shared<ItemImage>(this);
    }
    else if (name == L"sound-board")
    {
        item = make_shared<ItemSoundBoard>(this);
    }
    else if (name == L"score-board")
    {
        item = make_shared<ItemScoreBoard>(this);
    }
    else if (name == L"meter")
    {
        item = make_shared<ItemMeter>(this);
    }

    if (item != nullptr)
    {
        item->XmlLoad(node);
        AddItem(item);
    }
}

/**
 * Handle a node of type declaration.
 * @param node XML node
 */
void Game::XmlDeclaration(wxXmlNode* node)
{
    shared_ptr<Declaration> declaration;

    // We have an item. What type?
    auto name = node->GetName();

    if (name == L"image")
    {
        declaration = make_shared<DeclarationImage>(this);
    }
    else if (name == L"sound-board")
    {
        declaration = make_shared<DeclarationSoundBoard>(this);
    }
    else if (name == L"score-board")
    {
        declaration = make_shared<DeclarationScoreBoard>(this);
    }
    else if (name == L"meter")
    {
        declaration = make_shared<DeclarationMeter>(this);
    }
    else if (name == L"note")
    {
        declaration = make_shared<DeclarationNote>(this);
    }

    if (declaration != nullptr)
    {
        declaration->XmlLoad(node);
        AddDeclaration(declaration);
    }
}

/**
 * Add an item to the game
 * @param item New item to add
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}


/**
 * Add an declaration to the game
 * @param declaration New declaration to add
 */
void Game::AddDeclaration(std::shared_ptr<Declaration> declaration)
{
    mDeclarations.push_back(declaration);
}

/**
 * Add an sound to the game
 * @param sound New sound to add
 */
void Game::AddAudio(std::shared_ptr<Sound> sound)
{
    mAudio.push_back(sound);
}

/**
 * Add an music to the game
 * @param music New music to add
 */
void Game::AddMusicNote(std::shared_ptr<MusicNote> musicNote)
{
    mMusicNotes.push_back(musicNote);
}

/**
* Update player's score
* @param value score to increment
*/
void Game::AddScore(int value)
{
    mScore += value;
}

/**
* Update player's score
* @param value score to increment
*/
void Game::SubtractScore(int value)
{
    mScore -= value;
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    if (mState == GameState::Ready)
    {
        mAbsoluteBeat = 0;
    }

    mTimePlaying += elapsed;

    if (mTimePlaying >= 2.0 && mState != GameState::Completed)
    {
        mAbsoluteBeat += elapsed * mMusic.GetBpMinute() / SecondsPerMinute;
    }

    UpdateState();

    if (mAbsoluteBeat >= 4 && mState == GameState::Playing && !mIsMusicPlayed)
    {
        mAudio[0]->LoadSound(mAudioEngine);
        mAudio[0]->PlaySound();
        mIsMusicPlayed = !mIsMusicPlayed;
    }
    else if (mState == GameState::Completed && mTimePlaying != 0)
    {
        mAudio[0]->PlayEnd();
        mTimePlaying = 0;
    }

    double beatsPerSecond = mMusic.GetBpMinute() / SecondsPerMinute;
    for (auto item : mItems)
    {
        item->Update(elapsed, beatsPerSecond);
    }
}

void Game::UpdateState()
{
    if(mAbsoluteBeat >= (mMusic.GetMeasures()+2) * mMusic.GetBpMeasure() && mState == GameState::Playing)
    {
        mState = GameState::Completed;
    }
    else if(wxRound(4 - mAbsoluteBeat) <= 0 && mState == GameState::Countdown)
    {
        mState = GameState::Playing;
    }
    else if(mTimePlaying >= 2.0 & mState == GameState::Ready)
    {
        mState = GameState::Countdown;
    }
}

/**
 * Check if the key hit the notes
 * @param x location x
 * @param y location y
 * @return pointer of the item hit.
 */
bool Game::HitTest(wxChar keyCode, int keyX, int keyY, long duration)
{
    CalculateAccuracy();
    int tot_score = 0;
    double currentBeat = 0;
    for (auto& note : mMusicNotes){
        if (note->CheckIfHit(currentBeat, keyX, keyY) ){//&& !note->IsReadyForDeletion()){
            mActiveNotes.push_back(note);
            if (note == nullptr){
                SubtractScore(10);
                return true;
            }
            else if(note->GetId().ToStdString().find("tp") != std::string::npos)
            {
                SubtractScore(20);

                std::shared_ptr<Sound> sound = note->GetSound();
                sound->LoadSound(mAudioEngine);
                sound->PlaySound();

                return true;
            }
            else
            {
                AddScore(10);
                mNotesHit += 1;

                std::shared_ptr<Sound> sound = note->GetSound();
                sound->LoadSound(mAudioEngine);
                sound->PlaySound();
                return true;
            }
        }
    }
    return false;
}

/**
 * Accept a visitor for the collection
 * @param visitor The visitor for the collection
 */
void Game::Accept(ItemVisitor* visitor)
{
    for (auto item : mItems)
    {
        item->Accept(visitor);
    }
}

int Game::GetAbsBeat()
{
    return mAbsoluteBeat;
}

void Game::DurationScoreBonus(int duration)
{
    shared_ptr note = mActiveNotes.front();
    mActiveNotes.erase(mActiveNotes.begin());
    int noteDuration = note->GetDuration();
    if (noteDuration >= duration)
    {
        int tot_score = (duration / noteDuration) * 10;
        AddScore(tot_score);
    }
}

shared_ptr<Sound> Game::FindSoundByName(const wxString& audioName)
{
    for (auto sound : mAudio)
    {
        if (sound->GetSoundName() == audioName)
        {
            return sound;
        }
    }
    return nullptr;
}


int Game::CalculateAccuracy()
{
    int totalNotesPassed = 0;
    TotalNotesVisitor visitor;
    this->Accept(&visitor);
    totalNotesPassed = visitor.GetTotalNotesPassed();
//    cout << "Accuracy" << endl;
//    cout << totalNotesPassed << endl;
//    cout << mNotesHit << endl;

    if(totalNotesPassed == 0)
    {
        return 0;
    }

    return mNotesHit / totalNotesPassed;
}
void Game::StopSound(char key)
{
    for (auto note : mActiveNotes)
    {
        if(note->GetAssociatedKey() == key)
        {
            note->GetSound()->PlayEnd();
            break;
        }
    }
}
