#pragma once

#include <SFML/Window.hpp>
#define byte win_byte_override
#include <Windows.h>


namespace sf 
{
	class StandardCursor
	{
	private:
		HCURSOR Cursor;

	public:
		enum TYPE { WAIT, TEXT, NORMAL, HAND };
		StandardCursor(const TYPE type_);
		~StandardCursor() {}

		void set(const sf::WindowHandle& window_handle_) const;
	};
}