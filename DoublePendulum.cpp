#include "DoublePendulum.h"

DoublePendulum::DoublePendulum(sf::RenderWindow& window, float m1, float m2, float pendulumWidth, float pendulum1Length, float pendulum2Length,
	float xPos, float yPos, float angle1, float angle2, float g) : pWidth(pendulumWidth), p1Length(pendulum1Length),
	p2Length(pendulum2Length), xPos(xPos - pendulumWidth / 2), yPos(yPos), window(window), p1Angle(angle1), p2Angle(angle2),
	p1AngleRad(angle1* PI / 180), p2AngleRad(angle2* PI / 180), g(g), m1(m1), m2(m2) {

	pendulum1.setSize(sf::Vector2f(pendulumWidth, pendulum1Length));
	pendulum2.setSize(sf::Vector2f(pendulumWidth, pendulum2Length));
	pendulum1.setOrigin(pWidth / 2, 0);
	pendulum2.setOrigin(pWidth / 2, 0);
	pendulum1.setFillColor(sf::Color::White);
	pendulum2.setFillColor(sf::Color::Red);
	pendulum1.setPosition(this->xPos, this->yPos);
	pendulum1.setRotation(angle1);
	pendulum2.setOrigin(pWidth / 2, 0);
	pendulum2.setPosition(this->xPos - pendulum1Length * sin(p1AngleRad), this->yPos + pendulum1Length * cos(p1AngleRad));
	pendulum2.setRotation(angle2);
	p1AngularVelocity = p2AngularVelocity = 0;

	trailSize = 20;
	trail1On = trail2On = true;

}

void DoublePendulum::step(float dt) {

	float a = g * (2 * m1 + m2) * sin(p1AngleRad);
	float b = m2 * g * sin(p1AngleRad - 2 * p2AngleRad);
	float c = 2 * sin(p1AngleRad - p2AngleRad) * m2 * (p2AngularVelocity * p2AngularVelocity * p2Length + p1AngularVelocity * p1AngularVelocity * p1Length * cos(p1AngleRad - p2AngleRad));
	float d = p1Length * (2 * m1 + m2 - m2 * cos(2 * p1AngleRad - 2 * p2AngleRad));
	float e;

	p1AngularVelocity += ((-a - b - c) / d) * dt;

	a = 2 * sin(p1AngleRad - p2AngleRad);
	b = p1AngularVelocity * p1AngularVelocity * p1Length * (m1 + m2);
	c = g * (m1 + m2) * cos(p1AngleRad);
	d = p2AngularVelocity * p2AngularVelocity * p2Length * m2 * cos(p1AngleRad - p2AngleRad);
	e = p2Length * (2 * m1 + m2 - m2 * cos(2 * p1AngleRad - 2 * p2AngleRad));

	p2AngularVelocity += a * (b + c + d) / e * dt;

	p1AngleRad += p1AngularVelocity * dt;
	p2AngleRad += p2AngularVelocity * dt;

	p1Angle = double(p1AngleRad * 180) / PI;
	p2Angle = double(p2AngleRad * 180) / PI;


	pendulum1.setRotation(p1Angle);

	pendulum2.setPosition(this->xPos - p1Length * sin(p1AngleRad), this->yPos + p1Length * cos(p1AngleRad));
	pendulum2.setRotation(p2Angle);
	if (trail.size() > trailSize)
		for(int i = 0; i < trailSize - trail.size(); i++)
			trail.pop_back();
	if (trail2.size() > trailSize)
		for (int i = 0; i < trailSize - trail2.size(); i++)
			trail2.pop_back();

	if(trail1On)
		trail.push_front(pendulum2.getPosition());
	if(trail2On)
		trail2.push_front(pendulum2.getPosition() + sf::Vector2f(-p2Length * sin(p2AngleRad), p2Length * cos(p2AngleRad)));

}

void DoublePendulum::drawTrail(std::deque<sf::Vertex>& trail) {

	sf::Vertex line[4];
	sf::Vector2f direction, unitDirection, unitPerpendicular, offset;
	sf::Color color(255, 255, 255, 255);
	for (int i = 0; i < trail.size() - 1; i++) {
		color.a -= 255/trailSize;
		direction = trail[i + 1].position - trail[i].position;
		unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
		unitPerpendicular.x = -unitDirection.y;
		unitPerpendicular.y = unitDirection.x;
		offset = (6 / 2.f) * unitPerpendicular;
		if (i == 0) {
			line[0] = trail[i + 1].position + offset;
			line[1] = trail[i].position + offset;
			line[2] = trail[i].position - offset;
			line[3] = trail[i + 1].position - offset;
		}
		else {
			line[1] = line[0];
			line[2] = line[3];
			line[0] = trail[i + 1].position + offset;
			line[3] = trail[i + 1].position - offset;
		}
		line[0].color = color;
		line[1].color = color;
		line[2].color = color;
		line[3].color = color;
		window.draw(line, 4, sf::Quads);
	}
}

void DoublePendulum::draw() {
	if(trail1On)
		drawTrail(trail);
	if(trail2On)
		drawTrail(trail2);
	window.draw(pendulum1);
	window.draw(pendulum2);
}

void DoublePendulum::setM1(float x)
{
	m1 = x;
}

void DoublePendulum::setM2(float x)
{
	m2 = x;
}

void DoublePendulum::setG(float x)
{
	g = x;
}

void DoublePendulum::setTrailSize(float x)
{
	trailSize = x;
}
