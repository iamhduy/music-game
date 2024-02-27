/**
 * @file SoundBoard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_SOUNDBOARD_H
#define PROJECT1_PROJECT1LIB_SOUNDBOARD_H
#include "Item.h"

class SoundBoard : public Item
{
private:
    wxString mId;

    int mSizeX;

    int mSizeY;

    int mNumTracks;

    int mTopWidth;

    wxString mImageFile;

    wxString mCoverFile;

public:
    /// Default constructor (disabled)
    SoundBoard() = delete;

    /// Copy constructor (disabled)
    SoundBoard(const SoundBoard &) = delete;

    /// Assignment operator
    void operator=(const SoundBoard &) = delete;

    SoundBoard(Game* game);

    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_PROJECT1LIB_SOUNDBOARD_H
