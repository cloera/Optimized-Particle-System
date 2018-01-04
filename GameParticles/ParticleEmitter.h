#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Math\Matrix.h"
#include "Math\Vect4D.h"
#include "Particle.h"
#include "Align16.h"

#include <list>
#include <vector>

class ParticleEmitter : public Align16
{
public:
	ParticleEmitter();
	ParticleEmitter(const ParticleEmitter &in);
	const ParticleEmitter & operator= (const ParticleEmitter &in);
	~ParticleEmitter();
	
	const void SpawnParticle();
	const void update();
	const void draw();

	const void addParticleToList( Particle * const p );
	const void removeParticleFromList( Particle * const p );

	const void Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc);

private:
	Particle *headParticle;
	float	last_spawn;
	float	last_loop;
	int		last_active_particle;
};

#endif // PARTICLEEMITTER_H
