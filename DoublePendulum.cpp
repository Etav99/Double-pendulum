#include "DoublePendulum.h"

DoublePendulum::DoublePendulum(sf::RenderWindow& window, float pendulumWidth, float pendulum1Length, float pendulum2Length,
	float xPos, float yPos, float angle1, float angle2) : pendulumWidth(pendulumWidth), pendulum1Length(pendulum1Length),
	pendulum2Length(pendulum2Length), xPos(xPos), yPos(yPos), window(window), angle1(angle1), angle2(angle2),
	angle1R(angle1* PI / 180), angle2R(angle2* PI / 180) {

	pendulum1.setSize(sf::Vector2f(pendulumWidth, pendulum1Length));
	pendulum2.setSize(sf::Vector2f(pendulumWidth, pendulum2Length));
	pendulum1.setFillColor(sf::Color::White);
	pendulum2.setFillColor(sf::Color::Red);
	pendulum1.setPosition(xPos, yPos);
	pendulum1.setRotation(angle1);
	pendulum2.setPosition(xPos * cos(angle1R), (yPos + pendulum1Length) * sin(angle1R));
	//pendulum2.setRotation(angle2);
}

void DoublePendulum::step(float dt) {
	// TODO
}

void DoublePendulum::draw() {
	window.draw(pendulum1);
	window.draw(pendulum2);
}