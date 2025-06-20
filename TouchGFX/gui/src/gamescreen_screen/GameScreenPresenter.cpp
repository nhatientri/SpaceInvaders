#include <gui/gamescreen_screen/GameScreenView.hpp>
#include <gui/gamescreen_screen/GameScreenPresenter.hpp>

GameScreenPresenter::GameScreenPresenter(GameScreenView& v)
    : view(v)
{

}

void GameScreenPresenter::activate()
{

}

void GameScreenPresenter::deactivate()
{

}

void GameScreenPresenter::updatePlayerX(int x) {
    view.updatePlayerPosition(x);
}

void GameScreenPresenter::updateADCValue(int value) {
	view.updateADCValue(value);
}

void GameScreenPresenter::fireBullet() {
    view.spawnBullet();
}
