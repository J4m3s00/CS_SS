#pragma once

class Mesh
{
public:
	struct Vertex
	{
		struct Vector
		{
			float x; 
			float y; 
			float z;
		} Position;
		struct UV
		{
			float t;
			float c;
		} TextureCoords;
		Vector Normal;
		Vector Tangent;
		Vector Binormal;
	};
public:
	Mesh(std::vector<Vertex>& vertices, std::vector<USHORT>& indices);
	~Mesh();

	void Draw();
private:
	DXBuffer* fpVertexBuffer;
	DXBuffer* fpIndexBuffer;
};