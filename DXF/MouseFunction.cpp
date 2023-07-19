#include "ComponentHeader.h"

void MouseFunction::Start()
{
	m_Transform = GetComponentFromObject(gameObject, Transform);
	m_RectTransform = GetComponentFromObject(gameObject, RectTransform);
	m_BoxCollider = GetComponentFromObject(gameObject, BoxCollider);
	m_SphereCollider = GetComponentFromObject(gameObject, SphereCollider);
}

void MouseFunction::Update()
{
	if (m_Transform != nullptr)
	{
		Vector3 pos = m_Transform->GetWorldPosition();
		Vector3 scale = m_Transform->GetWorldScale();

		bool result = false;

		if (m_BoxCollider != nullptr)
		{
			result = g_mouseraycast.IsPicked(m_BoxCollider);
		}
		else if (m_SphereCollider != nullptr)
		{
			result = g_mouseraycast.IsPicked(m_SphereCollider);
		}

		if (result != m_isEntering)
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
			for (int i = 0; i < gameObject->m_Components.size(); ++i)
			{
				list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

				while (iter != gameObject->m_Components.end())
				{
					(*iter++)->OnMouseOver();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONDOWN)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONDOWN)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONDOWN)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

				while (iter != gameObject->m_Components.end())
				{
					(*iter++)->OnMouseDown();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONUP)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONUP)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONUP)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

				while (iter != gameObject->m_Components.end())
				{
					(*iter++)->OnMouseUp();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONHOLD)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

				while (iter != gameObject->m_Components.end())
				{
					(*iter++)->OnMouseHold();
				}
			}
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

		bool result = Functions::Inner(rect, g_mousepos);

		if (result != m_isEntering)
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

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONDOWN)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONDOWN)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONDOWN)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

				while (iter != gameObject->m_Components.end())
				{
					(*iter++)->OnMouseDown();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONUP)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONUP)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONUP)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

				while (iter != gameObject->m_Components.end())
				{
					(*iter++)->OnMouseUp();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONHOLD)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->m_Components.begin();

				while (iter != gameObject->m_Components.end())
				{
					(*iter++)->OnMouseHold();
				}
			}
		}
	}
}