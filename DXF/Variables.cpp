#include "DXHeader.h"
#include "Global.h"

list<SPTR<GameObject>> Variables::Objects;
list<GameObject*> Variables::ColliderObjects;
GameObject* Variables::RootObject;
Transform* Variables::RootTransform;
GameObject* Variables::RootRectObject;
RectTransform* Variables::RootRectTransform;
vector<Component*> Variables::NewComponents;

RECT Variables::ScreenRect;
Frustum* Variables::Frustum;
int Variables::CullingObjects;
vector<Renderer*> Variables::TransformRenderList;
vector<Renderer*> Variables::RectTransformRenderList;