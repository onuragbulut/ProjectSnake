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
#include "game/model/SnakeModel.h"

#include "game/GameContext.h"
#include "game/Direction.h"

SnakeModel::SnakeModel(GameContext& gameContext)
		: SnakeModel(glm::vec2(100.0f), gameContext)
{
}

SnakeModel::SnakeModel(const glm::vec2& pieceSize, GameContext& gameContext)
			: mPieceSize(pieceSize)
			, mGameContext(gameContext)
			, mPieceCount(0)
			, mDirection(Direction::UP)
{
	mDirSpeedMappings[Direction::UP] = glm::vec2(0.0f, -1.0f);
	mDirSpeedMappings[Direction::DOWN] = glm::vec2(0.0f, 1.0f);
	mDirSpeedMappings[Direction::LEFT] = glm::vec2(-1.0f, 0.0f);
	mDirSpeedMappings[Direction::RIGHT] = glm::vec2(1.0f, 0.0f);
	
	AddNewPiece();
	AddNewPiece();
	AddNewPiece();
	AddNewPiece();
}

TransformList& SnakeModel::GetTransformList()
{
	return mTransformList;
}

std::size_t& SnakeModel::GetPieceCount()
{
	return mPieceCount;
}

const glm::vec2& SnakeModel::GetHeadPosition()
{
	return mPositionList[0];
}

const glm::vec2& SnakeModel::GetHeadPosition() const
{
	return mPositionList[0];
}

void SnakeModel::SetHeadPosition(const glm::vec2& position)
{
	mPositionList[0] = position;
}

const glm::vec2& SnakeModel::GetPieceSize()
{
	return mPieceSize;
}

const glm::vec2& SnakeModel::GetPieceSize() const
{
	return mPieceSize;
}

const Direction& SnakeModel::GetDirection()
{
	return mDirection;
}

void SnakeModel::Turn(Direction& direction)
{
	if(mDirection != direction)
	{
		mDirection = direction;
	}
}

void SnakeModel::AddNewPiece()
{
	glm::vec2 position = mPieceCount > 0 ?
						 mPositionList[mPieceCount - 1] : glm::vec2((mGameContext.GetScreenWidth() - mPieceSize.x) / 2,
						 		                                    (mGameContext.GetScreenHeight() - mPieceSize.y) / 2);
	
	position += (-mDirSpeedMappings[mDirection] * mPieceSize);
	mPositionList[mPieceCount++] = position;
	
	mGameContext.Dispatch(Event::SNAKE_EXTENDED);
}

void SnakeModel::Update()
{
	glm::vec2 prevPosition0 = mPositionList[0];
	mPositionList[0] = prevPosition0 + (mDirSpeedMappings[mDirection] * mPieceSize);
	
	mGameContext.Dispatch(Event::SNAKE_MOVED);// yeri değişecek
	
	glm::vec2 prevPosition1;
	for(std::size_t i = 1; i < mPieceCount; ++i)
	{
		if(i % 2 == 1)
		{
			prevPosition1 = mPositionList[i];
		} else
		{
			prevPosition0 = mPositionList[i];
		}
		mPositionList[i] = (i % 2 == 1) ? prevPosition0 : prevPosition1;
	}
	
	for(std::size_t i = 0 ; i < mPieceCount; ++i)
	{
		mTransformList[i] = glm::mat4();
		mTransformList[i] = glm::translate(mTransformList[i], glm::vec3(mPositionList[i], 0.0f));
		mTransformList[i] = glm::scale(mTransformList[i], glm::vec3(mPieceSize, 1.0f));
	}
	
	mGameContext.Dispatch(Event::CHECK_SNAKE_FOOD);
}
