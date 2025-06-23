#include <gui/endscreen_screen/EndScreenView.hpp>
#include <gui/endscreen_screen/EndScreenPresenter.hpp>

EndScreenPresenter::EndScreenPresenter(EndScreenView& v)
    : view(v)
{

}

void EndScreenPresenter::activate()
{
    int score = static_cast<FrontendApplication*>(Application::getInstance())->getFinalScore();
    view.setFinalScore(score);
}

void EndScreenPresenter::deactivate()
{

}
