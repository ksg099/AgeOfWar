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


//�ν��Ͻ� �Լ��� ���ڴ� �Լ��� �������� ������
void AniTest::Reset()
{
	//SpriteGo::Reset();

	animator.ClearEvent();

	std::function<void()> funcInstance = std::bind(&AniTest::TestInstance, this); //�ν��Ͻ��Լ��ϱ� �ν��Ͻ��� this�� �ѱ�
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
		isGrounded = false; //���� ������ �����ϰ� ������ ��
		animator.Play("animations/Idlejump.csv");
		velocity.y = -400.f; //���� �����Ҷ� -�� 0,0 ��ǥ ����
	}
	
	
	velocity.x = h * speed;  //�¿�
	velocity.y += gravity * dt;  //�� �Ʒ�
	position += velocity * dt;

	if (position.y > 0.f) //�ٴ� �浹��
	{
		isGrounded = true;
		position.y = 0.f;
		velocity.y = 0.f;
	}

	SetPosition(position);
	//������� �¿�� �����̱�

	if (h != 0.f)
	{
		SetFlipX(h < 0);
	}
	// ������ ���� �ٶ󺸱�

	//���̵��϶� �����̴� �ִϸ��̼�
	if (animator.GetCurrentClipId() == "animations/Idle.csv")
	{
		if (h != 0.f)
		{
			animator.Play("animations/IdleRun.csv");
		}
	}

	//�����̴� �ִϸ��̼��϶� ���̵� �ִϸ��̼�
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
	//	animator.PlayQueue("Idle"); //������ �� �����Ŀ� �ٲ�
	//	//animator.Play("Idle"); �ٷιٷ� �ٲ�
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
