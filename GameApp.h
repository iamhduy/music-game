/**
 * @file GameApp.h
 * @author phamhoan
 *
 */

#ifndef PROJECT1__GAMEAPP_H
#define PROJECT1__GAMEAPP_H

class GameApp : public wxApp
{
private:

public:
    bool OnInit() override;

    int OnExit() override;
};

#endif //PROJECT1__GAMEAPP_H
