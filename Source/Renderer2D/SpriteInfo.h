#pragma once
struct SpriteInfo
{
	GLuint texID;		//The identifier of the texture this sprite uses
	int x, y, w, h;		//The position in space of the sprite and its size
	int sx, sy, sw, sh;	//The position on the sprite sheet and size on the sprite sheet
	int imgX, imgY;		//The image size
	float r, g, b;
	bool isText;

	SpriteInfo() : x(0), y(0), w(0), h(0), sx(0), sy(0), sw(0), sh(0),imgX(0), imgY(0), r(0.f), g(0.f), b(0.f) {}

	SpriteInfo(GLuint _tex, int _x, int _y, int _w, int _h, int _imgX, int _imgY, int _sx, int _sy, int _sw, int _sh, float _r, float _g, float _b, bool _isText)
		: texID(_tex), x(_x), y(_y), w(_w), h(_h), imgX(_imgX), imgY(_imgY), sx(_sx), sy(_sy), sw(_sw), sh(_sh), r(_r), g(_g), b(_b), isText(_isText) {}

	void print(std::ostream &os)
	{
		os << "(" << texID << ", "<<x<<", "<<y<<", "<<r<<", "<<g<<", "<<b<< ")" << std::endl;
	}
};

