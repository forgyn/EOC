#include "FontHandle.h"

void FontHandler::addFont(const wstring& name, const string& path){
	_fonts.push_back(new FontHandle(name,path));
}

Font* FontHandler::getFont(const wstring& name)
{
	LOOP(_fonts.size()) {
		if (name == _fonts[i]->name)return _fonts[i]->getFont();
	}


	throw("ERROR! Font not found!");
}

FontHandler::FontHandle::FontHandle(const wstring& name, const string& path)
:name(name),path(path),_font(new Font){
	_font->loadFromFile(path);
}

FontHandler::FontHandle::~FontHandle()
{

}
