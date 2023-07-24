#include "ComponentHeader.h"

Vector2 RectTransform::SetScreenPosition()
{
	if (m_Parent != nullptr)
	{
		Vector2 pscale = m_Parent->GetScreenScale();
		Vector2 pos(pscale.x * m_Position.x, pscale.y * m_Position.y);
		Vector3 rot = m_Parent->GetScreenRotation();

		Matrix rotationMatrix;
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, D3DXToRadian(rot.y), D3DXToRadian(rot.x), D3DXToRadian(rot.z));

		Vector4 newPosition;
		D3DXVec2Transform(&newPosition, &pos, &rotationMatrix);

		pos = Vector2(newPosition.x, newPosition.y);
		return pos + m_Parent->GetScreenPosition();
	}
	return m_Position;
}

Vector3 RectTransform::SetScreenRotation()
{
	if (m_Parent != nullptr)
	{
		return m_Rotation + m_Parent->GetScreenRotation();
	}
	return m_Rotation;
}

Vector2 RectTransform::SetScreenScale()
{
	if (m_Parent != nullptr)
	{
		Vector2 pscale = m_Parent->GetScreenScale();
		return Vector2(m_Scale.x * pscale.x, m_Scale.y * pscale.y);
	}
	return m_Scale;
}

RectTransform::RectTransform(Vector2 p_Position, Vector3 p_Rotation, Vector2 p_Scale, Vector2 p_Size)
{
	m_Position = p_Position;
	m_Rotation = p_Rotation;
	m_Scale = p_Scale;
	m_Size = p_Size;
	m_Parent = g_RootRectTransform;
}

Vector2 RectTransform::GetScreenPosition()
{
	return m_ScreenPosition;
}

Vector3 RectTransform::GetScreenRotation()
{
	return m_ScreenRotation;
}

Vector2 RectTransform::GetScreenScale()
{
	return m_ScreenScale;
}

Vector2 RectTransform::GetPosition()
{
	return m_Position;
}

Vector3 RectTransform::GetRotation()
{
	return m_Rotation;
}

Vector2 RectTransform::GetScale()
{
	return m_Scale;
}

void RectTransform::SetPosition(Vector2 p_Position)
{
	m_Position = p_Position;
	m_ScreenPosition = SetScreenPosition();
}

void RectTransform::SetRotation(Vector3 p_Rotation)
{
	m_Rotation = p_Rotation;
	m_ScreenRotation = SetScreenRotation();
}

void RectTransform::SetScale(Vector2 p_Scale)
{
	m_Scale = p_Scale;
	m_ScreenScale = SetScreenScale();
}

int RectTransform::GetChildCount()
{
	return m_Childs.size();
}

RectTransform* RectTransform::GetChild(int _index)
{
	return m_Childs[_index];
}

RectTransform* RectTransform::GetParent()
{
	return m_Parent;
}

void RectTransform::AddChild(RectTransform* p_Child)
{
	p_Child->m_Parent = this;
	m_Childs.push_back(p_Child);
}

void RectTransform::AddChildAsFirst(RectTransform* p_Child)
{
	p_Child->m_Parent = this;
	m_Childs.insert(m_Childs.begin(), p_Child);
}

void RectTransform::RemoveChild(RectTransform* p_Child)
{
	for (int i = 0; i < m_Childs.size(); ++i)
	{
		if (m_Childs[i] == p_Child)
		{
			p_Child->m_Parent = nullptr;
			m_Childs.erase(m_Childs.begin() + i);
			break;
		}
	}
}

void RectTransform::SetAsFirstSibling()
{
	m_Parent->RemoveChild(this);
	m_Parent->AddChildAsFirst(this);
}

void RectTransform::SetAsLastSibling()
{
	m_Parent->RemoveChild(this);
	m_Parent->AddChild(this);
}

void RectTransform::PreUpdate()
{
	m_ScreenPosition = SetScreenPosition();
	m_ScreenRotation = SetScreenRotation();
	m_ScreenScale = SetScreenScale();
}