#include "mt_main.hpp"

#define GL_SILENCE_DEPRECATION

#if defined(__APPLE__)
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "mt.hpp"

#include "SysTime.hpp"
#include "World.hpp"

NAMESPACES

#ifdef MT_DEBUG
bool Debug::on = false;
#endif

int window_handle = 0;
GLsizei width = 800;
GLsizei height = 600;

const int FPS = 60;
uint8_t timer_wait = 1000 / FPS;

const bool ANTI_ALIAS = true;

bool paused = false;
float speed = 1;
World world;

void timer(int _t) {
    static uint64_t loop = 0;
    ++loop;
#ifdef MT_DEBUG
//    cout << "loop " << loop << endl;
#endif
    if (!paused) world.update(speed);
    glutPostRedisplay();
    glutTimerFunc(timer_wait, timer, 0);
}

void display(void) {
    glClear(GL_COLOR_BUFFER_BIT);
    world.draw();
    glFlush();
}

void reshape_window(int _w, int _h) {
    width = _w;
    height = _h;
    world.camera_width(width);
    world.camera_height(height);
    glViewport(0, 0, (GLsizei) width, (GLsizei) height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, width, 0.0, height, -1.f, 1.f);
}

void keyboard_down(unsigned char _key, int _x, int _y) {
    Logger::print(INFO_LOG, "key press ....... ( %c )", _key);
    cout << "key press ....... ( " << _key << " )" << endl;
    
    switch ((char) _key) {
        case ' ':
            world.player()->jump(true);
            break;
        case 'w':
        case 'W':
            world.player()->looking_up(true);
            break;
        case 's':
        case 'S':
            world.player()->looking_down(true);
            break;
        case 'a':
        case 'A':
            world.player()->moving_left(true);
            break;
        case 'd':
        case 'D':
            world.player()->moving_right(true);
            break;
        case 'r':
        case 'R':
            world.reset();
            world.camera_width(width);
            world.camera_height(height);
            break;
        case '>':
            world.camera_zoom_in();
            break;
        case '<':
            world.camera_zoom_out();
            break;
        case 27: // esc
            glutDestroyWindow(window_handle);
            MTAPP::shutdown();
            break;
        default:
        break;
    }
}

void keyboard_up(unsigned char _key, int _x, int _y) {
    Logger::print(INFO_LOG, "key release ..... ( %c )", _key);
    cout << "key release ..... ( " << _key << " )" << endl;
    
    switch ((char) _key) {
        case ' ':
            world.player()->jump(false);
            break;
        case 'w':
        case 'W':
            world.player()->looking_up(false);
            break;
        case 's':
        case 'S':
            world.player()->looking_down(false);
            break;
        case 'a':
        case 'A':
            world.player()->moving_left(false);
            break;
        case 'd':
        case 'D':
            world.player()->moving_right(false);
            break;
        case 'p':
        case 'P':
            paused = !paused;
            break;
#ifdef MT_DEBUG
        case '?':
            Debug::on = !Debug::on;
            break;
        case 'l':
        case 'L':
            static bool lights = false;
            world.lights(lights);
            lights = !lights;
            break;
        case 'g':
        case 'G':
            world.player()->god(!(world.player()->god()));
            //  world.player()->gravity_affected(!world.player()->gravity_affected());
            break;
#endif
        default:
        break;
    }
}

void mouse_click(int _button, int _state, int _x, int _y) {
    int modifiers;
    int shift;
    
    modifiers = glutGetModifiers();
    shift = modifiers & GLUT_ACTIVE_SHIFT;
    
    switch (_button) {
        // treat all as same
        case GLUT_LEFT_BUTTON:
        case GLUT_RIGHT_BUTTON:
        case GLUT_MIDDLE_BUTTON:
            if (_state == GLUT_DOWN) {
                Logger::print(INFO_LOG, "mouse click ..... ( %i : %i )", _x, _y);
                cout << "mouse click ..... ( " << _x << " : " << _y << " )" << endl;
                
                if (shift || (_button == GLUT_RIGHT_BUTTON)) {
                    world.player()->fire_hook();
                } else {
                    world.player()->fire_arrow();
                }
            }
            else if (_state == GLUT_UP) {
                Logger::print(INFO_LOG, "mouse release ... ( %i : %i )", _x, _y);
                cout << "mouse release ... ( " << _x << " : " << _y << " )" << endl;
                
                world.player()->release_bow();
            }
        default:
        break;
    }
}

void mouse_move(int _x, int _y) {
    world.mouse_movement(Coordinate((float)_x, (float)_y));
}

void MTAPP::run() {
    Logger::start();
    Random::seed();
//    Random::seed((unsigned int)SysTime::total_ms());
    
    world.camera_width(width);
    world.camera_height(height);
    
    int argc = 0; char * argv[] = { 0 };
    glutInit(&argc, argv);
    
    if (ANTI_ALIAS) glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH | GLUT_MULTISAMPLE);
    else glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    
    glutInitWindowSize(width, height);
    window_handle = glutCreateWindow("mt");
    
    if (ANTI_ALIAS) {
        glEnable(GL_MULTISAMPLE);
        glHint(GL_MULTISAMPLE_FILTER_HINT_NV, GL_NICEST);
        
        glEnable(GL_POINT_SMOOTH);
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_POLYGON_SMOOTH);
        
        glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);
        glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    }
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    glClearColor(0, 0, 0, 0);
    glutDisplayFunc(display);
    glutReshapeFunc(reshape_window);
    glutKeyboardFunc(keyboard_down);
    glutKeyboardUpFunc(keyboard_up);
    glutMouseFunc(mouse_click);
    glutMotionFunc(mouse_move);
    glutPassiveMotionFunc(mouse_move);
    
    glutTimerFunc(timer_wait, timer, 0);
    glutMainLoop();
}
    
void MTAPP::shutdown(int _exitcode) {
    Logger::close();
    exit(_exitcode);
}
