#ifndef Player_hpp
#define Player_hpp

#include "mt.hpp"
#include "Mob.hpp"
#include "HookRope.hpp"
#include "Hook.hpp"

namespace mt {
namespace exst {

class Player : public Mob {
public:
    virtual ~Player() { }
    Player(World *, const Coordinate & center);
    
    void update(float dt = 1) override;
    void draw(const Camera *) const override;
    void draw_reticle(const Camera *) const;
    
    void kill() override;
    void hurt(uint health) override;
    
    void moving_right(bool);
    void moving_left(bool);
    void looking_up(bool);
    void looking_down(bool);
    
    void jump(bool);
    
    void aim(const Angle &);
    void fire_hook();
    void fire_arrow();
    void release_bow();
    
private:
    void adjust_velocity(float dt) override;
    void move(float dt) override;
    
    void draw_head(const Camera *) const;
    void draw_body(const Camera *) const;
    void draw_front_arm(const Camera *) const;
    void draw_front_leg(const Camera *) const;
    void draw_back_arm(const Camera *) const;
    void draw_back_leg(const Camera *) const;
    void draw_boot(const Camera *, const Coordinate & foot_position) const;
    void draw_accessories(const Camera *) const;
    
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
    bool m_firing_arrow = false;
    Hook m_hook;
    HookRope m_rope;
    float m_rope_max_length;
    float m_hook_growth_speed;
    float m_hook_retract_speed;
    
    Timer m_reload_timer;
    
#ifdef MT_DEBUG
public:
    bool god() const;
    void god(bool);
private:
    /// @brief whether or not player is an indestructible god
    bool god_mode = true;
#endif
};

}
}

#endif /* Player_hpp */
