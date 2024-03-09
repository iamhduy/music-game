/**
 * @file ItemTrackTest.cpp
 * @author Milo Baran
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <ItemSoundBoard.h>
#include <Game.h>
#include <Item.h>
#include <ItemTrack.h>
#include <wx/sstream.h>

class ItemTrackTest : public ::testing::Test {
protected:
    void TestXMLLoad(wxString xmlString, int expectedItemsSizeWidth, int expectedItemsSizeHeight, wxString imageName, int trackNum) {
        Game game(nullptr);
        ItemSoundBoard soundboard(&game);
        ItemTrack track(&soundboard);

        // Create an XML doc consisting of a single node
        wxXmlDocument doc;
        wxStringInputStream stream(xmlString);
        doc.Load(stream);

        //get node from document
        wxXmlNode* node = doc.GetRoot();

        //run XmlLoad
        track.XmlLoad(node);

        //Assertions
        ASSERT_EQ(track.GetSizeX(), expectedItemsSizeWidth) << L"Incorrect width loaded for track: ";
        ASSERT_EQ(track.GetSizeY(), expectedItemsSizeHeight) << L"Incorrect height loaded for track: ";
        ASSERT_EQ(track.GetTrackNum(), trackNum) << L"Incorrect track number loaded for track: ";
        ASSERT_EQ(track.GetImageFile(), imageName) << L"Incorrect image filename loaded for track: ";
    }
};


TEST_F(ItemTrackTest, Construct){
    Game game(nullptr);
    ItemSoundBoard soundboard(&game);
    ItemTrack track(&soundboard);
}

TEST_F(ItemTrackTest, XmlLoad) {
    wxString xmlString1 = "<track track=\"1\" key-image=\"key-a.png\" key-size=\"88,66\" key=\"A\" />";
    wxString xmlString2 = "<track track=\"4\" key-image=\"key-f.png\" key-size=\"88,66\" key=\"F\" />";
    wxString xmlString3 = "<track track=\"8\" key-image=\"key-k.png\" key-size=\"88,66\" key=\"K\" />";


    // Testing XmlLoad function with the different nodes
    TestXMLLoad(xmlString1, 88, 66, L"key-a.png", 1);
    TestXMLLoad(xmlString2, 88, 66, L"key-f.png", 4);
    TestXMLLoad(xmlString3, 88, 66, L"key-k.png", 8);
}
