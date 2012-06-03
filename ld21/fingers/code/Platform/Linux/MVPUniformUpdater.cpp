#include "MVPUniformUpdater.h"

#include <Maths/Matrix4.h>
#include <Graphics/Camera.h>
#include <Graphics/Material.h>
#include <Resources/Resource.h>

using namespace GLESGAE;

void MVPUniformUpdater::update(const GLint uniformId, const Resource<Camera>& camera, const Resource<Material>&, const Resource<Matrix4>& transform)
{
	const Matrix4& view(camera->getViewMatrix());
	const Matrix4& projection(camera->getProjectionMatrix());

	const Matrix4 modelViewProjection((*transform).getTranspose() * view * projection);

#ifndef GLES1	
	glUniformMatrix4fv(uniformId, 1U, false, modelViewProjection.getData());
#endif
}

