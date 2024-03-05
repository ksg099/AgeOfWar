#pragma once
#include "SpriteGo.h"
#include "Animator.h"
class AniTest : public SpriteGo
{

protected:
	Animator animator;
	float speed = 400.f;

	float timer = 0.f;
	float duration = 0.f;
	float gravity = 500.f;
	sf::Vector2f velocity; // ���� * ���ǵ�
	
	bool isGrounded = true; //���� �پ�������
	
public:
	AniTest(const std::string& name = "");
	~AniTest() override; 

	void TestInstance();
	static void TestStaic();

	//���ε� �Լ� ���� �ϼ̴µ� �� ��⸸ �Ű����� ���� ���
	//void TestInstance(int num1, float num2);
	//static void TestStaic(int num1, float num2);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;


};

