#pragma once

#define SAFE_DELETE(object);	if(object != nullptr){\
									delete object;\
									object = nullptr;\
								}

#define SAFE_DELETE_WITH_FUNCTION(function, object);	if(object != nullptr){\
															function(object);\
															object = nullptr;\
														}

#define UNUSED(x) ((void) x)
