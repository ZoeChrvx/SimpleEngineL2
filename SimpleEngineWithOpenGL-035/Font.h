#pragma once
#include <string>
#include <unordered_map>
#include <SDL_ttf.h>
#include "Vector3.h"
#include "Color.h"
using std::string;

class Font
{
public:
    Font();
    ~Font();
    
    static bool initialize();
    static void close();
    void unload();

    //Render
    class Texture* renderText(const string& text, const Vector3& color = Color::white, int pointSize = 10);

    //Ajout de la police
    void addFontData(int size, TTF_Font* fontSize);

private:
    std::unordered_map<int, TTF_Font*>fontData;
    int alpha=255;
};
