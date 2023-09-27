#include "DXHeader.h"
#include "Global.h"

list<SPTR<GameObject>> Var::Objects;
list<GameObject*> Var::ColliderObjects;
HTREEITEM Var::DebugHandle = NULL;
GameObject* Var::DebugSelected = nullptr;
Component* Var::DebugComponent = nullptr;
Json::Value Var::DebugJson;
map<HTREEITEM, GameObject*> Var::DebugObjectMap;
vector<pair<HWND, Vector2>> Var::DebugHandleStatics;
vector<pair<HWND, Vector2>> Var::DebugHandleEdits;
vector<Json::Value*> Var::DebugValue;
int Var::DebugInspectorIndex = 0;
int Var::DebugInspectorMaxIndex = 0;
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
vector<Renderer*> Var::StencilMaskRenderList; 
vector<Renderer*> Var::StenciledObjectRenderList;