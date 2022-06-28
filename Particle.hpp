#pragma once
#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include "glm.hpp"
#include "GameObj3D.hpp"
#include "Textures.hpp"
#include "ShaderProgram.hpp"


struct Particle {

public:
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 Color;
	float lifeLength;

	Particle() :
		position(0.0f), velocity(0.0f), Color(0.0f), lifeLength(0.0f) {}

};

class ParticleGenerator
{
public:

	ParticleGenerator(unsigned int amount);

	void Update(float dt, GameObj3D& object, unsigned int newParticles, glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f));

	void Draw(ShaderProgram shader);

private:

	std::vector<Particle> particles;
	unsigned int amount;

	string texture;
	unsigned int particleVAO;
	void initParticle();
	unsigned int firstUnusedParticle();
	void respawnParticle(Particle& particle, GameObj3D& object, glm::vec3 offset);
};


ParticleGenerator::ParticleGenerator(unsigned int amount)
{
	this->initParticle();
}

void ParticleGenerator::initParticle()
{
	// set up mesh and attribute properties
	GLuint particleVBO;
	float particle_quad[] = {
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};
	glGenVertexArrays(1, &particleVAO);
	glGenBuffers(1, &particleVBO);
	glBindVertexArray(particleVAO);
	// fill mesh buffer
	glBindBuffer(GL_ARRAY_BUFFER, particleVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(particle_quad), particle_quad, GL_STATIC_DRAW);
	// set mesh attributes
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindVertexArray(0);

	// create this->amount default particle instances
	for (unsigned int i = 0; i < this->amount; ++i)
		this->particles.push_back(Particle());
}

void ParticleGenerator::Draw(ShaderProgram shader)
{
	// use additive blending to give it a 'glow' effect
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	shader.use();
	for (Particle particle : this->particles) 
	{
		if (particle.lifeLength > 0.0f)
		{
			shader.setVec2("offset", particle.position);
			shader.setVec4("color", particle.Color);

			

			GLuint texture;
			glGenTextures(1, &texture);
			glBindTexture(GL_TEXTURE_2D, texture);

			glBindVertexArray(this->particleVAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glBindVertexArray(0);
		}
	}
	// don't forget to reset to default blending mode
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


void ParticleGenerator::Update(float dt, GameObj3D& object, unsigned int newParticles, glm::vec3 offset)
{
	// add new particles 
	for (unsigned int i = 0; i < newParticles; ++i)
	{
		int unusedParticle = this->firstUnusedParticle();
		this->respawnParticle(this->particles[unusedParticle], object, offset);
	}
	// update all particles
	for (unsigned int i = 0; i < this->amount; ++i)
	{
		Particle& p = this->particles[i];
		p.lifeLength -= dt; // reduce life
		if (p.lifeLength > 0.0f)
		{	// particle is alive, thus update
			p.position -= p.velocity * dt;
			p.Color.a -= dt * 2.5f;
		}
	}
}


// stores the index of the last particle used (for quick access to next dead particle)
unsigned int lastUsedParticle = 0;
unsigned int ParticleGenerator::firstUnusedParticle()
{
	// first search from last used particle, this will usually return almost instantly
	for (unsigned int i = lastUsedParticle; i < this->amount; ++i) {
		if (this->particles[i].lifeLength <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// otherwise, do a linear search
	for (unsigned int i = 0; i < lastUsedParticle; ++i) {
		if (this->particles[i].lifeLength <= 0.0f) {
			lastUsedParticle = i;
			return i;
		}
	}
	// all particles are taken, override the first one (note that if it repeatedly hits this case, more particles should be reserved)
	lastUsedParticle = 0;
	return 0;
}

void ParticleGenerator::respawnParticle(Particle& particle, GameObj3D& object, glm::vec3 offset)
{
	float random = ((rand() % 100) - 50) / 10.0f;
	float rColor = 0.5f + ((rand() % 100) / 100.0f);
	particle.position = object.position() + random + offset;
	particle.Color = glm::vec4(rColor, rColor, rColor, 1.0f);
	particle.lifeLength = 1.0f;
	particle.velocity = object.velocity * 0.1f;
}
#endif