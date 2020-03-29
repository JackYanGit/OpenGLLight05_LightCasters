#define GLEW_STATIC           ////////////////////5
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
//包含OpenGL数学运算库
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Camera.h"
#include "Material.h"
#include "LightDirectional.h"
#include "LightPoint.h"
#include "LightSpot.h"
#pragma region Model Data
float vertices[] = {
	// positions          // normals           // texture coords
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  1.0f,  1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  0.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,  1.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,  0.0f,  1.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f,
	 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  1.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,  0.0f,  1.0f
};
//EBO数据
unsigned int indices[] = {
	0,1,2,
	2,3,0
};
//10个立方体的平移向量
glm::vec3 cubePositions[] = {
  glm::vec3(0.0f,  0.0f,  0.0f),
  glm::vec3(2.0f,  5.0f, -15.0f),
  glm::vec3(-1.5f, -2.2f, -2.5f),
  glm::vec3(-3.8f, -2.0f, -12.3f),
  glm::vec3(2.4f, -0.4f, -3.5f),
  glm::vec3(-1.7f,  3.0f, -7.5f),
  glm::vec3(1.3f, -2.0f, -2.5f),
  glm::vec3(1.5f,  2.0f, -2.5f),
  glm::vec3(1.5f,  0.2f, -1.5f),
  glm::vec3(-1.3f,  1.0f, -1.5f)
};
#pragma endregion

#pragma region Camera Declare
//全局camera
Camera camera(glm::vec3(0, 0, 3.0f), glm::radians(0.0f), glm::radians(180.0f), glm::vec3(0, 1.0f, 0));
#pragma endregion

#pragma region Light Declare
//平行光
//LightDirectional light(glm::vec3(10.0f, 10.0f, -5.0f),glm::vec3(glm::radians(45.0f), glm::radians(45.0f),0));
//点光源
//LightPoint light(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec3(glm::radians(45.0f), glm::radians(45.0f), 0), glm::vec3(10.0f, 10.0f, 10.0f));
//聚光灯
LightSpot light(glm::vec3(0.0f, 5.0f, 0.0f), glm::vec3(glm::radians(90.0f), 0, 0));
#pragma endregion
#pragma endregion

#pragma region Input Declare
//鼠标位置
float lastX;
float lastY;
bool firstMouse = true;
//输入控制函数声明
void processInput(GLFWwindow* window);
//鼠标回调函数声明
void mouse_callback(GLFWwindow* window,double xPos,double yPos);
//滑轮回调函数声明
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//图片加载函数声明
unsigned int loadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot, bool flipped);
#pragma endregion

int main() {
	#pragma region Open Window
	//初始化
	glfwInit();
	//设置版本3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//设置配置
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL 多个立方体", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	//绑定窗口到当前线程
	glfwMakeContextCurrent(window);
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		return -1;
	}
	//禁用光标
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//注册鼠标事件回调函数
	glfwSetCursorPosCallback(window, mouse_callback);
	//注册滑轮事件回调函数
	glfwSetScrollCallback(window, scroll_callback);
	//设置绘图区域
	glViewport(0, 0, 800, 600);
	//设置背面剔除 逆时针绘制为正面
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);

	//设置只绘制线条
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//启用深度测试  遮挡的部位不会绘制出来
	glEnable(GL_DEPTH_TEST);
#pragma endregion

	#pragma region Init Shader Program
	Shader* pshader = new Shader("vertextSource.vert", "fragmentSource.frag");
	pshader->print();
#pragma endregion 

#pragma region Init Material
	Material* myMaterial = new Material(pshader,
		loadImageToGPU("container.png",GL_RGB,GL_RGB,Shader::DIFFUSE,true),
		loadImageToGPU("container_specular.png", GL_RGBA, GL_RGBA, Shader::SPECULAR, false),
		loadImageToGPU("matrix.jpg", GL_RGB, GL_RGB, Shader::EMISSION, false),
		glm::vec3(1.0f, 1.0f, 1.0f), 
		32.0f);
#pragma endregion

	#pragma region Init and Load Models to VAO,VBO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	/*unsigned int EBO;
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);*/

	//与layout(location=0)中 lacation 缓冲区位置一样（0-15）
	//位置属性
	glVertexAttribPointer(15, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(15);
	//颜色属性
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	//glEnableVertexAttribArray(1);
	//uv坐标
	glVertexAttribPointer(7, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(7);
	//法向量
	glVertexAttribPointer(9, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(9);
#pragma endregion 
	
	#pragma region Init and Load Texture
	/*unsigned int TexBufferA;
	TexBufferA = loadImageToGPU("box.jpg", GL_RGB, GL_RGB, 0, false);

	unsigned int TexBufferB;
	TexBufferB = loadImageToGPU("awesomeface.png", GL_RGBA, GL_RGBA, 13,true);*/
#pragma endregion 

	#pragma region Prepare MVP Matrices
	//局部坐标转世界坐标  模型矩阵
	glm::mat4 modelMat;
	
	//世界坐标转相机坐标  观察矩阵
	glm::mat4 viewMat;
	
	//相机坐标转屏幕坐标（2D）投影矩阵
	glm::mat4 projMat;
	projMat = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
#pragma endregion 

	#pragma region Render Loop
	while (!glfwWindowShouldClose(window))
	{
		//Process input
		processInput(window);
		//Clear screen
		glClearColor(0.01, 0.01, 0.01, 1.0);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		for (size_t i = 0; i < 10; i++)
		{
			//set Model Matrix
			modelMat = glm::translate(glm::mat4(1.0f), cubePositions[i]);
			//旋转
			if (i % 3 < 2) {
				modelMat = glm::rotate(modelMat, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
			}
			//Set View and Projection here
			viewMat = camera.GetViewMatrix();

			//Set Material ->Shader Program
			pshader->use();

			//Set Material ->Texture
			glActiveTexture(GL_TEXTURE0+Shader::DIFFUSE);
			glBindTexture(GL_TEXTURE_2D, myMaterial->diffuse);
			glActiveTexture(GL_TEXTURE0+ Shader::SPECULAR);
			glBindTexture(GL_TEXTURE_2D, myMaterial->specular);
			glActiveTexture(GL_TEXTURE0 + Shader::EMISSION);
			glBindTexture(GL_TEXTURE_2D, myMaterial->emission);

			//Set Material ->Unifrom
			//uniform传递texture贴图数据
			/*glUniform1i(glGetUniformLocation(pshader->ID, "ourTextrue"), 0);
			glUniform1i(glGetUniformLocation(pshader->ID, "ourFace"), 13);*/
			//uniform传递旋转位移等变换矩阵，完成投影
			glUniformMatrix4fv(glGetUniformLocation(pshader->ID, "modelMat"), 1, GL_FALSE, glm::value_ptr(modelMat));
			glUniformMatrix4fv(glGetUniformLocation(pshader->ID, "viewMat"), 1, GL_FALSE, glm::value_ptr(viewMat));
			glUniformMatrix4fv(glGetUniformLocation(pshader->ID, "projMat"), 1, GL_FALSE, glm::value_ptr(projMat));
			//传递物体颜色和环境光颜色
			glUniform3f(glGetUniformLocation(pshader->ID, "objColor"), 1.0f, 1.0f, 1.0f);
			glUniform3f(glGetUniformLocation(pshader->ID, "ambientColor"), .3f, .3f, .3f);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightPos"), light.postion.x, light.postion.y, light.postion.z);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightColor"), light.color.r, light.color.g, light.color.b);
			glUniform3f(glGetUniformLocation(pshader->ID, "lightDirUniform"), light.direction.x, light.direction.y, light.direction.z);
			/*glUniform1f(glGetUniformLocation(pshader->ID, "lightP.constant"), light.constant);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP.linear"), light.linear);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightP.quadratic"), light.quadratic);*/
			glUniform1f(glGetUniformLocation(pshader->ID, "lightS.cosPhyInner"), light.cosPhyInner);
			glUniform1f(glGetUniformLocation(pshader->ID, "lightS.cosPhyOutter"), light.cosPhyOutter);

			glUniform3f(glGetUniformLocation(pshader->ID, "cameraPos"), camera.Position.x, camera.Position.y, camera.Position.z);

			//传递material
			//glUniform3f(glGetUniformLocation(pshader->ID, "material.ambient"), 1.0f, 1.0f, 1.0f);
			myMaterial->shader->SetUniform3f("material.ambient", myMaterial->ambient);
			//myMaterial->shader->SetUniform3f("material.diffuse", myMaterial->diffuse);
			//myMaterial->shader->SetUniform3f("material.specular", myMaterial->specular);
			myMaterial->shader->SetUniform1i("material.diffuse", Shader::DIFFUSE);
			myMaterial->shader->SetUniform1i("material.specular", Shader::SPECULAR);
			myMaterial->shader->SetUniform1i("material.emission", Shader::EMISSION);
			myMaterial->shader->SetUniform1f("material.shininess", myMaterial->shininess);
			//Draw Call VBO方式绘制
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
		//Clean up,prepare for next render loop
		glfwSwapBuffers(window);
		glfwPollEvents();
		camera.UpdateCameraPos();

	}
#pragma endregion

	//Exit Programe
	glfwTerminate();
	return 0;
}
void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.speedZ = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.speedZ = -1.0f;
	}
	else {
		camera.speedZ = .0f;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.speedX = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.speedX = -1.0f;
	}
	else {
		camera.speedX = .0f;
	}
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
		camera.speedY = 1.0f;
	}
	else if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		camera.speedY = -1.0f;
	}
	else {
		camera.speedY = .0f;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = lastX- xpos;
	float yoffset = lastY- ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.05;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.speedZ = yoffset*100;
}

unsigned int loadImageToGPU(const char* filename, GLint internalFormat, GLenum format, int textureSlot, bool flipped)
{
	//上下颠倒texture贴图
	stbi_set_flip_vertically_on_load(flipped);
	unsigned int TexBuffer;
	glGenTextures(1, &TexBuffer);
	glActiveTexture(GL_TEXTURE0 + textureSlot);
	glBindTexture(GL_TEXTURE_2D, TexBuffer);
	int width, height, numChannel;
	unsigned char* data = stbi_load(filename, &width, &height, &numChannel, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "load image failed0." << std::endl;
	}
	stbi_image_free(data);
	return TexBuffer;
}
