#include "Dependencies\glew\glew.h"
#include "Dependencies\freeglut\freeglut.h"
#include "Dependencies\glm\glm.hpp"
#include "Dependencies\glm\gtc\matrix_transform.hpp"
#include "Dependencies\glui\glui.h"
//#include "Dependencies\glui\glui.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <list>

#include "shader_install.h"
#include "Loading_func.h"
#include "Bind_Data.h"
#include "Dependencies\irr\irrKlang.h"
#pragma comment(lib, "irrKlang.lib")

using namespace irrklang;
using namespace std;
using glm::vec3;
using glm::mat4;
// ============================= //
// window size
int Win_w, Win_h;
float camera_fov = 45.0;


int  mainWindowID;
GLint programID;
GLint BID;
GLint CID;
GLint DID;
GLint EID;
GLint GID;
GLint Skybox_programID;
GLint star_ID;

glm::vec3 camera_position;
glm::vec3 camera_lookat ;
glm::vec3 camera_up;
GLuint TextureEarth_1;
GLuint TextureEarth_2;
GLuint TextureEarth_3;
GLuint sea_cubemapTexture;
GLuint TextureB_1;
GLuint TextureC_1;
GLuint TextureD_1;
GLuint TextureE_1;
GLuint TextureG_1;
GLuint TextureB_2;
GLuint TextureC_2;
GLuint TextureD_2;
GLuint TextureE_2;
GLuint TextureG_2;
GLuint TextureB_3;
GLuint TextureC_3;
GLuint TextureD_3;
GLuint TextureE_3;
GLuint TextureG_3;
GLuint TextureStar;

extern GLuint earthVao;
extern GLuint planetBVao;
extern GLuint planetCVao;
extern GLuint objDVao;
extern GLuint objEVao;
extern GLuint objGVao;
extern GLuint objStarVao;

extern int drawEarthSize;
extern int drawCSize;
extern int drawBSize;
extern int drawDSize;
extern int drawESize;
extern int drawGSize;
extern int drawStarSize;

glm::mat4 plane_matrix;

int viewpoint_flag = 0;

extern int amount;
GLuint skyboxVAO;
GLuint skyboxVBO;
GLUI* glui;
float dx = 0;
float dy = 0;
float dz = 0;

// view matrix
glm::mat4 common_viewM;
glm::mat4 common_projection;

float earth_innRot_Degree = 0.0f;
float vehicle_innRot_Degree = 0.0f;
float planetB_rotate_degree = 0.0f;

// ============================= //
const float M_PI = 3.14159265;
float radius = 30.0f;
float initViewHorizontal = -90.0f;
float initViewVertical = -90.0f;

float cameraX = 0;
float cameraY = 0;
float cameraZ = 0;

float viewRotateDegree[3] = { 0.0f, 0.0f, 0.0f };

float a_brightness = 1.0f;  //
float d_brightness = 0.5f;  //
float s_brightness = 0.5f;  //

float d_brightness_2 = 1.5f;  //
float s_brightness_2 = 1.5f;  //

int fog_flag = 0;

extern glm::mat4* modelMatrices;
float xLightPos = 0.0f;
float zLightPos = 0.0f;
float yLightPos = 0.0f;
float Vehicle_s = 1.0f;

glm::mat4 apple_matrix;
float Emove = 0;
bool Etoleft = true;
GLint normal_flag = 0;
int fog_jug = 0;

int trace_size = 0;
int view = 0;
list<glm::mat4> star;

extern glm::vec3 B_max;
extern glm::vec3 B_min;
extern glm::vec3 D_max;
extern glm::vec3 D_min;
extern int amout;
glm::vec3 temp_D_max;
glm::vec3 temp_B_max;
glm::vec3 temp_D_min;
glm::vec3 temp_B_min;
glm::mat4 moon_matrix;
int C = 0;
glm::mat4* modelmatrices;
int fog_color = 0;

bool keys[1024] = { false };
bool special_keys[1024] = { false };
bool pause = false;
int height;
GLfloat lastX = height / 2.0f;
GLfloat lastY = height / 2.0f;
GLfloat mouseControl_y_sensitivity = 28.0f;
GLfloat mouseControl_x_sensitivity = 28.0f;
GLfloat yaw = -90.0f;
GLfloat pitch = -20.0f;
vec3 cameraFront = vec3(0.0f, 0.0f, -1.0f);


float D_radius = 0;


GLuint loadCubemap(vector<const GLchar*> faces)
{
	int width, height;
	unsigned char* image;
	GLuint textureID;
	glGenTextures(1, &textureID);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

	for (GLuint i = 0; i < faces.size(); i++)
	{
		loadBMP_Data(faces[i], image, width, height);
		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	return textureID;
}

int collision(glm::vec3 b_max, glm::vec3 b_min, glm::vec3 d_max, glm::vec3 d_min)
{
	if (((b_min.x <= d_max.x) && (b_max.x >= d_min.x)) &&
		((b_min.y <= d_max.y) && (b_max.y >= d_min.y)) &&
		((b_min.z <= d_max.z) && (b_max.z >= d_min.z))
		)
	{
		C = C + 1;
		return C;
	}
	else
		return C;
}

void keyboard(unsigned char key, int x, int y)
{
	if (key >= 0 && key < 1024)
	{
		keys[key] = true;
	}


}

void PassiveMouse(int x, int y)
{
	if (!pause)
	{
		GLfloat xoffset = x - lastX;
		GLfloat yoffset = lastY - y;
		yoffset *= mouseControl_y_sensitivity - 10;
		yoffset /= height;
		cameraY -= yoffset;
		xoffset *= mouseControl_x_sensitivity;
		xoffset /= height;
		cameraX -= xoffset;

		glm::vec3 front;
		front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		front.y = sin(glm::radians(pitch));
		front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		cameraFront = glm::normalize(front);

	}
	lastX = (GLfloat)x;
	lastY = (GLfloat)y;

}


void handleKeys()
{

	if (special_keys[GLUT_KEY_UP])
	{
		Vehicle_s += 0.2f;
	}
	if (special_keys[GLUT_KEY_DOWN])
	{
		if(Vehicle_s>=0.20f)
			Vehicle_s -= 0.2f;
	}
	if (special_keys[GLUT_KEY_LEFT])
	{

		D_radius += 0.2f;
	}
	if (special_keys[GLUT_KEY_RIGHT])
	{
		if (D_radius >= -1.0f)
			D_radius -= 0.2f;
	}


	if (keys[27])
	{
		glutLeaveMainLoop();
	}


	if (keys[' '])
	{
		pause = !pause;
		keys[' '] = false;
	}

	if (keys['a'])
	{
		viewpoint_flag = 0;
	}

	if (keys['s'])
	{
		viewpoint_flag = 1;
	}

	if (keys['d'])
	{
		viewpoint_flag = 2;
	}

	if (keys['f'])
	{
		viewpoint_flag = 3;
	}


	if (keys['q'])
	{
		a_brightness += 0.02f;;
	}
	if (keys['w'])
	{
		if(a_brightness>=0.0f)
			a_brightness -= 0.02f;

	}
	if (keys['z'])
	{
		d_brightness += 0.2f;
	}
	if (keys['x'])
	{
		if (d_brightness >= 0.0f)
			d_brightness -= 0.2f;
	}
	if (keys['c'])
	{
		s_brightness += 0.05f;
	}
	if (keys['v'])
	{
		if (s_brightness >= 0.02f)
			s_brightness -= 0.05f;
	}

	if (keys['i'])
	{
		dz = dz - 0.5f;
	}
	if (keys['k'])
	{
		dz = dz + 0.5f;
	}
	if (keys['j'])
	{
		dx = dx - 0.5f;
	}
	if (keys['l'])
	{
		dx = dx + 0.5f;
	}
	if (keys['u'])
	{
		dy = dy + 0.5f;
	}
	if (keys['o'])
	{
		dy = dy - 0.5f;
	}

}



void keyboardUp(unsigned char key, int x, int y)
{
	if (key >= 0 && key < 1024)
	{
		keys[key] = false;
	}
}

void handleSpecialKeypress(int key, int x, int y)
{
	if (key >= 0 && key < 1024)
	{
		special_keys[key] = true;
	}


}

void handleSpecialKeyReleased(int key, int x, int y)
{
	if (key >= 0 && key < 1024)
	{
		special_keys[key] = false;
	}
}


void Mouse_Wheel_Func(int button, int state, int x, int y)
{
	if ((button == 3) || (button == 4))
	{
		if (state == GLUT_UP) return;
		if (button == 3)
		{
			radius -= 1.0f;
			cameraX = radius* cos(glm::radians(initViewHorizontal + viewRotateDegree[1]))*sin(glm::radians(initViewVertical + viewRotateDegree[0]));
			cameraY = radius* cos(glm::radians(initViewVertical + viewRotateDegree[0]));
			cameraZ = radius* sin(glm::radians(initViewHorizontal + viewRotateDegree[1]))*sin(glm::radians(initViewVertical + viewRotateDegree[0]));
		}
		else
		{
			radius += 1.0f;
			cameraX = radius* cos(glm::radians(initViewHorizontal + viewRotateDegree[1]))*sin(glm::radians(initViewVertical + viewRotateDegree[0]));
			cameraY = radius* cos(glm::radians(initViewVertical + viewRotateDegree[0]));
			cameraZ = radius* sin(glm::radians(initViewHorizontal + viewRotateDegree[1]))*sin(glm::radians(initViewVertical + viewRotateDegree[0]));
		}
	}
}

void LoadAllTextures()
{
	TextureEarth_1 = loadBMP2Texture("texture/earth.bmp");


	if(normal_flag==1)
		TextureEarth_2 = loadBMP2Texture("normal_map/earth_normal.bmp");
	else 
		TextureEarth_2 = loadBMP2Texture("texture/earth.bmp");
	TextureD_1 = loadBMP2Texture("texture/prot17.bmp");
	TextureB_1 = loadBMP2Texture("texture/brickWall.bmp");
	TextureC_1 = loadBMP2Texture("texture/glass_a.bmp");
	TextureC_2 = loadBMP2Texture("texture/glass_a.bmp");
	TextureE_1 = loadBMP2Texture("texture/apple.bmp");
	TextureG_1 = loadBMP2Texture("texture/stones.bmp");
	TextureStar = loadBMP2Texture("texture/starfy.bmp");
}

void bindSkybox()
{

	glUseProgram(Skybox_programID);
	GLfloat skyboxVertices[] =
	{
		-1.0f,  1.0f, -1.0f,
		-1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f, -1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,

		-1.0f, -1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
		-1.0f, -1.0f,  1.0f,

		-1.0f,  1.0f, -1.0f,
		1.0f,  1.0f, -1.0f,
		1.0f,  1.0f,  1.0f,
		1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f,  1.0f,
		-1.0f,  1.0f, -1.0f,

		-1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f, -1.0f,
		1.0f, -1.0f, -1.0f,
		-1.0f, -1.0f,  1.0f,
		1.0f, -1.0f,  1.0f,
	};

	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glBindVertexArray(0);


	vector<const GLchar*> earth_faces;
	earth_faces.push_back("texture/skycity_skybox/right.bmp");
	earth_faces.push_back("texture/skycity_skybox/left.bmp");
	earth_faces.push_back("texture/skycity_skybox/bottom.bmp");
	earth_faces.push_back("texture/skycity_skybox/top.bmp");
	earth_faces.push_back("texture/skycity_skybox/back.bmp");
	earth_faces.push_back("texture/skycity_skybox/front.bmp");

	sea_cubemapTexture = loadCubemap(earth_faces);
}





void sendDataToOpenGL()
{
	//Load objects and bind to VAO & VBO
	bindEarth("obj/planet.obj");
	bindD("obj/B-2_Spirit.obj");
	bindB("obj/planet.obj");
	bindC("obj/planet.obj");
	bindE("obj/apple.obj");
	bindG("obj/rock.obj");
	bindstar("obj/starfy.obj");
	bindSkybox();
	// load all textures
	LoadAllTextures();
}

void set_lighting (GLint ID)
{
	glUseProgram(ID);

	// ambient
	GLint ambientLightUniformLocation = glGetUniformLocation(ID, "ambientLight");
	glm::vec3 ambientLight(a_brightness, a_brightness, a_brightness);
	glUniform3fv(ambientLightUniformLocation, 1, &ambientLight[0]);
	// diffusion
	GLint kd = glGetUniformLocation(ID, "coefficient_d");
	glm::vec3 vec_kd(d_brightness, d_brightness, d_brightness);
	glUniform3fv(kd, 1, &vec_kd[0]);
	// specular
	GLint ks = glGetUniformLocation(ID, "coefficient_s");
	glm::vec3 vec_ks= glm::vec3(s_brightness, s_brightness, s_brightness);
	glUniform3fv(ks,1,&vec_ks[0]);

	
	GLint kd_2 = glGetUniformLocation(ID, "coefficient_d_2");
	glm::vec3 vec_kd_2(d_brightness_2, d_brightness_2, d_brightness_2);
	glUniform3fv(kd_2, 1, &vec_kd_2[0]);
	// specular
	GLint ks_2 = glGetUniformLocation(ID, "coefficient_s_2");
	glm::vec3 vec_ks_2 = glm::vec3(s_brightness_2, s_brightness_2, s_brightness_2);
	glUniform3fv(ks_2, 1, &vec_ks_2[0]);

	GLint lightPositionUniformLocation_2 = glGetUniformLocation(ID, "lightPositionWorld_2");
	glm::vec4 lp_2 = glm::vec4(-30.0f, 30.0f, -30.0f, 1.0f);
	glm::vec3 lightPosition_2 = glm::vec3(apple_matrix*lp_2);
	glUniform3fv(lightPositionUniformLocation_2, 1, &lightPosition_2[0]);
	


	// eye position
	GLint eyePositionUniformLocation = glGetUniformLocation(ID, "eyePositionWorld");
	vec3 eyePosition(cameraX, cameraY, cameraZ+radius);
	glUniform3fv(eyePositionUniformLocation, 1, &eyePosition[0]);
	// light position
	GLint lightPositionUniformLocation = glGetUniformLocation(ID, "lightPositionWorld");
	glm::vec4 lp = glm::vec4(xLightPos, yLightPos, zLightPos, 1.0f);
	glm::vec3 lightPosition = glm::vec3(apple_matrix*lp);
	glUniform3fv(lightPositionUniformLocation, 1, &lightPosition[0]);

	// light color
	
	GLint lightColorUniformLocation = glGetUniformLocation(ID, "lightColor");
	glm::vec3 lightColor= glm::vec3(1.0, 1.0, 1.0);
	glUniform3fv(lightColorUniformLocation, 1, &lightColor[0]);


	
}







void drawEarth(void)
{
	//earth
	GLfloat scale_fact = 2.3f;

	glUseProgram(programID);

	glBindVertexArray(earthVao);
	glm::mat4 scale_M = glm::scale(glm::mat4(1.0f), glm::vec3(scale_fact));
	glm::mat4 rot_M = glm::rotate(glm::mat4(1.0f), glm::radians(earth_innRot_Degree), glm::vec3(0, 1, 0));
	glm::mat4 trans_M = glm::translate(glm::mat4(1.0f), glm::vec3(-7.0f, 4.0f, 0.0f));
	glm::mat4 Model = trans_M*rot_M* scale_M;


	GLint F_ID = glGetUniformLocation(programID, "fog_flag");
	glUniform1i(F_ID, fog_flag);

	GLint N_ID = glGetUniformLocation(programID, "normal_flag");
	glUniform1i(N_ID, normal_flag);

	GLint C_ID = glGetUniformLocation(programID, "color_flag");
	glUniform1i(C_ID, fog_color);
	

	GLint M_ID = glGetUniformLocation(programID, "MM");
	glUniformMatrix4fv(M_ID, 1, GL_FALSE, &Model[0][0]);
	GLint V_ID = glGetUniformLocation(programID, "VM");
	glUniformMatrix4fv(V_ID, 1, GL_FALSE, &common_viewM[0][0]);
	GLint P_ID = glGetUniformLocation(programID, "PM");
	glUniformMatrix4fv(P_ID, 1, GL_FALSE, &common_projection[0][0]);

	// texture
	GLuint TextureID_1 = glGetUniformLocation(programID, "myTextureSampler_1");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureEarth_1);
	glUniform1i(TextureID_1, 0);


	GLuint TextureID_2 = glGetUniformLocation(programID, "myTextureSampler_2");
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureEarth_2);
	glUniform1i(TextureID_2, 1);


	glDrawArrays(GL_TRIANGLES, 0, drawEarthSize);
}



void drawC(void)
{
	GLfloat scale_fact = 1.6f;

	glUseProgram(CID);




	glBindVertexArray(planetCVao);
	glm::mat4 scale_M = glm::scale(glm::mat4(1.0f), glm::vec3(scale_fact));
	glm::mat4 rot_M = glm::rotate(glm::mat4(1.0f), glm::radians(earth_innRot_Degree), glm::vec3(0, 1, 0));
	glm::mat4 trans_M = glm::translate(glm::mat4(1.0f), glm::vec3(8.0f, -9.0f, 0.0f));
	glm::mat4 Model = trans_M * rot_M * scale_M;

	GLint M_ID = glGetUniformLocation(CID, "MM");
	glUniformMatrix4fv(M_ID, 1, GL_FALSE, &Model[0][0]);
	GLint V_ID = glGetUniformLocation(CID, "VM");
	glUniformMatrix4fv(V_ID, 1, GL_FALSE, &common_viewM[0][0]);
	GLint P_ID = glGetUniformLocation(CID, "PM");
	glUniformMatrix4fv(P_ID, 1, GL_FALSE, &common_projection[0][0]);


	GLint F_ID = glGetUniformLocation(CID, "fog_flag");
	glUniform1i(F_ID, fog_flag);

	GLint N_ID = glGetUniformLocation(CID, "normal_flag");
	glUniform1i(N_ID, normal_flag);

	GLint C_ID = glGetUniformLocation(CID, "color_flag");
	glUniform1i(C_ID, fog_color);

	// texture
	GLuint TextureID_1 = glGetUniformLocation(CID, "myTextureSampler_1");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureC_1);
	glUniform1i(TextureID_1, 0);

	
	GLuint TextureID_2 = glGetUniformLocation(CID, "myTextureSampler_2");
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, TextureC_2);
	glUniform1i(TextureID_2, 1);
	

	glDrawArrays(GL_TRIANGLES, 0, drawCSize);
}





void drawD(void)
{
	GLfloat scale_fact = 0.1f;

	glUseProgram(DID);

	glBindVertexArray(objDVao);
	glm::mat4 rot_M_S1 = glm::rotate(glm::mat4(1.0f), glm::radians(-40.0f), glm::vec3(0, 0, 1));
	glm::mat4 rot_M_S2 = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 1, 0));
	glm::mat4 scale_M = glm::scale(glm::mat4(1.0f), glm::vec3(scale_fact));
	glm::mat4 trans_M_T = glm::translate(glm::mat4(1.0f), glm::vec3(6.0f + D_radius, -7.0f - D_radius, 0.0f));
	glm::mat4 rot_M = glm::rotate(glm::mat4(1.0f), glm::radians(vehicle_innRot_Degree), glm::vec3(0, 0, 1));
	glm::mat4 trans_M = glm::translate(glm::mat4(1.0f), glm::vec3(-7.0f - D_radius, 6.0f + D_radius, 0.0f));
	glm::mat4 Model = trans_M*rot_M*trans_M_T*rot_M_S1*rot_M_S2*scale_M;

	plane_matrix = Model;

	GLint F_ID = glGetUniformLocation(DID, "fog_flag");
	glUniform1i(F_ID, fog_flag);

	GLint N_ID = glGetUniformLocation(DID, "normal_flag");
	glUniform1i(N_ID, normal_flag);

	GLint C_ID = glGetUniformLocation(DID, "color_flag");
	glUniform1i(C_ID, fog_color);

	GLint M_ID = glGetUniformLocation(DID, "MM");
	glUniformMatrix4fv(M_ID, 1, GL_FALSE, &Model[0][0]);
	GLint V_ID = glGetUniformLocation(DID, "VM");
	glUniformMatrix4fv(V_ID, 1, GL_FALSE, &common_viewM[0][0]);
	GLint P_ID = glGetUniformLocation(DID, "PM");
	glUniformMatrix4fv(P_ID, 1, GL_FALSE, &common_projection[0][0]);

	// texture
	GLuint TextureID_1 = glGetUniformLocation(DID, "myTextureSampler_1");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureD_1);
	glUniform1i(TextureID_1, 0);	


	
	glDrawArrays(GL_TRIANGLES, 0, drawDSize);


	bool nothing = false;
	if (trace_size == 0)
	{
		star.push_back(Model);
		trace_size++;
	}

	if ((star.back() == Model))
	{
		nothing = true;
	}
	else
	{
		if (trace_size <= 60)
		{

			star.push_back(Model);
			trace_size++;

		}
		else if (trace_size == 61)
		{
			star.pop_front();
			star.push_back(Model);


		}
	}

	glUseProgram(star_ID);
	glBindVertexArray(objStarVao);
	V_ID = glGetUniformLocation(DID, "VM");
	glUniformMatrix4fv(V_ID, 1, GL_FALSE, &common_viewM[0][0]);
	P_ID = glGetUniformLocation(DID, "PM");
	glUniformMatrix4fv(P_ID, 1, GL_FALSE, &common_projection[0][0]);
	GLuint s = glGetUniformLocation(star_ID, "MM");
	GLuint TextureIDstar_1 = glGetUniformLocation(star_ID, "myTextureSampler_1");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureStar);
	glUniform1i(TextureIDstar_1, 0);
	F_ID = glGetUniformLocation(DID, "fog_flag");
	glUniform1i(F_ID, fog_flag);

	N_ID = glGetUniformLocation(DID, "normal_flag");
	glUniform1i(N_ID, normal_flag);

	C_ID = glGetUniformLocation(DID, "color_flag");
	glUniform1i(C_ID, fog_color);


	list<glm::mat4>::iterator itr = star.begin();
	glm::mat4 m;
	float scale = 0.7;
	int idx = 0;
	glm::mat4 scale_star = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	while (itr != star.end())
	{
		if ((idx != 0) && (idx % 10 == 0)&&(idx >9)&&(idx < 50))
		{
			scale += 0.7;
			scale_star = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
			m = (*(itr))*scale_star;
			glUniformMatrix4fv(s, 1, GL_FALSE, &m[0][0]);
			
			glDrawArrays(GL_TRIANGLES, 0, drawStarSize);
		}
		itr++;
		idx++;
	}


}


void drawE(void)
{
	GLfloat scale_fact = 0.03f;

	glUseProgram(EID);

	glBindVertexArray(objEVao);


	glm::mat4 scale_M = glm::scale(glm::mat4(1.0f), glm::vec3(scale_fact));
	glm::mat4 trans_M = glm::translate(glm::mat4(1.0f), glm::vec3(Emove + 5, 13.5f, 0.0f));
	glm::mat4 Model = trans_M * scale_M;

	
	apple_matrix = Model;

	GLint M_ID = glGetUniformLocation(EID, "MM");
	glUniformMatrix4fv(M_ID, 1, GL_FALSE, &Model[0][0]);
	GLint V_ID = glGetUniformLocation(EID, "VM");
	glUniformMatrix4fv(V_ID, 1, GL_FALSE, &common_viewM[0][0]);
	GLint P_ID = glGetUniformLocation(EID, "PM");
	glUniformMatrix4fv(P_ID, 1, GL_FALSE, &common_projection[0][0]);



	GLint F_ID = glGetUniformLocation(EID, "fog_flag");
	glUniform1i(F_ID, fog_flag);

	GLint N_ID = glGetUniformLocation(EID, "normal_flag");
	glUniform1i(N_ID, normal_flag);

	GLint C_ID = glGetUniformLocation(EID, "color_flag");
	glUniform1i(C_ID, fog_color);


	// texture
	GLuint TextureID_1 = glGetUniformLocation(EID, "myTextureSampler_1");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureE_1);
	glUniform1i(TextureID_1, 0);

	


	glDrawArrays(GL_TRIANGLES, 0, drawESize);
}


void drawB(void)
{
	GLfloat scale_fact = 0.3f;

	glUseProgram(BID);

	GLint F_ID = glGetUniformLocation(BID, "fog_flag");
	glUniform1i(F_ID, fog_flag);

	GLint N_ID = glGetUniformLocation(BID, "normal_flag");
	glUniform1i(N_ID, normal_flag);

	GLint C_ID = glGetUniformLocation(BID, "color_flag");
	glUniform1i(C_ID, fog_color);


	glBindVertexArray(planetBVao);
	glm::mat4 rot_M_S = glm::rotate(glm::mat4(1.0f), glm::radians(planetB_rotate_degree), glm::vec3(0, 1, 0));
	glm::mat4 trans_M_S = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));

	glm::mat4 scale_M = glm::scale(glm::mat4(1.0f), glm::vec3(scale_fact));
	glm::mat4 trans_M_T = glm::translate(glm::mat4(1.0f), glm::vec3(5.50f, -6.0f, 0.0f));
	glm::mat4 rot_M = glm::rotate(glm::mat4(1.0f), glm::radians(planetB_rotate_degree), glm::vec3(5, 3, 0));
	glm::mat4 trans_M = glm::translate(glm::mat4(1.0f), glm::vec3(-7.0f, 6.0f, 0.0f));
	glm::mat4 Model = trans_M*rot_M  *trans_M_T* trans_M_S*rot_M_S*scale_M;
	moon_matrix = Model;

	GLint M_ID = glGetUniformLocation(BID, "MM");
	glUniformMatrix4fv(M_ID, 1, GL_FALSE, &Model[0][0]);
	GLint V_ID = glGetUniformLocation(BID, "VM");
	glUniformMatrix4fv(V_ID, 1, GL_FALSE, &common_viewM[0][0]);
	GLint P_ID = glGetUniformLocation(BID, "PM");
	glUniformMatrix4fv(P_ID, 1, GL_FALSE, &common_projection[0][0]);

	// texture
	GLuint TextureID_1 = glGetUniformLocation(BID, "myTextureSampler_1");
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, TextureB_1);
	glUniform1i(TextureID_1, 0);
	
	

	glDrawArrays(GL_TRIANGLES, 0, drawBSize);

}

void drawG(void)
{

	glUseProgram(GID);
	glm::mat4 rockModelMat_temp;
	glm::mat4 trans_Init = glm::translate(glm::mat4(1.0f), glm::vec3(7.5f, -8.5f, 0.0f));
	glm::mat4 rot_Init = glm::rotate(glm::mat4(1.0f), glm::radians(earth_innRot_Degree), glm::vec3(0, 1, 0));
	glm::mat4 Model = trans_Init * rot_Init;


		glBindVertexArray(objGVao);

		GLint M_ID = glGetUniformLocation(GID, "MM");
		glUniformMatrix4fv(M_ID, 1, GL_FALSE, &Model[0][0]);
		GLint V_ID = glGetUniformLocation(GID, "VM");
		glUniformMatrix4fv(V_ID, 1, GL_FALSE, &common_viewM[0][0]);
		GLint P_ID = glGetUniformLocation(GID, "PM");
		glUniformMatrix4fv(P_ID, 1, GL_FALSE, &common_projection[0][0]);

		GLint F_ID = glGetUniformLocation(GID, "fog_flag");
		glUniform1i(F_ID, fog_flag);

		GLint N_ID = glGetUniformLocation(GID, "normal_flag");
		glUniform1i(N_ID, normal_flag);

		GLint C_ID = glGetUniformLocation(GID, "color_flag");
		glUniform1i(C_ID, fog_color);

		GLuint TextureID_1 = glGetUniformLocation(GID, "myTextureSampler_1");
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, TextureG_1);
		glUniform1i(TextureID_1, 0);
		

		
		glDrawArraysInstanced(GL_TRIANGLES, 0, drawGSize, amount);
	
}

void paintGL(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	handleKeys();




	// ================================ //
	// view matrix
	if (viewpoint_flag == 0)
	{
		common_viewM = glm::lookAt(glm::vec3(cameraX + dx, cameraY + dy, cameraZ + dz + radius), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}
	else if (viewpoint_flag == 1)
	{
		common_viewM = glm::lookAt(glm::vec3(cameraX + dx, cameraY + dy + radius, cameraZ + dz), glm::vec3(0, 0, 0), glm::vec3(0, 0, 1));
	}
	else if (viewpoint_flag == 2)
	{
		common_viewM = glm::lookAt(glm::vec3(cameraX + dx + radius, cameraY + dy, cameraZ + dz), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	}
	else if (viewpoint_flag == 3)
	{
		glm::vec4 p = { 0.0, -30.0, 45.0, 1.0 };
		glm::vec4 lookat = { 0.0,10.0,0.0,1.0 };
		glm::vec4 up = { 0.0,0.0,1.0,1.0 };


		camera_position = vec3(plane_matrix*p);
		camera_lookat = vec3(plane_matrix*lookat);
		camera_up = vec3(plane_matrix*up);
		common_viewM = glm::lookAt(camera_position, camera_lookat, camera_up);
	}
	// projection matrix
	common_projection = glm::perspective(camera_fov, 1.0f, 0.1f, 200.0f);






	glDepthMask(GL_FALSE);
	glUseProgram(Skybox_programID);

	GLuint Skb_ModelUniformLoaction = glGetUniformLocation(Skybox_programID, "M");
	glm::mat4 Skb_ModelMatrix = glm::mat4(1.0f);
	glUniformMatrix4fv(Skb_ModelUniformLoaction, 1, GL_FALSE, &Skb_ModelMatrix[0][0]);

	glm::mat4 view = glm::mat4(glm::mat3(common_viewM));
	glm::mat4 projection = glm::perspective(camera_fov, 1.0f, 0.1f, 100.0f);

	glUniformMatrix4fv(glGetUniformLocation(Skybox_programID, "view"), 1, GL_FALSE, &view[0][0]);
	glUniformMatrix4fv(glGetUniformLocation(Skybox_programID, "projection"), 1, GL_FALSE, &projection[0][0]);
	glUniform1i(glGetUniformLocation(Skybox_programID, "fog_flag"), fog_flag);
	GLint C_ID = glGetUniformLocation(Skybox_programID, "color_flag");
	glUniform1i(C_ID, fog_color);

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(glGetUniformLocation(Skybox_programID, "skybox"), 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, sea_cubemapTexture);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);










	
	//=== draw ===//
	// set lighting parameters

	drawE();
	set_lighting(EID);
	



	set_lighting(programID);
	// draw earth
	drawEarth();
	
	set_lighting(DID);
	set_lighting(star_ID);
	drawD();

	if (C <= 20)
	{
		set_lighting(BID);
		drawB();
	}
	else 
	{
		int i=0;
	}
	set_lighting(CID);
	drawC();

	set_lighting(GID);
	drawG();

	C = collision(temp_B_max, temp_B_min, temp_D_max, temp_D_min);
	glm::vec4 dmax = { D_max.x,D_max.y,D_max.z,1.0 };
	glm::vec4 dmin = { D_min.x,D_min.y,D_min.z,1.0 };
	temp_D_min = vec3(plane_matrix*dmin);
	temp_D_max = vec3(plane_matrix*dmax);
	temp_D_min.x -= 2.5f;
	temp_D_min.y -= 2.5f;
	temp_D_min.z -= 2.5f;
	temp_D_max.x += 2.5f;
	temp_D_max.y += 2.5f;
	temp_D_max.z += 2.5f;
	printf("%d\n", C);



	glm::vec4 bmax = { B_max.x,B_max.y,B_max.z,1.0 };
	glm::vec4 bmin = { B_min.x,B_min.y,B_min.z,1.0 };
	temp_B_max = vec3(moon_matrix*bmax);
	temp_B_min = vec3(moon_matrix*bmin);

	
	glutSwapBuffers();
	glutPostRedisplay();
}

void Shaders_Installer()
{
	programID = installShaders("shader/planet.vs", "shader/earth.frag");
	Skybox_programID = installShaders("shader/skybox.vs", "shader/skybox.frag");
	DID = installShaders("shader/planet.vs", "shader/DBEG.frag");
	BID = installShaders("shader/planet.vs", "shader/DBEG.frag");
	CID = installShaders("shader/planet.vs", "shader/C.frag");
	EID = installShaders("shader/planet.vs", "shader/DBEG.frag");
	GID = installShaders("shader/rock.vs", "shader/DBEG.frag");
	star_ID = installShaders("shader/planet.vs", "shader/DBEG.frag");


	if (!checkProgramStatus(programID))
		return;
}

void initializedGL(void)
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	glEnable(GL_CULL_FACE);
	//glEnable(GL_FOG);

	// install all shaders
	Shaders_Installer();
	// load required obj and textures
	sendDataToOpenGL();
	ISoundEngine* engine = createIrrKlangDevice();
	engine->play2D("abcd.mp3", true);
}

void timerFunction(int id)
{
	vehicle_innRot_Degree += Vehicle_s;
	earth_innRot_Degree += 0.3;
	planetB_rotate_degree += 0.3;
	
	if (Etoleft)
	{
		Emove -= 0.05f;
		if (Emove < -10.0f)
		{
			Etoleft = false;
		}
	}
	else
	{
		Emove += 0.05f;
		if (Emove > 8.0f)
		{
			Etoleft = true;
		}
	}

	glutPostRedisplay();
	glutTimerFunc(700.0f / 60.0f, timerFunction, 1);
}
void controlFB(int ID)
{
	;
}
void reshape(int w, int h) {

	if (h == 0)
		h = 1;

	float ratio = 1.0* w / h;

	// 单位化投影矩阵。
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// 设置视口大小为增个窗口大小
	glViewport(0, 0, w, h);

	// 设置正确的投影矩阵
	gluPerspective(45, ratio, 1, 1000);
	//下面是设置模型视图矩阵
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


	gluLookAt(camera_position[0], camera_position[1], camera_position[2],camera_lookat[0], camera_lookat[1], camera_lookat[2],camera_up[0], camera_up[1], camera_up[2]);//观察者位置
}

int main(int argc, char *argv[])
{
	ISoundEngine* engine = createIrrKlangDevice();


	// play some sound stream, looped
	engine->play2D("h.mp3");

	/*Initialization of GLUT library*/
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowPosition(100, 100);
	height = GetSystemMetrics(SM_CYSCREEN)*0.8;
	glutInitWindowSize(height, height);

	glutInitContextVersion(4, 3);
	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);
	mainWindowID = glutCreateWindow("i-Navigation");
	
	



	// initialize openGL
	initializedGL();
	// draw
	glutDisplayFunc(paintGL);
	

	glutMouseFunc(Mouse_Wheel_Func);
	glutPassiveMotionFunc(PassiveMouse);
	glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
	glutSpecialFunc(handleSpecialKeypress);
	glutSpecialUpFunc(handleSpecialKeyReleased);

	glutTimerFunc(700.0f / 60.0f, timerFunction, 1);

	
	glui = GLUI_Master.create_glui_subwindow(mainWindowID, GLUI_SUBWINDOW_RIGHT);
	glui->set_main_gfx_window(mainWindowID);
	glui->add_separator();
	GLUI_StaticText *infoText = glui->add_statictext("SpaceVehicle-CUHK");
	infoText->set_alignment(GLUI_ALIGN_CENTER);
	glui->add_separator();
	(new GLUI_Spinner(glui, "Vehicle_S", &Vehicle_s))->set_int_limits(0, 60);


	glui->add_separator();
	glui->add_statictext("Move/NormalMap");
	glui->add_checkbox("Fog", &fog_flag, 1, controlFB);
	glui->add_checkbox("Normal", &normal_flag, 1, controlFB);


	glui->add_separator();
	GLUI_Panel *obj_panel = glui->add_panel("Viewpoint");
	GLUI_RadioGroup *group1 = glui->add_radiogroup_to_panel(obj_panel, &viewpoint_flag, 4, controlFB);
	glui->add_radiobutton_to_group(group1, "origin");
	glui->add_radiobutton_to_group(group1, "top");
	glui->add_radiobutton_to_group(group1, "right");
	glui->add_radiobutton_to_group(group1, "plane");

	glui->add_separator();
	GLUI_Panel *obj_panel2 = glui->add_panel("Fog Color");
	GLUI_RadioGroup *group2 = glui->add_radiogroup_to_panel(obj_panel2, &fog_color, 2, controlFB);
	glui->add_radiobutton_to_group(group2, "Grey");
	glui->add_radiobutton_to_group(group2, "Blood");


	glui->add_separator();
	glui->add_button("Quit", 0, (GLUI_Update_CB)exit);

	glui->set_main_gfx_window(mainWindowID);



	glutReshapeFunc(reshape);

	/*Enter the GLUT event processing loop which never returns.*/
	glutMainLoop();

	return 0;
}