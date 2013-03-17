#pragma once

struct Color
{
public:
	Color(float _r, float _g, float _b, float _a)
		: r(_r), g(_g), b(_b), a(_a)
	{

	}
	float r, g, b, a;

	static const Color White;
	static const Color Red;
	static const Color Blue;
	static const Color Green;
	static const Color Cyan;
	static const Color Magenta;
	static const Color Yellow;
	static const Color Gray65;
	static const Color Black;
	static const Color Gray35;
};

