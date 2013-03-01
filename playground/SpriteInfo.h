#pragma once
struct SpriteInfo
{
	int texID;		//The identifier of the texture this sprite uses
	int x, y, w, h;		//The position in space of the sprite and its size
	int sx, sy, sw, sh;	//The position on the sprite sheet and size on the sprite sheet
	float r, g, b;

	SpriteInfo() : x(0), y(0), w(0), h(0), sx(0), sy(0), sw(0), sh(0), r(0.f), g(0.f), b(0.f) {}

	SpriteInfo(int _texID, int _x, int _y, int _w, int _h, int _sx, int _sy, int _sw, int _sh, float _r, float _g, float _b)
		: texID(_texID), x(_x), y(_y), w(_w), h(_h), sx(_sx), sy(_sy), sw(_sw), sh(_sh), r(_r), g(_g), b(_b) {}

	void print(std::ostream &os)
	{
		os << "(" << texID << ", "<<x<<", "<<y<<", "<<r<<", "<<g<<", "<<b<<std::endl;
	}
};

