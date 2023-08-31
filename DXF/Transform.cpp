#include "ComponentHeader.h"

void Transform::SetWorldPosition()
{
	if (m_Parent != nullptr)
	{
		Vector3 pscale = m_Parent->GetWorldScale();
		Vector3 pos(pscale.x * m_Position.x, pscale.y * m_Position.y, pscale.z * m_Position.z);
		Quaternion rot = m_Parent->GetWorldRotation();

		Matrix rotationMatrix;
		D3DXMatrixRotationQuaternion(&rotationMatrix, &rot);

		Vector4 newPosition;
		D3DXVec3Transform(&newPosition, &pos, &rotationMatrix);

		pos = Vector3(newPosition.x, newPosition.y, newPosition.z);
		m_WorldPosition = pos + m_Parent->GetWorldPosition();
	}
	else
	{
		m_WorldPosition = m_Position;
	}

	for (int i = 0; i < m_Childs.size(); ++i)
	{
		m_Childs[i]->SetWorldPosition();
	}
}

void Transform::SetWorldRotation()
{
	if (m_Parent != nullptr)
	{
		Quaternion parentRotation = m_Parent->GetWorldRotation();
		Matrix16 parentMatrix;
		D3DXMatrixRotationQuaternion(&parentMatrix, &parentRotation);

		Matrix16 rotationMatrix;
		D3DXMatrixRotationQuaternion(&rotationMatrix, &m_Rotation);

		Matrix16 combinedMatrix = parentMatrix * rotationMatrix;

		Quaternion result;
		D3DXQuaternionRotationMatrix(&result, &combinedMatrix);

		m_WorldRotation = result;
	}
	else
	{
		m_WorldRotation = m_Rotation;
	}

	for (int i = 0; i < m_Childs.size(); ++i)
	{
		m_Childs[i]->SetWorldRotation();
	}
}

void Transform::SetWorldScale()
{
	if (m_Parent != nullptr)
	{
		Vector3 pscale = m_Parent->GetWorldScale();
		m_WorldScale = Vector3(m_Scale.x * pscale.x, m_Scale.y * pscale.y, m_Scale.z * pscale.z);
	}
	else
	{
		m_WorldScale = m_Scale;
	}

	for (int i = 0; i < m_Childs.size(); ++i)
	{
		m_Childs[i]->SetWorldScale();
	}
}

Transform::Transform(Vector3 p_Position, Vector3 p_Rotation, Vector3 p_Scale)
{
	m_Position = p_Position;
	m_Rotation = Functions::EulerToQuaternion(p_Rotation);
	m_Scale = p_Scale;
	m_Parent = Var::RootTransform;
}

Vector3 Transform::GetWorldPosition()
{
	return m_WorldPosition;
}

Quaternion Transform::GetWorldRotation()
{
	return m_WorldRotation;
}

Vector3 Transform::GetWorldScale()
{
	return m_WorldScale;
}

Vector3 Transform::GetPosition()
{
	return m_Position;
}

Quaternion Transform::GetRotation()
{
	return m_Rotation;
}

Vector3 Transform::GetScale()
{
	return m_Scale;
}

void Transform::SetPosition(Vector3 p_Position)
{
	m_Position = p_Position;
	SetWorldPosition();
}

void Transform::SetRotation(Quaternion p_Rotation)
{
	m_Rotation = p_Rotation;
	SetWorldRotation();
	SetWorldPosition();
}

void Transform::SetScale(Vector3 p_Scale)
{
	m_Scale = p_Scale;
	SetWorldScale();
	SetWorldPosition();
}

int Transform::GetChildCount()
{
	return m_Childs.size();
}

vector<int> Transform::GetChildID()
{
	return m_ChildID;
}

Transform* Transform::GetChild(int p_Index)
{
	return m_Childs[p_Index];
}

Transform* Transform::GetParent()
{
	return m_Parent;
}

void Transform::SetParent(Transform* p_Parent)
{
	p_Parent->AddChild(this);
}

void Transform::AddChild(Transform* p_Child)
{
	if (p_Child->m_Parent != nullptr) p_Child->m_Parent->RemoveChild(p_Child);
	p_Child->m_Parent = this;
	m_Childs.push_back(p_Child);
	
	DXFGame::DebugUpdate();
}

void Transform::AddChildAsFirst(Transform* p_Child)
{
	if (p_Child->m_Parent != nullptr) p_Child->m_Parent->RemoveChild(p_Child);
	p_Child->m_Parent = this;
	m_Childs.insert(m_Childs.begin(), p_Child);

	DXFGame::DebugUpdate();
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

void Transform::Start()
{
	SetWorldPosition();
	SetWorldRotation();
	SetWorldScale();
}