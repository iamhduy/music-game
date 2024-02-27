/**
 * @file Game.cpp
 * @author Milo Baran
 */
#include "pch.h"
#include "Game.h"
#include "Image.h"
#include "SoundBoard.h"
#include "ScoreBoard.h"
#include "ItemMeter.h"

using namespace std;

Game::Game(ma_engine *PEngine) : mAudioEngine(PEngine)
{
    //mBackground = make_unique<wxBitmap>(L"img/background1.png", wxBITMAP_TYPE_ANY);
}

/**
 * Clear the aquarium data.
 *
 * Deletes all known items in the aquarium.
 */
void Game::Clear()
{
    mItems.clear();
}

/**
 * draw background
 * @param dc device context
 */
void Game::OnDraw(wxDC *dc)
{
    //dc->DrawBitmap(*mBackground, 0, 0);

//    for (auto const item : mItems)
//    {
//        item->Draw(dc);
//    }
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
        if(name == L"item")
        {
            XmlItem(child);
        }
    }
}
void Game::XmlItem(wxXmlNode *node)
{
    shared_ptr<Item> item;

    // We have an item. What type?
    auto name = node->GetName();

    if (name == L"image")
    {
        item = make_shared<Image>(this);
    }
    else if (name == L"sound-board")
    {
        item = make_shared<SoundBoard>(this);
    }
    else if (name == L"score-board")
    {
        item = make_shared<ScoreBoard>(this);
    }
    else if (name == L"meter")
    {
        item = make_shared<ItemMeter>(this);
    }

    if (item != nullptr)
    {
        item->XmlLoad(node);
        Add(item);
    }
}

/**
 * Add an item to the aquarium
 * @param item New item to add
 */
void Game::Add(std::shared_ptr<Item> item)
{
    // Change the location later
    item->SetLocation(250, 250);
    mItems.push_back(item);
}
