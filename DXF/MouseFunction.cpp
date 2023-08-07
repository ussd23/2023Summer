#include "ComponentHeader.h"

void MouseFunction::Start()
{
	transform = GetComponentFromObject(gameObject, Transform);
	recttransform = GetComponentFromObject(gameObject, RectTransform);
	bcollider = GetComponentFromObject(gameObject, BoxCollider);
	scollider = GetComponentFromObject(gameObject, SphereCollider);
}

void MouseFunction::Update()
{
	if (transform != nullptr)
	{
		Vector3 pos = transform->GetWorldPosition();
		Vector3 scale = transform->GetWorldScale();

		bool result = false;

		if (bcollider != nullptr)
		{
			result = g_mouseraycast.IsPicked(bcollider);
		}
		else if (scollider != nullptr)
		{
			result = g_mouseraycast.IsPicked(scollider);
		}

		if (result != entering)
		{
			entering = !entering;

			if (entering)
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseEnter();
				}
			}
			else
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseExit();
				}
			}
		}

		if (entering)
		{
			for (int i = 0; i < gameObject->components.size(); ++i)
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseOver();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONDOWN)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONDOWN)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONDOWN)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseDown();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONUP)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONUP)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONUP)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseUp();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONHOLD)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseHold();
				}
			}
		}
	}

	if (recttransform != nullptr)
	{
		Vector2 pos = recttransform->GetScreenPosition();
		Vector2 scale = recttransform->GetScreenScale();
		Vector2 size = recttransform->size;

		RECT rect;
		SetRect(&rect, pos.x - (size.x * scale.x / 2), pos.y - (size.y * scale.y / 2),
			pos.x + (size.x * scale.x / 2), pos.y + (size.y * scale.y / 2));

		bool result = Functions::Inner(rect, g_mousepos);

		if (result != entering)
		{
			entering = !entering;

			if (entering)
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseEnter();
				}
			}
			else
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseExit();
				}
			}
		}

		if (entering)
		{

			list<SPTR<Component>>::iterator iter = gameObject->components.begin();

			while (iter != gameObject->components.end())
			{
				(*iter++)->OnMouseOver();
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONDOWN)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONDOWN)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONDOWN)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseDown();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONUP)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONUP)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONUP)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseUp();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONHOLD)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnMouseHold();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::WHEELUP)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnWheelUp();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::WHEELDOWN)))
			{
				list<SPTR<Component>>::iterator iter = gameObject->components.begin();

				while (iter != gameObject->components.end())
				{
					(*iter++)->OnWheelDown();
				}
			}
		}
	}
}