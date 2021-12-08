/*---------------------------------------------------------*/
/* ----------------  ProyectoFinal                -----------*/
/*-----------------    2022-1  --------------------------*/
/*------------- Alumno: Troncoso Moreno Javier Adan---------------*/
/*------------- No. Cuenta: 111005008---------------*/
#include <Windows.h>

#include <glad/glad.h>
#include <glfw3.h>	//main
#include <stdlib.h>		
#include <glm/glm.hpp>	//camera y model
#include <glm/gtc/matrix_transform.hpp>	//camera y model
#include <glm/gtc/type_ptr.hpp>
#include <time.h>


#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>	//Texture

#define SDL_MAIN_HANDLED
#include <SDL/SDL.h>

#include <shader_m.h>
#include <camera.h>
#include <modelAnim.h>
#include <model.h>
#include <Skybox.h>
#include <iostream>

//#pragma comment(lib, "winmm.lib")

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void my_input(GLFWwindow *window);
void my_input(GLFWwindow* window, int key, int scancode, int action, int mods);
void animate(void);
void musica(void);

// settings
unsigned int SCR_WIDTH = 800;
unsigned int SCR_HEIGHT = 600;
GLFWmonitor* monitors;

void getResolution(void);

// camera
Camera camera(glm::vec3(0.0f, 10.0f, 90.0f));
float MovementSpeed = 0.1f;
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
const int FPS = 60;
const int LOOP_TIME = 1000 / FPS; // = 16 milisec // 1000 millisec == 1 sec
double	deltaTime = 0.0f,
lastFrame = 0.0f;

//Lighting
glm::vec3 lightPosition(0.0f, 4.0f, -10.0f);
glm::vec3 lightDirection(15.0f, 0.0f, 0.0f);
glm::vec3 lightColores(0.0f, 0.0f, 1.0f);
double myy = 0.0;
double myVariable = 0.0;
// posiciones
//float x = 0.0f;
//float y = 0.0f;
float	movAuto_x = 0.0f,
movAuto_z = 0.0f,
movAuto_y = 0.0f,
orienta = 0.0f;
float giroLlantas = 0.0f;
int estado = 0;
int edo = 0;
float rotPuertaDer = 0;
float puertag = 0;
float l = 0;
bool	animacion = false,
animacion1 = false,
animacion2= false,
animacion3= false,
musica1=false,
recorrido1 = true,
recorrido2 = false,
recorrido3 = false,
recorrido4 = false;



void animate(void)
{
	

	//Animaciones puertas
	if (animacion)
	{
		if (estado == 0)
		{
			rotPuertaDer += 001.0f;
			if (rotPuertaDer >= 90.0f) 
				estado = 1;
		}
		if (estado == 1)
		{
			animacion = false;
			estado = 0;
		}
	if (musica1) {
			musica();
	}
	}
	//Animacion coche
	if (animacion3)
	{
		if (edo == 0 && estado == 1) {
			movAuto_x -= 3.0f;
			if (movAuto_x <= -230.0f)
				edo = 1;
		}
		if (edo == 1)
		{
			orienta = 90.0f;
			movAuto_z += 3.0f;
			if (movAuto_z >= 220.0f)
				edo = 2;
		}
		if (edo == 2)
		{
			orienta = 180.0f;
			movAuto_x += 3.0f;
			if (movAuto_x >= 350.0f)
				edo=3;
		}
		if (edo == 3)
		{
			orienta = 270.0f;
			movAuto_z -= 3.0f;
			if (movAuto_z <= -220.0f)
				edo=4;
		}
		if (edo == 4)
		{
			orienta = 360.0f;
			movAuto_x -= 3.0f;
			if (movAuto_x <= -220.0f)
				edo=5;
		}
		if (edo == 5)
		{
			orienta = 90.0f;
			movAuto_z += 3.0f;
			if (movAuto_z >= 20.0f)
				edo=6;
		}
		if (edo == 6 && estado == 1)
		{
			edo = 7;
		}
		if (edo == 7)
		{
			orienta = 180.0f;
			movAuto_x += 3.0f;
			if (movAuto_x >= 0.0f)
				edo=0;
		}
	}
	//Animacion Garage
	if (animacion1)
	{
		if (estado == 0)
		{
			puertag -= 001.0f;
			if (puertag <= -90.0f)
				estado = 1;
		}
		if (estado == 1)
		{
			animacion1 = false;
		}
	}
	//Animacion Remolino
	if (animacion2)
	{
			l -= 001.0f;
		
	}


}

void musica() {
		PlaySound(TEXT("Summer.wav"), NULL, SND_FILENAME | SND_ASYNC);
}

void getResolution()
{
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = mode->width;
	SCR_HEIGHT = (mode->height) - 80;
}


int main()
{
	// glfw: initialize and configure
	// ------------------------------
	glfwInit();
	/*glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);*/

#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// glfw window creation
	// --------------------
	// --------------------
	monitors = glfwGetPrimaryMonitor();
	getResolution();

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CGeIHC", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwSetWindowPos(window, 0, 30);
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetScrollCallback(window, scroll_callback);
	glfwSetKeyCallback(window, my_input);

	// tell GLFW to capture our mouse
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

	// glad: load all OpenGL function pointers
	// ---------------------------------------
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// configure global opengl state
	// -----------------------------
	glEnable(GL_DEPTH_TEST);

	// build and compile shaders
	// -------------------------
	Shader staticShader("Shaders/shader_Lights.vs", "Shaders/shader_Lights.fs");
	Shader skyboxShader("Shaders/skybox.vs", "Shaders/skybox.fs");
	Shader animShader("Shaders/anim.vs", "Shaders/anim.fs");

	vector<std::string> faces
	{
		"resources/skybox/right.jpg",
		"resources/skybox/left.jpg",
		"resources/skybox/top.jpg",
		"resources/skybox/bottom.jpg",
		"resources/skybox/front.jpg",
		"resources/skybox/back.jpg"
	};

	Skybox skybox = Skybox(faces);

	// Shader configuration
	// --------------------
	skyboxShader.use();
	skyboxShader.setInt("skybox", 0);

	// load models
	Model piso("resources/objects/piso/Piso.obj");
	Model PI("resources/objects/fachada/Puertaizquierda.obj");
	Model PD("resources/objects/fachada/Puertaderecha.obj");
	Model puerta("resources/objects/Garage/puerta.obj");
	Model pared ("resources/objects/Garage/pared.obj");
	Model coche("resources/objects/coche/coche.obj");
	Model cama("resources/objects/Recamara2/cama.obj");
	Model wc("resources/objects/Recamara3/wc.obj");
	Model tv("resources/objects/Recamara3/tv.obj");
	Model f("resources/objects/House/casa3.obj");
	Model t("resources/objects/House/techo.obj");
	Model cocina("resources/objects/Comedor/cocina.obj");
	Model m("resources/objects/Recamara2/muebles.obj");
	Model sofa("resources/objects/Comedor/sofa.obj");
	Model bano("resources/objects/Recamara1/wc1.obj");
	Model puertas("resources/objects/Recamara1/puertas.obj");
	Model ala("resources/objects/ala/ala.obj");
	Model base("resources/objects/ala/base.obj");
	Model c("resources/objects/Comedor/Comedor1.obj");


	// draw in wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// render loop
	// -----------
	while (!glfwWindowShouldClose(window))
	{
		skyboxShader.setInt("skybox", 0);

		// per-frame time logic
		// --------------------
		lastFrame = SDL_GetTicks();

		// input
		// -----
		//my_input(window);
		animate();

		// render
		// ------
		glClearColor(0.3f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// don't forget to enable shader before setting uniforms
		staticShader.use();
		//Setup Advanced Lights
		staticShader.setVec3("viewPos", camera.Position);
		staticShader.setVec3("dirLight.direction", lightDirection);
		staticShader.setVec3("dirLight.ambient", glm::vec3(1.0f, 1.0f, 1.0f));
		staticShader.setVec3("dirLight.diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("dirLight.specular", glm::vec3(0.0f, 0.0f, 0.0f));

		staticShader.setVec3("pointLight[0].position", lightPosition);
		staticShader.setVec3("pointLight[0].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[0].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[0].constant", 0.008f);
		staticShader.setFloat("pointLight[0].linear", 0.0009f);
		staticShader.setFloat("pointLight[0].quadratic", 0.00032f);

		staticShader.setVec3("pointLight[1].position", glm::vec3(-60.0, 0.0f, 80.0f));
		staticShader.setVec3("pointLight[1].ambient", glm::vec3(0.0f, 0.0f, 0.0f));;
		staticShader.setVec3("pointLight[1].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[1].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[1].constant", 1.0f);
		staticShader.setFloat("pointLight[1].linear", 0.0009f);
		staticShader.setFloat("pointLight[1].quadratic", 0.00032f);

		staticShader.setVec3("pointLight[2].position", glm::vec3(60.0, 0.0f, 80.0f));
		staticShader.setVec3("pointLight[2].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[2].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[2].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[2].constant", 0.008f);
		staticShader.setFloat("pointLight[2].linear", 0.0009f);
		staticShader.setFloat("pointLight[2].quadratic", 0.00032f);

		staticShader.setVec3("pointLight[3].position", glm::vec3(0.0, 0.0f, -80.0f));
		staticShader.setVec3("pointLight[3].ambient", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[3].diffuse", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setVec3("pointLight[3].specular", glm::vec3(0.0f, 0.0f, 0.0f));
		staticShader.setFloat("pointLight[3].constant", 0.008f);
		staticShader.setFloat("pointLight[3].linear", 0.0009f);
		staticShader.setFloat("pointLight[3].quadratic", 0.00032f);

		staticShader.setFloat("material_shininess", 32.0f);

		glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 tmp = glm::mat4(1.0f);
		// view/projection transformations
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 10000.0f);
		glm::mat4 view = camera.GetViewMatrix();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		//// Light
		glm::vec3 lightColor = glm::vec3(0.6f);
		glm::vec3 diffuseColor = lightColor * glm::vec3(0.5f);
		glm::vec3 ambientColor = diffuseColor * glm::vec3(0.75f);


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------
		//Remember to activate the shader with the animation
		animShader.use();
		animShader.setMat4("projection", projection);
		animShader.setMat4("view", view);

		animShader.setVec3("material.specular", glm::vec3(0.5f));
		animShader.setFloat("material.shininess", 32.0f);
		animShader.setVec3("light.ambient", ambientColor);
		animShader.setVec3("light.diffuse", diffuseColor);
		animShader.setVec3("light.specular", 1.0f, 1.0f, 1.0f);
		animShader.setVec3("light.direction", lightDirection);
		animShader.setVec3("viewPos", camera.Position);
		/*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-40.3f, 1.75f, 0.3f)); // translate it down so it's at the center of the scene
		model = glm::scale(model, glm::vec3(1.2f));	// it's a bit too big for our scene, so scale it down
		model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f));
		animShader.setMat4("model", model);
		//animacionPersonaje.Draw(animShader);*/



		// -------------------------------------------------------------------------------------------------------------------------
		// Segundo Personaje Animacion
		// -------------------------------------------------------------------------------------------------------------------------

	

		// -------------------------------------------------------------------------------------------------------------------------
		// Escenario
		// -------------------------------------------------------------------------------------------------------------------------
		staticShader.use();
		staticShader.setMat4("projection", projection);
		staticShader.setMat4("view", view);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));  //Comedor Sala
		staticShader.setMat4("model", model);
		bano.Draw(staticShader);  //bano
		///*
		model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -1.75f, 0.0f));
		staticShader.setMat4("model", model);
		piso.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));
		staticShader.setMat4("model", model);
		f.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-205.0f, 26.0f, -135.0f));//Cama Recamara2
		staticShader.setMat4("model", model);
		cama.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(21.0f, 26.0f, -48.0f));//Cama Recamara1
		staticShader.setMat4("model", model);
		cama.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));//Cama Recamara3
		staticShader.setMat4("model", model);
		cama.Draw(staticShader);


		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 30.0f, -10.0f));
		staticShader.setMat4("model", model);
		tv.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.2f, -10.0f));
		model = glm::rotate(model, glm::radians(puertag), glm::vec3(0.0f, 0.0f, 1.0));
		staticShader.setMat4("model", model);
		puerta.Draw(staticShader);
		

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));
		staticShader.setMat4("model", model);
		cama.Draw(staticShader);
		
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));
		staticShader.setMat4("model", model);
		f.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));  //Silla y Computadora
		staticShader.setMat4("model", model);
		t.Draw(staticShader);
		
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));  //Muebles recamara2
		staticShader.setMat4("model", model);
	    pared.Draw(staticShader);
		

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));  //Comedor Sala
		staticShader.setMat4("model", model);
		m.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));  //Comedor Sala
		staticShader.setMat4("model", model);
		cocina.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));  //Sofa Sala
		staticShader.setMat4("model", model);
		sofa.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(-200.0f, 20.0f, -60.1f));
		model = glm::rotate(model, glm::radians(l), glm::vec3(1.0f, 0.0f, 0.0f));
		staticShader.setMat4("model", model);
		ala.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(-200.0f, 20.0f, -60.1f));
		staticShader.setMat4("model", model);
		base.Draw(staticShader);

		model = glm::translate(tmp, glm::vec3(-210.0f, 26.0f, -10.0f));
		staticShader.setMat4("model", model);
		c.Draw(staticShader);

		model = glm::translate(glm::mat4(1.0f), glm::vec3(-173.0f + movAuto_x, -1.8f, -22.0f + movAuto_z));
		model = glm::rotate(model, glm::radians(-90.0f+orienta), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(10.0f, 10.0f, 10.0f));
		staticShader.setMat4("model", model);
		coche.Draw(staticShader);



		
		//*/


		// -------------------------------------------------------------------------------------------------------------------------
		// Personaje
		// -------------------------------------------------------------------------------------------------------------------------
		
		// -------------------------------------------------------------------------------------------------------------------------
		// Caja Transparente --- Siguiente Práctica
		// -------------------------------------------------------------------------------------------------------------------------
	
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));
		staticShader.setMat4("model", model);
		wc.Draw(staticShader);
		glDisable(GL_BLEND);
		glEnable(GL_BLEND);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, -0.5f, 30.0f));
		model = glm::rotate(model, glm::radians(-rotPuertaDer), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		PI.Draw(staticShader);
		glDisable(GL_BLEND);


		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, -0.5f, 49.0f));
		model = glm::rotate(model, glm::radians(rotPuertaDer), glm::vec3(0.0f, 1.0f, 0.0f));
		staticShader.setMat4("model", model);
		PD.Draw(staticShader);
		glDisable(GL_BLEND);
		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		model = glm::translate(glm::mat4(1.0f), glm::vec3(-210.0f, 26.0f, -10.0f));
		staticShader.setMat4("model", model);
		puertas.Draw(staticShader);
		glDisable(GL_BLEND);
		// ------------------------------------------------------------------------------------------------------------------------
		// Termina Escenario
		// -------------------------------------------------------------------------------------------------------------------------

		//-------------------------------------------------------------------------------------
		// draw skybox as last
		// -------------------
		skyboxShader.use();
		skybox.Draw(skyboxShader, view, projection, camera);

		// Limitar el framerate a 60
		deltaTime = SDL_GetTicks() - lastFrame; // time for full 1 loop
		//std::cout <<"frame time = " << frameTime << " milli sec"<< std::endl;
		if (deltaTime < LOOP_TIME)
		{
			SDL_Delay((int)(LOOP_TIME - deltaTime));
		}

		// glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
		// -------------------------------------------------------------------------------
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	skybox.Terminate();

	glfwTerminate();
	return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void my_input(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		camera.ProcessKeyboard(FORWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		camera.ProcessKeyboard(BACKWARD, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		camera.ProcessKeyboard(LEFT, (float)deltaTime);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		camera.ProcessKeyboard(RIGHT, (float)deltaTime);
	

	//Animaciones
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
		animacion ^= true;
	if (key == GLFW_KEY_7 && action == GLFW_PRESS)
		animacion1 ^= true;
	if (key == GLFW_KEY_8 && action == GLFW_PRESS)
		musica();
	if (key == GLFW_KEY_9 && action == GLFW_PRESS)
		animacion2 ^= true;
	if (key == GLFW_KEY_X && action == GLFW_PRESS)
		animacion3 ^= true;

	if (key == GLFW_KEY_R && action == GLFW_PRESS && animacion == false)
	puertag = 0.0f, rotPuertaDer = 0.0f,l=0.0f,estado=0;
	    
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	camera.ProcessMouseMovement(xoffset, yoffset);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.ProcessMouseScroll(yoffset);
}