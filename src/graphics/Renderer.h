#pragma once

namespace Renderer {

	void Submit(Mesh* pMesh, Material* pMaterial, const glm::vec3& position = { 0.0f, 0.0f, 0.0f }, const glm::vec3& rotation = { 0.0f, 0.0f, 0.0f }, const glm::vec3& scale = { 1.0f, 1.0f, 1.0f });

}