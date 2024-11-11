#pragma once

#include "pch.h"
#include "Mat4x4.h"

class Frustum {
public:
	Frustum();
	void ExtractFrustumPlanes(const Mat4x4& viewProjectionMatrix);

	//bool IsChunkInFrustum(const glm::vec3& min, const glm::vec3& max);
	bool IsChunkInFrustum(short global_x, short global_z);
	bool IsGroupChunkInFrustum(short group_x, short group_z, short group_size);
private:
	Vec4<float> m_FrustumPlanes[6];
};