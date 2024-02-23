/**
 * @file Puck.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_PUCK_H
#define PROJECT1_PROJECT1LIB_PUCK_H

#include "Item.h"
class Puck : public Item
{
private:
    wxString mId;

    int mTrack;

    wxString mImageFile;

    double mTolerance;

    double mSizeX;

    double mSizeY;

public:
    /// Default constructor (disabled)
    Puck() = delete;

    /// Copy constructor (disabled)
    Puck(const Puck &) = delete;

    /// Assignment operator
    void operator=(const Puck &) = delete;

    Puck(Level* Level);

    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_PROJECT1LIB_PUCK_H
