#pragma once

/**
* Allow construction and deconstruction of derived objects, but prevent copying.
*/
class Uncopyable {
	protected:
		Uncopyable(){}
		~Uncopyable(){}

	private:
		Uncopyable(const Uncopyable&);
		Uncopyable& operator=(const Uncopyable&);
};
