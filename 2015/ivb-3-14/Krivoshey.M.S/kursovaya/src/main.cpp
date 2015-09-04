#include "main.h"

#define SCREEN_SIZE vec2(820, 640)

GLFWwindow* window;
GLuint VertexArrayID;
GLuint backgroung_v;
Control* cursor;
Control* RootControl;
Laber *Fps;
shader* screen_space_effects;
GLuint FrameBuffer;
GLuint passTexture = -1;
char fps_text[100];
long last_time;
int fps;
float fps_pull;
bool enable_gray;

void
main(void)
{
	OnInit();

	RootControl = new Control();
	RootControl->name = _strdup("ROOT_CONTROL");
	RootControl->backColor = vec4(0, 0, 0, 1);
	RootControl->Scale(scaleValue(scaleValueType_window, 1, 1));

	cursor = new Control("Data\\textures\\cursors\\Default.dds");
	cursor->Scale(scaleValue(scaleValueType_absolute, 32, 32));

	Fps = new Laber();
	Fps->Move(scaleValue(scaleValueType_absolute, 3, 2));
	Fps->setFontSize(0.32f);
	RootControl->Attach(Fps);

	RootControl->Attach(new main_menu());

	do
	{
		OnUpdate();
	} while (glfwWindowShouldClose(window) == 0 && !main_menu::needExit);
	
	glfwTerminate();
}

void
OnInit()
{
	srand(time(NULL));

	new setting();

	if (!glfwInit()) {
		fprintf(stderr, "Failed to initialize GLFW\n");
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow((int)SCREEN_SIZE.x, (int)SCREEN_SIZE.y, "Viewport", NULL, NULL);
	if (window == NULL) {
		cout << "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n";
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	if (glewInit() != GLEW_OK) {
		cout << "Failed to initialize GLEW\n";
		return;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
	glClearColor(0.0f, 0.0f, 0.4f, 1.0f);

	for (int i = 0; i < mouse_button_reg; i++) {
		Control::mouse_btn_state[i] = 0;
		Control::mouse_btn_state_old[i] = 0;
	}

	Control::Init();
	Control::Default_shader = ShaderManager::load("gui");
	Particle::ParticleSystem::Init("particle");
	Laber::Init("Data\\fonts\\main.dds", "Data\\fonts\\main.table");

	screen_space_effects = ShaderManager::load("SSE");

	glGenFramebuffers(1, &FrameBuffer);
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void
OnRender()
{
	if (setting::instance->sse) {
		glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
		glClear(0x00000000);
		RenderUI();

		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClear(0x00000000);

		glUseProgram(screen_space_effects->ProgramID);
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, passTexture);
		glUniform1i(screen_space_effects->TextureID, 0);
		
		glUniform1i(screen_space_effects->diffuse_enableID, enable_gray ? 1 : 0);
		
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, Control::default_vx);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, Control::default_uv);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, 6);

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
	}
	else
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		RenderUI();
	}
	glfwSwapBuffers(window);
	glfwPollEvents();
}

void
RenderUI()
{
	glClear(0x00000000);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	RootControl->Render();
	cursor->Render();
}

void
OnUpdate()
{
	long t = clock();
	long delta = (t - last_time);
	Control::tickDelta = delta / 1000.0f;

	RootControl->cleaner();

	for (int i = 0; i < mouse_button_reg; i++) {
		Control::mouse_btn_state_old[i] = Control::mouse_btn_state[i];
		Control::mouse_btn_state[i] = glfwGetMouseButton(window, i) != 0;
	}

	for (int i = 0; i < KEY_REG; i++)
		Control::key_state[i] = glfwGetKey(window, i) == GLFW_PRESS;

	enable_gray = game::pause;

	int w, h;
	glfwGetWindowSize(window, &w, &h);
	if (w != Control::ScreenSize.x || h != Control::ScreenSize.y)
		OnResize(w, h);

	double x, y;
	glfwGetCursorPos(window, &x, &y);
	Control::mouse_pos_old = Control::mouse_pos;
	Control::mouse_pos = vec2((int)x, (int)y) / Control::ScreenSize;
	cursor->Move(scaleValue(scaleValueType_absolute, (int)x, (int)y));

	OnRender();

	fps_pull += Control::tickDelta;
	if (fps_pull >= 1)
	{
		if (setting::instance->show_fps) {
			int _fps = fps == 0 ? 1 : fps;
			sprintf(fps_text, "FPS:%i DrawCall:%i Particle count: %i",
				fps,
				(int)(Control::renderCount / _fps),
				(int)(Particle::ParticleSystem::particle_count / _fps));

			Fps->setText(fps_text);
			Fps->MoveToTop();
			Fps->visible = true;
		} else
			Fps->visible = false;
		fps = 0;
		fps_pull = 0;
		Particle::ParticleSystem::particle_count = 0;
		Control::renderCount = 0;
	}
	else
		fps++;
	last_time = t;
}

void
OnResize(int w, int h)
{
	glViewport(0, 0, w, h);
	Control::ScreenSize.x = (float)w;
	Control::ScreenSize.y = (float)h;
	RootControl->UpdateTransform();

	if (passTexture != -1)
		glDeleteTextures(1, &passTexture);

	passTexture = TextureManager::CreateEmpty(GL_RGBA8, GL_RGB, w, h);
	glBindFramebuffer(GL_FRAMEBUFFER, FrameBuffer);
	glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, passTexture, 0);
}