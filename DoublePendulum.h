#pragma once
#ifndef PI
	#define PI 3.14159265358979323846
#endif
#include <SFML/graphics.hpp>
#include <cmath>

class DoublePendulum {
	sf::RenderWindow& window;

	static float g; // Gravitational acceleration
	sf::RectangleShape pendulum1, pendulum2; // Shape of pendulums
	float pendulumWidth; // Width of both pendulum
	float pendulum1Length, pendulum2Length; // Length of pendulums
	float xPos, yPos; // Suspension point
	float angle1, angle2; //Angle of pendulums in deegrees
	float angle1R, angle2R; //Angle of pendulums in radians

public:
	DoublePendulum(sf::RenderWindow& window, float pendulumWidth, float pendulum1Length, float pendulum2Length,
		float xPos, float yPos, float angle1, float angle2);

	void step(float dt); // Calculate pendulum properties based on time step;
	void draw(); // Draw pendulum on window
};