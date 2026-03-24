#include <complex>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <string>
#include <SDL3_ttf/SDL_ttf.h>
#include "weather_api.hpp"

constexpr int kScreenWidth{640};
constexpr int kScreenHeight{480};

bool init();
bool loadMedia();
void close();

SDL_Window* gWindow{ nullptr };
SDL_Renderer* gRenderer{ nullptr };
SDL_Surface* gSurface{ nullptr };
SDL_Texture* gTexture{ nullptr };
TTF_Font* gFont{ nullptr };
TTF_TextEngine* gTextEngine{ nullptr };
TTF_Text* gText{ nullptr };
std::string imagePath{ "assets/test.bmp" };
std::string fontPath{"assets/KiwiSoda.ttf" };

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
            TTF_Init();
            gFont = TTF_OpenFont(fontPath.c_str(), 100);
            gTextEngine = TTF_CreateRendererTextEngine(gRenderer);
        }
    }

    return success;
}

bool loadMedia() {
    bool success{ true };
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

    TTF_DestroyText(gText);
    TTF_DestroyRendererTextEngine(gTextEngine);
    TTF_CloseFont( gFont );
    TTF_Quit();
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

            json weather_data = get_weather_data();
            double temp = weather_data["current"]["temperature_2m"];
            double feel_temp = weather_data["current"]["apparent_temperature"];
            std::string temperatures = std::format("Adelaide\nTemp:{}\nFeel Temp:{}\n", temp, feel_temp);
            gText = TTF_CreateText(gTextEngine, gFont, temperatures.c_str(), 0);
            TTF_SetTextColor(gText, 18, 53, 36, 255);

            while ( quit == false ) {
                while ( SDL_PollEvent( &e ) == true ) {
                    if ( e.type == SDL_EVENT_QUIT ) {
                        quit = true;
                    }
                }
                SDL_RenderClear( gRenderer );
                TTF_DrawRendererText(gText, 1, 0);
                SDL_RenderPresent( gRenderer );
            }
        }

        close();

        return exitCode;
    }
}