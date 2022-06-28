#pragma once

#include "glm/glm.hpp"
#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <cstdlib>

/*
emitter
*/


class SimpleEmitter
{
public:
	SimpleEmitter();
	~SimpleEmitter();

	void update(const float dt);

	void draw();

private:
	struct Particle
	{
		glm::vec3 position;
		float lifetime;
	};

	vector<Particle> particles;

	float positions[400];

	GLuint vertexBuffer;
	GLuint positionBuffer;
};



/*
shader
*/
class SimpleParticleShader
{
public:
	SimpleParticleShader();
	~SimpleParticleShader();

	void setUniformViewMatrix(const glm::mat4& M_v);
	void setUniformProjectionMatrix(const glm::mat4& M_p);
	void setUniformParticleSize(const float particleSize);

private:
	static const std::string VS;
	static const std::string FS;

	GLuint u_M_v;
	GLuint u_M_p;
	GLuint u_particleSize;
};



/*
controller
*/
class SimpleController
{
public:
	SimpleController();
	~SimpleController();

	void draw(const float dt, const glm::mat4 M_p, const glm::mat4& M_v);

private:
	SimpleParticleShader* shader;

	SimpleEmitter* emitter;
};

SimpleEmitter::SimpleEmitter()
{
	// create 100 particles
	this->particles.resize(100);
	for (unsigned int i = 0; i < this->particles.size(); ++i)
	{
		// give every particle a random position
		this->particles[i].position = glm::vec3(rand()/RAND_MAX);
		this->particles[i].lifetime = rand()/RAND_MAX*2;
	}

	// create a vertex and position buffer
	this->vertexBuffer = glGenBuffer();
	this->positionBuffer = glGenBuffer();

	// fill the vertex buffer
	std::vector< float > vertices;
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(0.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

	// fill the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, this->particles.size() * 4 * sizeof(float), this->positions, GL_DYNAMIC_DRAW);
}



SimpleEmitter::~SimpleEmitter()
{
	delete(this);
	delete(this);
}



void SimpleEmitter::update(const float dt)
{
	for (unsigned int i = 0; i < this->particles.size(); ++i)
	{
		// subtract from the particles lifetime
		this->particles[i].lifetime -= dt;

		// if the lifetime is below 0 respawn the particle
		if (this->particles[i].lifetime <= 0.0f)
		{
			this->particles[i].position = glm::vec3(rand()/RAND_MAX);
			this->particles[i].lifetime = rand()/RAND_MAX*2;
		}

		// move the particle down depending on the delta time
		this->particles[i].position -= glm::vec3(0.0f, dt * 2.0f, 0.0f);

		// update the position buffer
		this->positions[i * 4 + 0] = this->particles[i].position[0];
		this->positions[i * 4 + 1] = this->particles[i].position[1];
		this->positions[i * 4 + 2] = this->particles[i].position[2];
		this->positions[i * 4 + 3] = this->particles[i].lifetime;
	}
}



void SimpleEmitter::draw()
{
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(4);

	// update the position buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, this->particles.size() * 4 * sizeof(float), this->positions);

	// vertex buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

	// position buffer
	glBindBuffer(GL_ARRAY_BUFFER, this->positionBuffer);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
	glVertexAttribDivisor(4, 1);

	// draw triangles
	glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, this->particles.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(4);
}



/*
shader
*/




SimpleParticleShader::SimpleParticleShader()
{
	this->createFromString(VS, FS);

	this->u_M_v = glGetUniformLocation("M_v");
	this->u_M_p = this->glGetUniformLocation("M_p");
	this->u_particleSize = this->glGetUniformLocation("particleSize");
}



SimpleParticleShader::~SimpleParticleShader()
{

}



void SimpleParticleShader::setUniformViewMatrix(const glm::mat4& M_v)
{
	this->glUniformMatrix4fv(this->u_M_v, M_v);
}



void SimpleParticleShader::setUniformProjectionMatrix(const glm::mat4& M_p)
{
	this-glUniformMatrix4fv(this->u_M_p, M_p);
}



void SimpleParticleShader::setUniformParticleSize(const float particleSize)
{
	this->glUniform1f(this->u_particleSize, particleSize);
}



/*
controller
*/



SimpleController::SimpleController()
{
	this->shader = new SimpleParticleShader();
	this->emitter = new SimpleEmitter();
}



SimpleController::~SimpleController()
{
	delete this->shader;
	delete this->emitter;
}



void SimpleController::draw(const float dt, const glm::mat4 M_p, const glm::mat4& M_v)
{
	this->emitter->update(dt);

	this->shader->use();
	this->shader->setUniformProjectionMatrix(M_p);
	this->shader->setUniformViewMatrix(M_v);
	this->shader->setUniformParticleSize(0.1f);

	this->emitter->draw();
}