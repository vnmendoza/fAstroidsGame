#include "Bullet.h"


Bullet::Bullet()
{
    pos = glm::vec3(0, 0,0);
    vel = pos;
    rotation = 0;
    speed = 10;

}

void Bullet::setup(glm::vec3 p, ofImage* bullet_image) {
    //from_player = f_p;
    pos = p;
    img = bullet_image;
    imgWidth = img->getWidth();
    imgHeight = img->getHeight();
}

void Bullet::update() {
    /*
    if (from_player) {
        pos.y -= speed;
    }
    else {
        pos.y += speed;
    }
*/
    cout << "super bullet" << endl;
}
void Bullet::draw() {
    ofPushMatrix();
    ofSetColor(ofColor::white);
    ofMultMatrix(getMatrix());
    img->setAnchorPoint(imgWidth / 2, imgHeight / 2);
    img->draw(0, 0, imgWidth, imgHeight);
    ofPopMatrix();

}

glm::vec3 Bullet::getPos()
{
    return pos;
}

float Bullet::getWidth()
{
    return imgWidth;
}

float Bullet::getDamage()
{
    return damage;
}

void Bullet::setDamage(float dmg)
{
    damage = dmg;
}

glm::mat4 Bullet::getMatrix() {
    glm::mat4 trans = glm::translate(glm::mat4(1.0), pos);
    glm::mat4 rot = glm::rotate(glm::mat4(1.0), glm::radians(rotation), glm::vec3(0, 0, 1));
    glm::mat4 scale = glm::scale(glm::mat4(1.0), scaler);
    return (trans * rot * scale);
}

// PLAYER BULLET
PlayerBullet::PlayerBullet() : Bullet()
{
    
}
void Bullet::setDirection(glm::vec3 mousePos)
{
    vel = pos - mousePos;
    vel = glm::normalize(vel);
    rotation = glm::orientedAngle(vel, glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));
    rotation = glm::degrees(rotation);
    vel *= -speed;
}
void PlayerBullet::move()
{
    pos += vel;
}
void PlayerBullet::update()
{
    move();
    //enemyCollision()
}


EnemyBullet::EnemyBullet() : Bullet()
{
}

void EnemyBullet::update()
{

}


