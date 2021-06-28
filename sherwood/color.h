#pragma once
#include <SFML/Graphics.hpp>
#include "types.h"

struct Colors {
	const Color red =		Color(252, 12, 12);
	const Color pink =		Color(255, 12, 132);
	const Color darkGreen = Color(30, 150, 30);
	const Color green =		Color(50, 200, 50);
	const Color lightGreen = Color(70, 255, 70);
	const Color blue =		Color(0, 17, 255);
	const Color lightBlue = Color(50, 129, 255);
	const Color black =		Color::Black;
	const Color purple =	Color(204, 0, 255);
	const Color teal =		Color(0, 212, 255);
	const Color orange =	Color(255, 159, 0);
	const Color white =		Color::White;
	const Color yellow =	Color(255, 255, 12);
	const Color darkGrey =	Color(90, 90, 90);
	const Color lightGrey = Color(150, 150, 150);
	const Color transparent = Color::Transparent;
	const Color brown =		Color(150, 82, 8);
};

extern const Colors colors;