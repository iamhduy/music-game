project(Project1Lib)

set(SOURCE_FILES
        pch.h
        MainFrame.cpp
        MainFrame.h
        GameView.cpp
        GameView.h
        ids.h
        Item.cpp
        Item.h
        Sound.cpp
        Sound.h
        ItemSoundBoard.cpp
        ItemSoundBoard.h
        Game.cpp
        Game.h
        ItemMeter.cpp
        ItemMeter.h
        ItemScoreBoard.cpp
        ItemScoreBoard.h
        Audio.cpp
        Audio.h
        ItemImage.cpp
        ItemImage.h
        ItemTrack.cpp
        ItemTrack.h
        Declaration.cpp
        Declaration.h
        DeclarationImage.cpp
        DeclarationImage.h
        DeclarationSoundBoard.cpp
        DeclarationSoundBoard.h
        DeclarationScoreBoard.cpp
        DeclarationScoreBoard.h
        DeclarationMeter.cpp
        DeclarationMeter.h
        DeclarationNote.cpp
        DeclarationNote.h
        Music.cpp
        Music.h
        MusicNote.cpp
        MusicNote.h)

set(wxBUILD_PRECOMP OFF)
find_package(wxWidgets COMPONENTS core base xrc html xml REQUIRED)

include(${wxWidgets_USE_FILE})

add_library(${PROJECT_NAME} STATIC ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})

target_precompile_headers(${PROJECT_NAME} PRIVATE pch.h)