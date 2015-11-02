#include "cCallbackManager.h"
#include "sCallback.h"

namespace StormFramework {

cCallbackManager::~cCallbackManager() {
	for (auto &iter : m_IntervalCallbacks) {
		delete iter.second;
	}
	m_IntervalCallbacks.clear();
	for (auto &iter : m_ManualCallbacks) {
		delete iter.second;
	}
	m_ManualCallbacks.clear();
	for (uint32_t i = 0; i < m_DelayedCallbacks.size(); i++) {
		delete m_DelayedCallbacks[i];
	}
	m_DelayedCallbacks.clear();
}

void cCallbackManager::Tick() {
	
}

void cCallbackManager::AddIntervalCallback(const std::string &name,
					  					   sIntervalCallback *callback) {
	if (IfExists(name)) {
		S_LogError("cCallbackManager", 
				   "Callback with name '%s' already exists", name.c_str());
		return;
	}
	m_IntervalCallbacks[name] = callback;
}
void cCallbackManager::AddManulaCallback(const std::string &name,
										 sManualCallback *callback) {
	if (IfExists(name)) {
		S_LogError("cCallbackManager", 
				   "Callback with name '%s' already exists", name.c_str());
		return;
	}
	m_ManualCallbacks[name] = callback;
}
void cCallbackManager::AddDelayedCallback(sManualCallback *callback) {
	m_DelayedCallbacks.push_back(callback);
}

void cCallbackManager::RemoveCallback(const std::string &name) {
	if (m_IntervalCallbacks.find(name) != m_IntervalCallbacks.end()) {
		// Callback is "on interval" type
		delete m_IntervalCallbacks[name];
		m_IntervalCallbacks.erase(name);
	} else if (m_ManualCallbacks.find(name) != m_ManualCallbacks.end()) {
		// Callback is "manual" type
		delete m_ManualCallbacks[name];
		m_ManualCallbacks.erase(name);
	}
}

bool cCallbackManager::IfExists(const std::string &name) {
	return m_IntervalCallbacks.find(name) != m_IntervalCallbacks.end() ||
		   m_ManualCallbacks.find(name) != m_ManualCallbacks.end();
}

} /* namespace StormFramework */