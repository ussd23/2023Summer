#include "ComponentHeader.h"

SpriteRenderer::SpriteRenderer(GameObject* _gameObject, string _texturename) :
    SpriteRenderer(_gameObject, _texturename, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0)) {}

SpriteRenderer::SpriteRenderer(GameObject* _gameObject, string _texturename, D3DXVECTOR2 _rectsize, D3DXVECTOR2 _rectindex) :
    SpriteRenderer(_gameObject, _texturename, 0xffffffff, _rectsize, _rectindex) {}

SpriteRenderer::SpriteRenderer(GameObject* _gameObject, string _texturename, DWORD _color, D3DXVECTOR2 _rectsize, D3DXVECTOR2 _rectindex)
{
    gameObject = _gameObject;
    texturename = _texturename;
    rectsize = _rectsize;
    rectindex = _rectindex;
    color = _color;
}

void SpriteRenderer::Start()
{
    recttransform = GetComponentFromObject(gameObject, RectTransform);

    if (texturename.size() <= 0) return;

    pTexture = TextureManager::GetInstance()->GetTexture(texturename);

    if (pTexture == NULL) return;

    D3DSURFACE_DESC desc;
    pTexture->GetLevelDesc(0, &desc);
    SetRect(&texturesize, 0, 0, desc.Width, desc.Height);
}

void SpriteRenderer::Render()
{
	if (recttransform == nullptr) return;
    if (pTexture == NULL) return;

    D3DXVECTOR2 temp = D3DXVECTOR2(texturesize.right / rectsize.x, texturesize.bottom / rectsize.y);
    RECT rect;
    SetRect(&rect, rectindex.x * temp.x, rectindex.y * temp.y, (rectindex.x + 1) * temp.x, (rectindex.y + 1) * temp.y);
    
    D3DXVECTOR2 pos = recttransform->GetScreenPosition();
    D3DXVECTOR3 rot = recttransform->GetScreenRotation();
    D3DXVECTOR2 scale = recttransform->GetScreenScale();
    D3DXVECTOR2 size = recttransform->size;

	D3DXMATRIX matScreenPosition;
	D3DXMatrixTranslation(&matScreenPosition, pos.x - size.x / 2, pos.y - size.y / 2, 0);

    D3DXMATRIXA16 matScreenRotationX;
    D3DXMatrixRotationX(&matScreenRotationX, D3DXToRadian(rot.x));

    D3DXMATRIXA16 matScreenRotationY;
    D3DXMatrixRotationY(&matScreenRotationY, D3DXToRadian(rot.y));

    D3DXMATRIXA16 matScreenRotationZ;
    D3DXMatrixRotationZ(&matScreenRotationZ, D3DXToRadian(rot.z));

    D3DXMATRIX matScreenScale;
    D3DXMatrixScaling(&matScreenScale, (size.x / temp.x) * scale.x, (size.y / temp.y) * scale.y, 0);

    D3DXMATRIXA16 matScreenSet;
    D3DXMatrixIdentity(&matScreenSet);
    matScreenSet = matScreenScale * matScreenRotationX * matScreenRotationY * matScreenRotationZ * matScreenPosition;
	g_pSprite->SetTransform(&matScreenSet);
    g_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
    g_pSprite->Draw(pTexture, &rect, NULL, NULL, color);
    g_pSprite->End();
}
