#include "DoublePendulum.h"

DoublePendulum::DoublePendulum(sf::RenderWindow& window, float m1, float m2, float pendulumWidth, float pendulum1Length, float pendulum2Length,
	float xPos, float yPos, float angle1, float angle2, float g) : pWidth(pendulumWidth), p1Length(pendulum1Length),
	p2Length(pendulum2Length), xPos(xPos - pendulumWidth / 2), yPos(yPos), window(window), p1Angle(angle1), p2Angle(angle2),
	p1AngleRad(angle1* PI / 180), p2AngleRad(angle2* PI / 180), g(g), m1(m1), m2(m2) {

	pendulum1.setSize(sf::Vector2f(pendulumWidth, pendulum1Length));
	pendulum2.setSize(sf::Vector2f(pendulumWidth, pendulum2Length));
	pendulum1.setFillColor(sf::Color::White);
	pendulum2.setFillColor(sf::Color::Red);
	pendulum1.setPosition(this->xPos, this->yPos);
	pendulum1.setRotation(angle1);
	pendulum2.setPosition(this->xPos - pendulum1Length * sin(p1AngleRad), this->yPos + pendulum1Length * cos(p1AngleRad));
	pendulum2.setRotation(angle2);
	p1AngularVelocity = p2AngularVelocity = 0;
}

void DoublePendulum::step(float dt) {

	float a = g * (2 * m1 + m2) * sin(p1AngleRad);
	float b = m2 * g * sin(p1AngleRad - 2 * p2AngleRad);
	float c = 2 * sin(p1AngleRad - p2AngleRad) * m2 * (p2AngularVelocity * p2AngularVelocity * p2Length + p1AngularVelocity * p1AngularVelocity * p1Length * cos(p1AngleRad - p2AngleRad));
	float d = p1Length * (2 * m1 + m2 - m2 * cos(2 * p1AngleRad - 2 * p2AngleRad));
	float e;

	p1AngularVelocity += ((-a - b - c) / d)*dt;

	a = 2 * sin(p1AngleRad - p2AngleRad);
	b = p1AngularVelocity * p1AngularVelocity * p1Length * (m1 + m2);
	c = g * (m1 + m2) * cos(p1AngleRad);
	d = p2AngularVelocity * p2AngularVelocity * p2Length * m2 * cos(p1AngleRad - p2AngleRad);
	e = p2Length * (2 * m1 + m2 - m2 * cos(2 * p1AngleRad - 2 * p2AngleRad));

	p2AngularVelocity += a*(b+c+d)/e * dt;

	p1AngleRad += p1AngularVelocity * dt;
	p2AngleRad += p2AngularVelocity * dt;

	p1Angle = double(p1AngleRad * 180) / PI;
	p2Angle = double(p2AngleRad * 180) / PI;


	pendulum1.setRotation(p1Angle);

	pendulum2.setPosition(this->xPos - p1Length * sin(p1AngleRad), this->yPos + p1Length * cos(p1AngleRad));
	pendulum2.setRotation(p2Angle);

}

void DoublePendulum::draw() {
	window.draw(pendulum1);
	window.draw(pendulum2);
}