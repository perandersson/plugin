#pragma once
#ifndef _PLUGIN_DEFINES_H_
#define _PLUGIN_DEFINES_H_

#define SSTRINGIFY(x) #x
#define STRINGIFY(x) SSTRINGIFY(x)

#define PLUGIN_ENGINE_CONTRACT_MAJOR_VERSION 1
#define PLUGIN_ENGINE_CONTRACT_MINOR_VERSION 0
#define PLUGIN_ENGINE_CONTRACT_PATCH_VERSION 0
#define PLUGIN_ENGINE_CONTRACT_VERSION STRINGIFY(PLUGIN_ENGINE_CONTRACT_MAJOR_VERSION) "." STRINGIFY(PLUGIN_ENGINE_CONTRACT_MINOR_VERSION) "." STRINGIFY(PLUGIN_ENGINE_CONTRACT_PATCH_VERSION)

#ifdef _USRDLL
#ifndef PLUGIN_API
#define PLUGIN_API __declspec(dllexport)
#endif
#endif

#ifdef PLUGIN_EXPORTS 
#ifndef PLUGIN_API
#define PLUGIN_API __declspec(dllexport)
#endif
#else
#ifndef PLUGIN_API
#define PLUGIN_API __declspec(dllimport)
#endif
#endif

#ifndef THREAD_LOCAL
#ifdef WIN32
#define THREAD_LOCAL __declspec(thread)
#else
#define THREAD_LOCAL __thread
#endif
#endif

#endif
