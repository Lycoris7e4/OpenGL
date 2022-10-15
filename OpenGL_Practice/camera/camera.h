#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// Default camera values
const glm::vec3 FRONT = glm::vec3(0.0f, 0.0f, -1.0f);
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera {
public:
    // Attributes
    glm::vec3 Position;
    glm::vec3 WorldUp;
    glm::vec3 Front = FRONT;
    glm::vec3 Up;
    glm::vec3 Right;

    // Euler Angles
    float Yaw;
    float Pitch;

    // Configurations
    float MovementSpeed = SPEED;
    float MouseSensitivity = SENSITIVITY;
    float Zoom = ZOOM;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
           glm::vec3 up       = glm::vec3(0.0f, 1.0f, 0.0f),
           float yaw = YAW, float pitch = PITCH);

    Camera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch = true);
    void ProcessMouseScroll(float yoffset);

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void updateCameraVectors();
};
#endif
