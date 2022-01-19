#include "mtapp.hpp"

#if defined(__APPLE__)
#include <unistd.h>
#include <SDL2/SDL.h>
#else
#endif

#include "mt.hpp"

#include "SysTime.hpp"
#include "SysGraphics.hpp"
#include "World.hpp"

NAMESPACES

#ifdef MT_DEBUG
bool Debug::on = false;
#endif

const int   FPS   = 30;
const float SPEED = 1; // 60 / FPS;

uint32_t WIDTH  = 1200;
uint32_t HEIGHT = 720;

bool PAUSED = false;
bool QUIT   = false;

void keyboard_down(World & world, char _key) {
    Logger::log(INFO_LOG, "key press ....... ( %c )", _key);

    switch (_key) {
        case ' ':
            world.player()->jump(true);
            break;
        case 'w':
            world.player()->looking_up(true);
            break;
        case 's':
            world.player()->looking_down(true);
            break;
        case 'a':
            world.player()->moving_left(true);
            break;
        case 'd':
            world.player()->moving_right(true);
            break;
        case 'r':
            world.reset();
            break;
        case 'z':
            world.camera_zoom(1);
            break;
        case '.':
            world.camera_zoom_in();
            break;
        case ',':
            world.camera_zoom_out();
            break;
        case 27: // esc
            QUIT = true;
            break;
        default:
        break;
    }
}

void keyboard_up(World & world, char _key) {
    Logger::log(INFO_LOG, "key release ..... ( %c )", _key);

    switch ((char) _key) {
        case ' ':
            world.player()->jump(false);
            break;
        case 'w':
            world.player()->looking_up(false);
            break;
        case 's':
            world.player()->looking_down(false);
            break;
        case 'a':
            world.player()->moving_left(false);
            break;
        case 'd':
            world.player()->moving_right(false);
            break;
        case 'p':
            PAUSED = !PAUSED;
            break;
#ifdef MT_DEBUG
        case '/':
            Debug::on = !Debug::on;
            break;
        case '\\':
            static bool cursor_shown = true;
            SysGraphics::show_cursor(cursor_shown);
            cursor_shown = !cursor_shown;
            break;
        case 'l':
            static bool lights_on = false;
            world.lights(lights_on);
            lights_on = !lights_on;
            break;
        case 'g':
            world.player()->god(!(world.player()->god()));
            break;
#endif
        default:
        break;
    }
}

void mouse_left_click_down(World & world) {
    Logger::log(INFO_LOG, "mouse down ...... (left)");
    
    world.player()->fire_arrow();
}

void mouse_left_click_up(World & world) {
    Logger::log(INFO_LOG, "mouse up ........ (left)");
    
    world.player()->release_bow();
}

void mouse_right_click_down(World & world) {
    Logger::log(INFO_LOG, "mouse down ...... (right)");
    
    world.player()->fire_hook();
}

void mouse_right_click_up(World & world) {
    Logger::log(INFO_LOG, "mouse up ........ (right)");
    
    world.player()->release_bow();
}

void mouse_move(World & world, int _x, int _y) {
//    Logger::log(INFO_LOG, "mouse move ...... (%i, %i)", _x, _y);
    world.mouse_movement(Coordinate((float)_x, (float)_y));
}

void mouse_scroll_up(World & world) {
//    Logger::log(INFO_LOG, "mouse scroll .... (up)");
    world.camera_zoom_in();
}

void mouse_scroll_down(World & world) {
//    Logger::log(INFO_LOG, "mouse scroll .... (down)");
    world.camera_zoom_out();
}

void mtapp::run() {
    Assert::fatal(!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK), "SDL initialization");
    Assert::fatal(SysGraphics::start(WIDTH, HEIGHT));
    
    Logger::start();
    Random::seed();
    
    bool using_controller = false;
    SDL_JoystickEventState(SDL_ENABLE);
    if (SDL_JoystickOpen(0)) using_controller = true;
    
    World world;
    world.camera_width(WIDTH);
    world.camera_height(HEIGHT);
    
    QUIT = false;
    uint64_t loop = 0;
    while (!QUIT) {
        
        int start_ticks = SDL_GetTicks();
        
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_KEYDOWN:
                    keyboard_down(world, (char)event.key.keysym.sym);
                    break;
                case SDL_KEYUP:
                    keyboard_up(world, (char)event.key.keysym.sym);
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            mouse_left_click_down(world);
                            break;
                        case SDL_BUTTON_RIGHT:
                            mouse_right_click_down(world);
                            break;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    switch (event.button.button) {
                        case SDL_BUTTON_LEFT:
                            mouse_left_click_up(world);
                            break;
                        case SDL_BUTTON_RIGHT:
                            mouse_right_click_up(world);
                            break;
                    }
                    break;
                case SDL_MOUSEMOTION:
                    mouse_move(world, event.motion.x, event.motion.y);
                    break;
                case SDL_MOUSEWHEEL:
                    static bool scroll_flipped = false;
                    if ((scroll_flipped ? -1 : 1) * event.wheel.y > 0) mouse_scroll_up(world);
                    if ((scroll_flipped ? -1 : 1) * event.wheel.y < 0) mouse_scroll_down(world);
                    break;
                    
                // PS4 dualshock
                case SDL_JOYBUTTONDOWN:
                    switch (event.jbutton.button) {
                        case 0: // X
                            world.player()->jump(true);
                            break;
                        case 1: // CIRCLE
                            break;
                        case 2: // SQUARE
                            break;
                        case 3: // TRIANGLE
                            break;
                        case 9: // L1
                            world.player()->jump(true);
                            break;
                        case 10: // R1
                            world.player()->fire_arrow();
                            break;
                        case 11: // D-UP
                            world.camera_zoom_in();
                            break;
                        case 12: // D-DOWN
                            world.camera_zoom_out();
                            break;
                        case 13: // D-LEFT
                            break;
                        case 14: // D-RIGHT
                            break;
                        case 7: // L3
                            break;
                        case 8: // R3
                            break;
                        case 6: // OPTIONS
                            break;
                        case 4: // SHARE
                            break;
                        case 5: // HOME
                            break;
                        case 15: // TOUCH PAD
                            break;
                    }
                    break;
                case SDL_JOYBUTTONUP:
                    switch (event.jbutton.button) {
                        case 0: // X
                            world.player()->jump(false);
                            break;
                        case 1: // CIRCLE
                            break;
                        case 2: // SQUARE
                            break;
                        case 3: // TRIANGLE
                            break;
                        case 9: // L1
                            world.player()->jump(false);
                            break;
                        case 10: // R1
                            world.player()->release_bow();
                            break;
                        case 11: // D-UP
                            break;
                        case 12: // D-DOWN
                            break;
                        case 13: // D-LEFT
                            break;
                        case 14: // D-RIGHT
                            break;
                        case 7: // L3
                            break;
                        case 8: // R3
                            break;
                        case 6: // OPTIONS
                            PAUSED = !PAUSED;
                            break;
                        case 4: // SHARE
                            static bool lights = false;
                            world.lights(lights);
                            lights = !lights;
                            break;
                        case 5: // HOME
#ifdef MT_DEBUG
                            world.player()->god(!(world.player()->god()));
#endif
                            break;
                        case 15: // TOUCH PAD
                            break;
                    }
                    break;
                case SDL_JOYAXISMOTION:
                    // L2 and R2
                    if ((event.jaxis.axis == 4) || (event.jaxis.axis == 5)) {
                        if (event.jaxis.value > 1200) {
                            if (event.jaxis.axis == 5) {
                                world.player()->fire_hook();
                            }
                        } else {
                            world.player()->release_bow();
                        }
                    } else {
                        // left joystick
                        if ((event.jaxis.axis == 0) || (event.jaxis.axis == 1)) {
                            
                            if (event.jaxis.axis == 0) {
                                if (event.jaxis.value > 6400) {
                                    world.player()->moving_right(true);
                                } else if (event.jaxis.value < -6400) {
                                    world.player()->moving_left(true);
                                } else {
                                    world.player()->moving_right(false);
                                    world.player()->moving_left(false);
                                }
                            } else if (event.jaxis.axis == 1) {
                                if (event.jaxis.value > 6400) {
                                    world.player()->looking_down(true);
                                } else if (event.jaxis.value < -6400) {
                                    world.player()->looking_up(true);
                                } else {
                                    world.player()->looking_down(false);
                                    world.player()->looking_up(false);
                                }
                            }
                            
                        }
                        
                        // right joystick
                        if ((event.jaxis.axis == 2) || (event.jaxis.axis == 3)) {
                            static int x_axis = 0;
                            static int y_axis = 0;
                            if (abs(event.jaxis.value) > 3200) {
                                if (event.jaxis.axis == 2) x_axis = event.jaxis.value;
                                if (event.jaxis.axis == 3) y_axis = -event.jaxis.value;
                            }
                            
                            world.mouse_movement(world.player()->position() + Vector(Angle((float)x_axis, (float)y_axis), 128));
                        }
                    }
                    
                    break;
                    
                // exit
                case SDL_WINDOWEVENT:
                    switch (event.window.event) {
                        case SDL_WINDOWEVENT_CLOSE:
                            QUIT = true;
                            break;
                    }
                    break;
                case SDL_QUIT:
                    QUIT = true;
                    break;
                
            }
        }
        
        if (QUIT) break;
        
        SysGraphics::clear();
        
        if (!PAUSED) world.update(SPEED);
        world.draw();
        ++loop;
        
        SysGraphics::render();
        
        int end_ticks = SDL_GetTicks();
        int delta_ticks = end_ticks - start_ticks;
        int wait_ticks = (1000.0 / (float)FPS) - (float)delta_ticks;
        
        if (wait_ticks > 0) {
            SDL_Delay(wait_ticks);
        } else if (wait_ticks < 0) {
#ifdef MT_DEBUG
            if (Debug::on) {
//                Logger::log(INFO_LOG, "missed target by %ims", abs(wait_ticks));
            }
#endif
        }
    }
    
    if (using_controller) SDL_JoystickClose(0);
    SysGraphics::close();
    SDL_Quit();
    Logger::close();
}
