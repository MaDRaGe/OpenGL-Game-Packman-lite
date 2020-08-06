#include "Camera.h"

Camera::Camera()
{ 
    position = vec3(0,30,30); 
    calcDistance(); 
    calcAngleA(); 
    calcAngleB(); 
}
Camera::Camera(vec3 position) 
{ 
    this->position = position; 
    calcDistance(); 
    calcAngleA(); 
    calcAngleB(); 
}
Camera::Camera(
    float x, 
    float y, 
    float z
)
{ 
    position = vec3(x, y, z); 
    calcDistance(); 
    calcAngleA(); 
    calcAngleB();  
}

// ���������� ��������� 
void Camera::calcPosition()
{
    position.y = distance * sin(3.14 / 180 * angleA);
    position.x = distance * cos(3.14 / 180 * angleA) * cos(3.14 / 180 * angleB);
    position.z = distance * cos(3.14 / 180 * angleA) * sin(3.14 / 180 * angleB);
}
void Camera::setPosition(vec3 position)
{ 
    this->position = position; 

}
vec3 Camera::getPosition()
{ 
    return position; 
}

// ��������� ���� �������� �� ���������
void Camera::calcAngleA()
{
    angleA = acos( sqrt(pow(position.x, 2) + pow(position.z, 2))
                   / distance
                 ) * 180 / 3.14;
}
void Camera::setAngleA(float angle)
{
    if (angle > 85) angle = 85;
    if (angle < 5) angle = 5;
    this->angleA = angle;

    // ��������� ����� ���������
    calcPosition();
}
float Camera::getAngleA() 
{ 
    return angleA; 
}

// ��������� ���� �������� �� �����������
void Camera::calcAngleB()
{
    angleB = acos(
        position.x / sqrt(
            pow(position.x, 2) + 
            pow(position.z, 2)
        )
    ) * 180 / 3.14;
}
void Camera::setAngleB(float angle)
{
    if (angle > 360) angle = -360;
    if (angle < -360) angle = 360;
    this->angleB = angle;

    // ��������� ����� ���������
    calcPosition();
}
float Camera::getAngleB() 
{ 
    return angleB; 
}

// ���������� ��������� �� ������ ���������
void Camera::calcDistance()
{
    distance = sqrt(
        pow(position.x, 2) + 
        pow(position.y, 2) + 
        pow(position.z, 2)
    );
}
void Camera::setDistance(float dist)
{
    // �������� ������������ �������� ���������
    if (dist > 50) dist = 50;
    if (dist < 10) dist = 10;
    distance = dist;

    // ��������� ����� ���������
    calcPosition();
}
float Camera::getDistance() 
{ 
    return distance; 
}

// ������� ������ �� �����������
void Camera::rotateLeftRight(float degree)
{
    angleB += degree;
    setAngleB(angleB);
}

// ������� ������ �� ���������
void Camera::rotateUpDown(float degree)
{
    angleA += degree;
    setAngleA(angleA);
}

// �������� ���������� �� ������ �����
void Camera::zoomInOut(float dist)
{
    distance += dist;
    setDistance(distance);
}

// ���������� �������� ������
void Camera::apply()
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(
        position.x, 
        position.y, 
        position.z, 
        0, 0, 0, 
        0, 1, 0
    );
}
