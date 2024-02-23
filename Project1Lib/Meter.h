/**
 * @file Meter.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_METER_H
#define PROJECT1_PROJECT1LIB_METER_H

#include "Item.h"
class Meter : public Item
{
private:
    wxString mId;

    int mSizeX;

    int mSizeY;

    int mNumTracks;

    int mTopWidth;

    wxString mImageFile;

    wxString mCoverFile;

    wxString mNeedleFile;
public:
    /// Default constructor (disabled)
    Meter() = delete;

    /// Copy constructor (disabled)
    Meter(const Meter &) = delete;

    /// Assignment operator
    void operator=(const Meter &) = delete;

    Meter(Level* Level);

    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_PROJECT1LIB_METER_H
