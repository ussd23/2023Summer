#include "DXHeader.h"
#include "Global.h"

list<SPTR<GameObject>> Var::Objects;
list<GameObject*> Var::ColliderObjects;
map<HTREEITEM, GameObject*> Var::DebugObjectMap;
GameObject* Var::RootObject;
Transform* Var::RootTransform;
GameObject* Var::RootRectObject;
RectTransform* Var::RootRectTransform;
vector<Component*> Var::NewComponents;
list<Component*> Var::WaitComponents;

RECT Var::ScreenRect;
Frustum* Var::Frustum;
int Var::CullingObjects;
vector<Renderer*> Var::TransformRenderList;
vector<Renderer*> Var::RectTransformRenderList;