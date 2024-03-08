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
#include <memory>

/// Image Directory
const std::wstring ImagesDir = L"./images";

///Seconds in a minute
double SecondsPerMinute = 60;

using namespace std;

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
    // INSERT YOUR DRAWING CODE HERE
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


    //draw every note at (0,0) - should be changed
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

    graphics->PopState();
}

/**
 * Load the game from XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the game from.
 */
void Game::Load(const wxString &filename)
{
    wxXmlDocument xmlDoc;
    if(!xmlDoc.Load(filename))
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
//    int cnt = visitor.GetNumBuildings();
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
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Game::Update(double elapsed)
{
    mAbsoluteBeat += elapsed * mMusic.GetBpMinute() / SecondsPerMinute;

    double beatsPerSecond = mMusic.GetBpMinute() / SecondsPerMinute;
    double beatSize = 4; //hardcoded
    double timeOnTrack = beatSize / beatsPerSecond;
    for (auto item : mItems)
    {
        item->Update(elapsed, timeOnTrack);
    }
}

/**
 * Check if the key hit the notes
 * @param x location x
 * @param y location y
 * @return pointer of the item hit.
 */
std::shared_ptr<Item> Game::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); i++)
    {
        if ((*i)->HitTest(x,y))
        {
            return *i;
        }
    }
    return nullptr;
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
