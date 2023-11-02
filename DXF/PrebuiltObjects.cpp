#include "ComponentHeader.h"

EmptyObject::EmptyObject(string p_Name, Vector3 p_Position)
	: GameObject(p_Name)
{
	Transform* transform = new Transform(p_Position, Vector3(0, 0, 0), Vector3(1, 1, 1));
	AddComponent(transform);

	Var::Objects.push_back(this);
	Var::RootTransform->AddChild(transform);
}

EmptyRectObject::EmptyRectObject(string p_Name, Vector2 p_Size, Vector2 p_Position)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

CameraObject::CameraObject(string p_Name, Vector3 p_Position, Vector3 p_Destination)
	: GameObject(p_Name)
{
	Transform* transform = new Transform(p_Position, Vector3(0, 0, 0), Vector3(1, 1, 1));
	AddComponent(transform);

	Camera* camera = new Camera(p_Destination);
	AddComponent(camera);

	Var::Objects.push_back(this);
	Var::RootTransform->AddChild(transform);
}

vector<Vertex> PlaneObject::m_Vector;

PlaneObject::PlaneObject(string p_Name, Vector3 p_Position, string p_TextureName)
	: GameObject(p_Name)
{
	Transform* transform = new Transform(p_Position, Vector3(0, 0, 0), Vector3(1, 1, 1));
	AddComponent(transform);

	if (m_Vector.size() == 0)
	{
		m_Vector.push_back({ -0.5f, 0.0f, -0.5f, 0xffffffff, 0.0f, 1.0f });
		m_Vector.push_back({ -0.5f, 0.0f,  0.5f, 0xffffffff, 0.0f, 0.0f });
		m_Vector.push_back({ 0.5f, 0.0f, -0.5f, 0xffffffff, 1.0f, 1.0f });
		m_Vector.push_back({ 0.5f, 0.0f,  0.5f, 0xffffffff, 1.0f, 0.0f });
	}

	VerticeRenderer* vertice = new VerticeRenderer(p_TextureName, m_Vector, D3DPRIMITIVETYPE::D3DPT_TRIANGLESTRIP, 0, 2);
	AddComponent(vertice);

	Var::Objects.push_back(this);
	Var::RootTransform->AddChild(transform);
}

MeshObject::MeshObject(string p_Name, Vector3 p_Position, string p_ModelName)
	: GameObject(p_Name)
{
	Transform* transform = new Transform(p_Position, Vector3(0, 0, 0), Vector3(1, 1, 1));
	AddComponent(transform);

	MeshRenderer* mesh = new MeshRenderer(p_ModelName);
	AddComponent(mesh);

	Var::Objects.push_back(this);
	Var::RootTransform->AddChild(transform);
}

SpriteObject::SpriteObject(string p_Name, Vector2 p_Size, Vector2 p_Position, string p_TextureName)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	SpriteRenderer* sprite = new SpriteRenderer(p_TextureName);
	AddComponent(sprite);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

TextObject::TextObject(string p_Name, Vector2 p_Size, Vector2 p_Position, string p_FontName, int p_FontSize, string p_Text)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	TextRenderer* text = new TextRenderer(p_FontName, p_FontSize, p_Text);
	AddComponent(text);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

ButtonObject::ButtonObject(string p_Name, Vector2 p_Size, Vector2 p_Position, string p_TextureName)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	SpriteRenderer* sprite = new SpriteRenderer(p_TextureName);
	AddComponent(sprite);

	MouseFunction* mouse = new MouseFunction(true);
	AddComponent(mouse);

	Button* button = new Button();
	AddComponent(button);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

CheckBoxObject::CheckBoxObject(string p_Name, Vector2 p_Size, Vector2 p_Position)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	SpriteRenderer* sprite = new SpriteRenderer("system\\CheckBoxOff.png");
	AddComponent(sprite);

	MouseFunction* mouse = new MouseFunction(true);
	AddComponent(mouse);

	CheckBox* checkBox = new CheckBox("system\\CheckBoxOff.png", "system\\CheckBoxOn.png");
	AddComponent(checkBox);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

ContentBoxObject::ContentBoxObject(string p_Name, Vector2 p_Size, Vector2 p_Position)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	SpriteRenderer* sprite = new SpriteRenderer("system\\default.png");
	AddComponent(sprite);

	ContentBox* contentBox = new ContentBox();
	AddComponent(contentBox);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

ViewBoxObject::ViewBoxObject(string p_Name, Vector2 p_Size, Vector2 p_Position)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	SpriteRenderer* sprite = new SpriteRenderer("system\\default.png");
	AddComponent(sprite);

	MouseFunction* mouse = new MouseFunction(true);
	AddComponent(mouse);

	ViewBox* viewBox = new ViewBox();
	AddComponent(viewBox);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

ScrollObject::ScrollObject(string p_Name, Vector2 p_Size, Vector2 p_Position, bool p_IsVertical)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	SpriteRenderer* sprite = new SpriteRenderer("system\\Scroll.png");
	AddComponent(sprite);

	MouseFunction* mouse = new MouseFunction(true);
	AddComponent(mouse);

	Scroll* scroll = new Scroll(p_IsVertical);
	AddComponent(scroll);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

ScrollBarObject::ScrollBarObject(string p_Name, Vector2 p_Size, Vector2 p_Position)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	SpriteRenderer* sprite = new SpriteRenderer("system\\ScrollBar.png");
	AddComponent(sprite);

	MouseFunction* mouse = new MouseFunction(true);
	AddComponent(mouse);

	ScrollBar* scrollBar = new ScrollBar();
	AddComponent(scrollBar);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

DropDownObject::DropDownObject(string p_Name, Vector2 p_Size, Vector2 p_Position)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(p_Position, Vector3(0, 0, 0), Vector2(1, 1), p_Size);
	AddComponent(recttransform);

	SpriteRenderer* sprite = new SpriteRenderer("system\\DropDownNormal.png");
	AddComponent(sprite);

	MouseFunction* mouse = new MouseFunction(true);
	AddComponent(mouse);

	DropDown* dropdown = new DropDown();
	AddComponent(dropdown);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}

DropDownOptionObject::DropDownOptionObject(string p_Name, string p_FontName, int p_FontSize, string p_Text)
	: GameObject(p_Name)
{
	RectTransform* recttransform = new RectTransform(Vector2(0, 0), Vector3(0, 0, 0), Vector2(1, 1), Vector2(1, 1));
	AddComponent(recttransform);

	TextRenderer* text = new TextRenderer(p_FontName, p_FontSize, p_Text);
	text->m_Color = RGB(0, 0, 0);
	AddComponent(text);

	MouseFunction* mouse = new MouseFunction(true);
	AddComponent(mouse);

	DropDownOption* dropdownoption = new DropDownOption();
	AddComponent(dropdownoption);

	Var::Objects.push_back(this);
	Var::RootRectTransform->AddChild(recttransform);
}