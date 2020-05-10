#include "TextureHandle.h"


TextureHandler::TextureHandle::TextureHandle(const std::wstring& name, const std::string& path)
	:_name(name), _texture(new Texture()), _path(path) {
	_texture->loadFromFile(path);
}

TextureHandler::TextureHandle::~TextureHandle()
{
}

void TextureHandler::addTexture(const std::wstring& tex_name, const std::string& tex_path)
{
	_textures.push_back(new TextureHandle(tex_name, tex_path));
}

void TextureHandler::addAnimationTexture(const std::wstring& tex_name, const std::string& tex_path)
{
	_animation_textures.push_back(new TextureHandle(tex_name, tex_path));
}

void TextureHandler::addHudTexture(const std::wstring& tex_name, const std::string& tex_path)
{
	_hud_textures.push_back(new TextureHandle(tex_name, tex_path));
}

Texture* TextureHandler::getTexture(const std::wstring& tex_name)
{
	LOOP(_textures.size()) {
		if (_textures[i]->getName() == tex_name)return _textures[i]->getTexture();
	}
	
	throw("ERROR: Texture not found!");

	return nullptr;
}

Texture* TextureHandler::getAnimationTexture(const std::wstring& tex_name)
{
	LOOP(_animation_textures.size()) {
		if (_animation_textures[i]->getName() == tex_name)return _animation_textures[i]->getTexture();
	}

	throw("ERROR: Texture not found!");

	return nullptr;
}

Texture* TextureHandler::getHudTexture(const std::wstring& tex_name)
{
	LOOP(_hud_textures.size()) {
		if (_hud_textures[i]->getName() == tex_name)return _hud_textures[i]->getTexture();
	}

	throw("ERROR: Texture not found!");

	return nullptr;
}


