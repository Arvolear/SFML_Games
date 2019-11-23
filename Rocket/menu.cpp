#include "Rocket.h"
#include "Market.h"
#include "Level.h"
#include "Help.h"

using namespace sf;
using namespace std;

int wwidth = 800;
int wheight = 600;

struct B
{
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
};

B Buttons[10];

C Cash;

Sign sign;

information info[10];

Music musicmenu;

RenderWindow menu(VideoMode(800, 600), "Rocket 1.0", Style::None);

void inmenu()
{
	ifstream coins("system/coins.txt");
	coins >> Cash.name;
	coins.close();

	Cash.font.loadFromFile("fonts/BAUHS93.ttf");	
	Cash.text.setFont(Cash.font);
	Cash.text.setString(Cash.name);
	Cash.text.setCharacterSize(40);
	Cash.text.setColor(Color(255, 211, 62));
	Cash.text.setPosition(145, 25);

	sign.font.loadFromFile("fonts/MAGNETOB.ttf");
	sign.text.setFont(sign.font);
	sign.name = "Choose a level!";
	sign.text.setString(sign.name);
	sign.text.setCharacterSize(50);
	sign.text.setColor(Color(230, 213, 132));
	sign.text.setPosition(340, 20);

	for (int i = 0; i < 10; i++)
	{
		info[i].font.loadFromFile("fonts/MAGNETOB.ttf");
		info[i].text.setFont(info[i].font);
	}
	
	Buttons[0].name = "Play1.bmp";
	Buttons[0].image.loadFromFile("images/Play1.bmp");
	Buttons[0].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[0].texture.loadFromImage(Buttons[0].image);
	Buttons[0].sprite.setTexture(Buttons[0].texture);
	Buttons[0].sprite.setPosition(800 / 2 - 80, 600 / 2 - 40);

	Buttons[1].name = "Market1.bmp";
	Buttons[1].image.loadFromFile("images/Market1.bmp");
	Buttons[1].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[1].texture.loadFromImage(Buttons[1].image);
	Buttons[1].sprite.setTexture(Buttons[1].texture);
	Buttons[1].sprite.setPosition(800 / 2 - 60, 600 / 2 - 80 - 30);	

	Buttons[2].name = "Exit1.bmp";
	Buttons[2].image.loadFromFile("images/Exit1.bmp");
	Buttons[2].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[2].texture.loadFromImage(Buttons[2].image);
	Buttons[2].sprite.setTexture(Buttons[2].texture);
	Buttons[2].sprite.setPosition(800 / 2 - 40, 600 / 2 - 80 - 80 - 40);

	Buttons[3].name = "Zoom1.bmp";
	Buttons[3].image.loadFromFile("images/Zoom1.bmp");
	Buttons[3].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[3].texture.loadFromImage(Buttons[3].image);
	Buttons[3].sprite.setTexture(Buttons[3].texture);
	Buttons[3].sprite.setPosition(800 / 2 - 70, 600 / 2 + 50);

	Buttons[4].name = "Help1.bmp";
	Buttons[4].image.loadFromFile("images/Help1.bmp");
	Buttons[4].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[4].texture.loadFromImage(Buttons[4].image);
	Buttons[4].sprite.setTexture(Buttons[4].texture);
	Buttons[4].sprite.setPosition(800 / 2 - 20, 600 / 2 + 50);
}

void Press(RenderWindow &menu)
{
	Vector2i pixelPos = Mouse::getPosition(menu);
	Vector2f pos = menu.mapPixelToCoords(pixelPos);

	if (Buttons[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Buttons[0].name = "Play2.bmp";
		Buttons[0].image.loadFromFile("images/Play2.bmp");
		Buttons[0].image.createMaskFromColor(Color(255, 255, 255));
		Buttons[0].texture.loadFromImage(Buttons[0].image);
		Buttons[0].sprite.setTexture(Buttons[0].texture, true);		
	}

	if (Buttons[1].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Buttons[1].name = "Market2.bmp";
		Buttons[1].image.loadFromFile("images/Market2.bmp");
		Buttons[1].image.createMaskFromColor(Color(255, 255, 255));
		Buttons[1].texture.loadFromImage(Buttons[1].image);
		Buttons[1].sprite.setTexture(Buttons[1].texture, true);
	}

	if (Buttons[2].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Buttons[2].name = "Exit2.bmp";
		Buttons[2].image.loadFromFile("images/Exit2.bmp");
		Buttons[2].image.createMaskFromColor(Color(255, 255, 255));
		Buttons[2].texture.loadFromImage(Buttons[2].image);
		Buttons[2].sprite.setTexture(Buttons[2].texture, true);
	}

	if (Buttons[3].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		if (Buttons[3].name == "Zoom1.bmp")
		{
			Buttons[3].name = "Zoom2.bmp";
			Buttons[3].image.loadFromFile("images/Zoom2.bmp");
			Buttons[3].image.createMaskFromColor(Color(255, 255, 255));
			Buttons[3].texture.loadFromImage(Buttons[3].image);
			Buttons[3].sprite.setTexture(Buttons[3].texture, true);
			
			wwidth = 960;
			wheight = 720;

			menu.setSize(Vector2u(wwidth, wheight));
		}

		else if (Buttons[3].name == "Zoom2.bmp")
		{
			Buttons[3].name = "Zoom3.bmp";
			Buttons[3].image.loadFromFile("images/Zoom3.bmp");
			Buttons[3].image.createMaskFromColor(Color(255, 255, 255));
			Buttons[3].texture.loadFromImage(Buttons[3].image);
			Buttons[3].sprite.setTexture(Buttons[3].texture, true);

			wwidth = 2266;
			wheight = 1700;

			menu.setSize(Vector2u(wwidth, wheight));
		}

		else if (Buttons[3].name == "Zoom3.bmp")
		{
			Buttons[3].name = "Zoom1.bmp";
			Buttons[3].image.loadFromFile("images/Zoom1.bmp");
			Buttons[3].image.createMaskFromColor(Color(255, 255, 255));
			Buttons[3].texture.loadFromImage(Buttons[3].image);
			Buttons[3].sprite.setTexture(Buttons[3].texture, true);

			wwidth = 800;
			wheight = 600;

			menu.setSize(Vector2u(wwidth, wheight));
		}
	}

	if (Buttons[4].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Buttons[4].name = "Help2.bmp";
		Buttons[4].image.loadFromFile("images/Help2.bmp");
		Buttons[4].image.createMaskFromColor(Color(255, 255, 255));
		Buttons[4].texture.loadFromImage(Buttons[4].image);
		Buttons[4].sprite.setTexture(Buttons[4].texture, true);
	}
}

void Release(RenderWindow &menu)
{
	Vector2i pixelPos = Mouse::getPosition(menu);
	Vector2f pos = menu.mapPixelToCoords(pixelPos);

	if (Buttons[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{		
		if (Buttons[0].name == "Play2.bmp")
		{
			//menu.close();
			//musicmenu.stop();
			//ROCKET();
			LEVEL();
			//musicmenu.openFromFile("music/" + to_string(rand() % 2 + 1) + ".ogg");
			//musicmenu.setVolume(2);
			//musicmenu.play();
		}
	}

	if (Buttons[1].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{		
		//menu.close();		
		if (Buttons[1].name == "Market2.bmp")
		{
			MARKET();
		}
	}

	if (Buttons[2].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{	
		if (Buttons[2].name == "Exit2.bmp")
		{
			musicmenu.stop();
			menu.close();
			exit(0);
		}
	}

	if (Buttons[4].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		if (Buttons[4].name == "Help2.bmp")
		{
			HELP();
		}
	}

	Buttons[0].name = "Play1.bmp";
	Buttons[0].image.loadFromFile("images/Play1.bmp");
	Buttons[0].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[0].texture.loadFromImage(Buttons[0].image);
	Buttons[0].sprite.setTexture(Buttons[0].texture, true);

	Buttons[1].name = "Market1.bmp";
	Buttons[1].image.loadFromFile("images/Market1.bmp");
	Buttons[1].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[1].texture.loadFromImage(Buttons[1].image);
	Buttons[1].sprite.setTexture(Buttons[1].texture, true);

	Buttons[2].name = "Exit1.bmp";
	Buttons[2].image.loadFromFile("images/Exit1.bmp");
	Buttons[2].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[2].texture.loadFromImage(Buttons[2].image);
	Buttons[2].sprite.setTexture(Buttons[2].texture, true);

	Buttons[4].name = "Help1.bmp";
	Buttons[4].image.loadFromFile("images/Help1.bmp");
	Buttons[4].image.createMaskFromColor(Color(255, 255, 255));
	Buttons[4].texture.loadFromImage(Buttons[4].image);
	Buttons[4].sprite.setTexture(Buttons[4].texture, true);
}

void showmenu(RenderWindow &menu)
{
	menu.clear(Color(15, 15, 50));

	ifstream coins("system/coins.txt");
		coins >> Cash.name;
	coins.close();
	Cash.text.setString(Cash.name);
	menu.draw(Cash.text);

	menu.draw(Buttons[0].sprite);
	menu.draw(Buttons[1].sprite);
	menu.draw(Buttons[2].sprite);
	menu.draw(Buttons[3].sprite);
	menu.draw(Buttons[4].sprite);

	menu.display();
}

int main()
{
	srand(unsigned(time(NULL)));

	//ContextSettings settings;
	//settings.antialiasingLevel = 8;		

	menu.setPosition(Vector2i(50, 50));
	menu.setFramerateLimit(120);

	Image icon;
	
	icon.loadFromFile("./images/icon.png");

	
	musicmenu.openFromFile("music/" + to_string(rand() % 2 + 1) + ".ogg");
	musicmenu.setVolume(100);///////////////////////10
	//musicmenu.setLoop(true);
	musicmenu.play();

	inmenu();

	menu.setIcon(64, 64, icon.getPixelsPtr());

	Event event;

	while (menu.isOpen())
	{
		while (menu.pollEvent(event))
		{
			if (event.type == Event::Closed)			
				menu.close();
			
			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					Press(menu);

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					Release(menu);
		}

		if (!musicmenu.getStatus())
		{
			musicmenu.openFromFile("music/" + to_string(rand() % 2 + 1) + ".ogg");
			musicmenu.setVolume(100); //////////////////////////////////10
			musicmenu.play();
		}

		showmenu(menu);
	}

	return 0;
}
