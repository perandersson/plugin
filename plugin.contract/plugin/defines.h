#pragma once
#ifndef _PLUGIN_DEFINES_H_
#define _PLUGIN_DEFINES_H_

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

#define PLUGIN_ENGINE_MAJOR_VERSION 0
#define PLUGIN_ENGINE_MINOR_VERSION 1

#ifndef THREAD_LOCAL
#ifdef WIN32
#define THREAD_LOCAL __declspec(thread)
#else
#define THREAD_LOCAL __thread
#endif
#endif

#endif
