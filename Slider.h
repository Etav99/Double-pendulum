#pragma once
#include <SFML/graphics.hpp>
#include "DoublePendulum.h"

typedef void (DoublePendulum::*setter)(float);

class Slider {
	sf::RenderWindow& window;

	float xPos, yPos;
	float value;
	float width, height;
	float step;
	float minValue, maxValue;

	float handlePosition, handlePositionStep, handleWidth;

	sf::RectangleShape boundingBox, handleBox;

	DoublePendulum* dp;
	setter boundSetter;

	bool focused;

	void updateHandlePosition();

public:
	Slider(sf::RenderWindow& window, float xPos, float yPos, float value,
		float width, float height, float step, float minValue, float maxValue,
		DoublePendulum* dp, setter);
	void draw();
	void setValue(float newValue);
	void onMouseMoved(int x, int y);
};