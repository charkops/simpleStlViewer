#include <iostream>

#include "StlReader.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Camera.hpp"

#include "ConvertRanges.hpp"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glad/glad.h"
#include <GLFW/glfw3.h>



using std::cout;
using std::cerr;
using std::endl;
using std::string;

using namespace simpleStlViewer;

// Settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

Camera camera (glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// Timing 
float deltaTime = 0.0f;
float lastFrame = 0.0f;

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
  if (firstMouse) {
    lastX = xpos;
    lastY = ypos;
    firstMouse = false;
  }

  float xoffset = xpos - lastX;
  float yoffset = lastY - ypos;

  lastX = xpos;
  lastY = ypos;

  camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
  camera.ProcessMouseScroll(yoffset);
}

void processInput(GLFWwindow *window) {
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}

  if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    camera.ProcessKeyboard(FORWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    camera.ProcessKeyboard(BACKWARD, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    camera.ProcessKeyboard(LEFT, deltaTime);
  if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    camera.ProcessKeyboard(RIGHT, deltaTime);
}

class StlMesh {
public:
	StlMesh(const std::vector<simpleStlViewer::Triangle> &triangles) {
		// Convert triangles to std::vector<float>
		vertices.reserve(triangles.size() * 3 * 3);
		for (const auto &tri : triangles) {
			vertices.push_back(tri.p0_.x_);
			vertices.push_back(tri.p0_.y_);
			vertices.push_back(tri.p0_.z_);
			vertices.push_back(tri.p1_.x_);
			vertices.push_back(tri.p1_.y_);
			vertices.push_back(tri.p1_.z_);
			vertices.push_back(tri.p2_.x_);
			vertices.push_back(tri.p2_.y_);
			vertices.push_back(tri.p2_.z_);
		}

    convertRanges();
		setupMesh();
	};

	~StlMesh() = default;

	void Draw(Shader &shader) {
		shader.use();
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, vertices.size() / 3);
		glBindVertexArray(0);
	};

private:
	unsigned int VAO, VBO;
	std::vector<float> vertices;
	void setupMesh() {
		// Generate VAO, VBO
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
		
		glBindVertexArray(VAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
		glBindVertexArray(0);
	};

  void convertRanges(float new_min = -0.5, float new_max = 0.5) {
    convertVectorToNDC(vertices, new_min, new_max);
  }
};

void sendToShader(simpleStlViewer::Shader &shader, const std::string &name, const glm::mat4 &matrixName) {
  int matrixNameLoc = glGetUniformLocation(shader.ID, name.c_str());
  glUniformMatrix4fv(matrixNameLoc, 1, GL_FALSE, glm::value_ptr(matrixName));
}

int main(int argc, char **argv) {
	if (argc != 2) {
		cout << "Usage: " << argv[0] << "\tfile.stl" << endl;
		return EXIT_FAILURE;
	}

  std::string stlFile (argv[1]);
	auto triangles = simpleStlViewer::loadStlFileIntoTriangles(stlFile);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


	GLFWwindow *window = glfwCreateWindow(800, 600, "StlViewer", NULL, NULL);
	if (window == NULL) {
		cout << "Could not create window" << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  glfwSetCursorPosCallback(window, mouse_callback);
  glfwSetScrollCallback(window, scroll_callback);

	simpleStlViewer::Shader shader ("../shaders/vertexShader.glsl", "../shaders/fragmentShader.glsl");
	shader.use();	

	StlMesh mesh (triangles);

	glm::mat4 model = glm::mat4(1.0f);
	glm::mat4 view = glm::mat4(1.0f);

	while(!glfwWindowShouldClose(window)) {

    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

		processInput(window);

		// Clear buffer 
		glClearColor(0.1f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

    glm::mat4 view = camera.GetViewMatrix();
		sendToShader(shader, "view", view);

		// glm::mat4 projection = glm::mat4(1.0f);
		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
		sendToShader(shader, "projection", projection);

		mesh.Draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return EXIT_SUCCESS;
}
