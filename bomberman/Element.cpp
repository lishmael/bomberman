#include "Element.h"

Element::Element(wchar_t el) {
	elem.first = valueOf(el);
	elem.second = el;
}

Element::Element(String name) {
	elem.second = Elements.at(name);
	elem.first = name;
}

wchar_t Element::getChar() const {
	return elem.second;
}

String Element::valueOf(wchar_t ch) const {
	for (auto i : Elements) {
		if (i.second == ch) return i.first;
	}
	throw new std::invalid_argument("No such Elment for " + ch);
}

bool Element::operator==(const Element& el) const {
	return elem == el.elem;
}

ElementMap Element::initialiseElements() {
	ElementMap mapOfElements;

	/// This is your Bomberman
	mapOfElements[L"BOMBERMAN"] =  L'☺';             // this is what he usually looks like
	mapOfElements[L"BOMB_BOMBERMAN"] =  L'☻';        // this is if he is sitting on own bomb
	mapOfElements[L"DEAD_BOMBERMAN"] =  L'Ѡ';        // oops, your Bomberman is dead  ("don't worry, he will appear somewhere in next move
													// you're getting -200 for each death

	/// this is other players Bombermans
	mapOfElements[L"OTHER_BOMBERMAN"] =  L'♥';       // this is what other Bombermans looks like
	mapOfElements[L"OTHER_BOMB_BOMBERMAN"] =  L'♠';  // this is if player just set the bomb
	mapOfElements[L"OTHER_DEAD_BOMBERMAN"] =  L'♣';  // enemy corpse , Lit will disappear shortly, right on the next move
								// if you've done it you'll get +1000

	/// the bombs
	mapOfElements[L"BOMB_TIMER_5"] =  L'5';          // after bomberman set the bomb, the timer starts  ("5 tacts
	mapOfElements[L"BOMB_TIMER_4"] =  L'4';          // this will blow up after 4 tacts
	mapOfElements[L"BOMB_TIMER_3"] =  L'3';          // this after 3
	mapOfElements[L"BOMB_TIMER_2"] =  L'2';          // two
	mapOfElements[L"BOMB_TIMER_1"] =  L'1';          // one
	mapOfElements[L"BOOM"] =  L'҉';                  // Boom! this is what is bomb does, everything that is destroyable got destroyed

	/// walls
	mapOfElements[L"WALL"] =  L'☼';                  // indestructible wall - it will not fall from bomb
	mapOfElements[L"DESTROY_WALL"] =  L'#';          // this wall could be blowed up
	mapOfElements[L"DESTROYED_WALL"] =  L'H';        // this is how broken wall looks like, it will dissapear on next move
								// if it's you did it - you'll get +10 points.

	/// meatchoppers
	mapOfElements[L"MEAT_CHOPPER"] =  L'&';          // this guys runs over the board randomly and gets in the way all the time
													// if it will touch bomberman - it will die
													// you'd better kill this piece of ... meat, you'll get +100 point for it
	mapOfElements[L"DEAD_MEAT_CHOPPER"] =  L'x';     // this is chopper corpse

	/// a void
	mapOfElements[L"SPACE"] =  L' ';                 // this is the only place where you can move your Bomberman
	return mapOfElements;
};

const ElementMap Element::Elements = Element::initialiseElements();