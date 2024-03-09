/**
 * @file DeclarationSoundBoardTest.cpp
 * @author Milo Baran
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <DeclarationSoundBoard.h>
#include <Game.h>
#include <Declaration.h>
#include <wx/sstream.h>

class DeclarationSoundBoardMock : public DeclarationSoundBoard {
public:
    DeclarationSoundBoardMock(Game* game = nullptr) : DeclarationSoundBoard(game) {}


    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y) override {}

};

class DeclarationTest : public ::testing::Test {
protected:
    void TestXMLLoad(wxString xmlString, wxString coverfile, int topWidth, int sizeBeats) {
        Game game(nullptr);
        DeclarationSoundBoardMock declaration(&game);

        // Create an XML doc consisting of a single node
        wxXmlDocument doc;
        wxStringInputStream stream(xmlString);
        doc.Load(stream);

        //get node from document
        wxXmlNode* node = doc.GetRoot();

        //run XmlLoad
        declaration.XmlLoad(node);

        //Assertions
        ASSERT_EQ(declaration.GetCoverFile(), coverfile) << L"Incorrect coverfile loaded for soundboard: ";
        ASSERT_EQ(declaration.GetTopWidth(), topWidth) << L"Incorrect top width loaded for soundboard: ";
        ASSERT_EQ(declaration.GetSizeBeats(), sizeBeats) << L"Incorrect size-beats loaded for soundboard: ";
    }
};


TEST_F(DeclarationTest, Construct){
    Game game(nullptr);
    DeclarationSoundBoardMock declaration(&game);
}

TEST_F(DeclarationTest, XmlLoad) {
    wxString xmlString1 = "<sound-board id=\"i622\" size=\"835,627\" size-beats=\"4\" top-width=\"345\" image=\"sound-board.png\" cover=\"sound-board-cover.png\" />";
    wxString xmlString2 = "<sound-board id=\"i622\" size=\"726,545\" size-beats=\"4\" top-width=\"300\" image=\"sound-board.png\" cover=\"sound-board-cover.png\" />";

    // Testing XmlLoad function with the different nodes
    TestXMLLoad(xmlString1, "sound-board-cover.png", 345, 4);
    TestXMLLoad(xmlString2, "sound-board-cover.png", 300, 4);
}