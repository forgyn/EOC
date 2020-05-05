#pragma once
#include "Utility.h"


class FontHandler{
public:

	static void addFont(const wstring& name,const string& path);
	static Font* getFont(const wstring& name);
private:
	class FontHandle {
	public:
		FontHandle(const wstring& name, const string& path);
		~FontHandle();
		Font* getFont() { return _font; }
		const wstring name;
		const string path;
	private:
		Font* _font;
	};
	static vector<FontHandle*> _fonts;

};

