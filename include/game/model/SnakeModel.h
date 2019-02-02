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
#ifndef PROJECTMATCH3_SNAKEMODEL_H
#define PROJECTMATCH3_SNAKEMODEL_H

#include "core/system/AppCommons.h"

#include <array>
#include <map>

using TransformList = std::array<glm::mat4, 10000>;
using PositionList = std::array<glm::vec2, 10000>;

class GameContext;
enum class Direction;

class SnakeModel
{
public:
	explicit SnakeModel(GameContext& gameContext);
	SnakeModel(const glm::vec2& pieceSize, GameContext& gameContext);
	
	TransformList& GetTransformList();
	std::size_t& GetPieceCount();
	const glm::vec2& GetHeadPosition();
	const glm::vec2& GetHeadPosition() const;
	void SetHeadPosition(const glm::vec2& position);
	const glm::vec2& GetPieceSize();
	const glm::vec2& GetPieceSize() const;
	const Direction& GetDirection();
	
	void Turn(Direction& direction);
	void AddNewPiece();
	void Update();
private:
	const glm::vec2 mPieceSize;
	GameContext& mGameContext;
	
	std::size_t mPieceCount;
	Direction mDirection;
	TransformList mTransformList;
	PositionList mPositionList;
	std::map<Direction, glm::vec2> mDirSpeedMappings;
};

#endif //PROJECTMATCH3_SNAKEMODEL_H
