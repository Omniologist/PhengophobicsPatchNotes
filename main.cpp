#include <complex>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <SDL3_ttf/SDL_ttf.h>

constexpr int kScreenWidth{480};
constexpr int kScreenHeight{640};

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow{ nullptr };
SDL_Renderer* gRenderer{ nullptr };
SDL_Surface* gSurface{ nullptr };
SDL_Texture* gTexture{ nullptr };


bool init() {

    bool success{ true };

    if ( SDL_Init( SDL_INIT_VIDEO ) == false ) {
        SDL_Log( "SDL could not intialize! SDL error: %s\n", SDL_GetError() );
        success = false;
    }
    else {
        if (gWindow = SDL_CreateWindow("Phengophobics Patch Notes", kScreenWidth, kScreenHeight, 0 ); gWindow == nullptr) {
            SDL_Log( "Window could not be created! SDL error: %s\n", SDL_GetError() );
            success = false;
        }
        else {
            gRenderer = SDL_CreateRenderer(gWindow, nullptr);
        }
    }

    return success;
}

bool loadMedia() {
    bool success{ true };
    std::string imagePath{ "assets/test.bmp" };
    if ( gSurface = SDL_LoadBMP(imagePath.c_str() ); gSurface == nullptr ) {
        SDL_Log( "Unable to load image %s! SDL Error: %s\n", imagePath.c_str(), SDL_GetError() );
        success = false;
    }

    gTexture = SDL_CreateTextureFromSurface(gRenderer, gSurface);
    SDL_DestroySurface( gSurface );
    gSurface = nullptr;

    return success;
}

void close() {
    //Clean up surface
    SDL_DestroyTexture( gTexture );
    gTexture = nullptr;

    SDL_DestroyWindow( gWindow );
    gWindow = nullptr;
    SDL_DestroyRenderer( gRenderer );
    gRenderer = nullptr;

    SDL_Quit();
}

int main( int argc, char* args[] ) {
    int exitCode{ 0 };

    if ( init() == false ) {
        SDL_Log( "Unable to intialize program!\n" );
        exitCode = 1;
    }

    else {
        if ( loadMedia() == false ) {
            SDL_Log( "Unable to load media\n" );
            exitCode = 2;
        }
        else {
            bool quit{ false };
            SDL_Event e;
            SDL_zero( e );

            while ( quit == false ) {
                while ( SDL_PollEvent( &e ) == true ) {
                    if ( e.type == SDL_EVENT_QUIT ) {
                        quit = true;
                    }
                }

                SDL_RenderClear( gRenderer );
                SDL_RenderTexture( gRenderer, gTexture, nullptr, nullptr);
                SDL_RenderPresent( gRenderer );
            }
        }

        close();

        return exitCode;
    }
}