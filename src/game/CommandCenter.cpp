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
#include "game/CommandCentre.h"
#include "game/command/GameCommand.h"

CommandCenter::CommandCenter()
{
	mCommandList.reserve(10000);
	mLastIndex = 0;
}

void CommandCenter::Dispatch(const Event& event)
{
	mCommandList.emplace_back(event);
}

void CommandCenter::Map(const Event& event, GameCommand* command)
{
	mCommandMappings[event] = command;
}

void CommandCenter::ProcessCommands()
{
	// performans geliştirmesi için command list yerine circular queue implement edilecek
	for(int i = mLastIndex; i < mCommandList.size(); i++)
	{
		Event event = mCommandList[i];
		if(event != Event::NONE)
		{
			if(GameCommand *gc = mCommandMappings[event])
			{
				gc->Execute();
			}
			mCommandList[i] = Event::NONE;
			mLastIndex = i;
		}
	}
}