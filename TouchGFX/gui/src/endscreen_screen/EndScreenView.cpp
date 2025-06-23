#include <gui/endscreen_screen/EndScreenView.hpp>

EndScreenView::EndScreenView()
{

}

void EndScreenView::setupScreen()
{
    EndScreenViewBase::setupScreen();
}

void EndScreenView::tearDownScreen()
{
    EndScreenViewBase::tearDownScreen();
}

void EndScreenView::setFinalScore(int score)
{
    Unicode::snprintf(scoreTextBuffer, sizeof(scoreTextBuffer), "%d", score);
    scoreText.invalidate();  // Redraw the TextArea
}
