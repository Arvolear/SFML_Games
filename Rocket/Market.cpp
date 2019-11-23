#include "Market.h"

using namespace std;
using namespace sf;

bool ExitM = false;

struct E
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

S Select;

E Elements[30];

void inmarket(RenderWindow &market, int COINS)
{	
	Elements[0].image.loadFromFile("images/back.bmp");
	Elements[0].image.createMaskFromColor(Color(255, 255, 255));
	Elements[0].texture.loadFromImage(Elements[0].image);
	Elements[0].sprite.setTexture(Elements[0].texture, true);
	Elements[0].sprite.setPosition(20, 20);
	Elements[0].select = false;

	Select.image.loadFromFile("images/Selected.bmp");
	Select.image.createMaskFromColor(Color(255, 255, 255));
	Select.texture.loadFromImage(Select.image);
	Select.sprite.setTexture(Select.texture, true);

	int l = 0;

	for (int i = 1; i < 15; i++)
	{
		if (COINS < i * i)
		{
			Elements[i].name = "Locked.bmp";
			Elements[i].image.loadFromFile("images/" + Elements[i].name);
			Elements[i].image.createMaskFromColor(Color(255, 255, 255));
			Elements[i].texture.loadFromImage(Elements[i].image);
			Elements[i].sprite.setTexture(Elements[i].texture, true);
			Elements[i].sprite.setScale(1, 1);

			Elements[i].sprite.setPosition(50 + (i % 5) * 150, 70 + (i / 5) * 180);
			Elements[i].select = false;
		}

		else
		{
			Elements[i].name = "Rocket" + to_string(i) + ".bmp";
			Elements[i].image.loadFromFile("images/" + Elements[i].name);
			Elements[i].image.createMaskFromColor(Color(255, 255, 255));
			Elements[i].texture.loadFromImage(Elements[i].image);
			Elements[i].sprite.setTexture(Elements[i].texture, true);
			Elements[i].sprite.setScale(2, 2);

			Elements[i].sprite.setPosition(80 + (i % 5) * 150, 70 + (i / 5) * 180);
			Elements[i].select = false;
		}		
	}

	string choose = "";
	ifstream SKIN("system/skin.txt");
		SKIN >> choose;	
	SKIN.close();

	for (int i = 1; i < 15; i++)
	{
		if (Elements[i].name == choose + ".bmp")
		{
			Elements[i].select = true;
			break;
		}
	}
}

void PressBackM(RenderWindow &market)
{
	Vector2i pixelPos = Mouse::getPosition(market);
	Vector2f pos = market.mapPixelToCoords(pixelPos);

	Elements[0].select = false;

	if (Elements[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Elements[0].select = true;
	}
}

void ReleaseBackM(RenderWindow &market)
{
	Vector2i pixelPos = Mouse::getPosition(market);
	Vector2f pos = market.mapPixelToCoords(pixelPos);

	if (Elements[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		if (Elements[0].select == true)
		{
			//market.close();
			ExitM = true;
		}
	}
}

void selectskin(RenderWindow &market)
{
	Vector2i pixelPos = Mouse::getPosition(market);
	Vector2f pos = market.mapPixelToCoords(pixelPos);

	int save = 0;

	for (int i = 1; i < 15; i++)
	{
		if (Elements[i].sprite.getGlobalBounds().contains(pos.x, pos.y))
		{
			if (Elements[i].name != "Locked.bmp")
			{
				ofstream SKIN("system/skin.txt");
					SKIN.trunc;
					SKIN << "Rocket" + to_string(i);					
				SKIN.close();
			
				Elements[i].select = true;
				save = i;
				break;
			}
		}
	}

	if (save == 0)
	{
		if (!Elements[0].sprite.getGlobalBounds().contains(pos.x, pos.y))
		{
			ofstream SKIN("system/skin.txt");
				SKIN.trunc;
				SKIN << "RocketStock";
			SKIN.close();
		}
	}

	for (int i = 1; i < 15; i++)
	{
		if (i != save)
		{
			Elements[i].select = false;
		}
	}
}

void showmarket(RenderWindow &market)
{
	market.clear(Color(5, 5, 25));

	for (int i = 0; i < 15; i++)
		market.draw(Elements[i].sprite);	

	market.draw(Elements[0].sprite);
		
	for (int i = 1; i < 15; i++)
	{
		if (Elements[i].select == true)
		{
			Select.sprite.setPosition(35 + (i % 5) * 150, 55 + (i / 5) * 180);
			market.draw(Select.sprite);
		}
	}

	extern struct C Cash;

	ifstream coins("system/coins.txt");
	coins >> Cash.name;
	coins.close();
	Cash.text.setString(Cash.name);
	market.draw(Cash.text);

	market.display();
}

void MARKET()
{
	//ContextSettings settings;
	//settings.antialiasingLevel = 8;

	//RenderWindow market(VideoMode(800, 600), "Market", Style::None, settings);
	ExitM = false;

	extern RenderWindow menu;

	//menu.setSize(Vector2u(wwidth, wheight));
	//market.setPosition(Vector2i(0, 0));
	//market.setFramerateLimit(120);

	Event event;

	int COINS = 0;
	ifstream coins("system/coins.txt");
	coins >> COINS;
	coins.close();

	inmarket(menu, COINS);

	while (menu.isOpen())
	{
		while (menu.pollEvent(event))
		{
			if (event.type == Event::Closed)
				menu.close();

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
				{
					PressBackM(menu);
					selectskin(menu);
				}
					
			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					ReleaseBackM(menu);					
		}

		if (ExitM)
			break;

		showmarket(menu);
	}
}