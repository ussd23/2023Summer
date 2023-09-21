#include "ComponentHeader.h"

vector<pair< MouseFunction*, bool* >> MouseFunction::m_UniqueMouseFunctions;

MouseFunction::MouseFunction(const bool& p_isUnique)
	: m_isUnique(p_isUnique) {}

void MouseFunction::Start()
{
	m_Transform = GetComponentFromObject(gameObject, Transform);
	m_RectTransform = GetComponentFromObject(gameObject, RectTransform);
	m_BoxCollider = GetComponentFromObject(gameObject, BoxCollider);
	m_SphereCollider = GetComponentFromObject(gameObject, SphereCollider);
}

void MouseFunction::Update()
{
	m_Result = false;

	if (m_Transform != nullptr)
	{
		Vector3 pos = m_Transform->GetWorldPosition();
		Vector3 scale = m_Transform->GetWorldScale();

		if (m_BoxCollider != nullptr)
		{
			m_Result = Input::MouseRaycast.IsPicked(m_BoxCollider);
		}
		else if (m_SphereCollider != nullptr)
		{
			m_Result = Input::MouseRaycast.IsPicked(m_SphereCollider);
		}
	}

	if (m_RectTransform != nullptr)
	{
		Vector2 pos = m_RectTransform->GetScreenPosition();
		Vector2 scale = m_RectTransform->GetScreenScale();
		Vector2 size = m_RectTransform->m_Size;

		RECT rect;
		SetRect(&rect, pos.x - (size.x * scale.x * 0.5f), pos.y - (size.y * scale.y * 0.5f),
			pos.x + (size.x * scale.x * 0.5f), pos.y + (size.y * scale.y * 0.5f));

		m_Result = Functions::Inner(rect, Input::MousePosition);

		if (m_Result && m_isUnique)
		{
			m_UniqueMouseFunctions.push_back(make_pair(this, &m_Result));
		}
	}
}

void MouseFunction::LateUpdate()
{
	if (m_Result != m_isEntering)
	{
		m_isEntering = !m_isEntering;

		if (m_isEntering)
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnMouseEnter();
			}
		}
		else
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnMouseExit();
			}
		}
	}

	if (m_isEntering)
	{
		list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

		while (iter != gameObject->m_Components.end())
		{
			(*iter++)->OnMouseOver();
		}

		if ((GetInputBuffer(Mouse, MouseInput::LBUTTONDOWN)) ||
			(GetInputBuffer(Mouse, MouseInput::RBUTTONDOWN)) ||
			(GetInputBuffer(Mouse, MouseInput::MBUTTONDOWN)))
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnMouseDown();
			}
		}

		if ((GetInputBuffer(Mouse, MouseInput::LBUTTONUP)) ||
			(GetInputBuffer(Mouse, MouseInput::RBUTTONUP)) ||
			(GetInputBuffer(Mouse, MouseInput::MBUTTONUP)))
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnMouseUp();
			}
		}

		if ((GetInputBuffer(Mouse, MouseInput::LBUTTONHOLD)) ||
			(GetInputBuffer(Mouse, MouseInput::RBUTTONHOLD)) ||
			(GetInputBuffer(Mouse, MouseInput::MBUTTONHOLD)))
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnMouseHold();
			}
		}

		if ((GetInputBuffer(Mouse, MouseInput::WHEELUP)))
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnWheelUp();
			}
		}

		if ((GetInputBuffer(Mouse, MouseInput::WHEELDOWN)))
		{
			list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

			while (iter != gameObject->m_Components.end())
			{
				(*iter++)->OnWheelDown();
			}
		}
	}
}

void MouseFunction::UniqueCheck()
{
	if (m_UniqueMouseFunctions.size() == 0) return;

	bool* last = nullptr;

	for (vector<pair<MouseFunction*, bool*>>::iterator iter = m_UniqueMouseFunctions.begin(); iter != m_UniqueMouseFunctions.end(); ++iter)
	{
		last = iter->second;
		*(iter->second) = false;
	}

	if (last != nullptr) *last = true;

	m_UniqueMouseFunctions.clear();
}