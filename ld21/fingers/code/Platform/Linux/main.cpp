#include <Platform/Application.h>
#include <Graphics/GraphicsSystem.h>
#include <Graphics/Context/ShaderBasedContext.h>
#include <Resources/ResourceManager.h>

#include "MVPUniformUpdater.h"
#include "Texture0UniformUpdater.h"
#include "../FingersLifecycle.h"
#include "../../Resources/Shaders.h"

using namespace GLESGAE;

int main(void)
{
	Application* application(Application::getInstance());
	application->setLifecycle(new FingersLifecycle);
	
	application->onCreate(GraphicsSystem::FIXED_FUNCTION_RENDERING);
	
	application->onStart();
	application->onResume();
	
	{
		GraphicsSystem* graphicsSystem(application->getGraphicsSystem());
		graphicsSystem->enableAlphaBlending();
		ResourceManager* resourceManager(application->getResourceManager());
		ResourceBank<ShaderUniformUpdater>& shaderUpdaterBank(resourceManager->createBank<ShaderUniformUpdater>(Resources::ShaderUniformUpdater));
		Fingers::Shaders::Bank = shaderUpdaterBank.getId();
		Fingers::Shaders::Group = shaderUpdaterBank.newGroup();
	
		Resource<ShaderUniformUpdater>& mvpUpdater(shaderUpdaterBank.add(Fingers::Shaders::Group, Resources::ShaderUniformUpdater, new MVPUniformUpdater));
	
		Resource<ShaderUniformUpdater>& textureUpdater(shaderUpdaterBank.add(Fingers::Shaders::Group, Resources::ShaderUniformUpdater, new Texture0UniformUpdater));
	
		ShaderBasedContext* const shaderContext(graphicsSystem->getShaderContext());
		if (0 != shaderContext) {
			shaderContext->addUniformUpdater("u_mvp", mvpUpdater);
			shaderContext->addUniformUpdater("s_texture0", textureUpdater);
		}
	}
	
	bool applicationRunning(true);
	while (true == applicationRunning)
		applicationRunning = application->onLoop();
		
	application->onPause();
	application->onStop();
	application->onDestroy();
	
	return 0;
}

