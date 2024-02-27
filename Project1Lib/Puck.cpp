/**
 * @file Puck.cpp
 * @author hduy
 */

#include "pch.h"
#include "Puck.h"
#include <string>
using namespace std;

Puck::Puck(Game *game) : Item(game)
{
}

void Puck::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"id", &mId);
    node->GetAttribute(L"image", &mImageFile);
    node->GetAttribute(L"tolerance", L"0.5").ToDouble(&mTolerance);

    string size = node->GetAttribute(L"size", L"0,0").ToStdString();
    auto index = size.find(',');
    mSizeX = stoi(size.substr(index));
    mSizeY = stoi(size.substr(index+1, size.size()));

    Item::XmlLoad(node);
}
