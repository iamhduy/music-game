/**
 * @file DeclarationSoundBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "DeclarationSoundBoard.h"

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
    node->GetAttribute(L"cover", &mCoverFile);
    node->GetAttribute(L"top-width").ToInt(&mTopWidth);
    node->GetAttribute(L"size-beats").ToInt(&mSizeBeats);

    Declaration::XmlLoad(node);
}

