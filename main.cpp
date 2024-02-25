/**
 * @file main.cpp
 * @author phamhoan
 */

#include "pch.h"
#include "GameApp.h"

wxIMPLEMENT_APP(GameApp);


//If we had scoreboard class, could do something like
//this to keep score
//void ScoreBoard::KeepScore()
//{
//    if (SoundPlayedSuccessfully() && NotLongSound())
//    {
//        mScore += 10;
//    }
//    else if (SoundPlayedSuccessfully() && LongSound())
//    {
//        mScore += 10 * DurationPlayed();
//    }
//
//}

//If we had a Game and Item class we could do something like this
//to move an image to a desired location
//
//void Game::Add(std::shared_ptr<Item> item, double startX, double startY)
//{
//    item->SetLocation(startX, startY);
//    mItems.push_back(item);
//}
