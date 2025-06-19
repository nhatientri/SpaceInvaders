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
