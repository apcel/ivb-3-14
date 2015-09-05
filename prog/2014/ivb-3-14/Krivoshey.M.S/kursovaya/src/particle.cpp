#include "particle.hpp"

shader * Particle::ParticleSystem::sh;
int Particle::ParticleSystem::particle_count = 0;

void
Particle::ParticleSystem::Init(string shader)
{
	sh = ShaderManager::load(shader);
}

#define vertex_buff_size 4
#define vertex_buff_count 6
#define vertex_buff_len (vertex_buff_size*vertex_buff_count)

void
Particle::ParticleSystem::Render()
{
	int offest = 0;
	Particle* p;
	for (int n = 0; n < emitters.size(); n++) {
		Emitter* em = emitters[n];
		for (int i = 0; i < em->count && em->total <= em->limit; i++) {
			for (; offest < particles.size(); offest++) {
				if (particles[offest].life <= 0) {
					p = &particles[offest];
					goto end;
				}
			}
			particles.push_back(Particle());
			p = &particles[offest++];
		end:
			em->operator()(p);
		}
	}

	float* vertex_buff = new float[particles.size()*vertex_buff_len];
	int count_real = 0;
	vec2 position;

	for (int i = 0; i<particles.size(); i++) {
		p = &particles[i];
		p->life -= tickDelta;

		if (p->life > 0 && p->color_alpha > 0 && p->scale.x > 0 && p->scale.y > 0) {
			for (int n = 0; n < affectors.size(); n++)
				affectors[n]->operator()(p);

			p->position += tickDelta * p->dir;
			float cos = glm::cos(p->rotation);
			float sin = glm::sin(p->rotation);

			position.x = p->position.x*2 - 1.0f;
			position.y = -(p->position.y*2 - 1.0f);

			mat3 A;
			A[0][0] = p->scale.x * cos;		A[0][1] = p->scale.x * -sin;			A[0][2] = 0;
			A[1][0] = p->scale.x * sin;		A[1][1] = p->scale.y * cos;				A[1][2] = 0;
			A[2][0] = position.x;			A[2][1] = position.y;					A[2][2] = 1;


			vec3 tl = A*vec3(-1.0f,	1.0f, 1),
				 tr = A*vec3(1.0f,	1.0f, 1),
				 br = A*vec3(1.0f, -1.0f, 1),
				 bl = A*vec3(-1.0f,-1.0f, 1);

			vertex_buff[count_real++] = tl.x; vertex_buff[count_real++] = tl.y; vertex_buff[count_real++] = 0; vertex_buff[count_real++] = p->color_alpha;
			vertex_buff[count_real++] = tr.x; vertex_buff[count_real++] = tr.y; vertex_buff[count_real++] = 1; vertex_buff[count_real++] = p->color_alpha;
			vertex_buff[count_real++] = br.x; vertex_buff[count_real++] = br.y; vertex_buff[count_real++] = 2; vertex_buff[count_real++] = p->color_alpha;

			vertex_buff[count_real++] = tl.x; vertex_buff[count_real++] = tl.y; vertex_buff[count_real++] = 0; vertex_buff[count_real++] = p->color_alpha;
			vertex_buff[count_real++] = br.x; vertex_buff[count_real++] = br.y; vertex_buff[count_real++] = 2; vertex_buff[count_real++] = p->color_alpha;
			vertex_buff[count_real++] = bl.x; vertex_buff[count_real++] = bl.y; vertex_buff[count_real++] = 3; vertex_buff[count_real++] = p->color_alpha;
		} else {
			p->life = 0;
			if (p->owner != nullptr)
				p->owner->total--;
		}
	}

	if (count_real) {
		GLuint geometry;
		glGenBuffers(1, &geometry);
		glBindBuffer(GL_ARRAY_BUFFER, geometry);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)*count_real, vertex_buff, GL_STATIC_DRAW);

		glUseProgram(sh->ProgramID);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
		glUniform1i(sh->TextureID, 0);

		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, geometry);
		glVertexAttribPointer(0, vertex_buff_size, GL_FLOAT, GL_FALSE, 0, (void*)0);

		glDrawArrays(GL_TRIANGLES, 0, count_real / vertex_buff_size);

		glDisableVertexAttribArray(0);
		glDeleteBuffers(0, &geometry);
		particle_count += count_real / vertex_buff_len;
	}

	delete[] vertex_buff;
}

void
Particle::EmitterPoint::operator()(Particle*p)
{
	p->life = life();
	p->dir = dir();
	p->scale = scale.get(scaleValueType_window);
	p->rotation = rotation();
	p->position = point.get(scaleValueType_window);
	p->color_alpha = color_alpha();
	p->owner = this;
	total++;
}

void
Particle::EmitterBox::operator()(Particle*p)
{
	p->life = life();
	p->dir = dir();
	p->scale = scale.get(scaleValueType_window);
	p->rotation = rotation();
	p->color_alpha = color_alpha();
	p->owner = this;

	vec2 p1 = topLeft.get(scaleValueType_window);
	vec2 p2 = buttomRight.get(scaleValueType_window);

	range<float> r1(p1.x, p2.x);
	range<float> r2(p1.y, p2.y);

	p->position = vec2(r1(), r2());
	total++;
}