#include "pch.h"
#include "Animator.h"

using namespace std;

Animator::Animator() :
	owner_(),
	frame_rate_(60),
	is_play_()
{
}

Animator::Animator(const Animator& kOrigin) :
	owner_(kOrigin.owner_),
	frame_rate_(kOrigin.frame_rate_)
{
}
