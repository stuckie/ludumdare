#include "Texture0UniformUpdater.h"

#include <Maths/Matrix4.h>
#include <Graphics/Camera.h>
#include <Graphics/Material.h>
#include <Graphics/Texture.h>
#include <Resources/Resource.h>

using namespace GLESGAE;

void Texture0UniformUpdater::update(const GLint, const Resource<Camera>&, const Resource<Material>& material, const Resource<Matrix4>&)
{
	const Resource<Texture>& texture(material->getTexture(0U));
#ifndef GLES1
	glUniform1i(texture->getId(), 0U);
#endif
}

