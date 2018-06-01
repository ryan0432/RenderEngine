#pragma once
#include "Camera_Base.h"
class Camera_Free : public Camera_Base
{
public:
	Camera_Free(std::string camName, vec3 camPos, CamType camType,
				float fovY, float aspectRatio,
				float nearClip, float farClip,
				vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis);

	Camera_Free(std::string camName, vec3 camPos, CamType camType,
				float left, float right, float bottom, float top,
				float nearClip, float farClip,
				vec3 lookAtFrom, vec3 lookAtTo, vec3 camUpAxis);

	virtual ~Camera_Free();
	virtual void Update();
};

