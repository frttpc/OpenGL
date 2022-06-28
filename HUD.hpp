#pragma once

#include "glm.hpp"
#include "Textures.hpp"
#include <glad/glad.h>

void HUD()
{
	vector<std::string> hud_file{ "./particles/particleStar.jpg" };
	vector<unsigned int> HUDtext = Textures::loadTextures(hud_file);

	glBindTexture(GL_TEXTURE_2D, HUDtext[0]);
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0, 1.0);		glVertex2f(0.05, 0.05);
	glTexCoord2f(1.0, 1.0);		glVertex2f(0.3, 0.05);
	glTexCoord2f(1.0, 0.0);		glVertex2f(0.3, 0.15);
	glTexCoord2f(0.0, 0.0);		glVertex2f(0.05, 0.15);
	glEnd();
}

void drawHUD()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glOrtho(0.0, 1.0, 1.0, 0.0, 0.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	HUD();

	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}