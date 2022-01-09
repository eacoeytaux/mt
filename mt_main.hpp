#ifndef mt_main_hpp
#define mt_main_hpp

#include "util/mt.hpp"

namespace mt {

/// @class MTAPP
/// @brief actual game application
class MTAPP {
public:
    /// @brief run game
    static void run();
    /// @brief shutdown application
    /// @param exitcode exit code for application
    static void shutdown(int exitcode = 0);
};

/// @mainpage mt
/// @section intro_sec Introduction
/// this is a game engine titled mt
/// \n
/// it is written in C++
/// \n
/// it uses OpenGL and GLUT
/// \n
/// it is 2d
/// \n
/// it is amazing
/// @section controls_sec Controls
/// @subsection Game
/// A - move left
/// \n
/// D - move right
/// \n
/// space - jump
/// \n
/// click + shift - fire grappling hook (and hold)
/// \n
/// click - fire arrow
/// \n
/// P - pause
/// @subsection Debug
/// G - toggle god mode (WASD to move)
/// \n
/// L - toggle the lights
/// \n
/// ? - toggle debug mode
/// \n
/// < - zoom out
/// \n
/// > - zoom in
/// @section install_sec Installation
/// @subsection Mac OSX
/// OpenGL and GLUT come installed
/// \n
/// go to Project -> Build Phases -> Link Binary With Library and add OpenGL and GLUT
/// @subsection Windows 10
/// just give up...

}

#endif /* mt_main_hpp */
