#pragma once

#include "utils/utils.h"


class Element {
public:
	Element(wchar_t el);
	Element(String name);

	bool operator==(const Element& el) const;

	wchar_t getChar() const;
	String valueOf(wchar_t ch) const;

private:
	static ElementMap initialiseElements();
	static const ElementMap Elements;

	ElementItem elem;
};