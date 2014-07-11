#include "GStatePlaceholder.h"
#include "Logger.h"

GStatePlaceholder::GStatePlaceholder() {

}

GStatePlaceholder::~GStatePlaceholder() {

}

void GStatePlaceholder::load() {
	Log(DEBUG) << "Loading placeholder...";
}

void GStatePlaceholder::unload() {
	Log(DEBUG) << "\tUnloading placeholder...";

	cleanEntities();
}

void GStatePlaceholder::update(const double dt_) {

}

void GStatePlaceholder::render() {

}
