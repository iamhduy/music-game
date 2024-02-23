/**
 * @file Scoreboard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_SCOREBOARD_H
#define PROJECT1_PROJECT1LIB_SCOREBOARD_H

#include "Item.h"
class Scoreboard : public Item
{
private:
    wxString mId;

    int mSizeX;

    int mSizeY;

    int mTopWidth;

    wxString mImageFile;
public:
    /// Default constructor (disabled)
    Scoreboard() = delete;

    /// Copy constructor (disabled)
    Scoreboard(const Scoreboard &) = delete;

    /// Assignment operator
    void operator=(const Scoreboard &) = delete;

    Scoreboard(Level* Level);

    void XmlLoad(wxXmlNode *node) override;

};

#endif //PROJECT1_PROJECT1LIB_SCOREBOARD_H
