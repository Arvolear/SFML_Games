#include "Level.h"
#include "Rocket.h"
#include "Market.h"

using namespace std;
using namespace sf;

bool ExitL = false;

struct L
{
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
	bool select;
};

struct S
{
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
};

struct St
{
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
};

S Selectedlevel;

St Start;

int Levelselected = -1;

L Levels[10];

void inlevel()
{
	Levels[0].image.loadFromFile("images/back.bmp");
	Levels[0].image.createMaskFromColor(Color(255, 255, 255));
	Levels[0].texture.loadFromImage(Levels[0].image);
	Levels[0].sprite.setTexture(Levels[0].texture, true);
	Levels[0].sprite.setPosition(20, 20);
	Levels[0].select = false;

	Selectedlevel.image.loadFromFile("images/Selectedlevel.bmp");
	Selectedlevel.image.createMaskFromColor(Color(255, 255, 255));
	Selectedlevel.texture.loadFromImage(Selectedlevel.image);
	Selectedlevel.sprite.setTexture(Selectedlevel.texture, true);

	Start.image.loadFromFile("images/Play1.bmp");
	Start.image.createMaskFromColor(Color(255, 255, 255));
	Start.texture.loadFromImage(Start.image);
	Start.sprite.setTexture(Start.texture, true);
	Start.sprite.setPosition(320, 500);

	for (int i = 1; i <= 6; i++)
	{
		Levels[i].name = "Level" + to_string(i) + ".bmp";
		Levels[i].image.loadFromFile("images/" + Levels[i].name);
		Levels[i].image.createMaskFromColor(Color(255, 255, 255));
		Levels[i].texture.loadFromImage(Levels[i].image);
		Levels[i].sprite.setTexture(Levels[i].texture, true);
		Levels[i].sprite.setPosition(50 + ((i - 1) % 3) * 250, 100 + (i / 4) * 150);
		Levels[i].select = false;
	}
}

void Selectlevel(RenderWindow &level)
{
	Vector2i pixelPos = Mouse::getPosition(level);
	Vector2f pos = level.mapPixelToCoords(pixelPos);

	int save = -1;

	for (int i = 1; i <= 6; i++)
	{
		if (Levels[i].sprite.getGlobalBounds().contains(pos.x, pos.y))
		{			
			Levels[i].select = true;
			save = i;			
			break;			
		}
	}

	if (!Start.sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Levelselected = save;		
	
		for (int i = 1; i <= 6; i++)
		{
			if (i != save)
			{
				Levels[i].select = false;
			}
		}
	}
}

void PressL(RenderWindow &level)
{
	Vector2i pixelPos = Mouse::getPosition(level);
	Vector2f pos = level.mapPixelToCoords(pixelPos);

	if (Start.sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Start.image.loadFromFile("images/Play2.bmp");
		Start.image.createMaskFromColor(Color(255, 255, 255));
		Start.texture.loadFromImage(Start.image);
		Start.sprite.setTexture(Start.texture, true);
	}
}

void ReleaseL(RenderWindow &level)
{
	Vector2i pixelPos = Mouse::getPosition(level);
	Vector2f pos = level.mapPixelToCoords(pixelPos);

	if (Start.sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		bool S = false;
		for (int i = 1; i <= 6; i++)
			if (Levels[i].select == true)
				S = true;

		if (S)
		{
			extern Music musicmenu;

			musicmenu.stop();
			ROCKET();

			musicmenu.openFromFile("music/" + to_string(rand() % 2 + 1) + ".ogg");
			musicmenu.setVolume(100);
			musicmenu.play();
		}
	}

	Start.image.loadFromFile("images/Play1.bmp");
	Start.image.createMaskFromColor(Color(255, 255, 255));
	Start.texture.loadFromImage(Start.image);
	Start.sprite.setTexture(Start.texture, true);	
}

void PressBackL(RenderWindow &level)
{
	Vector2i pixelPos = Mouse::getPosition(level);
	Vector2f pos = level.mapPixelToCoords(pixelPos);

	Levels[0].select = false;

	if (Levels[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Levels[0].select = true;
	}
}

void ReleaseBackL(RenderWindow &level)
{
	Vector2i pixelPos = Mouse::getPosition(level);
	Vector2f pos = level.mapPixelToCoords(pixelPos);

	if (Levels[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		if (Levels[0].select == true)
		{
			//level.close();
			ExitL = true;
		}
	}
}

void complete()
{
	vector < string > mem;
	string s = "";

	ifstream COMc("system/complete.txt");

	while (COMc >> s)
	{
		mem.push_back(s);
		s = "";
	}

	COMc.close();

	for (int i = 1; i <= 6; i++)
	{
		for (int j = 0; j < mem.size(); j++)
		{
			if (Levels[i].name == (mem[j] + ".bmp"))
			{
				Levels[i].name = "Complete.bmp";
				Levels[i].image.loadFromFile("images/" + Levels[i].name);
				Levels[i].image.createMaskFromColor(Color(255, 255, 255));
				Levels[i].texture.loadFromImage(Levels[i].image);
				Levels[i].sprite.setTexture(Levels[i].texture, true);
			}
		}
	}
}

void showlevel(RenderWindow &level)
{
	level.clear(Color(10, 20, 60));

	level.draw(Levels[0].sprite);

	level.draw(Start.sprite);

	for (int i = 1; i <= 6; i++)
		level.draw(Levels[i].sprite);

	for (int i = 1; i <= 6; i++)
	{
		if (Levels[i].select == true)
		{
			Selectedlevel.sprite.setPosition(35 + ((i - 1) % 3) * 250, 85 + (i / 4) * 150);
			level.draw(Selectedlevel.sprite);
		}
	}

	extern struct C Cash;

	ifstream coins("system/coins.txt");
	coins >> Cash.name;
	coins.close();
	Cash.text.setString(Cash.name);
	level.draw(Cash.text);

	extern struct Sign sign;

	level.draw(sign.text);

	level.display();
}

void LEVEL()
{
	srand(unsigned(time(NULL)));

	//ContextSettings settings;
	//settings.antialiasingLevel = 8;

	//RenderWindow level(VideoMode(800, 600), "Level", Style::None, settings);

	extern RenderWindow menu;	

	//level.setSize(Vector2u(wwidth, wheight));
	//level.setPosition(Vector2i(0, 0));
	//level.setFramerateLimit(120);
	ExitL = false;
	Levelselected = -1;

	inlevel();

	Event event;

	while (menu.isOpen())
	{
		while (menu.pollEvent(event))
		{
			if (event.type == Event::Closed)
				menu.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					PressBackL(menu);
					PressL(menu);
					Selectlevel(menu);
				}

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{
					ReleaseL(menu);
					ReleaseBackL(menu);
				}
		}

		/*if (!musiclevel.getStatus())
		{
			musiclevel.openFromFile("music/" + to_string(rand() % 2 + 1) + ".ogg");
			musiclevel.setVolume(2);
			musiclevel.play();
		}*/

		if (ExitL)
			break;

		complete();

		showlevel(menu);
	}
}
