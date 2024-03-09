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
    std::wstring mCoverFile;

    /// Cover's image
    std::unique_ptr<wxImage> mCoverImage;

    /// Cover's bitmap
    std::unique_ptr<wxBitmap> mCoverBitmap;
public:
    /// Default constructor (disabled)
    DeclarationSoundBoard() = delete;

    /// Copy constructor (disabled)
    DeclarationSoundBoard(const DeclarationSoundBoard &) = delete;

    /// Assignment operator
    void operator=(const DeclarationSoundBoard &) = delete;

    DeclarationSoundBoard(Game* game);

    void XmlLoad(wxXmlNode *node) override;

    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y) override;

    /**
     * @return the TopWidth of this object
     */
    int GetTopWidth() override { return mTopWidth; };

    /**
     * @return the coverfile of this object
     */
    wxString GetCoverFile() { return mCoverFile; };

    /**
     * @return the coverfile of this object
     */
    int GetSizeBeats() { return mSizeBeats; };
};

#endif //PROJECT1_PROJECT1LIB_DECLARATIONSOUNDBOARD_H
