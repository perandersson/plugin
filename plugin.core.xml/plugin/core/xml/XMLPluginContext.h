#pragma once
#ifndef _CORE_XML_PLUGIN_CONTEXT_H_
#define _CORE_XML_PLUGIN_CONTEXT_H_

#include <plugin/core/PluginContext.h>
#include <plugin/core/Version.h>

namespace plugin
{
	namespace core
	{
		namespace xml
		{
			//
			// 
			class XMLPluginContext : public PluginContext
			{
			public:
				XMLPluginContext();
				virtual ~XMLPluginContext();

				//
				// Load plugins using the supplied XML
				void Load(const char* xml);
			};
		}
	}
}

#endif
