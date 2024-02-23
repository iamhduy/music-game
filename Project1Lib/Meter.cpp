/**
 * @file Meter.cpp
 * @author hduy
 */
#include "pch.h"
#include <string>
#include "Meter.h"
using namespace std;

const wstring ImageFile = L"images/meter.png";

Meter::Meter(Level *Level) : Item(Level, ImageFile)
{
}

void Meter::XmlLoad(wxXmlNode *node)
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
