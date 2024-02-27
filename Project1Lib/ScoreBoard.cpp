/**
 * @file ScoreBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "ScoreBoard.h"
#include <string>

using namespace std;

ScoreBoard::ScoreBoard(Game *game) : Item(game)
{
}

void ScoreBoard::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"id", &mId);
    node->GetAttribute(L"top-width", "300").ToInt(&mTopWidth);

    node->GetAttribute(L"image", &mImageFile);

    string size = node->GetAttribute(L"size", L"0,0").ToStdString();
    auto index = size.find(',');
    mSizeX = stoi(size.substr(index));
    mSizeY = stoi(size.substr(index+1, size.size()));

    Item::XmlLoad(node);
}
