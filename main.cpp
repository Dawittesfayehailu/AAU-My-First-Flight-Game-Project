#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <iostream>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <windows.h>
#include <string>
#include <string>


using namespace std;
using namespace sf;

const double SCREEN_WIDTH=800;
const double SCREEN_HEIGH=900;
const int borderLeft = 60;
const int borderRight = 535;
const int travellerWidth = 100;
const int travellerHeight = 87;
string stringscore = "";
int score = 0;
double gameSpeed = 0.5;


//Create Main Windows
RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "My First Flight");

//Create random Number for game loop
int getRandomNumber(int a, int b);

// Create game over screen
int gameOver();

int main()
{

	SoundBuffer gameSoundBuffer;
	gameSoundBuffer.loadFromFile("sound/game.wav");
	Sound GameSound;
	GameSound.setBuffer(gameSoundBuffer);

	Texture background, traveller, obs1, obs2, obs3, obs4, gameover;

	Font myfont;
	myfont.loadFromFile("myfonts/Pacifico.ttf");

	//Load all images
	if (!background.loadFromFile("plane/background.png")) return EXIT_FAILURE;
	if (!traveller.loadFromFile("plane/traveller.png")) return EXIT_FAILURE;
	if (!obs1.loadFromFile("plane/obs1.png")) return EXIT_FAILURE;
	if (!obs2.loadFromFile("plane/obs2.png")) return EXIT_FAILURE;
	if (!obs3.loadFromFile("plane/obs3.png")) return EXIT_FAILURE;
	if (!obs4.loadFromFile("plane/obs4.png")) return EXIT_FAILURE;

	//Create sprite
	Sprite Background(background), Background1(background), Traveller(traveller), Obs1(obs1), Obs2(obs2), Obs3(obs3), Obs4(obs4), Gameover(gameover);

	double TravellerX, TravellerY, Obs1X, Obs1Y, Obs2X, Obs2Y, Obs3X, Obs3Y, Obs4X, Obs4Y;

    //Set plane and Obs pos
	TravellerX = SCREEN_WIDTH / 2;
	TravellerY = SCREEN_HEIGH- travellerHeight;
	Obs1X = getRandomNumber(borderLeft, borderRight);
	Obs2X = getRandomNumber(borderLeft, borderRight);
	Obs3X = getRandomNumber(borderLeft, borderRight);
	Obs4X = getRandomNumber(borderLeft, borderRight);
	Obs1Y = 0, Obs2Y = -100, Obs3Y = -200, Obs4Y = -300;
	double BackgroundY1 = 0;
	double BackgroundY2 = -600;

	GameSound.play();
	GameSound.setLoop(true);

	//GAME LOOP
	while (app.isOpen())
	{
        //Init and count score
		stringscore = "SCORE:" + to_string(score);
		Text text(stringscore, myfont, 45);
		text.setPosition(5, 5);

		//Set Plane position
		Traveller.setPosition(TravellerX, TravellerY);
		Obs1.setPosition(Obs1X, Obs1Y);
		Obs2.setPosition(Obs2X, Obs2Y);
		Obs3.setPosition(Obs3X, Obs3Y);
		Obs4.setPosition(Obs4X, Obs4Y);



        //Set Obst LOOP
		if (Obs1Y>SCREEN_HEIGH)
		{
			Obs1Y = 0; Obs1X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs1Y = Obs1Y + gameSpeed; }
		if (Obs2Y>SCREEN_HEIGH)
		{
			Obs2Y = 0; Obs2X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs2Y = Obs2Y + gameSpeed; }
		if (Obs3Y>SCREEN_HEIGH)
		{
			Obs3Y = 0; Obs3X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs3Y = Obs3Y + gameSpeed; }
		if (Obs4Y>SCREEN_HEIGH)
		{
			Obs4Y = 0; Obs4X = getRandomNumber(borderLeft, borderRight); score++;
		}
		else { Obs4Y = Obs4Y + gameSpeed; }

		//Game level
		if (score>15 && score<25) { gameSpeed = 0.7; }
		if (score>25 && score<35) { gameSpeed = 0.9; }
		if (score>35 && score<50) { gameSpeed = 1.1; }
		if (score>50 && score<70) { gameSpeed = 1.3; }
		if (score>70 && score<100) { gameSpeed = 1.8; }
		if (score>70 && score<100) { gameSpeed = 1.9; }
		if (score>70 && score<100) { gameSpeed = 1.9; }
		if (score>70 && score<100) { gameSpeed = 1.9; }

		//Create event to handle input from keyboard
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Left)
				{
					if (TravellerX>borderLeft) { TravellerX = TravellerX - 50; }
				}
				if (event.key.code == sf::Keyboard::Right)
				{
					if (TravellerX<borderRight) { TravellerX = TravellerX + 50; }
				}
				if (event.key.code == sf::Keyboard::Up)
				{
					if (TravellerY>0) { TravellerY = TravellerY - 10; }
				}
				if (event.key.code == sf::Keyboard::Down)
				{
					if (TravellerY<SCREEN_HEIGH - 70) { TravellerY = TravellerY + 10; }
				}
			}
		}

		//Check if accident happen
		if (((TravellerX >= (Obs1X - 30)) && (TravellerX <= (Obs1X + 30))) && ((TravellerY >= (Obs1Y - 30)) && (TravellerY) <= (Obs1Y + 30)))
		{
			GameSound.stop(); gameOver();
		};
		if (((TravellerX >= (Obs2X - 30)) && (TravellerX <= (Obs2X + 30))) && ((TravellerY >= (Obs2Y - 30)) && (TravellerY) <= (Obs2Y + 30)))
		{
			GameSound.stop(); gameOver();
		};
		if (((TravellerX >= (Obs3X - 30)) && (TravellerX <= (Obs3X + 30))) && ((TravellerY >= (Obs3Y - 30)) && (TravellerY) <= (Obs3Y + 30)))
		{
			GameSound.stop(); gameOver();
		};
		if (((TravellerX >= (Obs4X - 30)) && (TravellerX <= (Obs4X + 30))) && ((TravellerY >= (Obs4Y - 30)) && (TravellerY) <= (Obs4Y + 30)))
		{
			GameSound.stop(); gameOver();
		};



		//Clear and redraw position
		app.clear();
		app.draw(Background);
		app.draw(Background1);
		app.draw(Traveller);
		app.draw(Obs1);
		app.draw(Obs2);
		app.draw(Obs3);
		app.draw(Obs4);
		app.draw(text);
		app.display();
	}
	return EXIT_SUCCESS;
}
int startGame()
{
	//TODO
}
//Game over
int gameOver()
{
	Texture gameover, troll;
	if (!gameover.loadFromFile("plane/over.png")) return EXIT_FAILURE;
	if (!troll.loadFromFile("plane/troll.png")) return EXIT_FAILURE;

	Sprite Gameover(gameover);
	Sprite Troll(troll);
	Troll.setPosition(10, 350);
	SoundBuffer gameOver;
	gameOver.loadFromFile("sound/crash.wav");
	Sound GameOver;
	GameOver.setBuffer(gameOver);
	GameOver.play();
	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();
		}
		Font myfont;
		myfont.loadFromFile("myfonts/Pacifico.ttf");
		stringscore = "YOUR SCORE:" + to_string(score);
		Text text(stringscore, myfont, 70);
		text.setPosition(65, 350);
		app.clear();
		app.draw(Gameover);
		app.draw(text);
		app.draw(Troll);
		app.display();


	}


}
int getRandomNumber(int a, int b)
{
	static bool first = true; if (first) { srand(time(NULL)); first = false; }
	int result = a + rand() % ((b + 1) - a);
	result = (result / 10) * 10;
	return result;

}
