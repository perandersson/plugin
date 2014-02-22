#include "xmlplugincontext.h"
#include <tinyxml2.h>

using namespace plugin;
using namespace plugin::core;
using namespace plugin::core::xml;

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
		if (path == nullptr) {
			return true;
		}

		std::string name = element.Attribute("name") == nullptr ? 
			GetNameFromPath(path) : std::string(element.Attribute("name"));

		mPluginContext.LoadPlugin(std::string(path), name);
	}

	return true;
}

//////////////////////////

XMLPluginContext::XMLPluginContext()
: PluginContext()
{

}

XMLPluginContext::XMLPluginContext(IPluginActivator* hostActivator, const std::string& hostName, const Version& hostVersion)
: PluginContext(hostActivator, hostName, hostVersion)
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
