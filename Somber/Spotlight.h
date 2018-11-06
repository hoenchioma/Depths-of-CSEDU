#define RADIUS_SPOTLIGHT 180
#define DIAMETER_SPOTLIGHT 360

class Spotlight
{
public:
	float x, y, dirX = 1, dirY = 1;
	sf::CircleShape circleSpot;

	Spotlight()
	{
		dirX = 1; dirY = 1;
		circleSpot.setRadius(RADIUS_SPOTLIGHT);
		circleSpot.setPointCount(100);
	}
	~Spotlight() {}
};