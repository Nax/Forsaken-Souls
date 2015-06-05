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
}

static void
initShaders()
{
    auto& provider = lm::ShaderProvider::instance();

    auto& mainMenu = provider.set(Assets::Shader::MainMenu);
    mainMenu.attach(lm::Shader("shaders/main_menu.vert.glsl", lm::Shader::Type::Vertex));
    mainMenu.attach(lm::Shader("shaders/main_menu.frag.glsl", lm::Shader::Type::Fragment));
    mainMenu.bindAttribLocation(lm::Vertex::Position, "position");
    mainMenu.bindAttribLocation(lm::Vertex::Texture, "tex");
    mainMenu.bindAttribLocation(lm::Vertex::Color, "color");
    mainMenu.link();
}

void
Assets::init()
{
	initImages();
	initTextures();
	initShaders();
}