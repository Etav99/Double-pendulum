#include "Slider.h"
#include <cmath>

void Slider::updateHandlePosition()
{
	handlePosition = xPos + ((value - minValue) / step) * handleWidth;
	handleBox.setPosition(handlePosition, yPos);
}

Slider::Slider(sf::RenderWindow& window, float xPos, float yPos, float value,
	float width, float height, float step, float minValue, float maxValue, DoublePendulum* dp, setter boundSetter) :
	window(window), xPos(xPos), yPos(yPos), value(value), width(width), height(height),
	step(step), minValue(minValue), maxValue(maxValue), dp(dp), boundSetter(boundSetter),
	handleWidth(width / ((maxValue - minValue) / (step)+1)), focused(false){

	boundingBox.setSize(sf::Vector2f(width, height));
	boundingBox.setPosition(xPos, yPos);

	handleBox.setSize(sf::Vector2f(handleWidth, height));
	updateHandlePosition();

	boundingBox.setFillColor(sf::Color::White);
	handleBox.setFillColor(sf::Color::Red);
}

void Slider::draw() {
	window.draw(boundingBox);
	window.draw(handleBox);
}

void Slider::setValue(float newValue){
	if (value != newValue) {
		value = newValue;
		updateHandlePosition();
		printf("\r%f", value);
		(dp->*boundSetter)(value);
	}

}

void Slider::onMouseMoved(int x, int y)
{
	if (boundingBox.getGlobalBounds().contains(x, y))
		focused = true;
	else
		focused = false;

	if (focused && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		float value = minValue + floor(((x - xPos) / handleWidth)) * step;
		setValue(value);
	}
}
