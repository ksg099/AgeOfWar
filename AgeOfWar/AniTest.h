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
	sf::Vector2f velocity; // 방향 * 스피드
	
	bool isGrounded = true; //땅에 붙어있을때
	
public:
	AniTest(const std::string& name = "");
	~AniTest() override; 

	void TestInstance();
	static void TestStaic();

	//바인드 함수 설명 하셨는데 걍 듣기만 매개변수 받을 경우
	//void TestInstance(int num1, float num2);
	//static void TestStaic(int num1, float num2);

	void Init() override;
	void Reset() override;
	void Update(float dt) override;


};

