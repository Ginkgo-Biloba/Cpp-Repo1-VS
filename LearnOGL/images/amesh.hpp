#ifndef AMASH_HPP
#define AMASH_HPP

#include <vector>
#include <string>
#include "shader.hpp"


struct Vertex
{
	glm::vec3 Position, Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent, Bitangent;
};


struct Texture
{
	unsigned id;
	std::string type, path;
};


/****************************** Mesh ******************************/

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned> indices;
	std::vector<Texture> textures;
	unsigned VAO;

protected:
	unsigned VBO, EBO;
	void setupMesh()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);
		glBindVertexArray(VAO);

		// load data into vertex buffers
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		// A great thing about structs is that their memory layout is sequential for all its items.
		// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array 
		// which again translates to 3/2 floats which translates to a byte array.
		glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

		// set the vertex attribute pointers
		// vertex Positions
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]), 0);
		// vertex normals
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
			reinterpret_cast<void*>(offsetof(Vertex, Normal)));
		// vertex texture coords
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
			reinterpret_cast<void*>(offsetof(Vertex, TexCoords)));
		// vertex tangent
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
			reinterpret_cast<void*>(offsetof(Vertex, Tangent)));
		// vertex bitangent
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
			reinterpret_cast<void*>(offsetof(Vertex, Bitangent)));
	}

public:
	Mesh(std::vector<Vertex> const& vertices,
		std::vector<unsigned> const& indices,
		std::vector<Texture> const& textures)
	{
		this->vertices = vertices;
		this->indices = indices;
		this->textures = textures;

		// now that we have all the required data
		// set the vertex buffers and its attribute pointers.
		setupMesh();
	}

	// render the mesh
	void Draw(Shader shader)
	{
		// bind appropriate textures
		unsigned diffuseNr = 1, specularNr = 1, normalNr = 1, heightNr = 1;
		int number, len = static_cast<int>(textures.size());
		char buf[1 << 10];

		for (int i = 0; i < len; ++i)
		{
			// active proper texture unit before binding
			glActiveTexture(GL_TEXTURE0 + i);
			// retrieve texture number (the N in diffuse_textureN)
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = diffuseNr++;
			else if (name == "texture_specular")
				number = specularNr++;
			else if (name == "texture_normal")
				number = normalNr++;
			else if (name == "texture_height")
				number = heightNr++;

			// now set the sampler to the correct texture unit
			snprintf(buf, sizeof(buf), "%s%d", name.c_str(), i);
			glUniform1i(glGetUniformLocation(shader.ID, buf), i);
			// and finally bind the texture
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

		// draw mesh
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);

		// always good practice to set everything back to defaults once configured.
		glActiveTexture(GL_TEXTURE0);
	}
};


/****************************** Model ******************************/

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
	std::vector<Mesh> meshes;
	std::string directory;

	void processNode(aiNode* node, aiScene const* scene);
	void processMesh(aiMesh* mesh, aiScene const* scene);
	void loadMaterialTextures(aiMaterial* mat, aiTextureType type,
		std::string const& typeName, std::vector<Texture>& dst);
	void loadModel(char const* path)
	{
		Assimp::Importer importer;
		aiScene const* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
		
		if (!scene || (scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE) || !(scene->mRootNode))
		{
			std::cerr << "ERROR::ASSIMP::" << importer.GetErrorString() << std::endl;
			return;
		}
		directory = std::string(path);
		if (directory.find_last_of('/') != std::string::npos)
		{
			while (directory.back() != '/')
				directory.pop_back();
			directory.pop_back();
		}
		processNode(scene->mRootNode, scene);
	}

public:
	Model(char const* path) { loadModel(path); }
	void Draw(Shader shader)
	{
		size_t len = meshes.size();
		for (size_t i = 0; i < len; ++i)
			meshes[i].Draw(shader);
	}
};


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/


/******************************  ******************************/





#endif // !AMASH_HPP

