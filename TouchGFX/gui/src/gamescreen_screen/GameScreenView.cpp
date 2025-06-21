#include <gui/gamescreen_screen/GameScreenView.hpp>
#include <images/BitmapDatabase.hpp>
#include "main.h"

extern "C" RNG_HandleTypeDef hrng;

GameScreenView::GameScreenView()
{

}

void GameScreenView::setupScreen()
{
    GameScreenViewBase::setupScreen();

    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        bullets[i].setBitmap(Bitmap(BITMAP_BULLET_ID));
        bullets[i].setVisible(false);
        add(bullets[i]);
    }

    int startX = 15;
    int startY = 30;
    int spacingX = 35;
    int spacingY = 25;

    for (int row = 0; row < ROWS; ++row)
    {
        for (int col = 0; col < COLS; ++col)
        {
            enemies[row][col].setBitmap(Bitmap(enemyBitmaps[row]));
            enemies[row][col].setXY(startX + col * spacingX, startY + row * spacingY);
            enemies[row][col].setVisible(true);
            add(enemies[row][col]);
        }
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; ++i)
    {
        enemyBullets[i].setBitmap(Bitmap(BITMAP_BULLET_ID));
        enemyBullets[i].setVisible(false);
        add(enemyBullets[i]);
    }
    // SCORE
    Unicode::snprintf(scoreTextBuffer, sizeof(scoreTextBuffer), "%d", score);
    Unicode::snprintf(highScoreTextBuffer, sizeof(highScoreTextBuffer), "%d", highScore);

    scoreText.invalidate();
    highScoreText.invalidate();



}

void GameScreenView::tearDownScreen()
{
    GameScreenViewBase::tearDownScreen();
}

void GameScreenView::updatePlayerPosition(int x) {
    player.moveTo(x - player.getWidth() / 2, player.getY());
}

void GameScreenView::updateADCValue(int value) {
	Unicode::snprintf(textArea1Buffer, sizeof(textArea1Buffer),"%d", value);
	textArea1.invalidate();
}

void GameScreenView::spawnBullet()
{
    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        if (!bullets[i].isVisible())
        {
            bullets[i].setXY(
                player.getX() + player.getWidth() / 2 - bullets[i].getWidth() / 2,
                player.getY() - bullets[i].getHeight());

            bullets[i].setVisible(true);
            bullets[i].invalidate();
            break;  // chỉ bắn 1 viên mỗi lần
        }
    }
}

void GameScreenView::handleTickEvent()
{
    for (int i = 0; i < MAX_BULLETS; ++i)
    {
        if (bullets[i].isVisible())
        {
            int newY = bullets[i].getY() - 4;
            if (newY < -bullets[i].getHeight())
            {
                bullets[i].setVisible(false);  // reset slot
            }
            else
            {
                bullets[i].moveTo(bullets[i].getX(), newY);
                bullets[i].invalidate();
            }
        }
    }

    for (int b = 0; b < MAX_BULLETS; ++b)
    {
        if (!bullets[b].isVisible()) continue;

        // Kiểm tra với tất cả alien
        for (int row = 0; row < ROWS; ++row)
        {
            for (int col = 0; col < COLS; ++col)
            {
                if (!enemies[row][col].isVisible()) continue;

                if (bulletCollidesWithAlien(bullets[b], enemies[row][col]))
                {
                    bullets[b].setVisible(false);
                    enemies[row][col].setVisible(false);

                    bullets[b].invalidate();
                    enemies[row][col].invalidate();

                    // (Tùy chọn) tăng điểm ở đây
                    if (enemyBitmaps[row] == BITMAP_RED_ID)
                    {
                    	score += 20;
                    }
                    else if (enemyBitmaps[row] == BITMAP_GREEN_ID)
                    {
                    	score += 10;
                    }
                    else
                    {
                    	score += 5;
                    }

                	Unicode::snprintf(scoreTextBuffer, sizeof(scoreTextBuffer), "%d", score);
                	scoreText.invalidate();

                    if (score > highScore)
                    {
                    	highScore = score;
                    	Unicode::snprintf(highScoreTextBuffer, sizeof(highScoreTextBuffer), "%d", highScore);
                    	highScoreText.invalidate();
                    }
                    goto nextBullet;  // thoát vòng lặp 3 tầng
                }
            }
        }
    nextBullet:;
    }

    tickCounter++;
    if (tickCounter < stepDelay)
        return;  // chưa đến lúc di chuyển
    tickCounter = 0;  // reset

    // Thực hiện 1 bước theo hướng hiện tại
    for (int row = 0; row < ROWS; ++row) {
        for (int col = 0; col < COLS; ++col) {
            if (!enemies[row][col].isVisible()) continue;

            int x = enemies[row][col].getX();
            int y = enemies[row][col].getY();

            switch (enemyMoveDir) {
                case RIGHT: x += stepSize; break;
                case DOWN:  y += stepSize; break;
                case LEFT:  x -= stepSize; break;
                case UP:    y -= stepSize; break;
            }

            enemies[row][col].moveTo(x, y);
            enemies[row][col].invalidate();
        }
    }

    moveCounter++;
    if (moveCounter >= maxSteps) {
        moveCounter = 0;
        enemyMoveDir = static_cast<Direction>((enemyMoveDir + 1) % 4);  // xoay chiều
    }

    // Chọn alien ngẫu nhiên
    int randRow = getRandomInRange(0, ROWS - 1);
    int randCol = getRandomInRange(0, COLS - 1);

    // Chỉ cho alien đang sống bắn
    if (enemies[randRow][randCol].isVisible())
    {
        // Tỷ lệ 1/20 (hoặc tùy chỉnh)
        if (getRandomInRange(0, 19) == 0)
        {
            int bulletX = enemies[randRow][randCol].getX() + enemies[randRow][randCol].getWidth() / 2;
            int bulletY = enemies[randRow][randCol].getY() + enemies[randRow][randCol].getHeight();

            spawnEnemyBullet(bulletX, bulletY);
        }
    }

    for (int i = 0; i < MAX_ENEMY_BULLETS; ++i)
    {
        if (enemyBullets[i].isVisible())
        {
            int newY = enemyBullets[i].getY() + 4;
            if (newY > 320)
            {
                enemyBullets[i].setVisible(false);
            }
            else
            {
                enemyBullets[i].moveTo(enemyBullets[i].getX(), newY);
                enemyBullets[i].invalidate();
            }
        }
    }

}

bool GameScreenView::bulletCollidesWithAlien(const Image& bullet, const Image& alien)
{
    int bx = bullet.getX();
    int by = bullet.getY();
    int bw = bullet.getWidth();
    int bh = bullet.getHeight();

    int ax = alien.getX();
    int ay = alien.getY();
    int aw = alien.getWidth();
    int ah = alien.getHeight();

    return !(bx + bw < ax || bx > ax + aw || by + bh < ay || by > ay + ah);
}

int GameScreenView::highScore = 0;

uint32_t GameScreenView::getRandom()
{
    uint32_t val;
    if (HAL_RNG_GenerateRandomNumber(&hrng, &val) == HAL_OK)
        return val;
    return 42;  // fallback
}

uint32_t GameScreenView::getRandomInRange(uint32_t min, uint32_t max)
{
    if (max <= min) return min;
    return getRandom() % (max - min + 1) + min;
}

void GameScreenView::spawnEnemyBullet(int x, int y)
{
    for (int i = 0; i < MAX_ENEMY_BULLETS; ++i)
    {
        if (!enemyBullets[i].isVisible())
        {
            enemyBullets[i].setXY(x, y);
            enemyBullets[i].setVisible(true);
            enemyBullets[i].invalidate();
            break;
        }
    }
}
