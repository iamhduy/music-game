/**
 * @file Music.cpp
 * @author hduy
 */

#include "Music.h"
/**
 * Constructor
 * @param game The game this music is a member of
 *
 */
Music::Music()
{
}

/**
 * Destructor
 */
Music::~Music()
{
}

/**
 * Load the attributes for an music node.
 * @param node The Xml node we are loading the item from
 */
void Music::XmlLoad(wxXmlNode *node)
{
    node->GetAttribute(L"beats-per-minute").ToInt(&mBpMinute);
    node->GetAttribute(L"beats-per-measure").ToInt(&mBpMeasure);
    node->GetAttribute(L"measures").ToInt(&mMeasures);
    node->GetAttribute(L"backing", &mBack);
}
