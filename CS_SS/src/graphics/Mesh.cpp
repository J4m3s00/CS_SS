#include <prefix.h>

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<USHORT>& indices)
{
	fpVertexBuffer = new DXBuffer(BUFFER_TYPE_VERTEX_BUFFER, &vertices[0], sizeof(Vertex), vertices.size());
	fpIndexBuffer = new DXBuffer(BUFFER_TYPE_INDEX_BUFFER, &indices[0], sizeof(USHORT), indices.size());
}

Mesh::~Mesh()
{
	if (fpVertexBuffer) {
		delete fpVertexBuffer;
		fpVertexBuffer = nullptr;
	}

	if (fpIndexBuffer) {
		delete fpIndexBuffer;
		fpIndexBuffer = nullptr;
	}

}

void Mesh::Draw()
{
	fpIndexBuffer->Bind();
	fpVertexBuffer->Bind();

	DXContext::sInstance.DrawIndexed(fpIndexBuffer->GetCount());
}