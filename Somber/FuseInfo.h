class FuseInfo
{
public:
	float health = 100;
	float X;
	float Y;
	bool fuseState;
	sf::Texture object;
	sf::Sprite fuseBox;
	sf::RectangleShape fuseHealthBar;
	FuseInfo()
	{
		health = 100;
		object.loadFromFile("res/fuseClosed.png");
		fuseBox.setTexture(object);
		fuseBox.setScale(.1, .1);
		fuseState = 1;
	}
	~FuseInfo() {}

};