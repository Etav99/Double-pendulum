#pragma once
#ifndef PI
#define PI 3.14159265358979323846
#endif
#include <SFML/graphics.hpp>
#include <cmath>
#include <deque>

class DoublePendulum {
	sf::RenderWindow& window;
	float g; // Gravitational acceleration
	sf::RectangleShape pendulum1, pendulum2; // Shape of pendulums
	float pWidth; // Width of both pendulum
	float p1Length, p2Length; // Length of pendulums
	float xPos, yPos; // Suspension point

	float m1, m2; //mass of pendulums
	float p1Angle, p2Angle; //Angles of pendulums in deegrees
	float p1AngleRad, p2AngleRad; //Angles of pendulums in radians

	float p1AngularVelocity, p2AngularVelocity;

	bool trail1On, trail2On;

	int trailSize;

	std::deque<sf::Vertex> trail;
	std::deque<sf::Vertex> trail2;


public:
	DoublePendulum(sf::RenderWindow& window, float m1, float m2, float pendulumWidth, float pendulum1Length, float pendulum2Length,
		float xPos, float yPos, float angle1, float angle2, float g);

	void step(float dt); // Calculate pendulum properties based on time step;
	void drawTrail(std::deque<sf::Vertex>& trail);
	void draw(); // Draw pendulum on window

	void setM1(float x);
	void setM2(float x);
	void setG(float x);
	void setTrailSize(float x);
};