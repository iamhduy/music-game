/**
 * @file DeclarationSoundBoard.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_DECLARATIONSOUNDBOARD_H
#define PROJECT1_PROJECT1LIB_DECLARATIONSOUNDBOARD_H
#include "Declaration.h"

/**
 * SoundBoard Class derived from Declaration
 *
 */
class DeclarationSoundBoard : public Declaration
{
private:
    /// beats size
    int mSizeBeats;

    /// top width
    int mTopWidth;

    /// Cover image dir
    wxString mCoverFile;
public:
    /// Default constructor (disabled)
    DeclarationSoundBoard() = delete;

    /// Copy constructor (disabled)
    DeclarationSoundBoard(const DeclarationSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const DeclarationSoundBoard &) = delete;

    DeclarationSoundBoard(Game* game);

    void XmlLoad(wxXmlNode *node) override;
};

#endif //PROJECT1_PROJECT1LIB_DECLARATIONSOUNDBOARD_H
