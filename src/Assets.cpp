#include <Lums>
#include "Assets.hpp"

static void
initImages()
{
	auto& provider = lm::ImageProvider::instance();

	auto& tileset = provider.set(Assets::Image::Tileset);
    tileset.setPath("images/tileset.png");
    
    auto& newGame = provider.set(Assets::Image::NewGame);
    newGame.setPath("images/new_game.png");
    
    auto& quit = provider.set(Assets::Image::Quit);
    quit.setPath("images/quit.png");

    auto& menuCursor = provider.set(Assets::Image::MenuCursor);
    menuCursor.setPath("images/menu_cursor.png");

    auto& background = provider.set(Assets::Image::Background);
    background.setPath("images/backgrounds.png");

    auto& yseult = provider.set(Assets::Image::Yseult);
    yseult.setPath("images/yseult.png");

    for (int i = 0; i < provider.size(); ++i)
        provider.set(i).setScale(0.5f);
}

static void
initTextures()
{
    auto& images = lm::ImageProvider::instance();
    auto& provider = lm::TextureProvider::instance();

    auto& tileset = provider.set(Assets::Texture::Tileset);
    tileset.setImage(images.set(Assets::Image::Tileset));
    tileset.pushAtlas(8, 52);

    auto& newGame = provider.set(Assets::Texture::NewGame);
    newGame.setImage(images.set(Assets::Image::NewGame));
    newGame.pushAtlas(1, 1);

    auto& quit = provider.set(Assets::Texture::Quit);
    quit.setImage(images.set(Assets::Image::Quit));
    quit.pushAtlas(1, 1);

    auto& menuCursor = provider.set(Assets::Texture::MenuCursor);
    menuCursor.setImage(images.set(Assets::Image::MenuCursor));
    menuCursor.pushAtlas(1, 1);

    auto& background = provider.set(Assets::Texture::Background);
    background.setImage(images.set(Assets::Image::Background));
    background.pushAtlas(3, 2);

    auto& yseult = provider.set(Assets::Texture::Yseult);
    yseult.setImage(images.set(Assets::Image::Yseult));
    yseult.pushAtlas(7, 6);
}

static void
initShaders()
{
    auto& provider = lm::ShaderProvider::instance();

    auto& basic2d = provider.set(Assets::Shader::Basic2D);
    basic2d.attach(lm::Shader("shaders/2D.vert.glsl", lm::Shader::Type::Vertex));
    basic2d.attach(lm::Shader("shaders/2D.frag.glsl", lm::Shader::Type::Fragment));
    basic2d.bindAttribLocation(lm::Vertex::Position, "position");
    basic2d.bindAttribLocation(lm::Vertex::Texture, "tex");
    basic2d.bindAttribLocation(lm::Vertex::Color, "color");
    basic2d.link();
}

void
Assets::init()
{
	initImages();
	initTextures();
	initShaders();
}