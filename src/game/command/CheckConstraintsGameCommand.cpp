/*
BSD 3-Clause License

Copyright (c) 2019, Onur A.
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

* Neither the name of the copyright holder nor the names of its
  contributors may be used to endorse or promote products derived from
  this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "game/command/CheckConstraintsGameCommand.h"
#include "game/model/SnakeModel.h"
#include "game/GameContext.h"
#include "game/Direction.h"

CheckConstraintsGameCommand::CheckConstraintsGameCommand(SnakeModel& snakeModel, const GameContext& gameContext)
	: mSnakeModel(snakeModel), mGameContext(gameContext)
{
}
void CheckConstraintsGameCommand::Execute()
{
	glm::vec2 headPos = mSnakeModel.GetHeadPosition();
	const Direction& actorDirection = mSnakeModel.GetDirection();
	
	if(headPos.y < 0 && actorDirection == Direction::UP)
	{
		headPos.y = mGameContext.GetScreenHeight();
	}
	else if(headPos.y > mGameContext.GetScreenHeight() && actorDirection == Direction::DOWN)
	{
		headPos.y = 0;
	}
	else if(headPos.x < 0 && actorDirection == Direction::LEFT)
	{
		headPos.x = mGameContext.GetScreenWidth();
	}
	else if(headPos.x > mGameContext.GetScreenWidth() && actorDirection == Direction::RIGHT)
	{
		headPos.x = 0;
	}

	mSnakeModel.SetHeadPosition(headPos);
}