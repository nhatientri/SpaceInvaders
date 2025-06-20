#ifndef GAMESCREENVIEW_HPP
#define GAMESCREENVIEW_HPP

#include <gui_generated/gamescreen_screen/GameScreenViewBase.hpp>
#include <gui/gamescreen_screen/GameScreenPresenter.hpp>
#include <touchgfx/widgets/Image.hpp>
#include <images/BitmapDatabase.hpp>

class GameScreenView : public GameScreenViewBase
{
public:
    GameScreenView();
    virtual ~GameScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();
    void updatePlayerPosition(int x);
    void updateADCValue(int value);
    void spawnBullet();  // Tạo viên đạn mới
    bool bulletCollidesWithAlien(const Image& bullet, const Image& alien);
    virtual void handleTickEvent() override;
protected:
    static const int MAX_BULLETS = 9;
    Image bullets[MAX_BULLETS];
    static const int ROWS = 3;
    static const int COLS = 6;

    Image enemies[ROWS][COLS];
    BitmapId enemyBitmaps[ROWS] = {
        BITMAP_RED_ID,
        BITMAP_GREEN_ID,
        BITMAP_YELLOW_ID
    };

    enum Direction { RIGHT, DOWN, LEFT, UP };
    Direction enemyMoveDir = RIGHT;

    int moveCounter = 0;
    const int maxSteps = 6;  // số bước mỗi cạnh vuông
    int stepSize = 3;         // số pixel mỗi bước
    int stepDelay = 10;       // delay giữa các bước (tick)

    int tickCounter = 0;      // đếm tick để điều tốc

};

#endif // GAMESCREENVIEW_HPP
