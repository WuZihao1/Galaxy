#include "Bind_Data.h"
#include "Loading_func.h"

GLuint earthVao;
GLuint planetBVao;
GLuint planetCVao;
GLuint objDVao;
GLuint objEVao;
GLuint objGVao;
GLuint objStarVao;
int drawEarthSize = 0;
int drawBSize = 0;
int drawCSize = 0;
int drawDSize = 0;
int drawESize = 0;
int drawGSize = 0;
int drawStarSize = 0;
int amount = 10000;

glm::mat4* modelMatrices;
unsigned int buffer;
glm::vec3 B_max = { 0.0,0.0,0.0 };
glm::vec3 B_min = { 0.0,0.0,0.0 };
glm::vec3 D_max = { 0.0,0.0,0.0 };
glm::vec3 D_min = { 0.0,0.0,0.0 };

void bindEarth(const char * path)
{
	//Earth data
	std::vector<glm::vec3> vao5_v;
	std::vector<glm::vec2> vao5_uvs;
	std::vector<glm::vec3> vao5_n;

	loadOBJ(path, vao5_v, vao5_uvs, vao5_n);

	//sending earth data
	glGenVertexArrays(1, &earthVao);
	glBindVertexArray(earthVao);
	GLuint vbo5ID;
	glGenBuffers(1, &vbo5ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5ID);
	glBufferData(GL_ARRAY_BUFFER, vao5_v.size() * sizeof(glm::vec3), &vao5_v[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UV data
	GLuint vbo5uvbuffer;
	glGenBuffers(1, &vbo5uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_uvs.size() * sizeof(glm::vec2), &vao5_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//normal data
	GLuint vbo5nor_buffer;
	glGenBuffers(1, &vbo5nor_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5nor_buffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_n.size() * sizeof(glm::vec3), &vao5_n[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//draw data
	drawEarthSize = vao5_v.size();
}

void bindD(const char * path)
{
	//Earth data
	std::vector<glm::vec3> vao5_v;
	std::vector<glm::vec2> vao5_uvs;
	std::vector<glm::vec3> vao5_n;

	loadOBJ_test(path, vao5_v, vao5_uvs, vao5_n, D_max, D_min);

	//sending earth data
	glGenVertexArrays(1, &objDVao);
	glBindVertexArray(objDVao);
	GLuint vbo5ID;
	glGenBuffers(1, &vbo5ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5ID);
	glBufferData(GL_ARRAY_BUFFER, vao5_v.size() * sizeof(glm::vec3), &vao5_v[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UV data
	GLuint vbo5uvbuffer;
	glGenBuffers(1, &vbo5uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_uvs.size() * sizeof(glm::vec2), &vao5_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//normal data
	GLuint vbo5nor_buffer;
	glGenBuffers(1, &vbo5nor_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5nor_buffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_n.size() * sizeof(glm::vec3), &vao5_n[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//draw data
	drawDSize = vao5_v.size();
}


void bindB(const char * path)
{
	//Earth data
	std::vector<glm::vec3> vao5_v;
	std::vector<glm::vec2> vao5_uvs;
	std::vector<glm::vec3> vao5_n;

	loadOBJ_test(path, vao5_v, vao5_uvs, vao5_n, B_max, B_min);

	//sending earth data
	glGenVertexArrays(1, &planetBVao);
	glBindVertexArray(planetBVao);
	GLuint vbo5ID;
	glGenBuffers(1, &vbo5ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5ID);
	glBufferData(GL_ARRAY_BUFFER, vao5_v.size() * sizeof(glm::vec3), &vao5_v[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UV data
	GLuint vbo5uvbuffer;
	glGenBuffers(1, &vbo5uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_uvs.size() * sizeof(glm::vec2), &vao5_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//normal data
	GLuint vbo5nor_buffer;
	glGenBuffers(1, &vbo5nor_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5nor_buffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_n.size() * sizeof(glm::vec3), &vao5_n[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//draw data
	drawBSize = vao5_v.size();
}

void bindC(const char * path)
{
	//Earth data
	std::vector<glm::vec3> vao5_v;
	std::vector<glm::vec2> vao5_uvs;
	std::vector<glm::vec3> vao5_n;

	loadOBJ(path, vao5_v, vao5_uvs, vao5_n);

	//sending earth data
	glGenVertexArrays(1, &planetCVao);
	glBindVertexArray(planetCVao);
	GLuint vbo5ID;
	glGenBuffers(1, &vbo5ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5ID);
	glBufferData(GL_ARRAY_BUFFER, vao5_v.size() * sizeof(glm::vec3), &vao5_v[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UV data
	GLuint vbo5uvbuffer;
	glGenBuffers(1, &vbo5uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_uvs.size() * sizeof(glm::vec2), &vao5_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//normal data
	GLuint vbo5nor_buffer;
	glGenBuffers(1, &vbo5nor_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5nor_buffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_n.size() * sizeof(glm::vec3), &vao5_n[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//draw data
	drawCSize = vao5_v.size();
}


void bindE(const char * path)
{
	//Earth data
	std::vector<glm::vec3> vao5_v;
	std::vector<glm::vec2> vao5_uvs;
	std::vector<glm::vec3> vao5_n;

	loadOBJ(path, vao5_v, vao5_uvs, vao5_n);

	//sending earth data
	glGenVertexArrays(1, &objEVao);
	glBindVertexArray(objEVao);
	GLuint vbo5ID;
	glGenBuffers(1, &vbo5ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5ID);
	glBufferData(GL_ARRAY_BUFFER, vao5_v.size() * sizeof(glm::vec3), &vao5_v[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UV data
	GLuint vbo5uvbuffer;
	glGenBuffers(1, &vbo5uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_uvs.size() * sizeof(glm::vec2), &vao5_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//normal data
	GLuint vbo5nor_buffer;
	glGenBuffers(1, &vbo5nor_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5nor_buffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_n.size() * sizeof(glm::vec3), &vao5_n[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//draw data
	drawESize = vao5_v.size();
}




void bindG(const char * path)
{

	std::vector<glm::vec3> vao5_v;
	std::vector<glm::vec2> vao5_uvs;
	std::vector<glm::vec3> vao5_n;

	loadOBJ(path, vao5_v, vao5_uvs, vao5_n);

	//sending earth data
	glGenVertexArrays(1, &objGVao);
	glBindVertexArray(objGVao);
	GLuint vbo5ID;
	glGenBuffers(1, &vbo5ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5ID);
	glBufferData(GL_ARRAY_BUFFER, vao5_v.size() * sizeof(glm::vec3), &vao5_v[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UV data
	GLuint vbo5uvbuffer;
	glGenBuffers(1, &vbo5uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_uvs.size() * sizeof(glm::vec2), &vao5_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//normal data
	GLuint vbo5nor_buffer;
	glGenBuffers(1, &vbo5nor_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5nor_buffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_n.size() * sizeof(glm::vec3), &vao5_n[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//draw data
	drawGSize = vao5_v.size();


	modelMatrices = new glm::mat4[amount];



	srand(glutGet(GLUT_ELAPSED_TIME));
	GLfloat radius = 15.0f;
	GLfloat offset = 2.0f;
	GLfloat displacement;
	for (GLuint i = 0; i < amount; i++)
	{
		glm::mat4 model;
		GLfloat angle = (GLfloat)i / (GLfloat)amount*360.0f;
		//x
		displacement = (rand() % (GLint)(2 * offset * 200)) / 100.0f - offset;
		GLfloat x = sin(angle)*radius + displacement;
		//y
		displacement = (rand() % (GLint)(2 * offset * 200)) / 100.0f - offset;
		GLfloat y = displacement*0.4f + 1;
		//z
		displacement = (rand() % (GLint)(2 * offset * 200)) / 100.0f - offset;
		GLfloat z = cos(angle)*radius + displacement;
		model = glm::translate(model, glm::vec3(x, y, z));

		GLfloat scale = (rand() % 10) / 100.0f + 0.05;
		model = glm::scale(model, glm::vec3(scale));

		GLfloat rotAngle = (rand() % 360);
		model = glm::rotate(model, rotAngle, glm::vec3(0.4f, 0.6f, 0.8f));

		//modelMatrices = model;
		modelMatrices[i] = model;
	}



	glGenBuffers(1, &buffer);
	glBindBuffer(GL_ARRAY_BUFFER, buffer);
	glBufferData(GL_ARRAY_BUFFER, amount * sizeof(glm::mat4), &modelMatrices[0], GL_STATIC_DRAW);



	// vertex Attributes
	//GLsizei vec4Size = sizeof(glm::vec4);
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)0);
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(sizeof(glm::vec4)));
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(2 * sizeof(glm::vec4)));
	glEnableVertexAttribArray(6);
	glVertexAttribPointer(6, 4, GL_FLOAT, GL_FALSE, sizeof(glm::mat4), (void*)(3 * sizeof(glm::vec4)));

	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);
	glVertexAttribDivisor(6, 1);

	glBindVertexArray(0);
}


void bindstar(const char * path)
{
	//Earth data
	std::vector<glm::vec3> vao5_v;
	std::vector<glm::vec2> vao5_uvs;
	std::vector<glm::vec3> vao5_n;

	loadOBJ(path, vao5_v, vao5_uvs, vao5_n);

	//sending earth data
	glGenVertexArrays(1, &objStarVao);
	glBindVertexArray(objStarVao);
	GLuint vbo5ID;
	glGenBuffers(1, &vbo5ID);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5ID);
	glBufferData(GL_ARRAY_BUFFER, vao5_v.size() * sizeof(glm::vec3), &vao5_v[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//UV data
	GLuint vbo5uvbuffer;
	glGenBuffers(1, &vbo5uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_uvs.size() * sizeof(glm::vec2), &vao5_uvs[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	//normal data
	GLuint vbo5nor_buffer;
	glGenBuffers(1, &vbo5nor_buffer);
	glBindBuffer(GL_ARRAY_BUFFER, vbo5nor_buffer);
	glBufferData(GL_ARRAY_BUFFER, vao5_n.size() * sizeof(glm::vec3), &vao5_n[0], GL_STATIC_DRAW);
	//vertex position
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//draw data
	drawStarSize = vao5_v.size();
}