#pragma once

#define SAFE_DELETE(x);	if(x != nullptr){\
							delete x;\
							x = nullptr;\
						}

#define UNUSED(x) ((void) x)
