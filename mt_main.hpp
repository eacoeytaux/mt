#ifndef mt_main_hpp
#define mt_main_hpp

#include "mt.hpp"

namespace mt {

/// @class MTROGUE
/// @brief actual game application
class MTROGUE {
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
/// click - fire grappling hook (and hold)
/// @subsection Debug
/// G - toggle god mode (WASD to move)
/// \n
/// L - toggle the lights
/// \n
/// ? - toggle debug mode
/// @section install_sec Installation
/// install OpenGL and GLUT
/// \n
/// TODO...

}

#endif /* mt_main_hpp */
