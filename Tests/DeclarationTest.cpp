/**
 * @file DeclarationTest.cpp
 * @author Milo Baran
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <Declaration.h>
#include <wx/sstream.h>

class DeclarationMock : public Declaration {
public:
    DeclarationMock(Game* game = nullptr) : Declaration(game) {}


    void Draw(std::shared_ptr<wxGraphicsContext> graphics, double x, double y) override {}
};

class DeclarationTest : public ::testing::Test {
protected:
    void TestXMLLoad(wxString xmlString, int expectedItemsSizeWidth, int expectedItemsSizeHeight, wxString id, wxString imageName) {
        Game game(nullptr);
        DeclarationMock declaration(&game);

        // Create an XML doc consisting of a single node
        wxXmlDocument doc;
        wxStringInputStream stream(xmlString);
        doc.Load(stream);

        //get node from document
        wxXmlNode* node = doc.GetRoot();

        //run XmlLoad
        declaration.XmlLoad(node);

        //Assertions
        ASSERT_EQ(declaration.GetSizeX(), expectedItemsSizeWidth) << L"Incorrect width loaded for declaration: ";
        ASSERT_EQ(declaration.GetSizeY(), expectedItemsSizeHeight) << L"Incorrect height loaded for declaration: ";
        ASSERT_EQ(declaration.GetId(), id) << L"Incorrect id loaded for declaration: ";
        ASSERT_EQ(declaration.GetImageFile(), imageName) << L"Incorrect image filename loaded for declaration: ";
    }
};


TEST_F(DeclarationTest, Construct){
    Game game(nullptr);
    DeclarationMock declaration(&game);
}

TEST_F(DeclarationTest, XmlLoad) {
    wxString xmlString1 = "<image id=\"i600\" size=\"1304,900\" image=\"background1.png\" />";
    wxString xmlString2 = "<sound-board id=\"i622\" size=\"835,627\" size-beats=\"4\" top-width=\"345\" image=\"sound-board.png\" cover=\"sound-board-cover.png\" />";
    wxString xmlString3 = "<note id=\"t3\" track=\"3\" image=\"puck-d.png\" size=\"60,60\" tolerance=\"0.5\" />";


    // Testing XmlLoad function with the different nodes
    TestXMLLoad(xmlString1, 1304, 900, L"i600", L"background1.png");
    TestXMLLoad(xmlString2, 835, 627, L"i622", L"sound-board.png");
    TestXMLLoad(xmlString3, 60, 60, L"t3", L"puck-d.png");

}