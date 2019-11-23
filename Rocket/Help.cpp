#include "Help.h"

using namespace std;
using namespace sf;

bool ExitH = false;

struct EH
{
	Image image;
	Texture texture;
	Sprite sprite;
	int select;
};

EH Exith;

void inhelp()
{
	extern struct information info[10];

	Exith.image.loadFromFile("images/back.bmp");
	Exith.image.createMaskFromColor(Color(255, 255, 255));
	Exith.texture.loadFromImage(Exith.image);
	Exith.sprite.setTexture(Exith.texture, true);
	Exith.sprite.setPosition(20, 20);
	Exith.select = false;

	info[0].name = "Help :";
	info[0].text.setString(info[0].name);
	info[0].text.setCharacterSize(50);
	info[0].text.setColor(Color(195, 195, 195));
	info[0].text.setPosition(310, 40);

	info[1].name = "Fly  ----------------  Upper arrow (^)";
	info[1].text.setString(info[1].name);
	info[1].text.setCharacterSize(30);
	info[1].text.setColor(Color(220, 220, 220));
	info[1].text.setPosition(100, 120);

	info[2].name = "Turn right  --------  Right arrow (>)";
	info[2].text.setString(info[2].name);
	info[2].text.setCharacterSize(30);
	info[2].text.setColor(Color(220, 220, 220));
	info[2].text.setPosition(100, 170);

	info[3].name = "Turn left  ----------  Left arrow (<)";
	info[3].text.setString(info[3].name);
	info[3].text.setCharacterSize(30);
	info[3].text.setColor(Color(220, 220, 220));
	info[3].text.setPosition(100, 220);

	info[4].name = "There are no brakes!";
	info[4].text.setString(info[4].name);
	info[4].text.setCharacterSize(30);
	info[4].text.setColor(Color(230, 230, 230));
	info[4].text.setPosition(205, 300);

	info[5].name = "To slow down fly in the opposite direction.";
	info[5].text.setString(info[5].name);
	info[5].text.setCharacterSize(30);
	info[5].text.setColor(Color(230, 230, 230));
	info[5].text.setPosition(50, 350);

	info[6].name = "Either touching the wall";
	info[6].text.setString(info[6].name);
	info[6].text.setCharacterSize(30);
	info[6].text.setColor(Color(240, 240, 240));
	info[6].text.setPosition(180, 430);

	info[7].name = "or running out of time";
	info[7].text.setString(info[7].name);
	info[7].text.setCharacterSize(30);
	info[7].text.setColor(Color(240, 240, 240));
	info[7].text.setPosition(200, 480);

	info[8].name = "restarts the level.";
	info[8].text.setString(info[8].name);
	info[8].text.setCharacterSize(30);
	info[8].text.setColor(Color(240, 240, 240));
	info[8].text.setPosition(240, 530);
}

void PressBackH(RenderWindow &help)
{
	Vector2i pixelPos = Mouse::getPosition(help);
	Vector2f pos = help.mapPixelToCoords(pixelPos);

	Exith.select = false;

	if (Exith.sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Exith.select = true;
	}
}

void ReleaseBackH(RenderWindow &help)
{
	Vector2i pixelPos = Mouse::getPosition(help);
	Vector2f pos = help.mapPixelToCoords(pixelPos);

	if (Exith.sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		if (Exith.select == true)
		{
			//level.close();
			ExitH = true;
		}
	}
}

void showhelp(RenderWindow &help)
{
	help.clear(Color(0, 0, 30));

	help.draw(Exith.sprite);

	extern struct information info[10];

	for (int i = 0; i < 10; i++)
		help.draw(info[i].text);

	help.display();
}

void HELP()
{
	extern RenderWindow menu;

	//level.setSize(Vector2u(wwidth, wheight));
	//level.setPosition(Vector2i(0, 0));
	//level.setFramerateLimit(120);	

	ExitH = false;

	inhelp();

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
					PressBackH(menu);									
				}

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
				{					
					ReleaseBackH(menu);
				}
		}

		/*if (!musiclevel.getStatus())
		{
		musiclevel.openFromFile("music/" + to_string(rand() % 2 + 1) + ".ogg");
		musiclevel.setVolume(2);
		musiclevel.play();
		}*/

		if (ExitH)
			break;		

		showhelp(menu);
	}
}
