#include "hendel.h"

#ifndef __particle
	#define __particle
	namespace Particle
	{
		struct Particle;
		class ParticleSystem;

		struct Emitter {
			float count = 1;
			int limit = 100;
			range<float> life = 1.0f;
			range<float> rotation = 0.0f;
			range<float> color_alpha = 1.0f;
			range<vec2> dir = vec2(0, 0);
			scaleValue scale = { scaleValueType_window, vec2(1.0f, 1.0f) };
			virtual void operator ()(Particle * p) = 0;
		protected:
			int total = 0;
			friend ParticleSystem;
		};

		struct EmitterPoint : public Emitter {
			scaleValue point = { scaleValueType_window, vec2(0.5f, 0.5f) };
			void operator ()(Particle * p);
		};

		struct EmitterBox : public Emitter {
			scaleValue topLeft = { scaleValueType_window, 0, 0 };
			scaleValue buttomRight = { scaleValueType_window, 1, 1 };
			void operator ()(Particle * p);
		};

		struct Particle {
			vec2 position, scale, dir;
			float life, rotation;
			float color_alpha;
		private:
			Emitter* owner = nullptr;
			friend EmitterPoint;
			friend EmitterBox;
			friend ParticleSystem;
		};

		struct Affector {
			virtual void operator ()(Particle * p) = 0;
		};

		struct AffectorScale : public Affector {
			scaleValue scale;
			AffectorScale(scaleValue scale) :scale(scale){}
			void operator ()(Particle * p)
			{
				p->scale += scale.get(scaleValueType_window);
			}
		};
		struct AffectorForce : public Affector {
			scaleValue force;
			AffectorForce(scaleValue force) :force(force){}
			void operator ()(Particle * p)
			{
				p->dir += force.get(scaleValueType_window);
			}
		};
		struct AffectorRotation : public Affector {
			range<float> angine;
			AffectorRotation(range<float> angine) :angine(angine){}
			void operator ()(Particle * p)
			{
				p->rotation += angine();
			}
		};
		struct AffectorColor : public Affector {
			range<float> color_alpha;
			AffectorColor(range<float> color) :color_alpha(color){}
			virtual void operator ()(Particle * p)
			{
				p->color_alpha += color_alpha();
			}
		};


		class ParticleSystem : public Control {
			static shader * sh;
			vector<Particle> particles;
		public:
			vector<Affector*> affectors;
			vector<Emitter*> emitters;
			void Render();

			static int particle_count;
			static void Init(string shader);
		};
	}
#endif