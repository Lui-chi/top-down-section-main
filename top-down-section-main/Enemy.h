#include "raylib.h"
#include "BaseCharacter.h"
#include "Character.h"

class Enemy : public BaseCharacter
{
private:
    Character* target;
    float speed = 1.5f;
    float damagePerSec{10.f};
    float radius{25.f};
public:
    Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture);
    void tick(float deltaTime) override;
    void setTarget(Character* character) {target = character; }
    virtual Vector2 getScreenPos() override;
};

