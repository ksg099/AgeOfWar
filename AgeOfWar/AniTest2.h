#pragma once
//탑뷰 애니메이션
#include "SpriteGo.h"
#include "Animator.h"

class AniTest2 : public SpriteGo
{
public:

	struct ClipInfo //8방향에서 direction과 비교해서 point와 가까운 애니메이션 출력
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
			:idle(idle), move(move), filpX(flipX), point(point)//위의 4개를 받는 생성자
		{

		}
	};

protected:
	
	Animator animator;


	sf::Vector2f direction; //이동 방향
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

