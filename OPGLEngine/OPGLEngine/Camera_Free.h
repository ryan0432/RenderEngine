#pragma once
#ifndef CAM_FREE_H
#define CAM_FREE_H
#include "Camera_Base.h"
class Camera_Free : public Camera_Base
{
public:
	Camera_Free(std::string camName, CamType camType,
				float fovY, float aspectRatio,
				float left, float right, float bottom, float top,
				float nearClip, float farClip,
				vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis);

	virtual ~Camera_Free();
	virtual void Update(float deltaTime);

private:
	float moveSpeed;
	float rotationSpeed;
};

#endif
