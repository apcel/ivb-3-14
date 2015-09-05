#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4244)
#pragma warning(disable: 4805)
#pragma warning(disable: 4407)
#pragma warning(disable: 4800)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <vector>
#include <queue>
#include <map>
#include <io.h>

#include "gl\glew.h"
#include "gl\glfw3.h"
#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtx\transform.hpp"

using namespace std;
using namespace glm;

#define KEY_REG 270
#define PI 3.14159265359f

#ifndef __INIT
	#define __INIT

	#include "setting.hpp"
	#include "scaleValue.hpp"
	#include "dds.hpp"
	#include "shader.hpp"
	#include "TextureManager.hpp"
	#include "utilit.hpp"

	#include "Control.hpp"
	#include "laber.hpp"
	#include "Button.hpp"
	#include "CheckBox.hpp"
	#include "Window.hpp"

	#include "particle.hpp"
	#include "ai.hpp"
	#include "unit.hpp"

	#include "dlg_YesNo.hpp"
	#include "main_menu.hpp"
	#include "help_menu.hpp"
	#include "pause_menu.hpp"
	#include "setting_menu.hpp"
	#include "game_end.hpp"
	#include "game.hpp"
	#include "level_editor.hpp"
#endif