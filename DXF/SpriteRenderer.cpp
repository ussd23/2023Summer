#include "ComponentHeader.h"

SpriteRenderer::SpriteRenderer(GameObject* _gameObject, string _texturename)
{
    gameObject = _gameObject;
    texturename = _texturename;
}

void SpriteRenderer::Start()
{
    recttransform = GetComponentFromObject(gameObject, RectTransform);

    if (texturename.size() <= 0) return;

    pTexture = TextureManager::GetInstance()->GetTexture(texturename);

    D3DXCreateSprite(g_pd3dDevice, &pSprite);
}

void SpriteRenderer::Render()
{
	if (recttransform == nullptr) return;
    if (pTexture == NULL) return;
    
    D3DSURFACE_DESC desc;
    pTexture->GetLevelDesc(0, &desc);

	RECT rect;
	SetRect(&rect, 0, 0, desc.Width, desc.Height);

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
    D3DXMatrixScaling(&matScreenScale, (size.x / desc.Width) * scale.x, (size.y / desc.Height) * scale.y, 0);

    D3DXMATRIXA16 matScreenSet;
    D3DXMatrixIdentity(&matScreenSet);
    matScreenSet = matScreenScale * matScreenRotationX * matScreenRotationY * matScreenRotationZ * matScreenPosition;
	pSprite->SetTransform(&matScreenSet);
	pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	pSprite->Draw(pTexture, &rect, NULL, NULL, 0xffffffff);
	pSprite->End();
}
