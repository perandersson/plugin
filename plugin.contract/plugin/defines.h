#pragma once
#ifndef _PLUGIN_DEFINES_H_
#define _PLUGIN_DEFINES_H_

#ifdef PLUGIN_EXPORTS
#define PLUGIN_API __declspec(dllexport)
#else
#define PLUGIN_API __declspec(dllimport)
#endif

#define PLUGIN_ENGINE_MAJOR_VERSION 0
#define PLUGIN_ENGINE_MINOR_VERSION 1

#endif
