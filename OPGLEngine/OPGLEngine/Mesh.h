#pragma once
#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Mesh
{
public:
	Mesh() : triCount(0), vao(0), vbo(0), ibo(0) {}
	virtual ~Mesh();

	struct Vertex
	{
		//Vertex position
		glm::vec4 position;

		//Vertex normal
		glm::vec4 normal;

		//Texture coordination
		glm::vec2 texCoord;
	};

	//Initialize a Quad
	void initialiseQuad();

	//Initialize a custom mesh
	void initialize(unsigned int vertexCount, const Vertex* vertices,
					unsigned int indexCount = 0,
					unsigned int* indices = nullptr);
	
	//Draw mesh
	virtual void draw();

protected:
	//Triangle counts
	unsigned int triCount;

	//Vertex Array Object (VAO)
	unsigned int vao;

	//Vertex Buffer Objects (VBOs)
	unsigned int vbo;

	//Index Buffer Object (IBO)
	unsigned int ibo;
};

