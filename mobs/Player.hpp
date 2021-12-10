#ifndef Player_hpp
#define Player_hpp

#include "Mob.hpp"

#include "Timer.hpp"
#include "Rope.hpp"

namespace mt {

class Player : public Mob {
public:
    Player(World*, const Coordinate & center);
    
    void update();
    void draw(const Camera &) const;
    void draw_reticle(const Camera &) const;
    
    void moving_right(bool);
    void moving_left(bool);
    void looking_up(bool);
    void looking_down(bool);
    
    void jump(bool);
    
    void aim(const Angle &);
    void fire_hook();
    void retract_hook();
    
private:
    void update_velocity();
    void move(const Vector &);
    
    void kill();
    void hurt(int health);
    
    bool m_moving_right = false;
    bool m_moving_left = false;
    bool m_looking_up = false;
    bool m_looking_down = false;
    bool m_jumping = false;
    float m_jump_degradation = 0;
    Timer m_jumping_timer;
    Timer m_jump_reset_timer;
    
    float m_movement_speed;
    
    bool m_aiming = true;
    Angle m_aim_angle = 0;
    
    bool m_firing_hook = false;
    
    Rope m_rope;
    float m_rope_max_length;
    float m_hook_growth_speed;
    float m_hook_retract_speed;
    
#ifdef MT_DEBUG
public:
    bool god() const;
    void god(bool);
private:
    bool god_mode = false;
#endif
};

}

#endif /* Player_hpp */
