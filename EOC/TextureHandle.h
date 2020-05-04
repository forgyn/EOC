#pragma once
#include "Utility.h"





class TextureHandle {
public:
	TextureHandle(const std::wstring& name, const std::string& path);
	Texture* getTexture() { return _texture; }
	wstring getName() { return _name; }
	string getPath() { return _path; }
	~TextureHandle();
private:
	const std::wstring _name;
	const std::string _path;
	Texture* _texture = nullptr;

};



static class TextureHandler {
public:
	static void addTexture(const std::wstring& tex_name, const std::string& tex_path);
	static Texture* getTexture(const std::wstring& tex_name);
	static TextureHandle* getTextureHandle(const std::wstring& tex_name);
private:
	static vector<TextureHandle*> _textures;
};

