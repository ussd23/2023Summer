#include "ComponentHeader.h"

Checkbox::Checkbox() :
    Checkbox(Vector2(1, 1), Vector2(0, 0)) {}

Checkbox::Checkbox(Vector2 _rectsize, Vector2 _rectindex) :
    Checkbox(0xffffffff, _rectsize, _rectindex) {}

Checkbox::Checkbox(DWORD _color, Vector2 _rectsize, Vector2 _rectindex)
{
    rectsize = _rectsize;
    rectindex = _rectindex;
    color = _color;
}

void Checkbox::Start()
{
    recttransform = GetComponentFromObject(gameObject, RectTransform);

    texturename[0] = "CheckBoxOff.png";
    texturename[1] = "CheckBoxOn.png";
    textureindex = 0;

    if (texturename[textureindex].size() <= 0) return;

    pTexture = TextureManager::GetInstance()->GetTexture(texturename[textureindex]);

    if (pTexture == NULL) return;

    D3DSURFACE_DESC desc;
    pTexture->GetLevelDesc(0, &desc);
    SetRect(&texturesize, 0, 0, desc.Width, desc.Height);
}

void Checkbox::Render()
{
    if (recttransform == nullptr) return;
    if (pTexture == NULL) return;

    Vector2 temp = Vector2(texturesize.right / rectsize.x, texturesize.bottom / rectsize.y);
    RECT rect;
    SetRect(&rect, rectindex.x * temp.x, rectindex.y * temp.y, (rectindex.x + 1) * temp.x, (rectindex.y + 1) * temp.y);

    Vector2 pos = recttransform->GetScreenPosition();
    Vector3 rot = recttransform->GetScreenRotation();
    Vector2 scale = recttransform->GetScreenScale();
    Vector2 size = recttransform->size;

    Matrix matScreenPosition;
    D3DXMatrixTranslation(&matScreenPosition, pos.x - size.x / 2, pos.y - size.y / 2, 0);

    Matrix16 matScreenRotationX;
    D3DXMatrixRotationX(&matScreenRotationX, D3DXToRadian(rot.x));

    Matrix16 matScreenRotationY;
    D3DXMatrixRotationY(&matScreenRotationY, D3DXToRadian(rot.y));

    Matrix16 matScreenRotationZ;
    D3DXMatrixRotationZ(&matScreenRotationZ, D3DXToRadian(rot.z));

    Matrix matScreenScale;
    D3DXMatrixScaling(&matScreenScale, (size.x / temp.x) * scale.x, (size.y / temp.y) * scale.y, 0);

    Matrix16 matScreenSet;
    D3DXMatrixIdentity(&matScreenSet);
    matScreenSet = matScreenScale * matScreenRotationX * matScreenRotationY * matScreenRotationZ * matScreenPosition;
    g_pSprite->SetTransform(&matScreenSet);
    g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
    g_pSprite->Draw(pTexture, &rect, NULL, NULL, color);
    g_pSprite->End();
}

void Checkbox::OnMouseDown()
{
    if (textureindex == 0) textureindex = 1;
    else textureindex = 0;

    recttransform = GetComponentFromObject(gameObject, RectTransform);

    if (texturename[textureindex].size() <= 0) return;

    pTexture = TextureManager::GetInstance()->GetTexture(texturename[textureindex]);

    if (pTexture == NULL) return;

    D3DSURFACE_DESC desc;
    pTexture->GetLevelDesc(0, &desc);
    SetRect(&texturesize, 0, 0, desc.Width, desc.Height);
}
