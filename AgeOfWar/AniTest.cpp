#include "pch.h"
#include "AniTest.h"

AniTest::AniTest(const std::string& name) : SpriteGo(name)
{
}

AniTest::~AniTest()
{
}

void AniTest::TestInstance()
{
	std::cout << "TestInstance()" << std::endl;
}

void AniTest::TestStaic()
{
	std::cout << "TestStaic()" << std::endl;

}


void AniTest::Init()
{
	SpriteGo::Init();
 

	//animator.AddClip(RES_MGR_ANI_CLIP.Get("animations/Idle.csv"));
	//animator.AddClip(RES_MGR_ANI_CLIP.Get("animations/Idlejump.csv"));
	//animator.AddClip(RES_MGR_ANI_CLIP.Get("animations/IdleRun.csv"));

	animator.SetTarget(&sprite);
}


//인스턴스 함수의 인자는 함수의 포인터의 포인터
void AniTest::Reset()
{
	//SpriteGo::Reset();

	animator.ClearEvent();

	std::function<void()> funcInstance = std::bind(&AniTest::TestInstance, this); //인스턴스함수니까 인스턴스도 this로 넘김
	animator.AddEvent("animations/Idlejump.csv", 5, funcInstance);

	std::function<void()> funcInstatic = std::bind(&AniTest::TestStaic);
	animator.AddEvent("animations/Idlejump.csv", 5, funcInstatic);


	animator.Play("animations/Idle.csv");
	SetOrigin(Origins::BC);
	SetPosition({ 0.f, 0.f });
}

void AniTest::Update(float dt)
{
	SpriteGo::Update(dt);
	animator.Update(dt);

	float h = InputMgr::GetAxisRaw(Axis::Horizontal); // -1, 0 ,1
	
	if (isGrounded && InputMgr::GetKeyDown(sf::Keyboard::Space))
	{
		isGrounded = false; //땅에 없을때 점프하고 있을때 임
		animator.Play("animations/Idlejump.csv");
		velocity.y = -400.f; //위로 증가할땐 -임 0,0 좌표 생각
	}
	
	
	velocity.x = h * speed;  //좌우
	velocity.y += gravity * dt;  //위 아래
	position += velocity * dt;

	if (position.y > 0.f) //바닥 충돌시
	{
		isGrounded = true;
		position.y = 0.f;
		velocity.y = 0.f;
	}

	SetPosition(position);
	//여기까지 좌우로 움직이기

	if (h != 0.f)
	{
		SetFlipX(h < 0);
	}
	// 움직인 방향 바라보기

	//아이들일때 움직이는 애니메이션
	if (animator.GetCurrentClipId() == "animations/Idle.csv")
	{
		if (h != 0.f)
		{
			animator.Play("animations/IdleRun.csv");
		}
	}

	//움직이는 애니메이션일때 아이들 애니메이션
	if (animator.GetCurrentClipId() == "animations/IdleRun.csv")
	{
		if (h == 0.f)
		{
			animator.Play("animations/Idle.csv");
		}
	}
	else if (animator.GetCurrentClipId() == "animations/Idlejump.csv" && isGrounded == true)
	{
		if (h == 0.f)
		{
			animator.Play("animations/Idle.csv");
		}
		else
		{
			animator.Play("animations/IdleRun.csv");
		}
	}

	//sf::Vector2f pos = position + direction * speed * dt;


	//if (InputMgr::GetKeyDown(sf::Keyboard::A))
	//{

	//	animator.Play("Run");
	//	SetPosition(pos);
	//	sprite.setScale(-1, 1);
	//	if (direction < 0)
	//	{

	//	}
	//}

	//if (InputMgr::GetKeyDown(sf::Keyboard::D))
	//{
	//	animator.Play("Run");
	//	
	//	SetPosition(pos);

	//	if (direction > 0)
	//	{

	//	}
	//	sprite.setScale(1, 1);
	//}

	//if (InputMgr::GetKeyDown(sf::Keyboard::Space))
	//{
	//	animator.Play("Jump");

	//	timer += dt;
	//	if (timer > duration)
	//	{
	//		SetActive(false);
	//		return;
	//	}
	//	velocity += gravity * dt;
	//	SetPosition(position + velocity * dt);
	//}
	//if (InputMgr::GetKeyDown(sf::Keyboard::Num1))
	//{
	//	animator.PlayQueue("Idle"); //동작이 다 끝난후에 바뀜
	//	//animator.Play("Idle"); 바로바로 바뀜
	//}

	//if (InputMgr::GetKeyDown(sf::Keyboard::Num2))
	//{
	//	animator.PlayQueue("Run");
	//}

	//if (InputMgr::GetKeyDown(sf::Keyboard::Num3))
	//{
	//	animator.PlayQueue("Jump");
	//}

}
