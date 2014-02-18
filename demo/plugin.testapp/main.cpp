#include <iostream>
#include <plugin/core/XMLPluginContext.h>

using namespace plugin;
using namespace plugin::core;

static const char PLUGINS_XML[] = { 
	"<plugins> \
			<plugin path=\"plugin1.dll\" /> \
			<plugin path=\"plugin2.dll\" /> \
	</plugins>" };

int main()
{
	XMLPluginContext pluginContext;
	pluginContext.Load(PLUGINS_XML);

	std::cin.get();
	return 0;
}
