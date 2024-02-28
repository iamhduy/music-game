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
    wxString mImageFile;
public:
    /// Default constructor (disabled)
    Declaration() = delete;

    /// Copy constructor (disabled)
    Declaration(const Declaration &) = delete;

    virtual ~Declaration();

    virtual void XmlLoad(wxXmlNode *node);

    /**
     * Get the pointer to the Level object
     * @return Pointer to Level object
     */
    Game *GetGame() { return mGame; }
};

#endif //PROJECT1_PROJECT1LIB_DECLARATION_H
