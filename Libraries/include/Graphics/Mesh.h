#ifndef MESH_H
#define MESH_H

#include <Graphics/Graphics.h>
#include <vector>

/* pcnt: position, color, normal, texUV
* vertex have attrixbute:
* - position:	vec3<float>
* - color:		vec3<float>
* - normal:		vec3<float>
* - texUV:		vec2<float>
*/
struct vertex_pcnt
{
	glm::vec3 postion;
	glm::vec3 color;
	glm::vec3 normal;
	glm::vec3 texUV;
};

/* pnt: position, normal, texUV
* vertex have attrixbute:
* - position:	vec3<float>
* - normal:		vec3<float>
* - texUV:		vec2<float>
*/
struct vertex_pnt
{
	glm::vec3 postion;
	glm::vec3 normal;
	glm::vec3 texUV;
};

/* pnt: position, normal, texUV
* vertex have attrixbute:
* - position:	vec3<float>
* - texUV:		vec2<float>
*/
struct vertex_pt
{
	glm::vec3 postion;
	glm::vec3 texUV;
};


class Mesh
{
private:
	GLuint vao;
	int size;

	void Init(const std::vector<float>& vertices, const std::vector<int>& indices);
	void Init(const std::vector<vertex_pcnt>& vertices, const std::vector<int>& indices);
	void Init(const std::vector<vertex_pnt>& vertices, const std::vector<int>& indices);
	void Init(const std::vector<vertex_pt>& vertices, const std::vector<int>& indices);

public:
	Mesh();
	Mesh(const std::vector<float>& vertices, const std::vector<int>& indices);
	Mesh(const std::vector<vertex_pcnt>& vertices, const std::vector<int>& indices);
	Mesh(const std::vector<vertex_pnt>& vertices, const std::vector<int>& indices);
	Mesh(const std::vector<vertex_pt>& vertices, const std::vector<int>& indices);

	~Mesh();
	
	void Draw();
	void destroy();

	void operator = (const Mesh& mesh);

};

#endif // !MESH_H
