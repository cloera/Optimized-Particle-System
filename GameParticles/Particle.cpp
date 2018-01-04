#include "Particle.h"
#include "Matrix.h"
#include "ParticleEmitter.h"

Particle::Particle()
	: next(0), prev(0)
{
	this->data = new ColdParticle();
}

Particle::Particle(const Particle & in)
	: next(in.next), prev(in.prev), data(in.data)
{
}

const Particle & Particle::operator=(const Particle & in)
{
	if (this != &in)
	{
		this->next = in.next;
		this->prev = in.prev;
		this->data = in.data;
	}
	return *this;
}

Particle::~Particle()
{
	// nothing to do
	delete data;
}


const void Particle::Update(const float& time_elapsed)
{
	// serious math below - magic secret sauce
	this->data->life += time_elapsed;
	this->data->position += (this->data->velocity * time_elapsed);
	Vect4D v(3.0f,4.0f,0.0f);
	this->data->position.Cross(Vect4D(0.0f, -0.25f, 1.0f), v);
	v.norm(v);
	this->data->position += v * 0.05f * this->data->life;

	this->data->rotation += this->data->rotation_velocity * time_elapsed * 2.01f;
}


// End of file

ColdParticle::ColdParticle()
	: life(0.0f), position(0.0f, 0.0f, 0.0f), velocity(0.0f, 1.0f, 0.0f),
	  scale(1.0f, 1.0f, 1.0f), rotation(0.0f), rotation_velocity(0.5f)
{
}

ColdParticle::ColdParticle(const ColdParticle & in)
	: position(in.position), velocity(in.velocity), scale(in.scale),
	  rotation(in.rotation), rotation_velocity(in.rotation_velocity),
	  life(in.life)
{
}

const ColdParticle & ColdParticle::operator=(const ColdParticle & in)
{
	if (this != &in)
	{
		this->position = in.position;
		this->velocity = in.velocity;
		this->scale = in.scale;
		this->rotation = in.rotation;
		this->rotation_velocity = in.rotation_velocity;
		this->life = in.life;
	}
	return *this;
}

ColdParticle::~ColdParticle()
{
}
