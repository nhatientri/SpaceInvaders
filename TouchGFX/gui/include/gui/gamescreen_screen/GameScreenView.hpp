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
    void spawnBullet();
    void spawnEnemyBullet(int x, int y);
    bool bulletCollides(const Image& bullet, const Image& alien);
    void playShootSound();
    virtual void handleTickEvent() override;
    uint32_t getRandom();
    uint32_t getRandomInRange(uint32_t min, uint32_t max);

protected:
    static const int MAX_BULLETS = 9;
    static const int MAX_ENEMY_BULLETS = 20;
    static const int ROWS = 3;
    static const int COLS = 6;
    static const int MAX_LIVES = 3;

    Image bullets[MAX_BULLETS];
    Image enemyBullets[MAX_ENEMY_BULLETS];
    Image enemies[ROWS][COLS];
    Image lifeIcons[MAX_LIVES];

    BitmapId enemyBitmaps[ROWS] = {
        BITMAP_RED_ID,
        BITMAP_GREEN_ID,
        BITMAP_YELLOW_ID
    };

    enum Direction { RIGHT, DOWN, LEFT, UP };
    Direction enemyMoveDir = RIGHT;

    int moveCounter = 0;
    const int maxSteps = 6;
    int stepSize = 3;
    int stepDelay = 10;

    int tickCounter = 0;
    int score = 0;
    static int highScore;

    int lives = MAX_LIVES;
    bool gameOverTriggered = false;
};


#endif // GAMESCREENVIEW_HPP
