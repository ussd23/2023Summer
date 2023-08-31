#include "ComponentHeader.h"

void RectTransform::SetScreenPosition()
{
	if (m_Parent != nullptr)
	{
		Vector2 pscale = m_Parent->GetScreenScale();
		Vector2 pos(pscale.x * m_Position.x, pscale.y * m_Position.y);
		Quaternion rot = m_Parent->GetScreenRotation();

		Matrix rotationMatrix;
		D3DXMatrixRotationQuaternion(&rotationMatrix, &rot);

		Vector4 newPosition;
		D3DXVec2Transform(&newPosition, &pos, &rotationMatrix);

		pos = Vector2(newPosition.x, newPosition.y);
		m_ScreenPosition = pos + m_Parent->GetScreenPosition();
	}
	else
	{
		m_ScreenPosition = m_Position;
	}

	for (int i = 0; i < m_Childs.size(); ++i)
	{
		m_Childs[i]->SetScreenPosition();
	}
}

void RectTransform::SetScreenRotation()
{
	if (m_Parent != nullptr)
	{
		Quaternion parentRotation = m_Parent->GetScreenRotation();
		Matrix16 parentMatrix;
		D3DXMatrixRotationQuaternion(&parentMatrix, &parentRotation);

		Matrix16 rotationMatrix;
		D3DXMatrixRotationQuaternion(&rotationMatrix, &m_Rotation);

		Matrix16 combinedMatrix = parentMatrix * rotationMatrix;

		Quaternion result;
		D3DXQuaternionRotationMatrix(&result, &combinedMatrix);

		m_ScreenRotation = result;
	}
	else
	{
		m_ScreenRotation = m_Rotation;
	}

	for (int i = 0; i < m_Childs.size(); ++i)
	{
		m_Childs[i]->SetScreenRotation();
	}
}

void RectTransform::SetScreenScale()
{
	if (m_Parent != nullptr)
	{
		Vector2 pscale = m_Parent->GetScreenScale();
		m_ScreenScale = Vector2(m_Scale.x * pscale.x, m_Scale.y * pscale.y);
	}
	else
	{
		m_ScreenScale = m_Scale;
	}

	for (int i = 0; i < m_Childs.size(); ++i)
	{
		m_Childs[i]->SetScreenScale();
	}
}

RectTransform::RectTransform(Vector2 p_Position, Vector3 p_Rotation, Vector2 p_Scale, Vector2 p_Size)
{
	m_Position = p_Position;
	m_Rotation = Functions::EulerToQuaternion(p_Rotation);
	m_Scale = p_Scale;
	m_Size = p_Size;
	m_Parent = Var::RootRectTransform;
}

Vector2 RectTransform::GetScreenPosition()
{
	return m_ScreenPosition;
}

Quaternion RectTransform::GetScreenRotation()
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

Quaternion RectTransform::GetRotation()
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
	SetScreenPosition();
}

void RectTransform::SetRotation(Quaternion p_Rotation)
{
	m_Rotation = p_Rotation;
	SetScreenRotation();
	SetScreenPosition();
}

void RectTransform::SetScale(Vector2 p_Scale)
{
	m_Scale = p_Scale;
	SetScreenScale();
	SetScreenPosition();
}

int RectTransform::GetChildCount()
{
	return m_Childs.size();
}

vector<int> RectTransform::GetChildID()
{
	return m_ChildID;
}

RectTransform* RectTransform::GetChild(int _index)
{
	return m_Childs[_index];
}

RectTransform* RectTransform::GetParent()
{
	return m_Parent;
}

void RectTransform::SetParent(RectTransform* p_Parent)
{
	p_Parent->AddChild(this);
}

void RectTransform::AddChild(RectTransform* p_Child)
{
	if (p_Child->m_Parent != nullptr) p_Child->m_Parent->RemoveChild(p_Child);
	p_Child->m_Parent = this;
	m_Childs.push_back(p_Child);

	DXFGame::DebugUpdate();
}

void RectTransform::AddChildAsFirst(RectTransform* p_Child)
{
	if (p_Child->m_Parent != nullptr) p_Child->m_Parent->RemoveChild(p_Child);
	p_Child->m_Parent = this;
	m_Childs.insert(m_Childs.begin(), p_Child);

	DXFGame::DebugUpdate();
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

void RectTransform::Start()
{
	SetScreenPosition();
	SetScreenRotation();
	SetScreenScale();
}