/* 
 * File:   sCallback.h
 * Author: master312
 *
 * Created on November 02, 2015, 9:09 PM
 */
#ifndef SCALLBACK_H__
#define SCALLBACK_H__
#include <functional>
#include <iostream>

namespace StormFramework {

typedef std::function<int(void *data)> TypeTimeCallback;
typedef std::function<void(void *data)> TypeCallback;

struct sIntervalCallback {
	/* Interval on what this callback is called (ms) */
	uint32_t m_Interval;
	/* Last time when this interval was called */
	uint32_t m_LastTime;
	/* Callback method */
	TypeTimeCallback m_Callback;

	sIntervalCallback(uint32_t interval, TypeTimeCallback callback) : 
				m_Interval(interval),
				m_LastTime(0), 
				m_Callback(callback) { }
};

struct sManualCallback {
	/* This variable is used only for delayed callbacks */
	/* If this is manual callback, this variable will be zero */
	uint32_t m_Delay;
	TypeCallback m_Callback;

	sManualCallback(TypeCallback callback) : 
			   m_Delay(0), m_Callback(callback) { }
	sManualCallback(uint32_t delay, TypeCallback callback) : 
			   m_Delay(delay), m_Callback(callback) { }
};

} /* namespace StormFramework  */
#endif /* SCALLBACK_H__ */