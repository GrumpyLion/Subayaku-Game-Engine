#include "GLSprite.h"
#include "GLShaderContainer.h"
#include "GLTexture.h"
#include "Core\Engine.h"
#include "Utilities\Utilities.h"

namespace Graphics
{
	namespace OpenGL
	{
		GLSprite::~GLSprite()
		{
			delete m_Texture;
			glDeleteVertexArrays(1, &m_VAO);

			glDeleteBuffers(1, &m_VBO);
			glDeleteBuffers(1, &m_TBO);
			glDeleteBuffers(1, &m_IBO);
		}

		bool GLSprite::Initialize()
		{
			m_Texture = new GLTexture();			
			if (!m_Texture->InitializeFromCache("Assets/Textures/Test.bmp", GL_NEAREST))
			{
				LogErr("Texture is null. Maybe File does't exist ?");
				return false;
			}

			m_SpriteShader = new GLShaderContainer();
			if (!m_SpriteShader->Initialize("Assets/Shaders/Sprite.vs", "Assets/Shaders/Sprite.fs"))
			{
				LogErr("ShaderContainer is null. Do Sprite Shaders exist?");
				return false;
			}
			
			GLfloat vertices[] = {
				// Positions      
				0.5f,  0.5f, 0.0f,
				0.5f, -0.5f, 0.0f,
				-0.5f, -0.5f, 0.0f,   
				-0.5f,  0.5f, 0.0f
			};

			GLfloat uv[] = {
				1.0f, 1.0f,
				1.0f, 0.0f,
				0.0f, 0.0f,
				0.0f, 1.0f
			};

			GLuint indices[] = {  
				0, 1, 3,
				1, 2, 3 
			};

			glGenVertexArrays(1, &m_VAO);
			glBindVertexArray(m_VAO);

			glGenBuffers(1, &m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);

			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);			
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

			glGenBuffers(1, &m_TBO);
			glBindBuffer(GL_ARRAY_BUFFER, m_TBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(uv), uv, GL_STATIC_DRAW);	
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, NULL);

			glGenBuffers(1, &m_IBO);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);

			return false;
		}

		void GLSprite::Render()
		{
			glDisable(GL_CULL_FACE);
			m_SpriteShader->BindProgram();

			glActiveTexture(GL_TEXTURE0);
			m_Texture->Bind();
			glUniform1i(glGetUniformLocation(m_SpriteShader->GetProgram(), "Texture"), 0);
			
			glBindVertexArray(m_VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
			glEnable(GL_CULL_FACE);
		}
	}
}