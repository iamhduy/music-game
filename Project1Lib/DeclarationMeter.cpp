/**
 * @file DeclarationMeter.cpp
 * @author hduy
 */
#include "pch.h"
#include "DeclarationMeter.h"
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
    node->GetAttribute(L"cover", &mCoverFile);
    node->GetAttribute(L"needle", &mNeedleFile);

    Declaration::XmlLoad(node);
}
