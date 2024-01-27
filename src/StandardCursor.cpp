#include "StandardCursor.h"

sf::StandardCursor::StandardCursor(const TYPE type_)
{
	printf("A\n");
	switch (type_) {
	case sf::StandardCursor::WAIT:
		Cursor = LoadCursor(NULL, IDC_WAIT);
		break;
	case sf::StandardCursor::HAND:
		Cursor = LoadCursor(NULL, IDC_HAND);
		break;
	case sf::StandardCursor::NORMAL:
		Cursor = LoadCursor(NULL, IDC_ARROW);
		break;
	case sf::StandardCursor::TEXT:
		Cursor = LoadCursor(NULL, IDC_IBEAM);
		break;
	}
}

void sf::StandardCursor::set(const sf::WindowHandle& window_handle_) const
{
	SetClassLongPtr(window_handle_, GCLP_HCURSOR, reinterpret_cast<LONG_PTR>(Cursor));
}
