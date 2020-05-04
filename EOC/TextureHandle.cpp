#include "TextureHandle.h"


TextureHandle::TextureHandle(const std::wstring& name, const std::string& path)
	:_name(name), _texture(new Texture()), _path(path) {
	_texture->loadFromFile(path);
}

TextureHandle::~TextureHandle()
{
}

void TextureHandler::addTexture(const std::wstring& tex_name, const std::string& tex_path)
{
	_textures.push_back(new TextureHandle(tex_name, tex_path));
}

Texture* TextureHandler::getTexture(const std::wstring& tex_name)
{
	LOOP(_textures.size()) {
		if (_textures[i]->getName() == tex_name)return _textures[i]->getTexture();
	}
	
	throw("ERROR: Texture not found!");

	return nullptr;
}

TextureHandle* TextureHandler::getTextureHandle(const std::wstring& text_name)
{
	LOOP(_textures.size()) {
		if (_textures[i]->getName() == text_name)return _textures[i];
	}

	throw("EEROR: TextureHandle not found!");

	return nullptr;
}
