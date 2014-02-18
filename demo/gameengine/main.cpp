#include <iostream>
#include <plugin/core/XMLPluginContext.h>
#include "../gameengine.contract/contract.h"

using namespace plugin;
using namespace plugin::core;

static const char PLUGINS_XML[] = {
	"<plugins> \
		<plugin path=\"demo.dll\" /> \
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
	auto game = dynamic_cast<gameengine::IGame*>(pluginContext.GetService(reference));
	if (game == nullptr) {
		std::cerr << "No IGame instance is registered" << std::endl;
		std::cin.get();
		return -1;
	}
	game->StartGame();

	//
	// Return the reference to the plugin system after it's been used!
	pluginContext.UngetService(reference);

	return 0;
}
