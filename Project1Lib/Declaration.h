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

    std::unique_ptr<wxImage> mItemImage;

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
     * @return size of this item
     */
    Game *GetGame() { return mGame; }

    /**
     *
     * @return the id of this object
     */
    wxString GetId() {return mId;}

    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y);


    /*
     * @return the TopWidth of this object (for soundboard)
     */
    virtual int GetTopWidth() {return 0;};
};

#endif //PROJECT1_PROJECT1LIB_DECLARATION_H
