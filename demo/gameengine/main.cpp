#include <iostream>
#include "../gameengine.contract/contract.h"

#include <plugin/core/xml/XMLPluginContext.h>
using namespace plugin::core::xml;

static const char PLUGINS_XML[] = {
	"<plugins> \
		<plugin path=\"demo.dll\" /> \
		<plugin path=\"mydemodll.dll\" /> \
	</plugins>" };

int main()
{
	//
	// Start the plugin context
	XMLPluginContext pluginContext;
	pluginContext.Load(PLUGINS_XML);

	//
	// Retrieve the reference for the game instance - if found
	auto reference = pluginContext.GetServiceReference(typeid(gameengine::IGame));

	//
	// Retrieve the actual pointer to the instance
	auto game = dynamic_cast<gameengine::IGame*>(reference->GetService());
	if (game == nullptr) {
		std::cerr << "No IGame instance is registered" << std::endl;
		std::cin.get();
		return -1;
	}
	game->StartGame();

	//
	// Return the reference to the plugin system after it's been used!
	reference->Release();

	return 0;
}
