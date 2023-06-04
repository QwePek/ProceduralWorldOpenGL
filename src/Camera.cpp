#include "Camera.h"

Camera::Camera(glm::vec3 pos = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = -90.0f, float pitch = 0.0f)
{
    this->position = pos;
    this->worldUp = up;
    this->yaw = yaw;
    this->pitch = pitch;

    recalculateCameraVectors();
}

Camera::Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
{
    this->position = glm::vec3(posX, posY, posZ);
    this->worldUp = glm::vec3(upX, upY, upZ);
    this->yaw = yaw;
    this->pitch = pitch;

    recalculateCameraVectors();
}

void Camera::processInput(direction dir, double dt)
{
    //Cam movement
    const float camSpeed = speed * dt;

    if (dir == direction::FORWARD)
        position += front * camSpeed;

    if (dir == direction::BACKWARD)
        position -= front * camSpeed;

    if (dir == direction::RIGHT)
        position += right * camSpeed;

    if (dir == direction::LEFT)
        position -= right * camSpeed;
}

void Camera::processMouse(double xOffs, double yOffs)
{
    xOffs *= mouseSensitivity;
    yOffs *= mouseSensitivity;

    yaw += xOffs;
    pitch += yOffs;

    //Constrains
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    recalculateCameraVectors();
}

void Camera::processZoom(double xOffset, double yOffset)
{
    zoom -= (float)yOffset;

    if (zoom < 1.0f)
        zoom = 1.0f;
    if (zoom > 45.0f)
        zoom = 45.0f;
}

glm::mat4 Camera::getProjectionMatrix(glm::vec2 windowSize)
{
    projection = glm::perspective(glm::radians(zoom), windowSize.x / (float)windowSize.y, 0.1f, 100.0f);

    return projection;
}

glm::mat4 Camera::getViewMatrix()
{
    view = glm::lookAt(position, position + front, up);

    return view;
}

void Camera::recalculateCameraVectors()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(direction);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}