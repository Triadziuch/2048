#include <Windows.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

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