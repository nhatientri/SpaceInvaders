#include <gui/gamescreen_screen/GameScreenView.hpp>
GameScreenView::GameScreenView()
{

}

void GameScreenView::setupScreen()
{
    GameScreenViewBase::setupScreen();
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
    bullet.setBitmap(Bitmap(BITMAP_BULLET_ID));  // Ảnh đạn bạn đã thêm vào
    bullet.setXY(player.getX() + player.getWidth() / 2 - bullet.getWidth() / 2,
                 player.getY() - bullet.getHeight());

    bullet.setVisible(true);
    add(bullet);
    bullet.invalidate();
}
