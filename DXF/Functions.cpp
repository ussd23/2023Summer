#include "Functions.h"
#include "Transform.h"
#include "Global.h"

float Functions::Lerp(float startValue, float endValue, float t)
{
    return startValue + t * (endValue - startValue);
}

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