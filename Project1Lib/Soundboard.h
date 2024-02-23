/**
 * @file Soundboard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_SOUNDBOARD_H
#define PROJECT1_PROJECT1LIB_SOUNDBOARD_H
#include "Item.h"

class Soundboard : public Item
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
    Soundboard() = delete;

    /// Copy constructor (disabled)
    Soundboard(const Soundboard &) = delete;

    /// Assignment operator
    void operator=(const Soundboard &) = delete;

    Soundboard(Level* Level);

    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_PROJECT1LIB_SOUNDBOARD_H
