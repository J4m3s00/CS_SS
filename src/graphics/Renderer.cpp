#include "prefix.h"

namespace Renderer {

	void Submit(Mesh* pMesh, BasicMaterial* pMaterial, const glm::vec3& position, const glm::vec3& rotation, const glm::vec3& scale)
	{
		if (pMaterial && pMesh)
		{
			glm::mat4& modelMatrix = pMaterial->GetConstantBuffer()->fModelMatrix;
			modelMatrix = glm::mat4(1.0f);
			modelMatrix = glm::rotate(modelMatrix, rotation.x, { 1, 0, 0 });
			modelMatrix = glm::rotate(modelMatrix, rotation.y, { 0, 1, 0 });
			modelMatrix = glm::rotate(modelMatrix, rotation.z, { 0, 0, 1 });
			modelMatrix = glm::translate(modelMatrix, position);
			modelMatrix = glm::scale(modelMatrix, scale);
			modelMatrix = glm::transpose(modelMatrix);

			pMaterial->Bind();
			pMesh->Draw();
		}
	}

}