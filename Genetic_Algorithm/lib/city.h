
#ifndef CITY_H
#define CITY_H

class City {
	float m_x, m_y;
	int m_id;
	char m_name;
public:
	City(float x = 0.0, float y = 0.0, int id = 0, char name = 'A');
	~City();

	int getId() const { return m_id; }
	void setId(int id) { m_id = id; }

	char getName() const { return m_name; }
	void setName(char name) { m_name = name; }

	float getX() const { return m_x; }
	void setX(float x) { m_x = x; }

	float getY() const { return m_y; }
	void setY(float y) { m_y = y; }

	float distanceTo(const City & city);
};

#endif
