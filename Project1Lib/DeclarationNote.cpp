/**
 * @file DeclarationNote.cpp
 * @author hduy
 */

#include "pch.h"
#include "DeclarationNote.h"
/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
DeclarationNote::DeclarationNote(Game *game) : Declaration(game)
{
}

/**
 * Load the attributes for an declaration node.
 * @param node The Xml node we are loading the declaration from
 */
void DeclarationNote::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"track").ToInt(&mTrack);
    node->GetAttribute(L"tolerance").ToDouble(&mTolerance);

    Declaration::XmlLoad(node);
}

/**
 * Draw this item
 * @param dc Device context to draw on
 * @param x location x
 * @param y location y
 */
void DeclarationNote::Draw(wxDC *dc, double x, double y)
{
}

