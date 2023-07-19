#include "Functions.h"
#include "Transform.h"
#include "Global.h"

bool Functions::Inner(const RECT& p_Rect, const Vector2& p_Pos)
{
    if (p_Rect.left <= p_Pos.x && p_Rect.right >= p_Pos.x &&
        p_Rect.top <= p_Pos.y && p_Rect.bottom >= p_Pos.y) return true;
    else return false;
}

bool Functions::Inner(const RECT& p_Rect1, const RECT& p_Rect2)
{
    if (p_Rect1.left <= p_Rect2.right && p_Rect1.right >= p_Rect2.left &&
        p_Rect1.top <= p_Rect2.bottom && p_Rect1.bottom >= p_Rect2.top) return true;
    else return false;
}

Vector2 Functions::WorldToScreen(Transform* p_Transform)
{
    Vector3 worldPosition = Vector3(0, 0, 0);
    Matrix16 matWorldSet;
    Matrix viewMatrix;
    Matrix projectionMatrix;
    Vector3 projectedPosition;
    D3DVIEWPORT9 viewport;
    g_pd3dDevice->GetViewport(&viewport);
    g_pd3dDevice->GetTransform(D3DTS_PROJECTION, &projectionMatrix);
    g_pd3dDevice->GetTransform(D3DTS_VIEW, &viewMatrix);

    Vector3 pos = p_Transform->GetWorldPosition();
    Vector3 rot = p_Transform->GetWorldRotation();
    Vector3 scale = p_Transform->GetWorldScale();

    Matrix16 matWorldPosition;
    D3DXMatrixTranslation(&matWorldPosition, pos.x, pos.y, pos.z);

    Matrix16 matWorldRotationX;
    D3DXMatrixRotationX(&matWorldRotationX, D3DXToRadian(rot.x));

    Matrix16 matWorldRotationY;
    D3DXMatrixRotationY(&matWorldRotationY, D3DXToRadian(rot.y));

    Matrix16 matWorldRotationZ;
    D3DXMatrixRotationZ(&matWorldRotationZ, D3DXToRadian(rot.z));

    Matrix16 matWorldScale;
    D3DXMatrixScaling(&matWorldScale, scale.x, scale.y, scale.z);

    D3DXMatrixIdentity(&matWorldSet);
    matWorldSet = matWorldScale * matWorldRotationX * matWorldRotationY * matWorldRotationZ * matWorldPosition;

    D3DXVec3Project(&projectedPosition, &worldPosition, &viewport, &projectionMatrix, &viewMatrix, &matWorldSet);

    return Vector2(projectedPosition.x, projectedPosition.y);
}

float Functions::GetDistanceSquare(const Vector2& p_Point1, const Vector2& p_Point2)
{
    Vector2 diff = p_Point2 - p_Point1;
    return D3DXVec2LengthSq(&diff);
}

float Functions::GetDistanceSquare(const Vector3& p_Point1, const Vector3& p_Point2)
{
    Vector3 diff = p_Point2 - p_Point1;
    return D3DXVec3LengthSq(&diff);
}

float Functions::GetDistanceSquare(const Vector4& p_Point1, const Vector4& p_Point2)
{
    Vector4 diff = p_Point2 - p_Point1;
    return D3DXVec4LengthSq(&diff);
}

Vector3 Functions::SLerp(const Vector3* p_Origin, const Vector3* p_Destination, float p_LerpT)
{
    Vector3 startVec = *p_Origin;
    Vector3 endVec = *p_Destination;

    D3DXVec3Normalize(&startVec, &startVec);
    D3DXVec3Normalize(&endVec, &endVec);

    float dot = D3DXVec3Dot(&startVec, &endVec);

    if (dot == 1.0f) {
        return startVec + p_LerpT * (endVec - startVec);
    }

    float theta = acosf(dot);
    float sinTheta = sinf(theta);

    float ratio1 = sinf((1.0f - p_LerpT) * theta) / sinTheta;
    float ratio2 = sinf(p_LerpT * theta) / sinTheta;

    Vector3 axis;
    D3DXVec3Cross(&axis, &startVec, &endVec);
    D3DXVec3Normalize(&axis, &axis);

    Quaternion quat;
    quat.x = axis.x * ratio1 + endVec.x * ratio2;
    quat.y = axis.y * ratio1 + endVec.y * ratio2;
    quat.z = axis.z * ratio1 + endVec.z * ratio2;
    quat.w = startVec.x * ratio1 + startVec.y * ratio2 + startVec.z * ratio2;

    Matrix rotMat;
    D3DXQuaternionNormalize(&quat, &quat);
    D3DXQuaternionToAxisAngle(&quat, &axis, &theta);
    D3DXQuaternionRotationMatrix(&quat, D3DXMatrixRotationAxis(&rotMat, &axis, theta));

    Vector3 result;
    Vector3 rvec(0.0f, 0.0f, 1.0f);
    D3DXVec3TransformCoord(&result, &rvec, &rotMat);

    return result;
}

Vector3 Functions::D3DXQuaternionToRotation(Quaternion p_Quaternion)
{
    float fqw = p_Quaternion.w * p_Quaternion.w;
    float fqx = p_Quaternion.x * p_Quaternion.x;
    float fqy = p_Quaternion.y * p_Quaternion.y;
    float fqz = p_Quaternion.z * p_Quaternion.z;

    float yaw = atan2f(2.0f * (p_Quaternion.x * p_Quaternion.z + p_Quaternion.w * p_Quaternion.y), (-fqx - fqy + fqx + fqw));
    float pitch = asinf(2.0f * (p_Quaternion.w * p_Quaternion.x + p_Quaternion.y * p_Quaternion.y));
    float roll = atan2f(2.0f * (p_Quaternion.x * p_Quaternion.y + p_Quaternion.w * p_Quaternion.z), (-fqx + fqy - fqx + fqw));

    float x = D3DXToDegree(pitch);
    float y = D3DXToDegree(yaw);
    float z = D3DXToDegree(roll);

    Vector3 vec = Vector3(x, y, z);
    return vec;
}