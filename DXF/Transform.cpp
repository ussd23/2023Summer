#include "ComponentHeader.h"

Vector3 Transform::SetWorldPosition()
{
	if (m_Parent != nullptr)
	{
		Vector3 pscale = m_Parent->GetWorldScale();
		Vector3 pos(pscale.x * m_Position.x, pscale.y * m_Position.y, pscale.z * m_Position.z);
		Vector3 rot = m_Parent->GetWorldRotation();

		Matrix rotationMatrix;
		D3DXMatrixRotationYawPitchRoll(&rotationMatrix, D3DXToRadian(rot.y), D3DXToRadian(rot.x), D3DXToRadian(rot.z));

		Vector4 newPosition;
		D3DXVec3Transform(&newPosition, &pos, &rotationMatrix);

		pos = Vector3(newPosition.x, newPosition.y, newPosition.z);
		return pos + m_Parent->GetWorldPosition();
	}
	return m_Position;
}

Vector3 Transform::SetWorldRotation()
{
	if (m_Parent != nullptr)
	{
		return m_Rotation + m_Parent->GetWorldRotation();
	}
	return m_Rotation;
}

Vector3 Transform::SetWorldScale()
{
	if (m_Parent != nullptr)
	{
		Vector3 pscale = m_Parent->GetWorldScale();
		return Vector3(m_Scale.x * pscale.x, m_Scale.y * pscale.y, m_Scale.z * pscale.z);
	}
	return m_Scale;
}

Transform::Transform(Vector3 p_Position, Vector3 p_Rotation, Vector3 p_Scale)
{
	m_Position = p_Position;
	m_Rotation = p_Rotation;
	m_Scale = p_Scale;
	m_Parent = g_RootTransform;
}

Vector3 Transform::GetWorldPosition()
{
	return m_WorldPosition;
}

Vector3 Transform::GetWorldRotation()
{
	return m_WorldRotation;
}

Vector3 Transform::GetWorldScale()
{
	return m_WorldScale;
}

int Transform::GetChildCount()
{
	return m_Childs.size();
}

Transform* Transform::GetChild(int p_Index)
{
	return m_Childs[p_Index];
}

Transform* Transform::GetParent()
{
	return m_Parent;
}

void Transform::AddChild(Transform* p_Child)
{
	p_Child->m_Parent = this;
	m_Childs.push_back(p_Child);
}

void Transform::AddChildAsFirst(Transform* p_Child)
{
	p_Child->m_Parent = this;
	m_Childs.insert(m_Childs.begin(), p_Child);
}

void Transform::RemoveChild(Transform* p_Child)
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

void Transform::SetAsFirstSibling()
{
	m_Parent->RemoveChild(this);
	m_Parent->AddChildAsFirst(this);
}

void Transform::SetAsLastSibling()
{
	m_Parent->RemoveChild(this);
	m_Parent->AddChild(this);
}

void Transform::Update()
{
	m_WorldPosition = SetWorldPosition();
	m_WorldRotation = SetWorldRotation();
	m_WorldScale = SetWorldScale();
}