#include<bangtal.h>
#pragma comment(lib,"bangtal.lib")
#include<cstdlib>
#include<ctime>
#include<iostream>
using namespace std;

SceneID scene1;
TimerID mostimer[10];
ObjectID startButton, endButton, allButton, mos[10];
int score = 0, allscore = 0;
bool isgame = false;


ObjectID createObject(const char* image, SceneID scene, int x, int y, bool shown)
{
    ObjectID object = createObject(image);
    locateObject(object, scene, x, y);
    if (shown == true)
    {
        showObject(object);
    }
    return object;
}
ObjectID makeMos(int n)
{
    int x, y;

    x = rand() % 1000;
    y = rand() % 1000;
    mos[n] = createObject("크기변환_크기변환_모기.jpg", scene1, x, y, true);
    setTimer(mostimer[n], 1.0f);
    startTimer(mostimer[n]);
    return mos[n];
}
void startGame()
{
    if (isgame)
    {
        for (int i = 0; i < 10; i++)
            makeMos(i);
    }
}
void endGame(bool b)
{
    showMessage("모기  10 마리 잡기 성공!");
    isgame = false;
    score = 0;
    cout << (allscore) << "\n";
    for (int i = 0; i < 10; i++)
    {
        hideObject(mos[i]);
        stopTimer(mostimer[i]);


    }
    setObjectImage(startButton, "restart.png");
    showObject(startButton);


}
void mouseCallback(ObjectID object, int x, int y, MouseAction action)
{
    if (object == startButton)
    {

        hideObject(startButton);
        isgame = true;
        startGame();
    }
    else if (object == endButton)
    {
        endGame();
    }
    /*else if (object == allButton)
    {
        showMessage("총 잡은마리는 콘솔창에 나옵니다.");
        cout << (allscore) << "\n";
    }*/
    for (int i = 0; i < 10; i++)
    {
        if (object == mos[i] && isgame == true)
        {
            score = score + 1;
            allscore = allscore + 1;
            if (score == 10)
            {
                endGame(true);
            }
            else
            {
                hideObject(mos[i]);
                mos[i] = makeMos(i);
            }

        }
    }

}
void timerCallback(TimerID timer)
{
    for (int i = 0; i < 10; i++)
    {
        if (timer == mostimer[i] && isgame == true)
        {
            hideObject(mos[i]);
            makeMos(i);

        }

    }

}

int main(void)
{
    int x, y;
    setMouseCallback(mouseCallback);
    setTimerCallback(timerCallback);
    srand((unsigned int)time(NULL));

    scene1 = createScene("scene1", "배경1.png");
    startButton = createObject("start.png", scene1, 590, 70, true);
    endButton = createObject("end.png", scene1, 590, 20, true);
    //allButton = createObject("총 몇마리?", "all.png", scene1, 590, 110, true);
    for (int i = 0; i < 10; i++)
        mostimer[i] = createTimer(1.0f);

    startGame(scene1);

}