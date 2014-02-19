#include "XMLPluginContext.h"
#include <tinyxml2.h>

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#endif

using namespace plugin;
using namespace plugin::core;
using namespace plugin::core::xml;

////////////////////////////////////////////////////////////////

namespace plugin
{
	namespace core
	{
		struct Helper
		{
#ifdef WIN32
			template<typename T>
			static T GetFunctionPtr(HMODULE library, const char* name) {
				FARPROC addr = GetProcAddress(library, name);
				if (addr == nullptr) {
					return nullptr;
				}
				return reinterpret_cast<T>(addr);
			}

			static HMODULE GetLibrary(const char* fileName) {
				return LoadLibraryA(fileName);
			}

			static void UnloadLibrary(HMODULE module) {
				FreeLibrary(module);
			}
#endif
		};
	}
}

////////////////////////////////////////////////////////////////

class XmlPluginRegistryVisitor : public tinyxml2::XMLVisitor
{
public:
	XmlPluginRegistryVisitor(XMLPluginContext& context);
	~XmlPluginRegistryVisitor();

	std::string GetNameFromPath(const char* path);


// tinyxml2::XMLVisitor
public:
	virtual bool VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute);

private:
	XMLPluginContext& mPluginContext;
};

XmlPluginRegistryVisitor::XmlPluginRegistryVisitor(XMLPluginContext& context)
: mPluginContext(context)
{

}

XmlPluginRegistryVisitor::~XmlPluginRegistryVisitor()
{

}

std::string XmlPluginRegistryVisitor::GetNameFromPath(const char* path)
{
	std::string pathAsString(path);
	std::string::size_type pos = pathAsString.find_last_of("\\");
	if (pos == std::string::npos) {
		pos = pathAsString.find_last_of("//");
	}
	if (pos != std::string::npos) {
		pathAsString = pathAsString.substr(pos);
	}

	pos = pathAsString.find_last_of('.');
	if (pos != std::string::npos) {
		pathAsString = pathAsString.substr(0, pos);
	}


	return pathAsString;
}

bool XmlPluginRegistryVisitor::VisitEnter(const tinyxml2::XMLElement& element, const tinyxml2::XMLAttribute* firstAttribute)
{
	static const std::string TAG_PLUGIN("plugin");

	const std::string name = element.Name();
	if (TAG_PLUGIN == name) {
		const char* path = element.Attribute("path");
		if (path == NULL) {
			return true;
		}

		std::string name = element.Attribute("name") == nullptr ? 
			GetNameFromPath(path) : std::string(element.Attribute("name"));

		auto library = Helper::GetLibrary(path);
		if (library == nullptr) {
			return true;
		}

		GetPluginEngineMajorVersionFunc getPluginEngineMajorVersion = 
			Helper::GetFunctionPtr<GetPluginEngineMajorVersionFunc>(library, "GetPluginEngineMajorVersion");
		GetPluginEngineMinorVersionFunc getPluginEngineMinorVersion = 
			Helper::GetFunctionPtr<GetPluginEngineMinorVersionFunc>(library, "GetPluginEngineMinorVersion");
		GetPluginActivatorFunc getPluginActivator = 
			Helper::GetFunctionPtr<GetPluginActivatorFunc>(library, "GetPluginActivator");
		GetPluginVersionFunc getPluginVersion =
			Helper::GetFunctionPtr<GetPluginVersionFunc>(library, "GetPluginVersion");

		if (getPluginEngineMajorVersion == nullptr ||
			getPluginEngineMajorVersion == nullptr ||
			getPluginActivator == nullptr) {
			Helper::UnloadLibrary(library);
			return true;
		}

		int expectedMajorVersion = (*getPluginEngineMajorVersion)();
		if (expectedMajorVersion != PLUGIN_ENGINE_MAJOR_VERSION) {
			Helper::UnloadLibrary(library);
			return true;
		}

		IPluginActivator* activator = (*getPluginActivator)(&mPluginContext);
		if (activator == nullptr) {
			Helper::UnloadLibrary(library);
			return true;
		}

		const char* pluginVersion = (*getPluginVersion)();
		int majorVersion = 0;
		int minorVersion = 0;
		int patchVersion = 0;
		if (pluginVersion != nullptr)
			sscanf(pluginVersion, "%d.%d.%d", &majorVersion, &minorVersion, &patchVersion);
		
		mPluginContext.StartPlugin(activator, std::string(name), Version(majorVersion, minorVersion, patchVersion));
	}

	return true;
}

//////////////////////////

XMLPluginContext::XMLPluginContext()
: PluginContext()
{

}

XMLPluginContext::~XMLPluginContext()
{

}

void XMLPluginContext::Load(const char* xml)
{
	tinyxml2::XMLDocument document;
	document.Parse(xml);

	XmlPluginRegistryVisitor visitor(*this);
	document.Accept(&visitor);
}
