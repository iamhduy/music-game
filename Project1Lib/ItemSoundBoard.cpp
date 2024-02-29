/**
 * @file ItemSoundBoard.cpp
 * @author hduy
 */

#include "pch.h"
#include "ItemSoundBoard.h"
#include <string>
using namespace std;
/// The maximum number of tracks
const int MaxTracks = 10;

/// What is the border of the left and right
/// of the tracks? This is the percentage of
/// the space to the left of the first track line
/// and to the right of the last track line
const double Border = 0.075;

/// Top clearance so we don't draw past the cover
/// as a fraction of the soundboard height. This
/// is where the pucks come in
const double TopClearance = 0.1;

/// Percentage down on the soundboard to the keys
/// This is where the pucks go under the key and
/// disappear.
const double KeyRow = 0.85;

/**
 * Constructor
 * @param game The level this item is a member of
 *
 */
ItemSoundBoard::ItemSoundBoard(Game* game) : Item(game)
{
}

/**
 * Load the attributes for an item node.
 * @param node The Xml node we are loading the item from
 */
void ItemSoundBoard::XmlLoad(wxXmlNode *node)
{
    Item::XmlLoad(node);

}

