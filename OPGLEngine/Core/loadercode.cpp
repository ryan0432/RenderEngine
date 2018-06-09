#include "tiny_obj_loader.h"
#include <vector>

tinyobj::attrib_t attrib;
std::vector<tinyobj::shape_t> shapes;
std::vector<tinyobj::material_t> materials;

std::string err;
auto ret = tinyobj::LoadObj(&attrib,
                            &shapes,
                            &materials,
                            &err,
                            file.c_str(),
                            file.parent_path().c_str(),
                            true);

for (size_t meshID = 0; meshID < shapes.size(); ++meshID)
{

	auto& shape = shapes[meshID];
	size_t indexOffset = 0;

	std::vector<glm::vec4> positions;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;

	for (size_t i = 0; i < shape.mesh.num_face_vertices.size(); ++i)
	{
		size_t fv = shape.mesh.num_face_vertices[i];
		for (size_t v = 0; v < fv; ++v)
		{
			auto idx = shape.mesh.indices[indexOffset + v];
			if (idx.vertex_index != -1)
			{
				positions.push_back({ attrib.vertices[3 * idx.vertex_index + 0],
									 attrib.vertices[3 * idx.vertex_index + 1],
									 attrib.vertices[3 * idx.vertex_index + 2],
									 1 });
			}

			if (idx.normal_index != -1)
			{
				normals.push_back({ attrib.normals[3 * idx.normal_index + 0],
								   attrib.normals[3 * idx.normal_index + 1],
								   attrib.normals[3 * idx.normal_index + 2] });
			}
			if (idx.texcoord_index != -1)
			{

				uvs.push_back({ attrib.texcoords[3 * idx.texcoord_index + 0],
							   attrib.texcoords[3 * idx.texcoord_index + 1] });
			}
		}
		indexOffset += fv;
	}
}