#include "Bullet.h"


Bullet::Bullet()
{
    pos = glm::vec3(0, 0,0);
    heading = pos;
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

void Bullet::setup(glm::vec3* pPosition, ofImage* pBullet_img)
{
    //pos = *pPosition;
    setup(glm::vec3(0), pBullet_img);
}

void Bullet::draw() {
    ofPushMatrix();
    ofSetColor(ofColor::white);
    //ofMultMatrix(glm::inverse(getMatrix()));
    img->setAnchorPoint(imgWidth / 2, imgHeight / 2);
    img->draw(0, pos.y, imgWidth, imgHeight);
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

void Bullet::setDirection(glm::vec3 targetPos)
{
    heading = pos - targetPos;
    heading = glm::normalize(heading);
    rotation = glm::orientedAngle(heading, glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));
    rotation = glm::degrees(rotation);
    heading *= -speed;
}
void Bullet::move()
{
    pos += heading;
}
void Bullet::update()
{
    move();
    //rotate?
}



