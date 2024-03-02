/**
 * @file DeclarationSoundBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "DeclarationSoundBoard.h"
#include "Game.h"
#include <string>

using namespace std;

/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
DeclarationSoundBoard::DeclarationSoundBoard(Game *game) : Declaration(game)
{
}

/**
 * Load the attributes for an declaration node.
 * @param node The Xml node we are loading the declaration from
 */
void DeclarationSoundBoard::XmlLoad(wxXmlNode *node)
{
    mCoverFile = node->GetAttribute(L"cover", "");
    node->GetAttribute(L"top-width").ToInt(&mTopWidth);
    node->GetAttribute(L"size-beats").ToInt(&mSizeBeats);

    Declaration::XmlLoad(node);
}
void DeclarationSoundBoard::Draw(wxDC *dc, double x, double y)
{
    Declaration::Draw(dc, x, y);

    wstring coverFile = this->GetGame()->GetImagesDirectory() + L"\\" + mCoverFile;

    std::unique_ptr<wxImage> coverImage = make_unique<wxImage>(coverFile, wxBITMAP_TYPE_ANY);
    std::unique_ptr<wxBitmap> coverBitmap = make_unique<wxBitmap>(*coverImage);
    dc->DrawBitmap(*coverBitmap, int(x - this->GetSizeX()/2), int(y -  this->GetSizeY()/2));
}



