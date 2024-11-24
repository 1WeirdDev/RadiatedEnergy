#include <pch.h>

#include "MatrixUtils.h"
#include "Core/Logger.h"
#include "Vec4.h"

void MatrixUtils::MultiplyMat4x4(float* dst, float* first, float* second){
    float data[16];
    memset(data, 0, sizeof(data));

    for (unsigned char row = 0; row < 4; ++row) {
        for (unsigned char col = 0; col < 4; ++col) {
            for (unsigned char k = 0; k < 4; ++k) {
                data[col * 4 + row] += GetMat4Data(first, row, k) * GetMat4Data(second, k, col);
            }
        }
    }

    for(unsigned char i = 0; i < 16; i++)
        dst[i] = data[i];
}

#pragma region Projection
void MatrixUtils::CreateOrthoProjection(float* dst, float pNear, float pFar, float left, float right, float top, float bottom){
    // Set the matrix values according to the orthographic projection formul
    SetMat4Data(dst, 0, 0, 2.0f / (right - left));
    SetMat4Data(dst, 0,3, -(right + left / right - left));

    SetMat4Data(dst, 1, 1, 2.0f / (top - bottom));
    SetMat4Data(dst, 1,3, -(top + bottom / top - bottom));
    //SetMat4Data(dst, 2,2,- 2.0f / (pFar - pNear));
    //SetMat4Data(dst, 3,2,- (pFar + pNear) / (pFar - pNear));
}

void MatrixUtils::CreatePerspectiveProjection(float* dst, float fovInRadians, float aspectRatio, float pNear, float pFar) {
    float tanHalfFovy = std::tan(fovInRadians / 2.0f);
    SetMat4Data(dst, 0, 0, 1.0f / (aspectRatio * tanHalfFovy));
    SetMat4Data(dst, 1, 1, (1.0f / tanHalfFovy));
    SetMat4Data(dst, 2, 2, - (pFar + pNear) / (pFar - pNear));
    SetMat4Data(dst, 3, 2, - 1.0f);
    SetMat4Data(dst, 2, 3, -(2.0f * pFar * pNear) / (pFar - pNear));
    SetMat4Data(dst, 3, 3, 0.0f);
}
#pragma endregion
#pragma region Translation

#pragma region Scaling
void MatrixUtils::CreateScalingMatrix(float* dst, float x, float y, float z) noexcept{
    SetMat4Data(dst, 0,0, x);
    SetMat4Data(dst, 1,1, y);
    SetMat4Data(dst, 2,2, z);
}
#pragma endregion
//Translation

void MatrixUtils::CreateTranslationMatrix(float* dst, float x, float y, float z)noexcept{
    SetMat4Data(dst, 0, 3, x);
    SetMat4Data(dst, 1, 3, y);
    SetMat4Data(dst, 2, 3, z);
}
#pragma endregion

#pragma region Rotation
void MatrixUtils::RotateMat4x4(float* dst, float angle, Vec3<float> _axis) noexcept{
    float const a = angle;
	float const c = cos(a);
	float const s = sin(a);

	Vec3<float> axis(_axis.GetNormalized());
	Vec3<float> temp(axis* (1.0f - c));

    float rotate[16];
	SetMat4Data(rotate, 0, 0, c + temp.m_X * axis.m_X);
	SetMat4Data(rotate, 1, 0, temp.m_X * axis.m_Y + s * axis.m_Z);
	SetMat4Data(rotate, 2, 0,(temp.m_X * axis.m_Z - s * axis.m_Y));

	SetMat4Data(rotate, 0, 1, temp.m_Y * axis.m_X - s * axis.m_Z);
	SetMat4Data(rotate, 1, 1, c + temp.m_Y * axis.m_Y);
	SetMat4Data(rotate, 2, 1, temp.m_Y * axis.m_Z + s * axis.m_X);

	SetMat4Data(rotate, 0, 2, temp.m_Z * axis.m_X + s * axis.m_Y);
	SetMat4Data(rotate, 1, 2, temp.m_Z * axis.m_Y - s * axis.m_X);
	SetMat4Data(rotate, 2, 2, c + temp.m_Z * axis.m_Z);

    Vec4<float> row1 = Vec4(dst[0], dst[1], dst[2], dst[3]);
    Vec4<float> row2 = Vec4(dst[4], dst[5], dst[6], dst[7]);
    Vec4<float> row3 = Vec4(dst[8], dst[9], dst[10], dst[11]);

    Vec4<float> f1 = row1 * GetMat4Data(rotate, 0, 0) + row2 * GetMat4Data(rotate,1,0) + row3 * GetMat4Data(rotate, 2,0);
    Vec4<float> f2 = row1 * GetMat4Data(rotate, 0, 1) + row2 * GetMat4Data(rotate,1,1) + row3 * GetMat4Data(rotate, 2,1);
    Vec4<float> f3 = row1 * GetMat4Data(rotate, 0, 2) + row2 * GetMat4Data(rotate,1,2) + row3 * GetMat4Data(rotate, 2,2);

    dst[0] = f1.m_X;
    dst[1] = f1.m_Y;
    dst[2] = f1.m_Z;

    dst[4] = f2.m_X;
    dst[5] = f2.m_Y;
    dst[6] = f2.m_Z;

    dst[8] = f3.m_X;
    dst[9] = f3.m_Y;
    dst[10] = f3.m_Z;
}
void MatrixUtils::CreateRotationMatrixAxisX(float* dst, float angleInRadians)noexcept{
    SetMat4Data(dst, 1,1, cos(angleInRadians));
    SetMat4Data(dst, 1,2, -sin(angleInRadians));
    SetMat4Data(dst, 2,1, sin(angleInRadians));
    SetMat4Data(dst, 2,2, cos(angleInRadians));
}
void MatrixUtils::CreateRotationMatrixAxisY(float* dst, float angleInRadians)noexcept{
    SetMat4Data(dst, 0,0, cos(angleInRadians));
    SetMat4Data(dst, 0,2, sin(angleInRadians));
    SetMat4Data(dst, 2,0, -sin(angleInRadians));
    SetMat4Data(dst, 2,2, cos(angleInRadians));
}
void MatrixUtils::CreateRotationMatrixAxisZ(float* dst, float angleInRadians)noexcept{
    SetMat4Data(dst, 0,0, cos(angleInRadians));
    SetMat4Data(dst, 0,1, -sin(angleInRadians));
    SetMat4Data(dst, 1,0, sin(angleInRadians));
    SetMat4Data(dst, 1,1, cos(angleInRadians));
}
#pragma endregion

#pragma region Scaling
void MatrixUtils::ScaleMat4x4(float* dst, float x, float y, float z) noexcept{
    //float* b = &x;
    //for(unsigned char i = 0; i < 12; i+=4){
    //    dst[i] *= *b;
    //    dst[i + 1] *= *b;
    //    dst[i + 2] *= *b;
    //    dst[i + 3] *= *b;
    //    b+=sizeof(float);
    //}
    dst[0] *= x;
    dst[1] *= x;
    dst[2] *= x;
    dst[3] *= x;

    dst[4] *= y;
    dst[5] *= y;
    dst[6] *= y;
    dst[7] *= y;

    dst[8] *= z;
    dst[9] *= z;
    dst[10] *= z;
    dst[11] *= z;
}
#pragma endregion