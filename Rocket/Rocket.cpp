#include "Rocket.h"
#include "Market.h"

using namespace sf;
using namespace std;

bool ExitR = false;
bool Starttime = false;
string Skin = "";

struct R
{
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y;
	int orent;
	vector < float > speed;
	vector < pair < float, float > > coords;
};

struct E
{
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
	bool select;
};

struct F
{
	string name;
	Image image;
	Texture texture;
	Sprite sprite;	
	float x, y;
};

struct Bo
{
	RectangleShape line;
	float x, y;
	float l, w;
};

struct T
{
	RectangleShape line;
	float x, y;
	float l, w;
};

struct M
{
	string name;
	Image image;
	Texture texture;
	Sprite sprite;
	float x, y;
};

T Timeleft;

F Finish;

E Exit;

R Rocket;

M Monetize[3];

vector < Bo > Border;

CircleShape help1;
CircleShape help2;
CircleShape help3;
CircleShape help4;
CircleShape help5;

void generate(RenderWindow &rocket)
{
	Border.clear();

	Rocket.name = Skin + ".bmp";
	Rocket.image.loadFromFile("images/" + Rocket.name);
	Rocket.image.createMaskFromColor(Color(255, 255, 255));
	Rocket.texture.loadFromImage(Rocket.image);
	Rocket.sprite.setTexture(Rocket.texture, true);	
	Rocket.orent = 45;	
	Rocket.sprite.setOrigin(22 / 2, 64 / 2);
	Rocket.speed.resize(361);
			
	Finish.name = "Finish.bmp";
	Finish.image.loadFromFile("images/" + Finish.name);
	Finish.image.createMaskFromColor(Color(255, 255, 255));
	Finish.texture.loadFromImage(Finish.image);
	Finish.sprite.setTexture(Finish.texture, true);	
	
	for (int i = 0; i < 3; i++)
	{
		Monetize[i].name = "Coin1.bmp"; 
		Monetize[i].image.loadFromFile("images/" + Monetize[i].name);
		Monetize[i].image.createMaskFromColor(Color(255, 255, 255));
		Monetize[i].texture.loadFromImage(Monetize[i].image);
		Monetize[i].sprite.setTexture(Monetize[i].texture, true);
	}

	extern int Levelselected;
	
	int SIZE;	
	int TIME;

	ifstream LVL("system/level" + to_string(Levelselected) + ".txt");

	LVL >> TIME;	

	LVL >> Rocket.x;
	LVL >> Rocket.y;

	Rocket.sprite.setPosition(Rocket.x, Rocket.y);
	Rocket.coords.push_back(make_pair(Rocket.x, Rocket.sprite.getGlobalBounds().top));	
	Rocket.coords.push_back(make_pair(Rocket.x, Rocket.y + (Rocket.y - Rocket.sprite.getGlobalBounds().top)));	

	LVL >> Finish.x;
	LVL >> Finish.y;	
	
	Finish.sprite.setPosition(Finish.x, Finish.y);

	for (int i = 0; i < 3; i++)
	{
		LVL >> Monetize[i].x >> Monetize[i].y;
		Monetize[i].sprite.setPosition(Monetize[i].x, Monetize[i].y);
	}
	
	LVL >> SIZE;

	Border.resize(SIZE);

	for (int i = 0; i < SIZE; i++)
	{		
		LVL >> Border[i].x;
		LVL >> Border[i].y;
		LVL >> Border[i].l;
		LVL >> Border[i].w;

		//cout << ' ' << Border[i].x << ' ' << Border[i].y << ' ' << Border[i].l << ' ' << Border[i].w;

		Border[i].line.setFillColor(Color(200, 200, 200));
		Border[i].line.setPosition(Border[i].x, Border[i].y);
		Border[i].line.setSize(Vector2f(Border[i].l, Border[i].w));
	}

	LVL.close();
}

void in()
{
	Exit.image.loadFromFile("images/back.bmp");
	Exit.image.createMaskFromColor(Color(255, 255, 255));
	Exit.texture.loadFromImage(Exit.image);
	Exit.sprite.setTexture(Exit.texture, true);
	Exit.sprite.setPosition(20, 20);	
	Exit.select = false;

	Timeleft.x = 250;
	Timeleft.y = 35;
	Timeleft.l = 480;
	Timeleft.w = 30;

	Timeleft.line.setFillColor(Color(200, 200, 200));
	Timeleft.line.setPosition(Timeleft.x, Timeleft.y);
	Timeleft.line.setSize(Vector2f(Timeleft.l, Timeleft.w));
}

void Fire(Sound &Firesound)
{
	Starttime = true;

	Rocket.name = Skin + "Fire.bmp";
	Rocket.image.loadFromFile("images/" + Rocket.name);
	Rocket.image.createMaskFromColor(Color(255, 255, 255));
	Rocket.texture.loadFromImage(Rocket.image);
	Rocket.sprite.setTexture(Rocket.texture, true);

	if (!Firesound.getStatus())
	{
		Firesound.play();
	}

	int orentation;

	orentation = Rocket.orent + 180;
	orentation = (360 + orentation) % 360;
	
	//Rocket.speed[Rocket.orent] += float(0.02);	

	for (int i = 0; i < Rocket.speed.size(); i++)
	{
		int LR;
		LR = min(abs(i - Rocket.orent), 360 - abs(i - Rocket.orent));

		if (LR < 90)
		{
			Rocket.speed[i] += 0.0002 * abs(cos(LR * 3.14159265 / 180));
		}
		if (LR > 90)
		{
			if (Rocket.speed[i] > 0.0001)
				Rocket.speed[i] -= 0.0001 * abs(cos(LR * 3.14159265 / 180));
			else
				Rocket.speed[i] = 0;
		}
		//cout << i << ' ' << LR << endl;
	}	
}

void Normal(Sound &Firesound)
{
	Rocket.name = Skin + ".bmp";
	Rocket.image.loadFromFile("images/" + Rocket.name);
	Rocket.image.createMaskFromColor(Color(255, 255, 255));
	Rocket.texture.loadFromImage(Rocket.image);
	Rocket.sprite.setTexture(Rocket.texture, true);

	if (Firesound.getStatus())
	{
		Firesound.stop();
	}
}

void PressBackR(RenderWindow &rocket)
{
	Vector2i pixelPos = Mouse::getPosition(rocket);
	Vector2f pos = rocket.mapPixelToCoords(pixelPos);

	Exit.select = false;

	if (Exit.sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		Exit.select = true;
	}
}

void ReleaseBackR(RenderWindow &rocket)
{
	Vector2i pixelPos = Mouse::getPosition(rocket);
	Vector2f pos = rocket.mapPixelToCoords(pixelPos);

	if (Exit.sprite.getGlobalBounds().contains(pos.x, pos.y))
	{
		if (Exit.select == true)
		{
			//rocket.close();
			Rocket.speed.clear();
			Rocket.coords.clear();
			Rocket.sprite.setRotation(0);
			ExitR = true;
		}
	}
}

void blim()
{
	for (int i = 0; i < 3; i++)
	{
		if (Monetize[i].name == "Coin1.bmp")
		{
			Monetize[i].name = "Coin2.bmp";		
		}

		else if (Monetize[i].name == "Coin2.bmp")
		{
			Monetize[i].name = "Coin3.bmp";			
		}

		else if (Monetize[i].name == "Coin3.bmp")
		{
			Monetize[i].name = "Coin4.bmp";
		}

		else if (Monetize[i].name == "Coin4.bmp")
		{
			Monetize[i].name = "Coin1.bmp";
		}

        if (Monetize[i].name != "")
        {
		    Monetize[i].image.loadFromFile("images/" + Monetize[i].name);
		    Monetize[i].image.createMaskFromColor(Color(255, 255, 255));
		    Monetize[i].texture.loadFromImage(Monetize[i].image);
		    Monetize[i].sprite.setTexture(Monetize[i].texture, true);
        }
	}
}

void checker()
{	
	int orentation;

	orentation = Rocket.orent;
	orentation = (360 + orentation) % 360;

	if (orentation <= 45 || orentation > 315)
	{
		//float radius = 33.8378;
		float radius = 32;
		float hord;
		float m;
		float n;

		float y1;
		float x1;

		if (orentation <= 45)
		{
			m = sin((45 - orentation) * 3.14159265 / 180) * radius;
			n = sqrt((radius * radius) - (m * m));

			x1 = m;
			y1 = n;

			Rocket.coords[0].first = Rocket.x - x1;
			Rocket.coords[0].second = Rocket.y - y1;
			
			Rocket.coords[1].first = 2 * Rocket.x - Rocket.coords[0].first;
			Rocket.coords[1].second = 2 * Rocket.y - Rocket.coords[0].second;
			
			//cout << Rocket.x - x1 << ' ' << Rocket.y - y1 << endl;
		}
		if (orentation > 315)
		{
			m = sin((45 + 360 - orentation) * 3.14159265 / 180) * radius;
			n = sqrt((radius * radius) - (m * m));

			x1 = n;
			y1 = m;

			Rocket.coords[0].first = Rocket.x - y1;
			Rocket.coords[0].second = Rocket.y - x1;

			Rocket.coords[1].first = 2 * Rocket.x - Rocket.coords[0].first;
			Rocket.coords[1].second = 2 * Rocket.y - Rocket.coords[0].second;

			//cout << Rocket.x - y1 << ' ' << Rocket.y - x1 << endl;
		}	
	}

	if (orentation > 45 && orentation <= 135)
	{
		//float radius = 33.8378;
		float radius = 32;
		float hord;
		float m;
		float n;

		float y1;
		float x1;

		if (orentation <= 90)
		{
			m = sin((orentation - 45) * 3.14159265 / 180) * radius;
			n = sqrt((radius * radius) - (m * m));

			x1 = m;
			y1 = n;

			Rocket.coords[0].first = Rocket.x + x1;
			Rocket.coords[0].second = Rocket.y - y1;

			Rocket.coords[1].first = 2 * Rocket.x - Rocket.coords[0].first;
			Rocket.coords[1].second = 2 * Rocket.y - Rocket.coords[0].second;

			//cout << Rocket.x + x1 << ' ' << Rocket.y - y1 << endl;
		}
		if (orentation > 90)
		{
			m = sin((orentation - 45) * 3.14159265 / 180) * radius;
			n = sqrt((radius * radius) - (m * m));

			x1 = n;
			y1 = m;

			Rocket.coords[0].first = Rocket.x + y1;
			Rocket.coords[0].second = Rocket.y - x1;

			Rocket.coords[1].first = 2 * Rocket.x - Rocket.coords[0].first;
			Rocket.coords[1].second = 2 * Rocket.y - Rocket.coords[0].second;

			//cout << Rocket.x + y1 << ' ' << Rocket.y - x1 << endl;
		}
	}

	if (orentation > 135 && orentation <= 225)
	{
		//float radius = 33.8378;
		float radius = 32;
		float hord;
		float m;
		float n;

		float y1;
		float x1;

		if (orentation <= 180)
		{
			m = sin((orentation - 45) * 3.14159265 / 180) * radius;
			n = sqrt((radius * radius) - (m * m));

			x1 = m;
			y1 = n;

			Rocket.coords[0].first = Rocket.x + x1;
			Rocket.coords[0].second = Rocket.y + y1;

			Rocket.coords[1].first = 2 * Rocket.x - Rocket.coords[0].first;
			Rocket.coords[1].second = 2 * Rocket.y - Rocket.coords[0].second;

			//cout << Rocket.x + x1 << ' ' << Rocket.y + y1 << endl;
		}
		if (orentation > 180)
		{
			m = sin((orentation - 45) * 3.14159265 / 180) * radius;
			n = sqrt((radius * radius) - (m * m));

			x1 = n;
			y1 = m;

			Rocket.coords[0].first = Rocket.x + y1;
			Rocket.coords[0].second = Rocket.y + x1;

			Rocket.coords[1].first = 2 * Rocket.x - Rocket.coords[0].first;
			Rocket.coords[1].second = 2 * Rocket.y - Rocket.coords[0].second;

			//cout << Rocket.x + y1 << ' ' << Rocket.y + x1 << endl;
		}
	}

	if (orentation > 225 && orentation <= 315)
	{
		//float radius = 33.8378;
		float radius = 32;
		float hord;
		float m;
		float n;

		float y1;
		float x1;

		if (orentation <= 270)
		{
			m = sin((45 + 360 - orentation) * 3.14159265 / 180) * radius;
			n = sqrt((radius * radius) - (m * m));

			x1 = m;
			y1 = n;

			Rocket.coords[0].first = Rocket.x - x1;
			Rocket.coords[0].second = Rocket.y + y1;

			Rocket.coords[1].first = 2 * Rocket.x - Rocket.coords[0].first;
			Rocket.coords[1].second = 2 * Rocket.y - Rocket.coords[0].second;

			//cout << Rocket.x - x1 << ' ' << Rocket.y + y1 << endl;
		}
		if (orentation > 270)
		{
			m = sin((45 + 360 - orentation) * 3.14159265 / 180) * radius;
			n = sqrt((radius * radius) - (m * m));

			x1 = n;
			y1 = m;

			Rocket.coords[0].first = Rocket.x - y1;
			Rocket.coords[0].second = Rocket.y + x1;

			Rocket.coords[1].first = 2 * Rocket.x - Rocket.coords[0].first;
			Rocket.coords[1].second = 2 * Rocket.y - Rocket.coords[0].second;

			//cout << Rocket.x - y1 << ' ' << Rocket.y + x1 << endl;
		}
	}

	Rocket.coords[1].first -= (Rocket.coords[1].first - Rocket.x) / 2;
	Rocket.coords[1].second -= (Rocket.coords[1].second - Rocket.y) / 2;

	extern int Levelselected;
	int SIZE;
	int TIME;

	ifstream LVL("system/level" + to_string(Levelselected) + ".txt");

	LVL >> TIME;

	int posx, posy, trash;
	LVL >> posx;
	LVL >> posy;	

	LVL >> trash;
	LVL >> trash;	

	vector < pair < int, int > > CCC;

	for (int i = 0; i < 3; i++)
	{
		int f, s;
		LVL >> f >> s;
		CCC.push_back(make_pair(f, s));
	}

	LVL >> SIZE;

	LVL.close();

	for (int i = 0; i < SIZE; i++)
	{		
		for (int j = 0; j < Rocket.coords.size(); j++)
		{
			bool resp = false;

			help1.setRadius(7);
			help1.setPosition((Rocket.coords[0].first + (Rocket.x + Rocket.coords[0].first) / 2) / 2 - 7,
							  (Rocket.coords[0].second + (Rocket.y + Rocket.coords[0].second) / 2) / 2 - 7);

			help1.setFillColor(Color(50, 50, 50));


			help2.setRadius(10);			
			help2.setPosition((Rocket.x + Rocket.coords[0].first) / 2 - 10,
							  (Rocket.y + Rocket.coords[0].second) / 2 - 10);

			help2.setFillColor(Color(50, 50, 50));


			help3.setRadius(10);
			help3.setPosition((Rocket.x + (Rocket.x + Rocket.coords[0].first) / 2) / 2 - 10,
				(Rocket.y + (Rocket.y + Rocket.coords[0].second) / 2) / 2 - 10);

			help3.setFillColor(Color(50, 50, 50));


			help4.setRadius(10);
			help4.setPosition(Rocket.x - 10, Rocket.y - 10);

			help4.setFillColor(Color(50, 50, 50));


			help5.setRadius(10);
			help5.setPosition((Rocket.coords[1].first + (Rocket.x + Rocket.coords[1].first) / 2) / 2 - 10,
				(Rocket.coords[1].second + (Rocket.y + Rocket.coords[1].second) / 2) / 2 - 10);

			help5.setFillColor(Color(50, 50, 50));
						
			if (Timeleft.l == 0)
			{				
				resp = true;
			}

			if (help1.getGlobalBounds().intersects(Border[i].line.getGlobalBounds()))
			{				
				resp = true;
			}

			if (help2.getGlobalBounds().intersects(Border[i].line.getGlobalBounds()))
			{
				resp = true;
			}

			if (help3.getGlobalBounds().intersects(Border[i].line.getGlobalBounds()))
			{
				resp = true;
			}
			
			if (help4.getGlobalBounds().intersects(Border[i].line.getGlobalBounds()))
			{
				resp = true;
			}

			if (help5.getGlobalBounds().intersects(Border[i].line.getGlobalBounds()))
			{
				resp = true;
			}

			if (resp)
			{
				Starttime = false;
				Timeleft.l = 480;
				Timeleft.line.setSize(Vector2f(Timeleft.l, Timeleft.w));	

				extern struct C Cash;
				ifstream coins("system/coins.txt");
				coins >> Cash.name;
				Cash.text.setString(Cash.name);				

				for (int i = 0; i < 3; i++)
				{
					Monetize[i].name = "Coin1.bmp";
					Monetize[i].sprite.setPosition(CCC[i].first, CCC[i].second);
				}

				Rocket.speed.clear();
				Rocket.coords.clear();
				Rocket.sprite.setRotation(0);
				Rocket.x = posx;
				Rocket.y = posy;
				Rocket.orent = 45;
				Rocket.sprite.setPosition(Rocket.x, Rocket.y);
				Rocket.sprite.setOrigin(22 / 2, 64 / 2);
				Rocket.speed.resize(361);
				Rocket.coords.resize(2);
			}
		}
	}
}

void collect()
{
	extern struct C Cash;

	bool col = false;

	for (int i = 0; i < 3; i++)
	{
		if (help1.getGlobalBounds().intersects(Monetize[i].sprite.getGlobalBounds()))
		{
			col = true;
		}

		if (help2.getGlobalBounds().intersects(Monetize[i].sprite.getGlobalBounds()))
		{
			col = true;
		}

		if (help3.getGlobalBounds().intersects(Monetize[i].sprite.getGlobalBounds()))
		{
			col = true;
		}

		if (help4.getGlobalBounds().intersects(Monetize[i].sprite.getGlobalBounds()))
		{
			col = true;
		}

		if (help5.getGlobalBounds().intersects(Monetize[i].sprite.getGlobalBounds()))
		{
			col = true;
		}

		if (col)
		{
			col = false;
			Monetize[i].name = "";
			Monetize[i].sprite.setPosition(-100, -100);

			int C;
			
			C = stoi(Cash.name);

			C++;

			Cash.name = to_string(C);

			Cash.text.setString(Cash.name);			
		}
	}
}

void restart()
{
	extern int Levelselected;
	int SIZE;
	int TIME;

	ifstream LVL("system/level" + to_string(Levelselected) + ".txt");

	LVL >> TIME;

	int posx, posy, trash;
	LVL >> posx;
	LVL >> posy;

	LVL >> trash;
	LVL >> trash;

	vector < pair < int, int > > CCC;

	for (int i = 0; i < 3; i++)
	{
		int f, s;
		LVL >> f >> s;
		CCC.push_back(make_pair(f, s));
	}

	LVL >> SIZE;

	LVL.close();


	Starttime = false;
	Timeleft.l = 480;
	Timeleft.line.setSize(Vector2f(Timeleft.l, Timeleft.w));

	extern struct C Cash;
	ifstream coins("system/coins.txt");
	coins >> Cash.name;
	Cash.text.setString(Cash.name);

	for (int i = 0; i < 3; i++)
	{
		Monetize[i].name = "Coin1.bmp";
		Monetize[i].sprite.setPosition(CCC[i].first, CCC[i].second);
	}

	Rocket.speed.clear();
	Rocket.coords.clear();
	Rocket.sprite.setRotation(0);
	Rocket.x = posx;
	Rocket.y = posy;
	Rocket.orent = 45;
	Rocket.sprite.setPosition(Rocket.x, Rocket.y);
	Rocket.sprite.setOrigin(22 / 2, 64 / 2);
	Rocket.speed.resize(361);
	Rocket.coords.resize(2);
}

void finish(RenderWindow &rocket)
{
	bool f = true;
	for (int i = 0; i < Rocket.coords.size(); i++)
	{
		if (!Finish.sprite.getGlobalBounds().contains(Rocket.coords[i].first, Rocket.coords[i].second))
		{
			f = false;
			break;
		}
	}	
		
	if (f)
	{
		//rocket.close();		
		Rocket.speed.clear();
		Rocket.coords.clear();
		Rocket.sprite.setRotation(0);
		ExitR = true;

		set < string > mem;
		string s = "";

		ifstream COMi("system/complete.txt");
		
		while (COMi >> s)
		{
			mem.insert(s);
			s = "";
		}

		COMi.trunc;
		
		COMi.close();

		ofstream COMo("system/complete.txt");

		extern int Levelselected;
		
		mem.insert("Level" + to_string(Levelselected));		

		for (set < string >::iterator it = mem.begin(); it != mem.end(); it++)
			COMo << *it << endl;

		COMo.close();		
		
		extern struct C Cash;

		ofstream coinss("system/coins.txt");

		coinss.trunc;

		coinss << Cash.name;

		Cash.text.setString(Cash.name);
		coinss.close();		
	}
}

void showrocket(RenderWindow &rocket)
{
	rocket.clear(Color(20, 20, 20));

	for (int i = 0; i < 3; i++)
	{
		if (Monetize[i].name != "")
			rocket.draw(Monetize[i].sprite);
	}
		

	rocket.draw(Finish.sprite);

	rocket.draw(Rocket.sprite);	

	rocket.draw(Exit.sprite);

	extern struct C Cash;

	//ifstream coins("system/coins.txt");
	//coins >> Cash.name;
	//coins.close();
	//Cash.text.setString(Cash.name);
	rocket.draw(Cash.text);	

	extern int Levelselected;
	int TIME;	

	ifstream LVL("system/level" + to_string(Levelselected) + ".txt");

	LVL >> TIME;

	LVL.close();

	if (Starttime)
	{
		if (Timeleft.l > 4)
			Timeleft.l -= 4 / float(TIME);
		else
			Timeleft.l = 0;

		Timeleft.line.setSize(Vector2f(Timeleft.l, Timeleft.w));
	}	

	rocket.draw(Timeleft.line);

	for (int i = 0; i < Border.size(); i++)
	{
		rocket.draw(Border[i].line);
	}	

	//rocket.draw(help1);
	//rocket.draw(help2);
	//rocket.draw(help3);
	//rocket.draw(help4);
	//rocket.draw(help5);

	rocket.display();
}

void ROCKET()
{
	srand(unsigned(time(NULL)));

	//ContextSettings settings;
	//settings.antialiasingLevel = 8;
	
	extern RenderWindow menu;

	//RenderWindow rocket(VideoMode(800, 600), "Rocket_1.0", Style::None, settings);
	//rocket.setSize(Vector2u(1920, 1080));
	//rocket.setPosition(Vector2i(0, 0));
	//rocket.setFramerateLimit(120);

	ifstream SKIN("system/skin.txt");
		SKIN >> Skin;
	SKIN.close();

	ExitR = false;	
	Starttime = false;

	Clock clock;
	Time shine;

	SoundBuffer buffer;
	buffer.loadFromFile("sounds/fire.ogg");
	Sound Firesound;
	Firesound.setBuffer(buffer);
	Firesound.setVolume(20);

	Music musicrocket;
	musicrocket.openFromFile("music/" + to_string(rand() % 4 + 3) + ".ogg");
	musicrocket.setVolume(50);
	//musicrocket.setLoop(true);
	musicrocket.play();

	in();
	generate(menu);

	Event event;
	while (menu.isOpen())
	{
		while (menu.pollEvent(event))
		{
			if (event.type == Event::Closed)
				menu.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == 17)
				{
					restart();
				}

			if (event.type == Event::KeyPressed)
				if (event.key.code == 73)
				{
					Fire(Firesound);
				}

			if (event.type == Event::KeyReleased)
				if (event.key.code == 73)
				{
					Normal(Firesound);
				}

			if (event.type == Event::KeyPressed)
				if (event.key.code == 71)
				{					
					Rocket.orent -= 3;
					Rocket.orent = (360 + Rocket.orent) % 360;					
					Rocket.sprite.setRotation(Rocket.sprite.getRotation() - 3);
				}

			if (event.type == Event::KeyPressed)
				if (event.key.code == 72)
				{	
					Rocket.orent += 3;
					Rocket.orent = (360 + Rocket.orent) % 360;			
					Rocket.sprite.setRotation(Rocket.sprite.getRotation() + 3);
				}

			if (event.type == Event::KeyPressed)
				if (event.key.code != 73)
				{
					Rocket.name = Skin + ".bmp";
					Rocket.image.loadFromFile("images/" + Rocket.name);
					Rocket.image.createMaskFromColor(Color(255, 255, 255));
					Rocket.texture.loadFromImage(Rocket.image);
					Rocket.sprite.setTexture(Rocket.texture, true);
				}

			if (event.type == Event::MouseButtonPressed)
				if (event.key.code == Mouse::Left)
					PressBackR(menu);

			if (event.type == Event::MouseButtonReleased)
				if (event.key.code == Mouse::Left)
					ReleaseBackR(menu);
		}

		////////////////////////////////////////////////////////////////
		for (int i = 0; i < Rocket.speed.size(); i++)
		{
			if (Rocket.speed[i] > 0.000002)
				Rocket.speed[i] -= float(0.000002);
			else if (Rocket.speed[i] > 0)
				Rocket.speed[i] = 0;
		}
		////////////////////////////////////////////////////////////////

		float movex = 0;
		float movey = 0;

		for (int i = 0; i < Rocket.speed.size(); i++)
		{
			if (Rocket.speed[i] != 0)
			{
				float s = sin((i + 45) * 3.14159265 / 180);
				float c = cos((i + 45) * 3.14159265 / 180);
				
				if (i <= 45 || i > 315)
				{
					movex -= abs(Rocket.speed[i] * c);
					movey -= abs(Rocket.speed[i] * s);
				}

				if (i > 45 && i <= 135)
				{
					movex += abs(Rocket.speed[i] * c);
					movey -= abs(Rocket.speed[i] * s);
				}

				if (i > 135 && i <= 225)
				{
					movex += abs(Rocket.speed[i] * c);
					movey += abs(Rocket.speed[i] * s);
				}

				if (i > 225 && i <= 315)
				{
					movex -= abs(Rocket.speed[i] * c);
					movey += abs(Rocket.speed[i] * s);
				}
			}
		}

		if (Rocket.x + movex < 10 || Rocket.x + movex > 790)
			rotate(Rocket.speed.begin(), Rocket.speed.begin() + 180, Rocket.speed.end());

		if (Rocket.y + movey < 10 || Rocket.y + movey > 590)
			rotate(Rocket.speed.begin(), Rocket.speed.begin() + 180, Rocket.speed.end());

		if (Rocket.x + movex > 10 && Rocket.x + movex < 790)
		{		
			Rocket.x += movex;
		}
	
		if (Rocket.y + movey > 10 && Rocket.y + movey < 590)
		{	
			Rocket.y += movey;
		}
		
		Rocket.sprite.setPosition(Rocket.x, Rocket.y);

		//cout << Rocket.orent << endl;

		/*for (int i = 0; i < Rocket.speed.size(); i++)
			if (Rocket.speed[i] != 0)
			cout << i << ' ' <<Rocket.speed[i] << endl;
		cout << endl << endl;*/

		if (!musicrocket.getStatus())
		{
			musicrocket.openFromFile("music/" + to_string(rand() % 4 + 3) + ".ogg");
			musicrocket.setVolume(5);
			musicrocket.play();
		}

		if (ExitR)
			break;		

		checker();

		collect();

		finish(menu);

		shine = clock.getElapsedTime();
		if (shine.asMilliseconds() > 150)
		{
			clock.restart();
			blim();			
		}

		showrocket(menu);
	}
}
