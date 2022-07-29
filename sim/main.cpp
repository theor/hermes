#include <stdio.h>
#include <stdbool.h>

#define SDL_MAIN_HANDLED

#include <Adafruit_SSD1306.h>
#include <SDL.h>
#include <cmath>

template<typename T>
T min(T a, T b) { return a < b ? a : b; }

template<typename T>
T max(T a, T b) { return a > b ? a : b; }


Adafruit_SSD1306 display(128, 64);
bool pressed = false;
bool debugMode = true;
#include <renderers/rain.h>

// Define MAX and MIN macros
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

// Define screen dimensions
int f = 4;
#define SDL_SCREEN_WIDTH    (SCREEN_HEIGHT*f + 2)
#define SDL_SCREEN_HEIGHT   (SCREEN_WIDTH*f + 2)

Rain::RainRenderer renderer;
#ifdef __cplusplus
extern "C"
#endif


void keyInfo(SDL_Keysym k)
{
    /* If there are none then say so and return */
    if (k.mod == KMOD_NONE)
    {
        printf("None\n");
        return;
    }

    /* Check for the presence of each SDLMod value */
    /* This looks messy, but there really isn't    */
    /* a clearer way.                              */
    if (k.mod & KMOD_NUM) printf("NUMLOCK ");
    if (k.mod & KMOD_CAPS) printf("CAPSLOCK ");
    if (k.mod & KMOD_LCTRL) printf("LCTRL ");
    if (k.mod & KMOD_RCTRL) printf("RCTRL ");
    if (k.mod & KMOD_RSHIFT) printf("RSHIFT ");
    if (k.mod & KMOD_LSHIFT) printf("LSHIFT ");
    if (k.mod & KMOD_RALT) printf("RALT ");
    if (k.mod & KMOD_LALT) printf("LALT ");
    if (k.mod & KMOD_CTRL) printf("CTRL ");
    if (k.mod & KMOD_SHIFT) printf("SHIFT ");
    if (k.mod & KMOD_ALT) printf("ALT ");
    printf("\n");
}

SDL_HitTestResult hit_test(SDL_Window *win,
              const SDL_Point *area,
              void *data){
return SDL_HITTEST_DRAGGABLE;
}

int main(int argc, char *argv[])
{
    // Unused argc, argv
//    (void) argc;
//    (void) argv;
    // Initialize SDL
    Serial.println("test");
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not be initialized!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 0;
    }

#if defined linux && SDL_VERSION_ATLEAST(2, 0, 8)
    // Disable compositor bypass
    if(!SDL_SetHint(SDL_HINT_VIDEO_X11_NET_WM_BYPASS_COMPOSITOR, "0"))
    {
        printf("SDL can not disable compositor bypass!\n");
        return 0;
    }
#endif

    // Create window
    SDL_Window *window = SDL_CreateWindow("Basic C SDL project",
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED,
                                          SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_ALWAYS_ON_TOP | SDL_WINDOW_BORDERLESS);
    if (!window)
    {
        printf("Window could not be created!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 1;
    }
    SDL_SetWindowHitTest(window, &hit_test, nullptr);
    // Create sdlRenderer
    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!sdlRenderer)
    {
        printf("Renderer could not be created!\n"
               "SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    rocket_init();


    int nx = 64;
    int ny = 128;
    SDL_Texture *theTexture = SDL_CreateTexture(sdlRenderer, SDL_PIXELFORMAT_ARGB8888,
                                                SDL_TEXTUREACCESS_STREAMING, nx, ny);
    uint32_t *textureBuffer = new uint32_t[nx * ny];

    // Event loop exit flag
    bool quit = false;

    display.begin();
    display.setRotation(1);
    display.setTextColor(WHITE, BLACK);
    renderer.start();
    sync_set_base(device, renderer.getPrefix());
    renderer.initTracks(device);
    Uint64 last = SDL_GetPerformanceCounter();
    // Event loop
    while (!quit)
    {
        rocket_update();
        Uint64 now = SDL_GetPerformanceCounter();
        Uint64 elapsed = (now - last) * 1000 / (double) SDL_GetPerformanceFrequency();
//        std::cout << elapsed << std::endl;

//        display.clearDisplay();
//        display.drawPixel(0, 64, WHITE);
//                display.drawPixel(4,0, WHITE);
//                display.drawPixel(4,8, WHITE);
//                display.fillCircle(32,32,32, WHITE);
//        display.drawRect(1, 1, 60, 120, WHITE);

        SDL_Event e;

        // Wait indefinitely for the next available event
        while (SDL_PollEvent(&e))
        {
            switch (e.type)
            {
                case SDL_MOUSEWHEEL:
                    f = max(1, f + ((e.wheel.y > 0) ? 1 : -1));
                    SDL_SetWindowSize(window, SDL_SCREEN_WIDTH, SDL_SCREEN_HEIGHT);
                    break;
                case SDL_KEYDOWN:
                    if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
                        quit = true;
                    if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    {
                        if (!pressed)
                            renderer.press(true);
                        pressed = true;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (e.button.button == 1)
                    {
                        if (!pressed)
                            renderer.press(true);
                        pressed = true;
                    }
                    break;
                case SDL_KEYUP:
                    if (e.key.keysym.scancode == SDL_SCANCODE_SPACE)
                    {
                        if (pressed)
                            renderer.press(false);
                        pressed = false;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (e.button.button == 1)
                    {
                        if (pressed)
                            renderer.press(false);
                        pressed = false;
                    }
                    break;

                    // User requests quit
                case SDL_QUIT:quit = true;
                    break;
                default:break;
            }
        }


        display.setCursor(4,32);
//        display.println("test");
        renderer.update(pressed);


        // Initialize sdlRenderer color white for the background
        SDL_SetRenderDrawColor(sdlRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        // Clear screen
        SDL_RenderClear(sdlRenderer);


        for (int i = 0; i < nx * ny; ++i)
        {
//                    auto b = display.getBuffer()[i/8];
//                    auto off = 1 << (i % 8);
            display.setRotation(0);
            auto mask = display.getPixel(SCREEN_WIDTH - (i / SCREEN_HEIGHT), i % SCREEN_HEIGHT);
            display.setRotation(1);
            textureBuffer[i] = (mask == display.inverted)
                    ? 0xff000000
                    : 0xff2ad0e7;
        }
        SDL_UpdateTexture(theTexture, NULL, textureBuffer, nx * sizeof(uint32_t));

        SDL_Rect rect = {1, 1, nx * f, ny * f};
        SDL_RenderCopy(sdlRenderer, theTexture, NULL, &rect);

        // Draw filled square

        // Set sdlRenderer color red to draw the square
        SDL_SetRenderDrawColor(sdlRenderer, pressed ? 0xFF : 0x00, 0x00, 0x00, 0xFF);
        SDL_Rect r = {1, 130 * f, 62 * f, 30 };
         SDL_RenderFillRect(sdlRenderer, &r);

        // Update screen
        SDL_RenderPresent(sdlRenderer);
    }

    // Destroy sdlRenderer
    SDL_DestroyRenderer(sdlRenderer);

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL
    SDL_Quit();

    return 0;
}
