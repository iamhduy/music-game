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

/// Image Directory
const std::wstring ImagesDir = L"\\images";

using namespace std;

/**
 * Game Constructor
 * @param PEngine audio engine
 */
Game::Game(ma_engine *PEngine) : mAudioEngine(PEngine)
{
    //mBackground = make_unique<wxBitmap>(L"images/background1", wxBITMAP_TYPE_ANY);
}

/**
 * Set the directory the images are stored in
 * @param dir
 */
void Game::SetImagesDirectory(const std::wstring &dir) {
    mImagesDirectory = dir + ImagesDir;
}

/**
 * Clear the aquarium data.
 *
 * Deletes all known items in the aquarium.
 */
void Game::Clear()
{
    mItems.clear();
    mScore = 0;
}

/**
 * draw background
 * @param dc device context
 */
void Game::OnDraw(std::shared_ptr<wxGraphicsContext> graphics, int width, int height)
{
//    for (auto const declaration : mDeclarations)
//    {
//        for (auto const item : mItems)
//        {
//            if (declaration->GetId() == item->GetId())
//            {
//                declaration->Draw(dc, item->GetX(), item->GetY());
//                break;
//            }
//        }
//    }

    // Determine the size of the playing area in pixels
    // This is up to you...

    int pixelWidth = 1034; //< Temporary placement to get everything else working.
    int pixelHeight = 900;

    //
    // Automatic Scaling
    //
    auto scaleX = double(width) / double(pixelWidth);
    auto scaleY = double(height) / double(pixelHeight);
    mScale = std::min(scaleX, scaleY);

    mXOffset = (width - pixelWidth * mScale) / 2.0;
    mYOffset = 0;
    if (height > pixelHeight * mScale)
    {
        mYOffset = (double)((height - pixelHeight * mScale) / 2.0);
    }

    graphics->PushState();

    graphics->Translate(mXOffset, mYOffset);
    graphics->Scale(mScale, mScale);

    //
    // Draw in virtual pixels on the graphics context
    //
    // INSERT YOUR DRAWING CODE HERE
    //
    // Drawing a rectangle that is the playing area size
    //
//    wxBrush background(*wxRED);
//
//    graphics->SetBrush(background);
//    graphics->DrawRectangle(0, 0, pixelWidth, pixelHeight);


    graphics->PopState();
}

/**
 * Load the aquarium from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the aquarium from.
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
    }
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
        auto trackNode = node->GetChildren();
        for( ; trackNode; trackNode=trackNode->GetNext())
        {
            shared_ptr<Item> itemTrack = make_shared<ItemTrack>(this);
            itemTrack->XmlLoad(trackNode);
            AddItem(itemTrack);
        }

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
 * AddItem an item to the game
 * @param item New item to add
 */
void Game::AddItem(std::shared_ptr<Item> item)
{
    // Change the location later
    item->SetLocation(250, 250);
    mItems.push_back(item);
}

/**
 * AddDeclaration an declaration to the game
 * @param declaration New declaration to add
 */
void Game::AddDeclaration(std::shared_ptr<Declaration> declaration)
{
    // Change the location later
    mDeclarations.push_back(declaration);
}

void Game::AddScore(int value)
{
    mScore += value;
}