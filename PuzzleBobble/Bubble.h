#pragma once
#include "Component.h"

struct IntVector2
{
	int x;
	int y;
};

class Bubble : public Component
{
protected:
	Transform*			m_Transform;
	float				m_Speed;
	Vector3				m_Mover;
	int					m_Code;
	IntVector2			m_PosInManager;
	GameObject*			m_Controll;
	GameObject*			m_BubbleManager;
	vector<Bubble*>		m_NearSameBubbles;
	bool				m_GameOver = false;
	
public:
	bool				m_isBullet = false;

public:
	Bubble(int p_Code);

	vector<Bubble*> FindBubbles(vector<Bubble*> p_Bubbles);
	void AddBubble(Bubble* p_Bubble);

	int GetCode();
	void SetPosInManager(int x, int y);
	void SetNearSameBubbles();

	void Start() override;
	void Update() override;
	void OnTriggerEnter(Collider* p_Collider) override;

	SerializeFunction(Bubble) 
	{
		Serialize(m_Code);
		Serialize(m_PosInManager);
	}
};

