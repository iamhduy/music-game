/**
 * @file Declaration.h
 * @author hduy
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_DECLARATION_H
#define PROJECT1_PROJECT1LIB_DECLARATION_H
#include <wx/xml/xml.h>
class Game;

/**
 * Declaration Base Class
 *
 */
class Declaration
{
protected:
    Declaration(Game* game);
private:
    /// The game this declaration is contained in
    Game   *mGame;

    /// Declaration's id
    wxString mId;

    int mSizeX = 0; ///< X size for the center of the item
    int mSizeY = 0; ///< Y size for the center of the item

    /// Declaration's image dir
    std::wstring mImageFile;

    /// Declaration's image
    std::unique_ptr<wxImage> mItemImage;

    /// Declaration's bitmap
    std::unique_ptr<wxBitmap> mItemBitmap;

public:
    /// Default constructor (disabled)
    Declaration() = delete;

    /// Copy constructor (disabled)
    Declaration(const Declaration &) = delete;

    virtual ~Declaration();

    virtual void XmlLoad(wxXmlNode *node);

    /**
     * @return size of this item
     */
    int GetSizeX() const {return mSizeX;}

    /**
     * @return Pointer to Level object
     */
    int GetSizeY() const {return mSizeY;}

    /**
     * @return game for this item
     */
    Game *GetGame() { return mGame; }

    /**
     *
     * @return the id of this object
     */
    wxString GetId() {return mId;}

    /**
     *
     * @return the image filename of this object
     */
    wxString GetImageFile() {return mImageFile;}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y);

    /**
     * Virtual function for meter percentage
     * @param pct percentage
     */
    virtual void UpdatePercentage(double pct) {}

    /**
     * @return the TopWidth of this object (for soundboard)
     */
    virtual int GetTopWidth() {return 0;};

    /**
     * @return the size-beat of this object (for soundboard)
     */
    virtual int GetBeatSize() {return 0;};

    /**
     * Virtual function for priority drawing
     * @param graphics draw device
     * @param x x pos
     * @param y y pos
     */
    virtual void DrawOnTop(std::shared_ptr<wxGraphicsContext> graphics, double x, double y) {}
};

#endif //PROJECT1_PROJECT1LIB_DECLARATION_H
