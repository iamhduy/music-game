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

/**
 * Draw this item
 * @param dc Device context to draw on
 * @param x location x
 * @param y location y
 */
void DeclarationMeter::Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y)
{
    Declaration::Draw(graphics, x, y);

    wstring coverFile = this->GetGame()->GetImagesDirectory() + L"\\" + mCoverFile;
    std::unique_ptr<wxImage> coverImage = make_unique<wxImage>(coverFile, wxBITMAP_TYPE_ANY);
    wxGraphicsBitmap coverBitmap = graphics->CreateBitmapFromImage(*coverImage);

    int coverWid = coverImage->GetWidth();
    int coverHit = coverImage->GetHeight();

    graphics->DrawBitmap(coverBitmap, int(x - this->GetSizeX()/2), int(y -  this->GetSizeY()/2), coverWid, coverHit);

    wstring needleFile = this->GetGame()->GetImagesDirectory() + L"\\" + mNeedleFile;
    std::unique_ptr<wxImage> needleImage = make_unique<wxImage>(needleFile, wxBITMAP_TYPE_ANY);
    wxGraphicsBitmap needleBitmap = graphics->CreateBitmapFromImage(*needleImage);

    int needleWid = needleImage->GetWidth();
    int needleHit = needleImage->GetHeight();

    graphics->DrawBitmap(needleBitmap, int(x - this->GetSizeX()/2), int(y -  this->GetSizeY()/2), needleWid, needleHit);
}
