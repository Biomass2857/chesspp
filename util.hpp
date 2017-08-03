#ifndef UTIL_HPP
#define UTIL_HPP
#include <SFML/Graphics.hpp>

enum class States
{
	INGAME,
	MENU,
	CONNECTING
};

enum class SessionType
{
	HOST,
	CLIENT
};

namespace sf
{
	typedef Vector2<char> Vector2c;
}

#endif
