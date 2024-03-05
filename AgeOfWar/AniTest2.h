#pragma once
//ž�� �ִϸ��̼�
#include "SpriteGo.h"
#include "Animator.h"

class AniTest2 : public SpriteGo
{
public:

	struct ClipInfo //8���⿡�� direction�� ���ؼ� point�� ����� �ִϸ��̼� ���
	{
		std::string idle;
		std::string move;
		bool filpX = false;
		sf::Vector2f point;

		ClipInfo()
		{
		}

		ClipInfo(const std::string& idle, const std::string& move, bool flipX,
			const sf::Vector2f& point)
			:idle(idle), move(move), filpX(flipX), point(point)//���� 4���� �޴� ������
		{

		}
	};

protected:
	
	Animator animator;


	sf::Vector2f direction; //�̵� ����
	float speed = 500.f;

	std::vector < ClipInfo> clipInfos; //init pushback 
	ClipInfo currnetClipInfo;

public:

	AniTest2(const std::string& name = "") : SpriteGo(name) {}
	~AniTest2() override = default;

	void Init() override;
	void Reset() override;
	void Update(float dt) override;

};

