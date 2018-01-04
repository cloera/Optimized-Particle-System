#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"
#include "Align16.h"

class ColdParticle;

class Particle : public Align16
{
public:
	friend class ParticleEmitter;
	
	Particle();
	Particle(const Particle &in);
	const Particle & operator= (const Particle &in);
	~Particle();

	const void Update(const float& time_elapsed);

private:
	Particle *next;
	Particle *prev;
	ColdParticle *data;
};


class ColdParticle : public Align16
{
public:
	friend class ParticleEmitter;
	friend class Particle;

	ColdParticle();
	ColdParticle(const ColdParticle &in);
	const ColdParticle & operator= (const ColdParticle &in);
	~ColdParticle();

private:
	Particle *header;
	float	life;
	float	rotation;
	float	rotation_velocity;

	Vect4D	position;
	Vect4D	velocity;
	Vect4D	scale;
};

#endif //PARTICLE_H
