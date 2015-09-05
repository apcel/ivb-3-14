#include "Control.hpp"

vec2 Control::ScreenSize;
GLuint Control::default_uv;
GLuint Control::default_vx;
shader* Control::Default_shader;
map<string, Control*> Control::cache;
float Control::tickDelta;
bool Control::invertYRender = false;
bool Control::mouse_btn_state[mouse_button_reg];
bool Control::mouse_btn_state_old[mouse_button_reg];
bool Control::key_state[KEY_REG];
vec2 Control::mouse_pos;
vec2 Control::mouse_pos_old;
int  Control::renderCount = 0;

static const GLfloat plane_vertex_buff[] = {
	-1.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, -1.0f,

	-1.0f, 1.0f,
	1.0f, -1.0f,
	-1.0f, -1.0f
};
static const GLfloat plane_uv_buff[] = {
	0.0f, 0.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	0.0f, 0.0f,
	1.0f, 1.0f,
	0.0f, 1.0f,
};

Control::Control() : Control::Control("")
{
	backColor = vec4(0, 0, 0, 0);
}

Control::Control(string Texture) : Control::Control(Texture, default_uv)
{
}

Control::Control(string Texture, GLuint uv)
{
	angine = 0;
	uvbuffer = uv;
	texture = Texture == "" ? -1 : TextureManager::load(Texture)->uint;
	colorMult = vec4(1, 1, 1, 1);
	base = nullptr;
	name = "";
	sh = Default_shader;
	MVP = mat3(1.0f);
}

void Control::Init()
{
	glGenBuffers(1, &default_vx);
	glBindBuffer(GL_ARRAY_BUFFER, default_vx);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane_vertex_buff), plane_vertex_buff, GL_STATIC_DRAW);

	glGenBuffers(1, &default_uv);
	glBindBuffer(GL_ARRAY_BUFFER, default_uv);
	glBufferData(GL_ARRAY_BUFFER, sizeof(plane_uv_buff), plane_uv_buff, GL_STATIC_DRAW);
}

void Control::Render()
{
	if (!visible) return;

	bool _isMouseEnter = containt(bound, mouse_pos);
	if (_isMouseEnter != isMouseEnter) {
		isMouseEnter = _isMouseEnter;
		if (isMouseEnter)
			onMouseEnter(this);
		else
			onMouseLeave(this);
	}

	if (isMouseEnter) {
		for (int i = 0; i < mouse_button_reg; i++) {
			if (mouse_btn_state[i] != mouse_btn_state_old[i]) {
				if (mouse_btn_state[i])
					onMouseDown(this);
				else
					onMouseUp(this);
			}
		}
	}

	if (_rendable) {
		glUseProgram(sh->ProgramID);
		glUniformMatrix3fv(sh->TransformID, 1, GL_FALSE, &MVP[0][0]);

		if (texture != -1) {
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			glUniform1i(sh->TextureID, 0);
		}
		glUniform1i(sh->diffuse_enableID, texture == -1 ? 0 : 1);

		glUniform4f(sh->colorBackID, backColor.r, backColor.g, backColor.b, backColor.a);
		glUniform4f(sh->colorMultID, colorMult.r, colorMult.g, colorMult.b, colorMult.a);
		glUniform1i(sh->invertYID, invertYRender ? 1 : 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, default_vx);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		renderCount++;
	}

	for (int i = 0; i < controls.size(); i++)
		controls[i]->Render();
}

void
Control::Move(scaleValue point)
{
	pos = point;
	UpdateTransform(true);
}

void
Control::Scale(scaleValue transform)
{
	scale = transform;
	UpdateTransform(true);
}

void
Control::Rotate(float angine)
{
	this->angine = angine;
	UpdateTransform(true);
}

void
Control::Transform(scaleValue position, scaleValue scale)
{
	pos = position;
	this->scale = scale;
	UpdateTransform(true);
}

void
Control::Transform(scaleValue position, scaleValue scale, float angine)
{
	pos = position;
	this->scale = scale;
	this->angine = angine;
	UpdateTransform(true);
}

void
Control::UpdateTransform(bool updateChildren)
{
	vec2 nScale = scale.get(scaleValueType_window);
	vec2 nPos = getOffestPos(scaleValueType_window);

	bound = vec4(nPos, nPos + nScale);

	float cos = glm::cos(angine);
	float sin = glm::sin(angine);

	MVP[0][0] = nScale.x * cos;
	MVP[1][1] = nScale.y * cos;
	MVP[1][0] = nScale.x * sin;
	MVP[0][1] = nScale.y * (-sin);
	MVP[2][2] = 1;
	MVP[2][0] = nPos.x * 2 - (1 - nScale.x);
	MVP[2][1] = -(nPos.y * 2 - (1 - nScale.y));

	if (updateChildren) {
		for (auto i = controls.begin(); i != controls.end(); i++)
			(*i)->UpdateTransform(true);
	}
}

vec2
Control::getOffestPos(int type)
{
	vec2 p = pos.get(type);

	vec2 size;
	if (align_h != alignment_leftORtop || align_v != alignment_leftORtop) {
		if (base != nullptr)
			size = base->scale.get(type);
		else {
			if (type == scaleValueType_absolute)
				size = ScreenSize;
			else
				size = vec2(1, 1);
		}

		switch (align_h) {
		case alignment_rightRObuttom:
			p.x = size.x - p.x;
			break;
		case alignment_center:
			p.x = (size.x / 2) + p.x;
			break;
		}

		switch (align_v) {
		case alignment_rightRObuttom:
			p.y = size.y - p.y;
			break;
		case alignment_center:
			p.y = (size.x / 2) + p.y;
			break;
		}
	}

	if (base != nullptr)
		p += base->getOffestPos(type);
	return p;
}

void
Control::Attach(Control *control)
{
	controls.push_back(control);
	control->base = this;
	control->UpdateTransform(true);
}

void
Control::Detach(Control *control, bool destroy)
{
	for (auto i = controls.begin(); i != controls.end(); i++) {
		if (*i == control) {
			if (destroy)
				(*i)->die();

			controls.erase(i);
			return;
		}
	}
}

void
Control::MoveToTop()
{
	if (base == nullptr || base->controls.back() == this)
		return;

	int i = 0;
	for each (Control* var in base->controls) {
		if (var == this) break;
		i++;
	}

	int len = base->controls.size() - 1;
	for (; i < len; ++i)
		swap(base->controls[i + 1], base->controls[i]);
}

void
Control::MoveToBack()
{
	if (base == nullptr || base->controls.front() == this)
		return;

	int i = 0;
	for each (Control* var in base->controls) {
		if (var == this) break;
		i++;
	}

	for (; i > 0; --i)
		swap(base->controls[i - 1], base->controls[i]);
}

Control *
Control::Clone()
{
	bool isBTN = typeid(*this) == typeid(Button);
	bool isLaber = typeid(*this) == typeid(Laber);
	bool isChbox = typeid(*this) == typeid(CheckBox);

	Control *c;
	
	if (isLaber)
		c = new Laber();
	else if (isBTN)
		c = new Button();
	else if (isChbox)
		c = new CheckBox();
	else
		c = new Control();

	c->pos = pos;
	c->scale = scale;
	c->rot = rot;
	c->align_h = align_h;
	c->align_v = align_v;

	c->uvbuffer = uvbuffer;
	c->texture = texture;
	c->backColor = backColor;
	c->colorMult = colorMult;
	c->visible = visible;
	c->_rendable = _rendable;
	c->name = name;
	c->sh = sh;
	
	if (!isLaber && controls.size()) {
		Button * this_btn = NULL, *c_btn = NULL;
		CheckBox * this_chbox = NULL, *c_chbox = NULL;

		if (isBTN) {
			this_btn = dynamic_cast<Button*>(this);
			c_btn = dynamic_cast<Button*>(c);
		} else if (isChbox) {
			this_chbox = dynamic_cast<CheckBox*>(this);
			c_chbox = dynamic_cast<CheckBox*>(c);
		}

		for (auto i = controls.begin(); i != controls.end(); i++) {
			Control * clone = (*i)->Clone();
			c->controls.push_back(clone);
			clone->base = c;

			if (isBTN) {
				if (*i == this_btn->state_normal)
					c_btn->state_normal = clone;
				else if (*i == this_btn->state_down)
					c_btn->state_down = clone;
				else if (*i == this_btn->state_mouse)
					c_btn->state_mouse = clone;
			} else if (isChbox) {
				if (*i == this_chbox->state_off)
					c_chbox->Bind(dynamic_cast<Button*>(clone), false);
				else if (*i == this_chbox->state_on)
					c_chbox->Bind(dynamic_cast<Button*>(clone), true);
			}
		}
	}

	if (isLaber) {
		Laber * this_laber = dynamic_cast<Laber*>(this);
		Laber * c_laber = dynamic_cast<Laber*>(c);

		c_laber->setCenter(this_laber->isCenter());
		c_laber->setText(this_laber->getText());
		c_laber->setFontSize(this_laber->getFontSize());
	}
	
	return c;
}

#define GUI_MAX_LINE_COUNT 512
Control *
Control::loadFromFile(string name)
{
	for (auto i = cache.begin(); i != cache.end(); i++)
		if (name == i->first)
			return i->second->Clone();

	cout << "Load GUI in '" << name.c_str() << "'\n";
	char ** buff = new char*[GUI_MAX_LINE_COUNT];
	std::ifstream file(name.c_str());

	int i = 0;
	for (string line; getline(file, line); i++) {
		if (i == GUI_MAX_LINE_COUNT) {
			cout << "Error. This file have " << GUI_MAX_LINE_COUNT << " lines (limit=" << GUI_MAX_LINE_COUNT << ").";
			break;
		}
		buff[i] = new char[line.length()];
		strcpy(buff[i], line.c_str());
	}
	if (i == 0) {
		cout << "Error. File '" << name.c_str() << "' not found.\n";
		return nullptr;
	}

	Control * c = Control::loadFromLines(buff, 0, i);
	free(buff);

	cache.insert(make_pair(name, c));

	return c->Clone();
}

Control *
Control::loadFromLines(char ** data, int offest, int len)
{
	Control* c = nullptr;
	bool cut = false;
	int cut_start = 0, cut_len = 0, eCount = 0;
	int O = offest;
	int end = offest + len;
	bool flag = false;
	string a;

	while (O < end) {
		string str(data[O++]);

		int offest = 0;
		int len = 0;
		int l = str.length();

		for (; offest < l; offest++) {
			if (str[offest] != ' ' && str[offest] != '\t')
				break;
		}

		if (cut) {
			if (str[offest] == '{')
				eCount++;
			if (str[offest] == '}')
				eCount--;
			if (eCount == 0) {
				cut = false;
				Control * temp = loadFromLines(data, cut_start, cut_len);
				c->Attach(temp);
				if (flag) {
					if (a == "state_normal")
						dynamic_cast<Button*>(c)->state_normal = temp;
					else if (a == "state_mouse")
						dynamic_cast<Button*>(c)->state_mouse = temp;
					else if (a == "state_down")
						dynamic_cast<Button*>(c)->state_down = temp;
					else if (a == "state_off")
						dynamic_cast<CheckBox*>(c)->Bind(dynamic_cast<Button*>(temp), false);
					else if (a == "state_on")
						dynamic_cast<CheckBox*>(c)->Bind(dynamic_cast<Button*>(temp), true);
				}
			}
			else
				cut_len++;
			continue;
		}

		for (len = offest; len < l; len++){
			if (str[len] == ' ' || str[len] == '\t') {
				len -= offest;
				break;
			}
		}

		if (len>0) {
			string cmd = str.substr(offest, len);

			if (cmd == "control")
				c = new Control();
			else if (cmd == "laber")
				c = new Laber();
			else if (cmd == "button")
				c = new Button();
			else if (cmd == "checkbox")
				c = new CheckBox();

			for (offest += len; offest < l; offest++) {
				if (str[offest] != ' ' && str[offest] != '\t' && str[offest] != '=')
					break;
			}

			len = l - offest;
			if (len>0) {
				char * arg = new char[len + 1];
				a = str.substr(offest, len);
				strcpy(arg, a.c_str());
				
				if (cmd == "file")
					c = loadFromFile(arg);
				else if (cmd == "name")
					c->name = string(arg);
				else if (cmd == "position")
					c->Move(scaleValue::fromString(arg));
				else if (cmd == "scale")
					c->Scale(scaleValue::fromString(arg));
				else if (cmd == "backColor")
					c->backColor = vec4fromString(arg);
				else if (cmd == "multer")
					c->colorMult = vec4fromString(arg);
				else if (cmd == "texture")
					c->texture = TextureManager::load(arg)->uint;
				else if (cmd == "shader")
					c->sh = ShaderManager::load(arg);
				else if (cmd == "align")
					c->setAlign(vec2fromString(arg));
				else if (cmd == "rendable")
					c->_rendable = arg[0] == '1';
				else if (cmd == "visible")
					c->visible = arg[0] == '1';
				else if (cmd == "uv")
					c->uvbuffer = BuildUV(arg);

				else if (cmd == "text")
					dynamic_cast<Laber*>(c)->setText(arg);
				else if (cmd == "fontSize")
					dynamic_cast<Laber*>(c)->setFontSize((float)atof(arg));
				else if (cmd == "center")
					dynamic_cast<Laber*>(c)->setCenter(arg[0] == '1');
				
				delete[] arg;
			}

			if (cmd == "attach") {
				flag = len > 0;
				cut = true;
				cut_start = O;
				cut_len = 0;
				eCount = 0;
			}
		}
	}

	c->UpdateTransform();
	return c;
}

vector<Control*>
Control::getByName(string name)
{
	vector<Control*> r;

	if (this->name == name)
		r.push_back(this);

	for (auto i = controls.begin(); i != controls.end(); i++) {
		vector<Control*> j = (*i)->getByName(name);
		for (auto v = j.begin(); v != j.end(); v++)
			r.push_back(*v);
	}

	return r;
}

Control*
Control::getByNameFirst(string name)
{
	if (this->name == name)
		return this;

	Control * r;

	for (auto i = controls.begin(); i != controls.end(); i++) {
		r = (*i)->getByNameFirst(name);
		if (r != nullptr)
			return r;
	}

	return nullptr;
}

vec2
Control::getScale(int type)
{
	return scale.get(type);
}

vec2
Control::getAlign()
{
	return vec2(align_h, align_v);
}

void
Control::setAlign(int horizontal, int vertical)
{
	align_h = horizontal;
	align_v = vertical;
	UpdateTransform();
}

void
Control::setAlign(vec2 value)
{
	setAlign((int)value.x, (int)value.y);
}

vec2
Control::pixelToScreen(vec2 pos)
{
	return pos / Control::ScreenSize;
}

vec2
Control::screenToPixel(vec2 pos)
{
	return pos * Control::ScreenSize;
}

vec4 Control::getBound(int type)
{
	vec4 r = bound;
	if (type == scaleValueType_absolute)
		r *= vec4(Control::ScreenSize, Control::ScreenSize);

	return r;
}

vec2
Control::getPos(int type)
{
	return getOffestPos(type);
}

scaleValue
Control::getPosition()
{
	return pos;
}

void
Control::DetachAll(bool destroy)
{
	if (destroy) {
		for (auto i = controls.begin(); i != controls.end(); i++)
			(*i)->die();
	}
	controls.clear();
}

GLuint
Control::renderToTexture()
{
	GLuint texture = TextureManager::CreateEmpty(GL_RGBA8, GL_RGB, ScreenSize.x, ScreenSize.y);
	renderToTexture(texture);
	return texture;
}

void
Control::renderToTexture(GLuint id)
{
	GLuint FrameBuffer;
	glGenFramebuffers(1, &FrameBuffer);
	bool rendableState = _rendable;
	_rendable = true;

	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, id, 0);

	glClear(0);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	invertYRender = true;
	Render();

	invertYRender = false;
	_rendable = rendableState;
	glDeleteFramebuffers(1, &FrameBuffer);
}

Control::~Control()
{
	if (base != nullptr)
		base->Detach(this, false);

	DetachAll(true);
}

void
Control::cleaner()
{
	for (int i = 0; i < controls.size(); i++) {
		Control * c = controls[i];
		if (!needDestroy && c->needDestroy) {
			Detach(c, false);
			i--;
		}
		c->cleaner();
	}

	if (needDestroy)
		delete this;
}

void
Control::die()
{
	onDestroy(this);
	visible = false;
	_rendable = false;
	needDestroy = true;

	for (auto i = controls.begin(); i != controls.end(); i++)
		(*i)->die();
}