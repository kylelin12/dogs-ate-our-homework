#include "main.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Key press surfaces constants
enum KeyPressSurfaces{
    
    KEY_PRESS_SURFACE_DEFAULT,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL
};


int init(){
    int success = 1;
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        success = 0;
    }
    else{
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }
        
        
        window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( window == NULL ){
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
            success = 0;
        }
        else{
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            if(renderer == NULL){
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = 0;
            }
            else{
                //Initialize renderer color
                SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
                
                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = 0;
                }
                
            }
            
        }
        
    }
    return success;
    
}

int loadMedia(){
    int success = 1;
    
    
    return success;
}


void closeProgram(){
    
    SDL_DestroyTexture(texture);
    texture = NULL;
    
    //Destroy window
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow( window );
    renderer = NULL;
    window = NULL;
    
    //Quit SDL subsystems
    SDL_Quit();
    IMG_Quit();
    
}

SDL_Texture* loadTexture(char * filepath){
    SDL_Texture* newTexture = NULL;
    
    SDL_Surface * tempSurface = IMG_Load(filepath);
    if( tempSurface == NULL ){
        printf( "Unable to load image %s! SDL_image Error: %s\n", filepath, IMG_GetError() );
    }
    else{
        //Create texture from surface pixels
        newTexture = SDL_CreateTextureFromSurface( renderer, tempSurface);
        if( newTexture == NULL){
            printf( "Unable to create texture from %s! SDL Error: %s\n", filepath, SDL_GetError() );
        }
        //Get rid of old loaded surface
        SDL_FreeSurface( tempSurface );
    }
    
    return newTexture;
}

void eventHandler(){
    //loop flag
    int quit = 0;
    
    //Event Handler
    SDL_Event event;
    //While application is running
    while(!quit){
        
        //Handle Events
        while(SDL_PollEvent(&event) != 0){
            
            //User requests quit
            if(event.type == SDL_QUIT){
                quit = 1;
            }
            
            else if( event.type == SDL_KEYDOWN )
            {
                //Select surfaces based on key press
                switch( event.key.keysym.sym )
                {
                    case SDLK_UP:
                        printf("Pressed Up\n");
                        break;
                        
                    case SDLK_DOWN:
                        printf("Pressed Down\n");
                        break;
                        
                    case SDLK_LEFT:
                        printf("Pressed Left\n");
                        break;
                        
                    case SDLK_RIGHT:
                        printf("Pressed Right\n");
                        break;
                        
                    default:
                        printf("Unknown Key Touch\n");
                        break;
                }
            }
            
        }
        
        //Updating the surface
        
        SDL_RenderClear(renderer);
        
        SDL_RenderCopy(renderer, texture, NULL, NULL);
        
        SDL_RenderPresent(renderer);
        
    }
}


int main( int argc, char* args[] ){
    if(!init()){
        printf( "Failed to initialize!\n" );
    }
    else{
        if(!loadMedia()){
            printf("failed to load media\n");
        }
        else{
            eventHandler();
        }
    }
    
    closeProgram();
    return 0;
}
