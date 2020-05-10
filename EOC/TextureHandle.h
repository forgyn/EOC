#pragma once
#include "Utility.h"

static class TextureHandler {
public:
	static void addTexture(const std::wstring& tex_name, const std::string& tex_path);
	static void addAnimationTexture(const std::wstring& tex_name, const std::string& tex_path);
	static void addHudTexture(const std::wstring& tex_name, const std::string& tex_path);
	static Texture* getTexture(const std::wstring& tex_name);
	static Texture* getAnimationTexture(const std::wstring& tex_name);
	static Texture* getHudTexture(const std::wstring& tex_name);
private:
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
	static vector<TextureHandle*> _textures;
	static vector<TextureHandle*> _animation_textures;
	static vector<TextureHandle*> _hud_textures;
};

