/**
 * @file DeclarationMeter.cpp
 * @author hduy
 */
#include "pch.h"
#include "DeclarationMeter.h"
#include "Game.h"
#include <string>

using namespace std;
/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
DeclarationMeter::DeclarationMeter(Game *game) : Declaration(game)
{
}

/**
 * Load the attributes for an declaration node.
 * @param node The Xml node we are loading the declaration from
 */
void DeclarationMeter::XmlLoad(wxXmlNode *node)
{
    mCoverFile = node->GetAttribute(L"cover", "");
    mNeedleFile = node->GetAttribute(L"needle", "");

    Declaration::XmlLoad(node);
}
void DeclarationMeter::Draw(wxDC *dc, double x, double y)
{
    Declaration::Draw(dc, x, y);

    wstring coverFile = this->GetGame()->GetImagesDirectory() + L"\\" + mCoverFile;

    std::unique_ptr<wxImage> coverImage = make_unique<wxImage>(coverFile, wxBITMAP_TYPE_ANY);
    std::unique_ptr<wxBitmap> coverBitmap = make_unique<wxBitmap>(*coverImage);
    dc->DrawBitmap(*coverBitmap, int(x - this->GetSizeX()/2), int(y -  this->GetSizeY()/2));

    wstring needleFile = this->GetGame()->GetImagesDirectory() + L"\\" + mNeedleFile;
    std::unique_ptr<wxImage> needleImage = make_unique<wxImage>(needleFile, wxBITMAP_TYPE_ANY);
    std::unique_ptr<wxBitmap> needleBitmap = make_unique<wxBitmap>(*needleImage);

    dc->DrawBitmap(*needleBitmap, int(x - this->GetSizeX()/2), int(y -  this->GetSizeY()/2));
}
