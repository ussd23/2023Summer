#include "Functions.h"
#include "Transform.h"
#include "Global.h"

template <typename T>
T Functions::Lerp(T startValue, T endValue, float t)
{
    return startValue + t * (endValue - startValue);
}

//float Functions::Lerp(float startValue, float endValue, float t)
//{
//    return startValue + t * (endValue - startValue);
//}

bool Functions::Inner(RECT _rect, D3DXVECTOR2 _pos)
{
    if (_rect.left <= _pos.x && _rect.right >= _pos.x &&
        _rect.top <= _pos.y && _rect.bottom >= _pos.y) return true;
    else return false;
}

D3DXVECTOR2 Functions::WorldToScreen(Transform* _transform)
{
    D3DXVECTOR3 worldPosition = D3DXVECTOR3(0, 0, 0);
    D3DXMATRIXA16 matWorldSet;
    D3DXMATRIX viewMatrix;
    D3DXMATRIX projectionMatrix;
    D3DXVECTOR3 projectedPosition;
    D3DVIEWPORT9 viewport;
    g_pd3dDevice->GetViewport(&viewport);
    g_pd3dDevice->GetTransform(D3DTS_PROJECTION, &projectionMatrix);
    g_pd3dDevice->GetTransform(D3DTS_VIEW, &viewMatrix);

    D3DXVECTOR3 pos = _transform->GetWorldPosition();
    D3DXVECTOR3 rot = _transform->GetWorldRotation();
    D3DXVECTOR3 scale = _transform->GetWorldScale();

    D3DXMATRIXA16 matWorldPosition;
    D3DXMatrixTranslation(&matWorldPosition, pos.x, pos.y, pos.z);

    D3DXMATRIXA16 matWorldRotationX;
    D3DXMatrixRotationX(&matWorldRotationX, D3DXToRadian(rot.x));

    D3DXMATRIXA16 matWorldRotationY;
    D3DXMatrixRotationY(&matWorldRotationY, D3DXToRadian(rot.y));

    D3DXMATRIXA16 matWorldRotationZ;
    D3DXMatrixRotationZ(&matWorldRotationZ, D3DXToRadian(rot.z));

    D3DXMATRIXA16 matWorldScale;
    D3DXMatrixScaling(&matWorldScale, scale.x, scale.y, scale.z);

    D3DXMatrixIdentity(&matWorldSet);
    matWorldSet = matWorldScale * matWorldRotationX * matWorldRotationY * matWorldRotationZ * matWorldPosition;

    D3DXVec3Project(&projectedPosition, &worldPosition, &viewport, &projectionMatrix, &viewMatrix, &matWorldSet);

    return D3DXVECTOR2(projectedPosition.x, projectedPosition.y);
}

float Functions::GetDistance(D3DXVECTOR3 point1, D3DXVECTOR3 point2)
{
    D3DXVECTOR3 diff = point2 - point1;
    return D3DXVec3Length(&diff);
}

D3DXVECTOR3 Functions::SLerp(const D3DXVECTOR3* origin, const D3DXVECTOR3* destination, float t) {
    D3DXVECTOR3 startVec = *origin;
    D3DXVECTOR3 endVec = *destination;

    D3DXVec3Normalize(&startVec, &startVec);
    D3DXVec3Normalize(&endVec, &endVec);

    float dot = D3DXVec3Dot(&startVec, &endVec);

    if (dot == 1.0f) {
        return startVec + t * (endVec - startVec);
    }

    float theta = acosf(dot);
    float sinTheta = sinf(theta);

    float ratio1 = sinf((1.0f - t) * theta) / sinTheta;
    float ratio2 = sinf(t * theta) / sinTheta;

    D3DXVECTOR3 axis;
    D3DXVec3Cross(&axis, &startVec, &endVec);
    D3DXVec3Normalize(&axis, &axis);

    D3DXQUATERNION quat;
    quat.x = axis.x * ratio1 + endVec.x * ratio2;
    quat.y = axis.y * ratio1 + endVec.y * ratio2;
    quat.z = axis.z * ratio1 + endVec.z * ratio2;
    quat.w = startVec.x * ratio1 + startVec.y * ratio2 + startVec.z * ratio2;

    D3DXMATRIX rotMat;
    D3DXQuaternionNormalize(&quat, &quat);
    D3DXQuaternionToAxisAngle(&quat, &axis, &theta);
    D3DXQuaternionRotationMatrix(&quat, D3DXMatrixRotationAxis(&rotMat, &axis, theta));

    D3DXVECTOR3 result;
    D3DXVECTOR3 rvec(0.0f, 0.0f, 1.0f);
    D3DXVec3TransformCoord(&result, &rvec, &rotMat);

    return result;
}

D3DXVECTOR3 Functions::D3DXQuaternionToRotation(D3DXQUATERNION quat) {
    float fqw = quat.w * quat.w;
    float fqx = quat.x * quat.x;
    float fqy = quat.y * quat.y;
    float fqz = quat.z * quat.z;

    float yaw = atan2f(2.0f * (quat.x * quat.z + quat.w * quat.y), (-fqx - fqy + fqx + fqw));
    float pitch = asinf(2.0f * (quat.w * quat.x + quat.y * quat.y));
    float roll = atan2f(2.0f * (quat.x * quat.y + quat.w * quat.z), (-fqx + fqy - fqx + fqw));

    float x = D3DXToDegree(pitch);
    float y = D3DXToDegree(yaw);
    float z = D3DXToDegree(roll);

    D3DXVECTOR3 vec = D3DXVECTOR3(x, y, z);
    return vec;
}