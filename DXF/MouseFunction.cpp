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
				for (int i = 0; i < gameObject->components.size(); ++i)
				{
					gameObject->components[i]->OnMouseEnter();
				}
			}
			else
			{
				for (int i = 0; i < gameObject->components.size(); ++i)
				{
					gameObject->components[i]->OnMouseExit();
				}
			}
		}

		if (entering)
		{
			for (int i = 0; i < gameObject->components.size(); ++i)
			{
				gameObject->components[i]->OnMouseOver();
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONCLK)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONCLK)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONCLK)))
			{
				for (int i = 0; i < gameObject->components.size(); ++i)
				{
					gameObject->components[i]->OnMouseClick();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONHOLD)))
			{
				for (int i = 0; i < gameObject->components.size(); ++i)
				{
					gameObject->components[i]->OnMouseHold();
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
				for (int i = 0; i < gameObject->components.size(); ++i)
				{
					gameObject->components[i]->OnMouseEnter();
				}
			}
			else
			{
				for (int i = 0; i < gameObject->components.size(); ++i)
				{
					gameObject->components[i]->OnMouseExit();
				}
			}
		}

		if (entering)
		{
			for (int i = 0; i < gameObject->components.size(); ++i)
			{
				gameObject->components[i]->OnMouseOver();
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONCLK)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONCLK)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONCLK)))
			{
				for (int i = 0; i < gameObject->components.size(); ++i)
				{
					gameObject->components[i]->OnMouseClick();
				}
			}

			if ((GetInputBuffer(g_mouse, MouseInput::LBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::RBUTTONHOLD)) ||
				(GetInputBuffer(g_mouse, MouseInput::MBUTTONHOLD)))
			{
				for (int i = 0; i < gameObject->components.size(); ++i)
				{
					gameObject->components[i]->OnMouseHold();
				}
			}
		}
	}
}