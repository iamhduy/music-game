/**
 * @file ItemTrackTest.cpp
 * @author Milo Baran
 */

#include <pch.h>
#include "gtest/gtest.h"
#include <Game.h>
#include <MusicNote.h>
#include <wx/sstream.h>

class ItemTrackTest : public ::testing::Test {
protected:
    void TestXMLLoad(wxString xmlString, wxString id, double measure, double beat, double duration) {
        Game game(nullptr);
        MusicNote note(&game);

        // Create an XML doc consisting of a single node
        wxXmlDocument doc;
        wxStringInputStream stream(xmlString);
        doc.Load(stream);

        //get node from document
        wxXmlNode* node = doc.GetRoot();

        //run XmlLoad
        note.XmlLoad(node);

        //Assertions
        ASSERT_EQ(note.GetId(), id) << L"Incorrect id loaded for track: ";
        ASSERT_EQ(note.GetMeasure(), measure) << L"Incorrect measure loaded for note: ";
        ASSERT_EQ(note.GetBeat(), beat) << L"Incorrect beat loaded for note: ";
        ASSERT_EQ(note.GetDuration(), duration) << L"Incorrect duration loaded for note: ";
    }
};


TEST_F(ItemTrackTest, Construct){
    Game game(nullptr);
    MusicNote note(&game);
}

TEST_F(ItemTrackTest, XmlLoad) {
    wxString xmlString1 = "<note id=\"t8\" sound=\"D6\" measure=\"1\" beat=\"1.0\" duration=\"0.5\"/>";
    wxString xmlString2 = "<note id=\"t2\" sound=\"G5\" measure=\"1\" beat=\"4.0\" duration=\"0.5\"/>";
    wxString xmlString3 = "<note id=\"t3\" sound=\"A3-long\" measure=\"3\" beat=\"2.5\" duration=\"1.0\"/>";


    // Testing XmlLoad function with the different nodes
    TestXMLLoad(xmlString1, "t8", 1, 1.0, 0.5);
    TestXMLLoad(xmlString2, "t2", 1, 4.0, 0.5);
    TestXMLLoad(xmlString3, "t3", 3, 2.5, 1);
}
