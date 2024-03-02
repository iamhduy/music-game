/**
 * @file Game.h
 * @author Milo Baran
 *
 *
 */

#ifndef PROJECT1_PROJECT1LIB_GAME_H
#define PROJECT1_PROJECT1LIB_GAME_H

#include <memory>
#include "Item.h"
#include "miniaudio.h"
#include "Declaration.h"


/**
 * Game Class
 *
 */
class Game
{
private:
// keep level objects for level 0,1,2,3?

    /// Audio Engine of the Game
    ma_engine* mAudioEngine;

    /// Background image to use
    wxBitmap mBackground;

    /// holding the item
    std::vector<std::shared_ptr<Item>> mItems;

    ///holding the declaration
    std::vector<std::shared_ptr<Declaration>> mDeclarations;

    /// Directory containing the system images
    std::wstring mImagesDirectory;

    int mScore = 0;

    void XmlItem(wxXmlNode *node);

    void XmlDeclaration(wxXmlNode *node);
public:
    Game(ma_engine *PEngine);

    void Load(const wxString &filename);

    void Clear();
    void OnDraw(wxDC *dc);
    void AddItem(std::shared_ptr<Item> item);
    void AddDeclaration(std::shared_ptr<Declaration> declaration);

    /**
     * Get the audio engine object
     * @return Pointer to the audio engine object
     */
    ma_engine* GetAudioEngine() {return mAudioEngine;};

    int GetScore() {return mScore;};

    void AddScore(int value);

    void SetImagesDirectory(const std::wstring &dir);

    std::wstring GetImagesDirectory() {return mImagesDirectory;}
    void Update(double elapsed);
};

#endif //PROJECT1_PROJECT1LIB_GAME_H
