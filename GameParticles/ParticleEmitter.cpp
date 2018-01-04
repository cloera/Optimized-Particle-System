#include "DO_NOT_MODIFY\Timer.h"
#include "DO_NOT_MODIFY\GlobalTimer.h"
#include "DO_NOT_MODIFY\OpenGLInterface.h"

#include <assert.h>

#define UNUSED_VAR(v) ((void *)v)
#include "ParticleEmitter.h"
#include "Settings.h"
#include "DO_NOT_MODIFY\Trace.h"

static const unsigned char squareColors[] = 
{
	255,  255,  000,  255,
	000,  255,  255,  255,
	000,  000,  000,  000,
	255,  000,  255,  255,
}; 

static const float squareVertices[] = 
{
	-0.015f,  -0.015f, 0.0f,
	 0.015f,  -0.015f, 0.0f,
	-0.015f,   0.015f, 0.0f,
	 0.015f,   0.015f, 0.0f,
};


ParticleEmitter::ParticleEmitter()
:	last_spawn( globalTimer::getTimerInSec() ),
	last_loop(  globalTimer::getTimerInSec() ),
	last_active_particle( -1 ),
	headParticle(0)
{
	// nothing to do
}

ParticleEmitter::ParticleEmitter(const ParticleEmitter & in)
	: last_spawn(in.last_spawn), last_loop(in.last_loop),
	  last_active_particle(in.last_active_particle)
{
	//this->last_spawn = in.last_spawn;
	//this->last_loop = in.last_loop;
	//this->last_active_particle = in.last_active_particle;
}

const ParticleEmitter & ParticleEmitter::operator=(const ParticleEmitter & in)
{
	if (this != &in)
	{
		this->last_spawn = in.last_spawn;
		this->last_loop = in.last_loop;
		this->last_active_particle = in.last_active_particle;
	}
	return *this;
}



ParticleEmitter::~ParticleEmitter()
{
	// do nothing
}


const void ParticleEmitter::SpawnParticle()
{
	// create another particle if there are ones free
	if( last_active_particle < NUM_PARTICLES-1 )
	{
		// create new particle
		Particle *newParticle = new Particle();

		// apply the variance
		this->Execute(newParticle->data->position, newParticle->data->velocity, newParticle->data->scale);

		// increment count
		last_active_particle++;

		// add to list
		this->addParticleToList( newParticle );
	}
}

const void ParticleEmitter::update()
{
	// get current time
	float current_time = globalTimer::getTimerInSec();

	// spawn particles
	float time_elapsed = current_time - last_spawn;
	
	// update
	// while spawn_frequency < time_elapsed
	while( 0.0000001f < time_elapsed )
	{
		// spawn a particle
		this->SpawnParticle();
		// adjust time
		// time_elapsed -= spawn_frequency
		time_elapsed -= 0.0000001f;
		// last time
		last_spawn = current_time;
	}
	
	// total elapsed
	time_elapsed = current_time - last_loop;

	Particle *p = this->headParticle;
	// walk the particles

	while( p!= 0 )
	{
		// call every particle and update its position 
		p->Update(time_elapsed);

		 //if it's live is greater that the max_life 
		 //and there is some on the list
		 //remove node
		if((p->data->life > MAX_LIFE) && (last_active_particle > 0))
		{
			// particle to remove
			Particle *s = p;

			// need to squirrel it away.
			p=p->next;

			// remove last node
			this->removeParticleFromList( s );

			// update the number of particles
			last_active_particle--;
		}
		else
		{
			// increment to next point
			p = p->next;
		}
	}

	last_loop = current_time;
}
	   
const void ParticleEmitter::addParticleToList(Particle * const p )
{
	//assert(p);

	if( this->headParticle == 0 )
	{ // first on list
		this->headParticle = p;
	}
	else 
	{ // add to front of list
		headParticle->prev = p;
		p->next = headParticle;
		headParticle = p;
	}

}

const void ParticleEmitter::removeParticleFromList( Particle * const p )
{
	// make sure we are not screwed with a null pointer
	//assert(p);

	if( p->prev == 0 && p->next == 0  )
	{ // only one on the list
		this->headParticle = 0;
	}
	else if( p->prev == 0 && p->next != 0  )
	{ // first on the list
		p->next->prev = 0;
		this->headParticle = p->next;
	}
	else if( p->prev!= 0 && p->next == 0 )
	{ // last on the list 
		p->prev->next = 0;
	}
	else//( p->next != 0  && p->prev !=0 )
	{ // middle of the list
		p->prev->next = p->next;
		p->next->prev = p->prev;
	}
	
	// bye bye
	delete p;
}

const void ParticleEmitter::draw()
{
	// get the camera matrix from OpenGL
	// need to get the position
	Matrix cameraMatrix;

	// get the camera matrix from OpenGL
	glGetFloatv(GL_MODELVIEW_MATRIX, reinterpret_cast<float*>(&cameraMatrix));

	// camera position
	Matrix transCamera(Vect4D(1.0f, 0.0f, 0.0f, 0.0f), Vect4D(0.0f, 1.0f, 0.0f, 0.0f),
						Vect4D(0.0f, 0.0f, 1.0f, 0.0f), cameraMatrix.v3);

	// OpenGL goo... don't worrry about this
	glVertexPointer(3, GL_FLOAT, 0, squareVertices);
	glEnableClientState(GL_VERTEX_ARRAY);
	glColorPointer(4, GL_UNSIGNED_BYTE, 0, squareColors);
	glEnableClientState(GL_COLOR_ARRAY);

	Matrix transParticle;
	Matrix rotParticle;
	Matrix scaleMatrix;
	Matrix pivotParticle;
	Vect4D pivotVect(1.0f, 0.0f, 50.0f);
	pivotVect *= 20.0f;

	Particle *currParticle = this->headParticle;

	while(currParticle != 0)
	{
		// particle position
		transParticle.setTransMatrix(currParticle->data->position );

		// rotation matrix
		rotParticle.setRotZMatrix(currParticle->data->rotation );

		// pivot Point
		pivotVect *= currParticle->data->life;
		pivotParticle.setTransMatrix( pivotVect );

		// scale Matrix
		scaleMatrix.setScaleMatrix(currParticle->data->scale );

		// total transformation of particle
		Matrix tmp = scaleMatrix * transCamera * transParticle * rotParticle * scaleMatrix;

		// set the transformation matrix
		glLoadMatrixf(reinterpret_cast<float*>(&(tmp)));

		// draw the trangle strip
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		
		// clears or flushes some internal setting, used in debug, but is need for performance reasons
		// magic...  really it's magic.
		GLenum glError = glGetError();
		UNUSED_VAR(glError);

		currParticle = currParticle->next;
	}
}


const void ParticleEmitter::Execute(Vect4D& pos, Vect4D& vel, Vect4D& sc)
{
	// Add some randomness...

	// Ses it's ugly - I didn't write this so don't bitch at me
	// Sometimes code like this is inside real commerical code ( so now you know how it feels )
	
	// x - variance
	float var = static_cast<float>(rand() % 1000) * 0.001f;
	float sign = static_cast<float>(rand() % 2);
	float *t_pos = reinterpret_cast<float*>(&pos);
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += var;

	// y - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += var;
	
	// z - variance
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += var;
	
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	
	// x  - add velocity
	t_pos = &vel[x];
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += var;
	
	// y - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += 4.0f * var;
	
	// z - add velocity
	var = static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	t_pos++;
	if(sign == 0)
	{
		var *= -1.0f;
	}
	*t_pos += 0.4f * var;
	
	// correct the sign
	var = 2.0f * static_cast<float>(rand() % 1000) * 0.001f;
	sign = static_cast<float>(rand() % 2);
	
	if(sign == 0)
	{
		var *= -1.0f;
	}
	sc *= var;
}


// End of file