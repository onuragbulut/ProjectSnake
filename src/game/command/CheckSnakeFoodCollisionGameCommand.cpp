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
#include "game/command/CheckSnakeFoodCollisionGameCommand.h"

#include "core/system/AppCommons.h"
#include "game/model/SnakeModel.h"
#include "game/model/FoodModel.h"
#include "game/Event.h"
#include "game/GameContext.h"

CheckSnakeFoodCollisionGameCommand::CheckSnakeFoodCollisionGameCommand(const SnakeModel& snakeModel, const FoodModel& foodModel, GameContext& gameContext)
									: mSnakeModel(snakeModel), mFoodModel(foodModel), mGameContext(gameContext)
{
}

void CheckSnakeFoodCollisionGameCommand::Execute()
{
	const glm::vec2& headPos = mSnakeModel.GetHeadPosition();
	const glm::vec2& headSize = mSnakeModel.GetPieceSize();
	const glm::vec2& foodPos = mFoodModel.GetPosition();
	const glm::vec2& foodSize = mFoodModel.GetPieceSize();
	
	const bool isFoodEaten = (headPos.x < (foodPos.x + foodSize.x) && (headPos.x + headSize.x) > foodPos.x &&
							  headPos.y < (foodPos.y + foodSize.y) && (headPos.y + headSize.y) > foodPos.y);
	
	if(isFoodEaten)
	{
		mGameContext.Dispatch(Event::FOOD_EATEN);
		mGameContext.Dispatch(Event::SNAKE_ATE_FOOD);
	}
}