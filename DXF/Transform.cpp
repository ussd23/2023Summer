#include "ComponentHeader.h"

Transform::Transform(Vector3 p_Position, Vector3 p_Rotation, Vector3 p_Scale)
{
	m_Position = p_Position;
	m_Rotation = p_Rotation;
	m_Scale = p_Scale;
	m_Parent = g_RootTransform;
}

Vector3 Transform::GetWorldPosition()
{
	if (m_Parent != nullptr)
	{
		Vector3 pscale = m_Parent->GetWorldScale();
		Vector3 pos(pscale.x * m_Position.x, pscale.y * m_Position.y, pscale.z * m_Position.z);

		return pos + m_Parent->GetWorldPosition();
	}
	return m_Position;
}

Vector3 Transform::GetWorldRotation()
{
	if (m_Parent != nullptr)
	{
		return m_Rotation + m_Parent->GetWorldRotation();
	}
	return m_Rotation;
}

Vector3 Transform::GetWorldScale()
{
	if (m_Parent != nullptr)
	{
		Vector3 pscale = m_Parent->GetWorldScale();
		return Vector3(m_Scale.x * pscale.x, m_Scale.y * pscale.y, m_Scale.z * pscale.z);
	}
	return m_Scale;
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