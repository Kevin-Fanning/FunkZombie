/*
 * FZombie Game Engine
 * SpriteInfo Class
 * Kevin Fanning
 * 2013
*/
#pragma once

//This class holds info for sprites and is used internally by the renderer
struct SpriteInfo
{
	GLuint texID;		//The identifier of the texture this sprite uses
	int x, y, w, h;		//The position in space of the sprite and its size
	int sx, sy, sw, sh;	//The position on the sprite sheet and size on the sprite sheet
	int imgX, imgY;		//The image size
	float r, g, b;		//Color tint
	float rotation;		//How much to rotate in radians
	int rotCenterX, rotCenterY; //What to rotate around
	float depth;		//How deep to draw
	bool isText;		//Is this sprite text?

	SpriteInfo() : x(0), y(0), w(0), h(0), sx(0), sy(0), sw(0), sh(0),imgX(0), imgY(0), rotation(0.f), depth(0.f), r(0.f), g(0.f), b(0.f), rotCenterY(0), rotCenterX(0) {}

	SpriteInfo(GLuint _tex, int _x, int _y, int _w, int _h, int _imgX, 
		int _imgY, int _sx, int _sy, int _sw, int _sh, float _rotation, 
		float _depth, float _r, float _g, float _b, bool _isText)
			: texID(_tex), x(_x), y(_y), w(_w), h(_h), imgX(_imgX),
			imgY(_imgY), sx(_sx), sy(_sy), sw(_sw), sh(_sh), 
			rotation(_rotation), depth(_depth), r(_r), g(_g), b(_b),
			isText(_isText), rotCenterX(0), rotCenterY(0) {}

	void print(std::ostream &os)
	{
		os << "(" << texID << ", "<<x<<", "<<y<<", "<<r<<", "<<g<<", "<<b<< ")" << std::endl;
	}
};

