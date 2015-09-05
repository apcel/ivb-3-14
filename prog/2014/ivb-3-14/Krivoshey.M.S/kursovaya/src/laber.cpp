#include "laber.hpp"

GLuint Laber::defaultTexture;
charInfo CharInfo[256];

Laber::Laber() : Control()
{
	texture = defaultTexture;
	Scale(scaleValue(scaleValueType_window, vec2(1, 1)));
	_rendable = false;
}

#define MEMORY_SIZE 12
void
Laber::Init(string texturePath, string font)
{
	float memory[MEMORY_SIZE];
	defaultTexture = TextureManager::load(texturePath)->uint;

	int temp, count, x, y, w, h;
	float tSize, x1 = 0, x2 = 0, y1 = 0, y2 = 0;
	unsigned char c;

	cout << "Load font table '" << font.c_str() << "'\n";
	ifstream f(font.c_str());
	f >> count;
	f >> temp; tSize = (float)temp;

	for (int i = 0; i < count; i++)	{
		f >> temp;
		c = (unsigned char)temp;

		CharInfo[c].c = c;
		f >> x;
		f >> y;
		f >> w;
		f >> h;

		x1 = (float)x / tSize;
		y1 = (float)y / tSize;
		x2 = (float)w / tSize + x1;
		y2 = (float)h / tSize + y1;

		f >> y;

		memory[0] = x1; memory[1] = y1;
		memory[2] = x2; memory[3] = y1;
		memory[4] = x2; memory[5] = y2;
		memory[6] = x1; memory[7] = y1;
		memory[8] = x2; memory[9] = y2;
		memory[10] = x1; memory[11] = y2;

		glGenBuffers(1, &CharInfo[c].uv);
		glBindBuffer(GL_ARRAY_BUFFER, CharInfo[c].uv);
		glBufferData(GL_ARRAY_BUFFER, MEMORY_SIZE * sizeof(float), memory, GL_STATIC_DRAW);

		CharInfo[c].scale = vec2(w, h);
		CharInfo[c].offestY = y;
	}

	f.close();
}

void Laber::setText(string text)
{
	this->text = text;
	for (int i = controls.size(); i > text.length(); i--)
		Detach(controls[i - 1], true);

	Control *c;
	for (int i = controls.size(); i < text.length(); i++) {
		c = new Control();
		c->texture = texture;
		c->Scale(scaleValue(scaleValueType_window, vec2(1, 1)));
		Attach(c);
	}

	for (int i = 0; i < text.length(); i++) {
		c = controls[i];
		c->name = string(" ");
		c->name[0] = text[i];
		c->uvbuffer = CharInfo[(unsigned char)text[i]].uv;
	}

	UpdateTransform(false);
}

string
Laber::getText()
{
	return text;
}

void
Laber::UpdateTransform(bool updateChildren)
{
	float y, x = 0;

	if (center && base != nullptr) {
		float len = 0;
		for (unsigned int i = 0; i < controls.size(); i++)
			len += CharInfo[(unsigned char)text[i]].scale.x * fontSize;

		vec4 b = base->getBound(scaleValueType_absolute);
		x = (b.z - b.x) / 2 - len / 2;
	}

	for (auto i = controls.begin(); i != controls.end(); i++) {
		unsigned char c = (*i)->name[0];
		if (c == ' ')
			x += 20 * fontSize;
		else {
			vec2 s = CharInfo[c].scale * fontSize;
			y = CharInfo[c].offestY * fontSize;
			(*i)->Transform(scaleValue(scaleValueType_absolute, vec2(x, y)), scaleValue(scaleValueType_absolute, s));
			(*i)->colorMult = colorMult;

			x += s.x;
		}
	}
}

void
Laber::setFontSize(float fontSize)
{
	this->fontSize = fontSize;
	UpdateTransform(false);
}

float
Laber::getFontSize()
{
	return fontSize;
}

void
Laber::setCenter(bool enable)
{
	center = enable;
	UpdateTransform(false);
}

bool
Laber::isCenter()
{
	return center;
}
