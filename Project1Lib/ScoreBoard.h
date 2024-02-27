/**
 * @file ScoreBoard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_SCOREBOARD_H
#define PROJECT1_PROJECT1LIB_SCOREBOARD_H

#include "Item.h"
class ScoreBoard : public Item
{
private:
    wxString mId;

    int mSizeX;

    int mSizeY;

    int mTopWidth;

    wxString mImageFile;
public:
    /// Default constructor (disabled)
    ScoreBoard() = delete;

    /// Copy constructor (disabled)
    ScoreBoard(const ScoreBoard &) = delete;

    /// Assignment operator
    void operator=(const ScoreBoard &) = delete;

    ScoreBoard(Game* game);

    void XmlLoad(wxXmlNode *node) override;

};

#endif //PROJECT1_PROJECT1LIB_SCOREBOARD_H
