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
#include "game/view/SnakeView.h"

#include "core/system/AppCommons.h"
#include "core/graphics/Shader.h"
#include "core/mesh/Sprite.h"

SnakeView::SnakeView(Shader& shader, const Sprite& sprite)
 				: mShader(shader)
 				, mSprite(sprite)
 				, mTotalCount(0)
{
}

void SnakeView::SetTransformList(TransformList* transformList)
{
	mTransformList = transformList;
}

void SnakeView::SetTotalCount(std::size_t& totalCount)
{
	mTotalCount = totalCount;
}

void SnakeView::Draw()
{
	if(mTotalCount > 0)
	{
		mShader.Use();
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, mSprite.GetTextureId());
		
		glBindVertexArray(mSprite.GetVAO());
		for(std::size_t i = 0; i < mTotalCount; ++i)
		{
			mShader.SetUniform(AppConstants::Shader::MODEL_MATRIX, (*mTransformList)[i]);
			glDrawArrays(GL_TRIANGLES, 0, mSprite.GetVertexCount());
		}
		glBindVertexArray(0);
	}
}